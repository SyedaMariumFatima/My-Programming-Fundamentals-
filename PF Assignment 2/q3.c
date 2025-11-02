#include <stdio.h>

int grid[4][4];

void update();
void query();
void diagnostic();
int main()
{
    int choice, leave = 0;
    printf("~~Welcome to power grid monitoring system~~\n");
    do
    {
        printf("\nEnter:\n1.to update\n2.to query\n3.to run system diagnostic\n");
        scanf("%d", &choice);
        printf("Remember that indexing of rows and columns start from 0!!!\n\n");
        switch (choice)
        {
        case 1:
            update();
            break;
        case 2:
            query();
            break;
        case 3:
            diagnostic();
            break;
        default:
            printf("Invalid input. Try harder. Womp Womp!!");
            break;
        }
        printf("enter 0 to stay or 1 to exit: ");
        scanf("%d", &leave);
    } while (leave != 1);
}
void update()
{
    int row, col, status;
    printf("Enter Row number: ");
    scanf("%d", &row);
    printf("Enter col number: ");
    scanf("%d", &col);
    printf("Enter Status: ");
    scanf("%d", &status);
    grid[row][col] = status;
}
void query()
{
    int row, col;
    printf("Enter row: ");
    scanf("%d", &row);
    printf("Enter col: ");
    scanf("%d", &col);
    if ((grid[row][col] & 1) == 1)
    {
        printf("ON\n");
    }
    else
        printf("OFF\n");
    if ((grid[row][col] & 2) == 2)
    {
        printf("Overloaded\n");
    }
    else
        printf("Normal\n");
    printf("Maintenance required? ");
    if ((grid[row][col] & 4) == 4)
    {
        printf("Yes\n");
    }
    else
        printf("No\n");
}
void diagnostic()
{
    int overload = 0, req_main = 0;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if ((grid[j][i] & 2) == 2)
                overload++;
            if ((grid[j][i] & 4) == 4)
                req_main++;
        }
    }
    printf("Number of sectors that are overloaded: %d\n", overload);
    printf("Number of sectors that require maintainence: %d\n", req_main);
}