#include<stdio.h>
#include<stdlib.h>
#include <time.h>

// 函数声明
void generateFirstGrade(int num);
void generateSecondGrade(int num);
void generateThirdGrade(int num);
void generateFourthToSixthGrade(int num);
void generateExercise();
void showMenu();

//一年级题目生成器
void generateFirstGrade(int num) {
    for (int i = 0; i < num; i++) {
        int num1 = rand() % 20;
        int num2 = rand() % 20;
        char op = (rand() % 2) == 0 ? '+' : '-';

        if (op == '-' && num1 < num2) {//保证结果不是负数
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        printf("%d %c %d = \n", num1, op, num2);

    }

}

// 二年级题目生成器
void generateSecondGrade(int num) {
    for (int i = 0; i < num; i++) {
        int num1 = rand() % 50;
        int num2 = rand() % 50;
        char op = (rand() % 2) == 0 ? '+' : '-';

        if (op == '-' && num1 < num2) {//保证结果不是负数
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        printf("%d %c %d = \n", num1, op, num2);
    }
}

// 三年级题目生成器
void generateThirdGrade(int num) {
    for (int i = 0; i < num; i++) {
        int num1 = rand() % 1000;
        int num2 = rand() % 1000;
        int num3 = rand() % 1000;
        char ops[3] = { '+', '-', '*' };
        char op1, op2;
        int result;
        do {
            op1 = ops[rand() % 3];
            op2 = ops[rand() % 3];

            // 根据不同的运算符组合计算结果
            if (op1 == '+' && op2 == '+') {
                result = num1 + num2 + num3;
            }
            else if (op1 == '+' && op2 == '-') {
                result = num1 + num2 - num3;
            }
            else if (op1 == '+' && op2 == '*') {
                result = num1 + num2 * num3;
            }
            else if (op1 == '-' && op2 == '+') {
                result = num1 - num2 + num3;
            }
            else if (op1 == '-' && op2 == '-') {
                result = num1 - num2 - num3;
            }
            else if (op1 == '-' && op2 == '*') {
                result = num1 - num2 * num3;
            }
            else if (op1 == '*' && op2 == '+') {
                result = num1 * num2 + num3;
            }
            else if (op1 == '*' && op2 == '-') {
                result = num1 * num2 - num3;
            }
            else { // op1 == '*' && op2 == '*'
                result = num1 * num2 * num3;
            }

            // 如果结果为负数，重新生成数字和运算符
        } while (result < 0);
        printf("%d %c %d %c %d = \n", num1, op1, num2, op2, num3);
    }
}

// 四到六年级题目生成器
void generateFourthToSixthGrade(int num) {
    int num1, num2, num3, num4;
    char op1, op2, op3;
    int result;

    // 初始化随机数发生器
    srand(time(NULL));

    for (int i = 0; i < num; i++) {
        do {
            // 生成随机数
            num1 = rand() % 1000 + 1;
            num2 = rand() % 1000 + 1;
            num3 = rand() % 1000 + 1;
            num4 = rand() % 1000 + 1; // 避免0

            // 随机选择三个不同的运算符
            char ops[4] = { '+', '-', '*', '/' };
            int chosen[4] = { 0 }; // 标记已选择的运算符
            int count = 0;

            while (count < 3) {
                int index = rand() % 4;
                if (chosen[index] == 0) {
                    chosen[index] = 1;
                    count++;
                }
            }

            // 根据标记选择运算符
            int j = 0;
            for (int k = 0; k < 4; k++) {
                if (chosen[k]) {
                    if (j == 0) op1 = ops[k];
                    if (j == 1) op2 = ops[k];
                    if (j == 2) op3 = ops[k];
                    j++;
                }
            }

            // 计算括号内的结果
            int intermediate1 = (op1 == '+') ? (num1 + num2) : (op1 == '-') ? (num1 - num2) : (op1 == '*') ? (num1 * num2) : (num1 / num2);
            int intermediate2 = (op2 == '+') ? (num3 + num4) : (op2 == '-') ? (num3 - num4) : (op2 == '*') ? (num3 * num4) : (num3 / num4);

            // 计算最终结果
            result = (op3 == '+') ? (intermediate1 + intermediate2) : (op3 == '-') ? (intermediate1 - intermediate2) : (op3 == '*') ? (intermediate1 * intermediate2) : (intermediate1 / intermediate2);

        } while (result < 0); // 确保结果不为负数

        // 输出算式
        printf("(%d %c %d) %c (%d %c %d) = \n", num1, op1, num2, op3, num3, op2, num4);
    }
}


void generateExercise() {
    int grade, num;

    printf("请输入年级（1-6）和题目数量：");
    scanf("%d %d", &grade, &num);
    if (grade < 1 || grade>6) {
        printf("输入的年级无效，请输入1到6之间的年级。\n");
        return;
    }

    switch (grade) {
    case 1:
        generateFirstGrade(num);
        break;
    case 2:
        generateSecondGrade(num);
        break;
    case 3:
        generateThirdGrade(num);
        break;
    default:
        generateFourthToSixthGrade(num);
        break;
   }
 
}

void showMenu() {
    int choice;
    do{
        printf("\n欢迎使用四则运算练习题生成器！\n");
        printf("1. 生成练习题\n");
        printf("2. 退出程序\n");
        printf("请输入您的选择：");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            generateExercise();
            break;
        case 2:
            printf("感谢使用，再见！\n");
            break;
        default:
            printf("无效选择，请重新输入！\n");
        }
    } while (choice != 2);

}

int main()
{    showMenu();
    return 0;
}