#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 5
#define MAX_INPUT_LINE_LENGTH 1024

typedef struct
{
    char **lines;
    int count;
    int capacity;
} TextEditor;

void initEditor(TextEditor *editor, int initialCapacity)
{
    editor->count = 0;
    editor->capacity = initialCapacity > 0 ? initialCapacity : INITIAL_CAPACITY;
    editor->lines = (char **)malloc(editor->capacity * sizeof(char *));

    if (editor->lines == NULL)
    {
        perror("FATAL ERROR: Initial lines array memory allocation failed");
        exit(EXIT_FAILURE);
    }
}

void freeAll(TextEditor *editor)
{
    if (editor->lines != NULL)
    {
        for (int i = 0; i < editor->count; i++)
        {
            free(editor->lines[i]);
        }
        free(editor->lines);
        editor->lines = NULL;
    }
    editor->count = 0;
    editor->capacity = 0;
    printf("\n--- All editor memory successfully freed. ---\n");
}

int growLinesArray(TextEditor *editor)
{
    int newCapacity = editor->capacity * 2;
    printf("-> Capacity reached. Reallocating from %d to %d.\n", editor->capacity, newCapacity);

    char **newLines = (char **)realloc(editor->lines, newCapacity * sizeof(char *));

    if (newLines == NULL)
    {
        perror("FATAL ERROR: Lines array expansion failed during realloc. Aborting.");
        return 0;
    }

    editor->lines = newLines;
    editor->capacity = newCapacity;
    return 1;
}

int insertLine(TextEditor *editor, int index, const char *text)
{
    if (index < 0 || index > editor->count)
    {
        fprintf(stderr, "ERROR: Cannot insert line. Index %d out of bounds (0 to %d).\n", index, editor->count);
        return 0;
    }

    if (editor->count == editor->capacity)
    {
        if (!growLinesArray(editor))
        {
            return 0;
        }
    }

    size_t text_len = strlen(text);
    char *newLine = (char *)malloc(text_len + 1);

    if (newLine == NULL)
    {
        perror("FATAL ERROR: Memory allocation for new line string failed. Aborting.");
        return 0;
    }

    strcpy(newLine, text);

    if (index < editor->count)
    {
        memmove(&editor->lines[index + 1], &editor->lines[index],
                (editor->count - index) * sizeof(char *));
    }

    editor->lines[index] = newLine;
    editor->count++;

    return 1;
}

int deleteLine(TextEditor *editor, int index)
{
    if (index < 0 || index >= editor->count)
    {
        fprintf(stderr, "ERROR: Cannot delete line. Index %d out of bounds (1 to %d).\n", index + 1, editor->count);
        return 0;
    }

    free(editor->lines[index]);
    editor->lines[index] = NULL;

    if (index < editor->count - 1)
    {
        memmove(&editor->lines[index], &editor->lines[index + 1],
                (editor->count - 1 - index) * sizeof(char *));
    }

    editor->count--;
    return 1;
}

void printAllLines(const TextEditor *editor)
{
    printf("\n--- Buffer Content (%d/%d lines) ---\n", editor->count, editor->capacity);
    if (editor->count == 0)
    {
        printf("[Buffer is empty]\n");
        return;
    }
    for (int i = 0; i < editor->count; i++)
    {
        printf("%03d: %s\n", i + 1, editor->lines[i]);
    }
    printf("------------------------------------\n");
}

int saveToFile(const TextEditor *editor, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("ERROR: Could not open file for saving");
        return 0;
    }

    for (int i = 0; i < editor->count; i++)
    {
        if (fprintf(file, "%s\n", editor->lines[i]) < 0)
        {
            perror("ERROR: Failed to write line to file");
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    printf("\n[SUCCESS] Buffer saved to %s (%d lines).\n", filename, editor->count);
    return 1;
}

int loadFromFile(TextEditor *editor, const char *filename)
{
    freeAll(editor);
    initEditor(editor, INITIAL_CAPACITY);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("ERROR: Could not open file for loading");
        return 0;
    }

    char buffer[MAX_INPUT_LINE_LENGTH];
    int linesLoaded = 0;

    printf("\n[LOADING] Starting to load lines from %s...\n", filename);

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
            len--;
        }

        if (len == MAX_INPUT_LINE_LENGTH - 1 && buffer[MAX_INPUT_LINE_LENGTH - 2] != '\n')
        {
            fprintf(stderr, "WARNING: Line truncated during load.\n");
        }

        if (insertLine(editor, editor->count, buffer))
        {
            linesLoaded++;
        }
        else
        {
            fprintf(stderr, "FATAL ERROR: Failed to insert line while loading. Aborting load.\n");
            fclose(file);
            return 0;
        }
    }

    if (ferror(file))
    {
        perror("ERROR: An error occurred while reading the file");
        fclose(file);
        return 0;
    }

    fclose(file);
    printf("[SUCCESS] File loaded. %d lines restored to buffer.\n", linesLoaded);
    return 1;
}

