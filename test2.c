#include <stdio.h>
#include <ctype.h> // 提供 isxdigit 和 tolower 函数

int hex_to_int(const char str[]) {
    int i = 0;
    int value;
    int result = 0;

    while (str[i] != '\0') { // 注意加上大括号
        char a = str[i];
        if (isxdigit(a)) { // 判断是否是合法的十六进制字符
            if (isdigit(a)) {
                value = a - '0';
            } else {
                value = tolower(a) - 'a' + 10;
            }
            result = result * 16 + value; // 累积计算
        } else {
            break; // 遇到非十六进制字符时终止
        }
        i++; // 遍历下一个字符
        printf("当前结果：%d\n", result); // 打印中间结果
    }
    return result;
}

int main() {
    char hex_str[100];
    
    printf("请输入一个十六进制数字串: ");
    scanf("%s", hex_str);

    int result = hex_to_int(hex_str);

    printf("转换结果为: %d\n", result);

    return 0;
}
