#include <stdio.h>

int main()
{
    int age;
    printf("enter your age:");
    scanf("%d", &age);
    if(age>=18)
    {
        printf("enter 'p' if you have passed the eyesight test and 'f' if you have failed:");
        char eyesight;
        scanf(" %c", &eyesight);
        if(eyesight=='p')
        {
            printf("Enter 'p' if you have passed the written test and 'f' if you have failed:");
            char written;
            scanf(" %c", &written);
            if(written=='p')
            {
                printf("Enter 'p' if you have passed the driving test and 'f' if you have failed:");
                char driving;
                scanf(" %c", &driving);
                if(driving=='p')
                {
                    if(age<60)
                    {
                    printf("you are eligible to drive");
                    }
                    else
                    {
                        printf("do you have a medical fitness certificate? (y/n):");
                        char medical;
                        scanf(" %c", &medical);
                        if(medical=='y')
                        {
                            printf("you are eligible to drive");
                        }
                        else if(medical=='n')
                        {
                            printf("you need a medical fitness certificate");
                        }
                        else
                        {
                            printf("invalid input");
                        }
                    }
                }
                else if(driving=='f')
                {
                    printf("you need to retake the driving test");
                }
                else
                {
                    printf("invalid input");
                }
            
            }
            else if(written=='f')
            {
                printf("you need to retake the written test");
            }
            else
            {
                printf("invalid input");
            }
        }
        else if(eyesight=='f')
        {
            printf("you need a prescription for glasses");
        }
        else
        {
            printf("invalid input");
        }
    }
    else
    {
        printf("you are not eligible to drive");
    }
}