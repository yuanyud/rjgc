#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// 函数声明
void generateExercise(int num, char ops[], int maxNumber, int useParentheses, int useDecimal, int outputMethod);

// 主函数
int main() {
    srand(time(NULL)); // 初始化随机数生成器

    int num, maxNumber, useParentheses, useDecimal, outputMethod;
    char ops[5]; // 存储运算符

    // 用户输入
    printf("请输入题目数量：");
    scanf("%d", &num);
    printf("请输入运算符（至少两种，例如：+-*/）：");
    scanf("%s", ops);
    printf("请输入最大数（如10表示十以内）：");
    scanf("%d", &maxNumber);
    printf("是否使用括号？（1表示是，0表示否）：");
    scanf("%d", &useParentheses);
    printf("是否使用小数？（1表示是，0表示否）：");
    scanf("%d", &useDecimal);
    printf("选择输出方式（1表示文件，2表示打印机，3表示屏幕）：");
    scanf("%d", &outputMethod);

    // 生成练习题
    generateExercise(num, ops, maxNumber, useParentheses, useDecimal, outputMethod);

    return 0;
}

// 练习题生成函数
void generateExercise(int num, char ops[], int maxNumber, int useParentheses, int useDecimal, int outputMethod) {
    FILE* file;
    if (outputMethod == 1) {
        file = fopen("exercises.txt", "w");
    }

    for (int i = 0; i < num; i++) {
        int numbers[3]; // 存储数字
        char operators[2]; // 存储运算符
        for (int j = 0; j < 3; j++) {
            numbers[j] = rand() % (maxNumber + 1); // 生成数字
        }
        for (int j = 0; j < 2; j++) {
            operators[j] = ops[rand() % strlen(ops)]; // 生成运算符
        }

        // 根据用户选择决定是否使用小数
        if (useDecimal) {
            float numbers_dec[3];
            for (int j = 0; j < 3; j++) {
                numbers_dec[j] = (float)numbers[j] + (rand() % 100) / 100.0; // 生成小数
            }
            // 使用括号时，确保括号的位置是合理的
            if (useParentheses) {
                if (outputMethod == 3) printf("%0.2f %c (%0.2f %c %0.2f) = \n", numbers_dec[0], operators[0], numbers_dec[1], operators[1], numbers_dec[2]);
                else if (outputMethod == 1) fprintf(file, "%0.2f %c (%0.2f %c %0.2f) = \n", numbers_dec[0], operators[0], numbers_dec[1], operators[1], numbers_dec[2]);
            }
            else {
                if (outputMethod == 3) printf("%0.2f %c %0.2f %c %0.2f = \n", numbers_dec[0], operators[0], numbers_dec[1], operators[1], numbers_dec[2]);
                else if (outputMethod == 1) fprintf(file, "%0.2f %c %0.2f %c %0.2f = \n", numbers_dec[0], operators[0], numbers_dec[1], operators[1], numbers_dec[2]);
            }
        }
        else {
            // 使用括号时，确保括号的位置是合理的
            if (useParentheses) {
                if (outputMethod == 3) printf("%d %c (%d %c %d) = \n", numbers[0], operators[0], numbers[1], operators[1], numbers[2]);
                else if (outputMethod == 1) fprintf(file, "%d %c (%d %c %d) = \n", numbers[0], operators[0], numbers[1], operators[1], numbers[2]);
            }
            else {
                if (outputMethod == 3) printf("%d %c %d %c %d = \n", numbers[0], operators[0], numbers[1], operators[1], numbers[2]);
                else if (outputMethod == 1) fprintf(file, "%d %c %d %c %d = \n", numbers[0], operators[0], numbers[1], operators[1], numbers[2]);
            }
        }
    }

    if (outputMethod == 1) {
        fclose(file);
        printf("练习题已输出到文件。\n");
    }
    else if (outputMethod == 2) {
        FILE* (outputMethod) = fopen("/dev/printer", "w");
    }
    else {
        FILE*(outputMethod) = stdout; // 默认输出到屏幕
    }
}