void displayHelp()
{
    printf("\n--- Editor Commands ---\n");
    printf("i <NUM> <TEXT>: Insert TEXT before the 1-based line NUM.\n");
    printf("d <NUM>: Delete the line at 1-based line NUM.\n");
    printf("p: Print all lines.\n");
    printf("s: Save the buffer to 'editor_notes.txt'.\n");
    printf("l: Load the buffer from 'editor_notes.txt' (overwrites).\n");
    printf("h: Display this help message.\n");
    printf("q: Quit.\n");
    printf("------------------------\n");
}

void runInteractiveEditor(TextEditor *editor)
{
    char inputBuffer[MAX_INPUT_LINE_LENGTH];
    char command[5];
    int index;
    int running = 1;
    const char *filename = "editor_notes.txt";

    displayHelp();

    while (running)
    {
        printf("\nEditor> ");
        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL)
        {
            running = 0;
            continue;
        }
        inputBuffer[sizeof(inputBuffer) - 1] = '\0';

        if (sscanf(inputBuffer, "%4s", command) != 1)
            continue;

        if (strcmp(command, "q") == 0)
        {
            running = 0;
            printf("Quitting editor. Goodbye!\n");
        }
        else if (strcmp(command, "p") == 0)
        {
            printAllLines(editor);
        }
        else if (strcmp(command, "i") == 0)
        {
            int offset = 0;
            int scan_count = sscanf(inputBuffer, "%4s %d%n", command, &index, &offset);

            if (scan_count == 2)
            {
                char *textStart = inputBuffer + offset;
                while (*textStart == ' ' || *textStart == '\t')
                    textStart++;

                if (*textStart != '\0' && *textStart != '\n')
                {
                    size_t len = strlen(textStart);
                    if (len > 0 && textStart[len - 1] == '\n')
                        textStart[len - 1] = '\0';

                    int zeroBasedIndex = index - 1;

                    if (zeroBasedIndex >= 0 && zeroBasedIndex <= editor->count)
                    {
                        insertLine(editor, zeroBasedIndex, textStart);
                        printf("Line inserted at position %d.\n", index);
                    }
                    else
                    {
                        fprintf(stderr, "ERROR: Invalid line number for insertion. Must be 1 to %d.\n", editor->count + 1);
                    }
                }
                else
                {
                    fprintf(stderr, "ERROR: Insert command requires text. Format: i <NUM> <TEXT>\n");
                }
            }
            else
            {
                fprintf(stderr, "ERROR: Insert command requires a line number and text. Format: i <NUM> <TEXT>\n");
            }
        }
        else if (strcmp(command, "d") == 0)
        {
            if (sscanf(inputBuffer, "d %d", &index) == 1)
            {
                if (deleteLine(editor, index - 1))
                {
                    printf("Line %d deleted.\n", index);
                }
            }
            else
            {
                fprintf(stderr, "ERROR: Delete command requires a line number. Format: d <NUM>\n");
            }
        }
        else if (strcmp(command, "s") == 0)
        {
            saveToFile(editor, filename);
        }
        else if (strcmp(command, "l") == 0)
        {
            loadFromFile(editor, filename);
        }
        else if (strcmp(command, "h") == 0)
        {
            displayHelp();
        }
        else
        {
            fprintf(stderr, "ERROR: Unknown command '%s'. Type 'h' for help.\n", command);
        }
    }
}

int main()
{
    TextEditor editor;
    initEditor(&editor, INITIAL_CAPACITY);

    printf("Minimal Line-Based Text Editor\n");
    printf("------------------------------\n");

    runInteractiveEditor(&editor);

    freeAll(&editor);

    return 0;
}
/*
 MEMORY EFFICIENCY EXPLANATION:
 -----------------------------------------------------------------------------
 This dynamic memory approach is highly efficient compared to using a large,
 fixed-size two-dimensional array (e.g., char buffer[1000][1024]).

 1. POINTER ARRAY EFFICIENCY (char** lines):
 - The outer array (`lines`) only stores pointers (`char*`), which are typically 8 bytes each.
 - It is resized with `realloc` only when the number of lines (`count`) exceeds the capacity.
 - This avoids pre-allocating large fixed blocks of memory for lines not yet used.

 2. LINE CONTENT EFFICIENCY (char* lines[i]):
 - Each line string is allocated its memory using `malloc(strlen(text) + 1)`.
 - **No Memory Wastage:** Memory is allocated only for the exact length of the text.
 - This is superior to static 2D arrays, which reserve the maximum possible length
   for every single line, resulting in significant memory waste for short lines.

 By using a dynamic array of dynamic strings (`char**`), we only allocate memory for what is
 actually needed, making the tool lightweight and efficient.
*/