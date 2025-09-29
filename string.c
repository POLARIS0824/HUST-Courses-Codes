#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 字符串复制函数
void strcopy(char *a, const char *b) {
    while ((*a++ = *b++) != '\0');
}

// 字符串连接函数
void strconcat(char *a, const char *b) {
    while (*a) a++;  // 跳过a的结尾
    while ((*a++ = *b++) != '\0');  // 拼接b到a的末尾
}

// 字符串分割函数
void strsplit(char *a, const char *delim) {
    char *token = strtok(a, delim);
    while (token) {
        printf("%s\n", token);
        token = strtok(NULL, delim);
    }
}

int main() {
    int op;
    char s1[100], s2[100];
    
    // 定义操作函数指针数组，指向不同的字符串操作函数
    void (*operation[])(char*, const char*) = {NULL, strcopy, strconcat, (void(*)(char*, const char*))strsplit};
    
    while (1) {
        scanf("%i", &op);  // 输入操作码
        if (op == 4) break;  // 如果操作码是4，退出循环
        
        getchar();  // 读取换行符
        fgets(s1, sizeof(s1), stdin);  // 获取第一个字符串
        fgets(s2, sizeof(s2), stdin);  // 获取第二个字符串
        
        // 去除换行符
        s1[strcspn(s1, "\n")] = '\0';
        s2[strcspn(s2, "\n")] = '\0';

        // 根据操作码调用对应的函数
        if (op >= 1 && op <= 3 && operation[op]) {
            operation[op](s1, s2);  // 调用函数指针数组中的函数
            printf("%s\n", s1);  // 输出操作结果
        }
    }
    return 0;
}
