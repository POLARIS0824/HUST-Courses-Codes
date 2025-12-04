#include <stdio.h>
#include <math.h>

int main() 
{
    int n;
    scanf("%d", &n);
    int found = 0;

    for (int a = 0; a * a < n; a++) 
    {
        int y = a * a;
        for (int b = 1; b * b * 10 <= y; b++) 
        {
            int remain = y - b * b * 10;
            int c = (int)sqrt(remain);

            if (c * c == remain) 
            {
                printf("%d=%d*%d=%d*%d*10+%d*%d\n",y,a,a,b,b,c,c);
                found = 1;
                break;
            }
        }
    }
}
