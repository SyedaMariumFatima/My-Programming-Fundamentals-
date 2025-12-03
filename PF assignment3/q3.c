#include <stdio.h>
#include <string.h>

// Define structure for Employee
struct Employee
{
    int id;
    char name[50];
    char designation[50];
    double salary;
};

// Function to display all employees
void displayEmployees(struct Employee employees[], int n)
{
    printf("\n%s %s %s %s\n", "ID", "Name", "Designation", "Salary");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d %s %s %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
    }
}
findHighestSalary(struct Employee employees[], int n)
{
    int maxIndex = 0;
    for (int i = 1; i < n; i++)
    {
        if (employees[i].salary > employees[maxIndex].salary)
        {
            maxIndex = i;
        }
    }
    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[maxIndex].id, employees[maxIndex].name, employees[maxIndex].designation, employees[maxIndex].salary);
}

void searchEmployee(struct Employee employees[], int n, int searchByID, char searchName[], int searchID)
{
    int found = 0;
    for (int i = 0; i < n; i++)
    {
        if ((searchByID && employees[i].id == searchID) ||
            (!searchByID && strcmp(employees[i].name, searchName) == 0))
        {
            printf("\nEmployee Found:\n");
            printf("ID: %d, Name: %s, Designation: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].designation, employees[i].salary);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("\nEmployee not found.\n");
    }
}

void giveBonus(struct Employee employees[], int n, double threshold)
{
    for (int i = 0; i < n; i++)
    {
        if (employees[i].salary < threshold)
        {
            employees[i].salary *= 1.10; // Increase salary by 10%
        }
    }
}

int main()
{
    int n;
    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee employees[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details for Employee %d:\n", i + 1);
        printf("ID: ");
        scanf("%d", &employees[i].id);
        printf("Name: ");
        scanf("%s", employees[i].name);
        printf("Designation: ");
        scanf("%s", employees[i].designation);
        printf("Salary: ");
        scanf("%lf", &employees[i].salary);
    }

    displayEmployees(employees, n);

    findHighestSalary(employees, n);

    int searchID;
    printf("\nEnter Employee ID to search: ");
    scanf("%d", &searchID);
    searchEmployee(employees, n, 1, "", searchID);

    char searchName[50];
    printf("\nEnter Employee Name to search: ");
    scanf("%s", searchName);
    searchEmployee(employees, n, 0, searchName, 0);

    double threshold = 50000;
    giveBonus(employees, n, threshold);

    printf("\nAfter Bonus Update:\n");
    displayEmployees(employees, n);

    return 0;
}