#include <stdio.h>

int main()
{
    int num;
    int numof0s=0, numof1s=0, numof2s=0, numof3s=0, numof4s=0, numof5s=0, numof6s=0, numof7s=0, numof8s=0, numof9s = 0;
    printf("Enter a number between 1 and 9: ");
    scanf("%d", &num);
    while(num >= 0 && num < 10)
    {
        switch(num)
        {
            case 0:
                numof0s++;
                break;
            case 1:
                numof1s++;
                break;
            case 2:
                numof2s++;
                break;
            case 3:
                numof3s++;
                break;
            case 4:
                numof4s++;
                break;
            case 5:
                numof5s++;
                break;
            case 6:
                numof6s++;
                break;
            case 7:
                numof7s++;
                break;
            case 8:
                numof8s++;
                break;
            case 9:
                numof9s++;
                break;
        }
     printf("Enter a number between 1 and 9: ");
     scanf("%d", &num);

    }
    printf("number \t\t\t\t number of occurences\n");
    printf("  0 \t\t\t\t\t %d\n", numof0s);
    printf("  1 \t\t\t\t\t %d\n", numof1s);
    printf("  2 \t\t\t\t\t %d\n", numof2s);
    printf("  3 \t\t\t\t\t %d\n", numof3s);
    printf("  4 \t\t\t\t\t %d\n", numof4s);
    printf("  5 \t\t\t\t\t %d\n", numof5s);
    printf("  6 \t\t\t\t\t %d\n", numof6s);
    printf("  7 \t\t\t\t\t %d\n", numof7s);
    printf("  8 \t\t\t\t\t %d\n", numof8s);
    printf("  9 \t\t\t\t\t %d\n", numof9s);
}