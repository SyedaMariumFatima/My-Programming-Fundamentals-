#include <stdio.h>

int main()
{
    int x, y;
    printf("enter x:");
    scanf("%d", &x);
    printf("enter y:");
    scanf("%d", &y);
    if(x>0 && y>0)
    {
        printf("point is in first quadrant");
    }
    else if(x<0 && y>0)
    {
        printf("point is in second quadrant");
    }
    else if(x<0 && y<0)
    {
        printf("point is in third quadrant");
    }
    else if(x>0 && y<0)
    {
        printf("point is in fourth quadrant");
    }
    else if(x==0 && y!=0)
    {
        printf("point is on y axis");
    }
    else if(y==0 && x!=0)
    {
        printf("point is on x axis");
    }
    else
    {
        printf("point is at origin");
    }
}   