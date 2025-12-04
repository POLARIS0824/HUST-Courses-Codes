#include<cs50.h>
#include<stdio.h>

int main(void)
{
    long cc_number = get_long("credit card number: ");
    int size = 0;
    int checksum = 0;
    int first_digit;
    int second_digit;
    int remain_digits = cc_number;
    //计算卡号的长度
    while (remain_digits > 0)
    {
        //取留下的数字中的最后一位
        int digit = remain_digits % 10;
        //依次去掉最后一位
        remain_digits = remain_digits / 10;
        if (size > 0)
        {
            //依次将后一位赋值给前一位，找出卡号前两位
            second_digit = first_digit;
        }
        //找出最开始的第一位
        first_digit = digit;
        //开始检查，先寻找偶数位
        if (size % 2 == 0)
        {
            checksum = checksum + digit;
        }
        //对于奇数位，乘以2，拆开并加和
        else
        {
            //%是取模，是个位，/是（整）除，是十位
            checksum += digit * 2 % 10 + digit * 2 / 10;
        }
        size++;
    }

    if (checksum % 10 != 0)
    {
        printf("无效卡号\n");
    }
    //卡号15位，且开头为34或37，则该卡为美国运通AMEX
    if (size == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
    {
        printf("AMEX\n");
    }
    //卡号16位，且开头为51至54，则该卡为美国万事达
    if (size == 16 && first_digit == 5 &&(second_digit >= 1 && second_digit <= 5))
    {
        printf("MasterCard\n");
    }
    //卡号13或16位，且开头为4，则该卡为美国visa
    if ((size == 13 || size == 16) && first_digit == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("无效卡号\n");
    }
}

