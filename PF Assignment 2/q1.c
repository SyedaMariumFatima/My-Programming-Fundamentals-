#include <stdio.h>

// Global arrays and counter
int isbns[100];
char titles[100][50];
float prices[100];
int quantities[100];
int count = 0;

// Function declarations
void addBook();
void processSale();
void lowStockReport();

int main()
{
    int choice;

    do
    {
        printf("\n1. Add Book\n2. Process Sale\n3. Low Stock Report\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1)
            addBook();
        else if (choice == 2)
            processSale();
        else if (choice == 3)
            lowStockReport();
        else if (choice == 4)
            printf("Goodbye.\n");
        else
            printf("Invalid.\n");

    } while (choice != 4);

    return 0;
}

// Function definitions

void addBook()
{
    if (count >= 100)
    {
        printf("Inventory full.\n");
        return;
    }

    int isbn;
    printf("ISBN: ");
    scanf("%d", &isbn);

    for (int i = 0; i < count; i++)
    {
        if (isbns[i] == isbn)
        {
            printf("Duplicate ISBN.\n");
            return;
        }
    }

    isbns[count] = isbn;
    printf("Title: ");
    scanf(" %[^\n]", titles[count]);
    printf("Price: ");
    scanf("%f", &prices[count]);
    printf("Quantity: ");
    scanf("%d", &quantities[count]);

    count++;
    printf("Book added.\n");
}

void processSale()
{
    int isbn, sold;
    printf("ISBN: ");
    scanf("%d", &isbn);
    printf("Copies sold: ");
    scanf("%d", &sold);

    for (int i = 0; i < count; i++)
    {
        if (isbns[i] == isbn)
        {
            if (quantities[i] >= sold)
            {
                quantities[i] -= sold;
                printf("Sale processed.\n");
            }
            else
            {
                printf("Insufficient stock.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void lowStockReport()
{
    printf("Low Stock (<5):\n");
    for (int i = 0; i < count; i++)
    {
        if (quantities[i] < 5)
        {
            printf("%d | %s | %.2f | %d\n", isbns[i], titles[i], prices[i], quantities[i]);
        }
    }
}