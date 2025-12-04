#include <stdio.h>

int main()
{
    int year, month, day;
    scanf("%d%d%d", &year, &month, &day);
    int days = 0;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int daysInMonthLeap[] =
                        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        for (int i = 0; i < month - 1 ; i++)
        {
            days += daysInMonthLeap[i];
        }
        printf("%d\n", days + day);
    }
    else
    {
        for (int i = 0; i < month - 1; i++)
        {
            days += daysInMonth[i];
        }
        printf("%d\n", days + day);
    }
    return 0;
}