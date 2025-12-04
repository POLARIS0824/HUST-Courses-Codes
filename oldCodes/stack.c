#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 定义栈的结构
typedef struct {
    int *data;      // 动态数组，用于存储栈中的元素
    int top;        // 栈顶指针，指示当前栈顶的位置
    int capacity;   // 栈的当前容量
} Stack;

// 初始化栈
Stack* createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("内存分配失败\n");
        return;
    }
    stack->data = (int*)malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        printf("内存分配失败\n");
        free(stack);
        return;
    }
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// 压栈
void push(Stack *stack, int value) {
    if (stack->top == stack->capacity - 1) {
        // 动态扩展栈容量
        stack->capacity *= 2;
        stack->data = (int*)realloc(stack->data, stack->capacity * sizeof(int));
        if (stack->data == NULL) {
            printf("内存重新分配失败\n");
            free(stack);
            return;
        }
    }
    stack->data[++stack->top] = value;
}

// 弹栈
int pop(Stack *stack) {
    if (stack->top == -1) {
        printf("栈下溢\n");
        return;
    }
    return stack->data[stack->top--];
}

// 判断是否为运算符
int isOperator(char *op) {
    return (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
            strcmp(op, "*") == 0 || strcmp(op, "/") == 0);
}

// 应用运算符
int applyOperator(int left, int right, char *op) {
    if (strcmp(op, "+") == 0) return left + right;
    if (strcmp(op, "-") == 0) return left - right;
    if (strcmp(op, "*") == 0) return left * right;
    if (strcmp(op, "/") == 0) {
        if (right == 0) {
            printf("不能除以零\n");
            return;
        }
        return left / right;
    }
    printf("未知运算符: %s\n", op);
    return;
}

int evaluateRPN(char *op[], int length) {
    // 使用表达式的长度作为初始容量
    Stack *stack = createStack(length);

    for (int i = 0; i < length; i++) {
        char *current_op = op[i];
        if (isOperator(current_op)) {
            // 确保栈中有足够的操作数
            if (stack->top < 1) {
                printf("运算符 %s 缺少操作数\n", current_op);
                free(stack->data);
                free(stack);
                return;
            }
            int right = pop(stack);
            int left = pop(stack);
            int result = applyOperator(left, right, current_op);
            push(stack, result);
        }
        else {
            // 验证是否为有效的整数
            char *endptr;
            int num = strtol(current_op, &endptr, 10);
            if (*endptr != '\0') {
                printf("无效的op: %s\n", current_op);
                free(stack->data);
                free(stack);
                return;
            }
            push(stack, num);
        }
    }

    // 最终结果应为栈顶唯一元素
    if (stack->top != 0) {
        printf("无效的表达式。");
        free(stack->data);
        free(stack);
        return;
    }

    int finalResult = pop(stack);
    free(stack->data);
    free(stack);
    return finalResult;
}

int main() {
    char input[10000];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("读取输入时出错\n");
        return 1;
    }

    // 分割输入为op
    char *op[1000];
    int length = 0;
    char *current_op = strtok(input, " \n");
    while (current_op != NULL && length < 1000) {
        op[length++] = current_op;
        current_op = strtok(NULL, " \n");
    }

    if (length == 0) {
        printf("未输入表达式。\n");
        return 1;
    }

    int result = evaluateRPN(op, length);
    printf("%d\n", result);

    return 0;
}
