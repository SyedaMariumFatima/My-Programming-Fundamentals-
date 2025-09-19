#include <stdio.h>
#include <string.h>
int main()
{
    char country[20];
    printf("Enter the country you are in:"); 
    scanf("%s", country);
    if(strcmp(country, "pakistan")==0)
    {
        int amount;
        printf("Enter the amount of transaction:");
        scanf("%d", &amount);
        if(amount < 10000)
        {
            printf("Rs. %d Successfully transferred\n", amount);

            printf("do want to carry out another transaction? (y/n):");
            char choice;
            scanf(" %c", &choice);
            if(choice == 'y')
            {
                printf("enter the country you are in:");
                scanf("%s", country);
                if(strcmp(country, "pakistan")==0)
                {
                    printf("enter the amount of transaction:");
                    scanf("%d", &amount);
                    if(amount < 10000)
                    {
                        printf("Rs. %d Successfully transferred\n", amount);

                        printf("do want to carry out another transaction? (y/n):");
                        scanf(" %c", &choice);  
                        if(choice == 'y')
                        {
                           printf("you cannot carry out anymore transactions.\n");
                           
                        }
                        else
                        {
                            printf("Thank you for using our services");
                        }
                        printf("Thank you for using our services");
                    }
                    else
                    {
                        printf("Transaction limit exceeded");
                    }
                }
                else
                {
                    printf("Transaction limit exceeded");
                }
            }
            else
            {
                printf("Thank you for using our services");
            }
        }
        else
        {
            printf("Transaction limit exceeded");
        }
    }
    else
    {
        printf("transaction cannot take place");
    }
}