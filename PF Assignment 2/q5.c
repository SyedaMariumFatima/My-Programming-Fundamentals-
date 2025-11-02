
#include <stdio.h>
#include <string.h>
void encode(char msg[]);
void decode(char msg[]);

int main()
{
    char message[256];
    int choice;

    do
    {
        printf("\n--- TCS Secure Messenger ---\n");
        printf("1. Encode Message\n");
        printf("2. Decode Message\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from input buffer

        if (choice == 1 || choice == 2)
        {
            printf("Enter message: ");
            fgets(message, sizeof(message), stdin);

            // Remove newline manually
            int i = 0;
            while (message[i] != '\0')
            {
                if (message[i] == '\n')
                {
                    message[i] = '\0';
                    break;
                }
                i++;
            }

            if (choice == 1)
            {
                encode(message);
                printf("Encoded: %s\n", message);
            }
            else
            {
                decode(message);
                printf("Decoded: %s\n", message);
            }
        }
        else if (choice == 3)
        {
            printf("Exiting system. Stay secure!\n");
        }
        else
        {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}

// Encode: reverse string + toggle 2nd and 5th bits
void encode(char msg[])
{
    int len = strlen(msg);

    // Reverse the string
    for (int i = 0; i < len / 2; i++)
    {
        char temp = msg[i];
        msg[i] = msg[len - 1 - i];
        msg[len - 1 - i] = temp;
    }

    // Toggle 2nd and 5th bits
    for (int i = 0; i < len; i++)
    {
        msg[i] ^= 2;  // Toggle bit 1
        msg[i] ^= 16; // Toggle bit 4
    }
}

// Decode: untoggle bits + reverse string
void decode(char msg[])
{
    int len = strlen(msg);

    // Untoggle 2nd and 5th bits
    for (int i = 0; i < len; i++)
    {
        msg[i] ^= 2;  // Untoggle bit 1
        msg[i] ^= 16; // Untoggle bit 4
    }

    // Reverse the string
    for (int i = 0; i < len / 2; i++)
    {
        char temp = msg[i];
        msg[i] = msg[len - 1 - i];
        msg[len - 1 - i] = temp;
    }
}
