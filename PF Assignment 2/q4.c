
#include <stdio.h>

int top = -1;
int stack[100];
int maxSize;

void push(int stack[], int maxSize);
void pop(int stack[]);
void peek(int stack[]);
void display(int stack[]);

int main()
{
    int choice;

    printf("Enter maximum size of the stack: ");
    scanf("%d", &maxSize);

    do
    {
        printf("\n--- Stack Menu ---\n");
        printf("1. PUSH\n");
        printf("2. POP\n");
        printf("3. PEEK\n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            push(stack, maxSize);
            break;
        case 2:
            pop(stack);
            break;
        case 3:
            peek(stack);
            break;
        case 4:
            display(stack);
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void push(int stack[], int maxSize)
{
    if (top >= maxSize - 1)
    {
        printf("Stack Overflow! Cannot push more elements.\n");
    }
    else
    {
        int value;
        printf("Enter value to push: ");
        scanf("%d", &value);
        top++;
        stack[top] = value;
        printf("%d pushed to stack.\n", value);
    }
}

void pop(int stack[])
{
    if (top == -1)
    {
        printf("Stack Underflow! No elements to pop.\n");
    }
    else
    {
        printf("%d popped from stack.\n", stack[top]);
        top--;
    }
}

void peek(int stack[])
{
    if (top == -1)
    {
        printf("Stack is empty. No top element.\n");
    }
    else
    {
        printf("Top element: %d\n", stack[top]);
    }
}

void display(int stack[])
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
    }
    else
    {
        printf("Stack elements:\n");
        for (int i = top; i >= 0; i--)
        {
            printf("%d\n", stack[i]);
        }
    }
}
