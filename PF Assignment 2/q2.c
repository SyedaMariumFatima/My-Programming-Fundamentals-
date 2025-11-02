
#include <stdio.h>
#include <string.h>

// Inventory data
int productCodes[] = {1, 2, 3, 4};
int stock[] = {50, 30, 20, 10};
float prices[] = {100, 200, 300, 500};

// Cart data
int cartCodes[10];
int cartQuantities[10];
int cartCount = 0;

// Customer data
char customerName[50];
char customerCNIC[20];

void getCustomerInfo();
void displayInventory();
void addItemToCart();
void updateInventory(int code, int quantity);
void displayTotalBill();

int main()
{
    int choice;

    do
    {
        printf("\n--- Supermarket Menu ---\n");
        printf("1. Enter Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add Item to Cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            getCustomerInfo();
            break;
        case 2:
            displayInventory();
            break;
        case 3:
            addItemToCart();
            break;
        case 4:
            displayTotalBill();
            break;
        case 5:
            printf("Exiting system. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void getCustomerInfo()
{
    printf("Enter customer name: ");
    scanf(" %[^\n]", customerName);
    printf("Enter CNIC number: ");
    scanf(" %[^\n]", customerCNIC);
}

void displayInventory()
{
    printf("\n| Product Code | Quantity in Stock | Price per Product |\n");
    for (int i = 0; i < 4; i++)
    {
        printf("| %03d          | %d     \t\t| %.2f |\n", productCodes[i], stock[i], prices[i]);
    }
}

void updateInventory(int code, int quantity)
{
    for (int i = 0; i < 4; i++)
    {
        if (productCodes[i] == code)
        {
            stock[i] -= quantity;
            break;
        }
    }
}

void addItemToCart()
{
    if (cartCount >= 10)
    {
        printf("Cart is full!\n");
        return;
    }

    int code, quantity;
    printf("Enter product code to add to cart: ");
    scanf("%d", &code);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    for (int i = 0; i < 4; i++)
    {
        if (productCodes[i] == code)
        {
            if (stock[i] >= quantity)
            {
                cartCodes[cartCount] = code;
                cartQuantities[cartCount] = quantity;
                cartCount++;
                updateInventory(code, quantity);
                printf("Item added to cart.\n");
            }
            else
            {
                printf("Not enough stock available.\n");
            }
            return;
        }
    }
    printf("Product code not found.\n");
}

void displayTotalBill()
{
    float total = 0;
    printf("\n--- Bill Summary ---\n");
    for (int i = 0; i < cartCount; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (cartCodes[i] == productCodes[j])
            {
                float itemTotal = cartQuantities[i] * prices[j];
                printf("Product %03d x %d = %.2f\n", cartCodes[i], cartQuantities[i], itemTotal);
                total += itemTotal;
            }
        }
    }

    printf("Total bill without discount: %.2f\n", total);

    char promo[20];
    printf("Enter promocode (if any): ");
    scanf(" %[^\n]", promo);

    if (strcmp(promo, "Eid2025") == 0)
    {
        float discount = total * 0.25;
        printf("Promocode applied. Discount: %.2f\n", discount);
        printf("Total bill after discount: %.2f\n", total - discount);
    }
    else
    {
        printf("No valid promocode applied.\n");
    }
}
