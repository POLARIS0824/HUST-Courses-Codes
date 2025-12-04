#include<stdio.h>
#include<cs50.h>

int calculate_a(int cents);
int calculate_b(int cents);
int calculate_c(int cents);
int calculate_d(int cents);

int main(void)
{
    //输入要找零的钱数
    int cents;
    do
    {
        cents = get_int("Changed Owned:");
    }
    while (cents < 0);

    //计算找零多少次20元
    int a = calculate_a(cents);
    cents = cents - (a * 25);

    //计算找零多少次10元
    int b = calculate_b(cents);
    cents = cents - (b * 10);

    //计算找零多少次5元
    int c = calculate_c(cents);
    cents = cents - (c * 5);

    //计算找零多少次1元
    int d = calculate_d(cents);
    cents = cents - (d * 1);

    printf("%i\n",a + b + c + d);
}

int calculate_a(int cents)   //int为什么有必要
{
    int a = 0;
    while (cents >= 25)
    {
        a++;
        cents = cents - 25;
    }
    return a;
}

int calculate_b(int cents)
{
    int b = 0;
    while (cents >= 10)
    {
        b++;
        cents = cents - 10;
    }
    return b;
}

int calculate_c(int cents)
{
    int c = 0;
    while (cents >= 5)
    {
        c++;
        cents = cents - 5;
    }
    return c;
}

int calculate_d(int cents)
{
    int d = 0;
    while (cents >= 1)
    {
        d++;
        cents = cents - 1;
    }
    return d;
}
