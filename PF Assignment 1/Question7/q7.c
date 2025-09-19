#include <stdio.h>

int main()
{
    int value;
    printf("please enter a value in the range 1-7:");
    scanf("%d", &value);
    switch(value)
    {
        case 1:
            printf("You entered Monday");
            break;
        case 2:
            printf("You entered Tuesday");
            break;
        case 3:
            printf("You entered Wednesday");
            break;
        case 4:
            printf("You entered Thursday");
            break;
        case 5:
            printf("You entered Friday");
            break;
        case 6:
            printf("You entered Saturday");
            break;
        case 7:
            printf("You entered Sunday");
            break;
    }
}