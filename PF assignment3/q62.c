#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <error.h>

typedef struct
{
    int id;
    char name[100];
    char batch[50];      // CS, SE, Cyber Security, AI
    char membership[10]; // IEEE / ACM
    char regDate[11];    // YYYY-MM-DD
    char dob[11];        // YYYY-MM-DD
    char interest[10];   // IEEE / ACM / Both
} Student;

Student *students = NULL; // dynamic array
int count = 0, capacity = 0;

// Ensure dynamic array capacity
void ensureCapacity()
{
    if (count >= capacity)
    {
        capacity = (capacity == 0) ? 2 : capacity + 50;
        Student *temp = realloc(students, capacity * sizeof(Student));
        if (!temp)
            perror("Memory allocation failed");
        students = temp;
    }
}

// Load database from file
void loadDatabase(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
        return; // no file yet
    Student s;
    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        ensureCapacity();
        students[count++] = s;
    }
    fclose(fp);
}

// Save database to file
void saveDatabase(const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (!fp)
        perror("Cannot open file for writing");
    fwrite(students, sizeof(Student), count, fp);
    fclose(fp);
}

// Check duplicate ID
int idExists(int id)
{
    for (int i = 0; i < count; i++)
        if (students[i].id == id)
            return 1;
    return 0;
}

// Add student
void addStudent(const char *filename)
{
    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    getchar();
    if (idExists(s.id))
    {
        printf("ID already exists!\n");
        return;
    }
    printf("Enter Name: ");
    fgets(s.name, 100, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Enter Batch: ");
    fgets(s.batch, 50, stdin);
    s.batch[strcspn(s.batch, "\n")] = 0;
    printf("Enter Membership (IEEE/ACM): ");
    fgets(s.membership, 10, stdin);
    s.membership[strcspn(s.membership, "\n")] = 0;
    printf("Enter Registration Date (YYYY-MM-DD): ");
    fgets(s.regDate, 11, stdin);
    s.regDate[strcspn(s.regDate, "\n")] = 0;
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    fgets(s.dob, 11, stdin);
    s.dob[strcspn(s.dob, "\n")] = 0;
    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(s.interest, 10, stdin);
    s.interest[strcspn(s.interest, "\n")] = 0;

    ensureCapacity();
    students[count++] = s;

    FILE *fp = fopen(filename, "ab");
    if (!fp)
        perror("Cannot open file for appending");
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("Student added!\n");
}

// Update student
void updateStudent(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            printf("Updating %s...\n", students[i].name);
            printf("Enter new Batch: ");
            fgets(students[i].batch, 50, stdin);
            students[i].batch[strcspn(students[i].batch, "\n")] = 0;
            printf("Enter new Membership: ");
            fgets(students[i].membership, 10, stdin);
            students[i].membership[strcspn(students[i].membership, "\n")] = 0;
            saveDatabase("members.dat");
            printf("Updated!\n");
            return;
        }
    }
    printf("ID not found.\n");
}

// Delete student
void deleteStudent(int id)
{
    for (int i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            memmove(&students[i], &students[i + 1], (count - i - 1) * sizeof(Student));
            count--;
            saveDatabase("members.dat");
            printf("Deleted!\n");
            return;
        }
    }
    printf("ID not found.\n");
}

// View all students
void viewStudents()
{
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d | Name: %s | Batch: %s | Membership: %s | Interest: %s\n", students[i].id, students[i].name, students[i].batch, students[i].membership, students[i].interest);
    }
}

// Batch-wise report
void reportByBatch()
{
    char batch[50], interest[10];
    printf("Enter Batch: ");
    fgets(batch, 50, stdin);
    batch[strcspn(batch, "\n")] = 0;
    printf("Enter Interest (IEEE/ACM/Both): ");
    fgets(interest, 10, stdin);
    interest[strcspn(interest, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].batch, batch) == 0 && strcmp(students[i].interest, interest) == 0)
        {
            printf("ID: %d | Name: %s | Membership: %s\n", students[i].id, students[i].name, students[i].membership);
            found = 1;
        }
    }
    if (!found)
        printf("No students found for this filter.\n");
}

int main()
{
    loadDatabase("members.dat");
    int choice, id;
    do
    {
        printf("\n1. Add Student\n2. Update Student\n3. Delete Student\n4. View Students\n5. Report by Batch\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            addStudent("members.dat");
            break;
        case 2:
            printf("Enter ID to update: ");
            scanf("%d", &id);
            getchar();
            updateStudent(id);
            break;
        case 3:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            getchar();
            deleteStudent(id);
            break;
        case 4:
            viewStudents();
            break;
        case 5:
            reportByBatch();
            break;
        case 6:
            saveDatabase("members.dat");
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 6);

    free(students);
    return 0;
}
