#include <stdio.h>

int main()
{
    int a, b, c, d, e;
    printf("Enter the five numbers(1-13) representing each card: ");
    scanf("%i%i%i%i%i", &a, &b, &c, &d, &e);

    if(a>=1 && a<=13 && b>=1 && b<=13 && c>=1 && c<=13 && d>=1 && d<=13 && e>=1 && e<=13) 
        
    {
           // Find two distinct ranks and count their occurrences
         int frstrank = a, frstcount = 1;
         int scndrank = 0,  scndcount= 0;

         // Check b
          if (b == frstrank) frstcount++;
         else { scndrank = b;  scndcount++; }
         // Check c
         if (c == frstrank) frstcount++;
         else if (c == scndrank) scndcount++;
         else if (scndrank == 0) { scndrank = c; scndcount ++; }
        
         // Check d
         if (d == frstrank) frstcount++;
         else if (d == scndrank) scndcount++;
         else if (scndrank == 0) { scndrank = d;  scndcount++; }
        
         // Check e
         if (e == frstrank) frstcount++;
         else if (e == scndrank) scndcount++;
         else if (scndrank == 0) { scndrank = e;  scndcount++; }
         

         //check for full house
         if ((frstcount == 3 &&  scndcount== 2) || (frstcount == 2 &&  scndcount== 3)) 
         {
         printf("Full House\n");
         }
         else
         {
        printf("Not a Full House\n");
         }
    } 
    else{
        printf("Invalid input. Please enter numbers between 1 and 13.\n");
    }

    
}           