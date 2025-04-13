#include "functions.h"
/*
    Лабораторная работа №5.
    ПОНЯТИЕ СТЕКА. ОПЕРАЦИИ НАД СТЕКОМ

    Задания:
    1) Создать стек для целых чисел. Максимальный размер стека вводится с экрана.
       Найти сумму элементов, идущих после минимального элемента стека.
    2) Создать два стека для целых чисел. Первый стек – ввод по возрастанию,
       второй стек – ввод по возрастанию. Без сортировок и переворачивания
       исходных стеков сформировать третий стек, упорядоченный по возрастанию.

    Фамилия студента: Масюков
    Дата написания кода: 09.04.2025
*/

int main(void)
{
    int mainChoice;
    int stackSize;

    struct Stack stack1, stack2, resultStack;
    printf("Enter the size of the stacks: ");
    scanf("%d", &stackSize);

    if (!initStack(&stack1, stackSize) || !initStack(&stack2, stackSize) || !initStack(&resultStack, stackSize * 2)) {
        printf("Stack initialization failed.\n");
        return 1;
    }

    do {
        printf("\nMAIN MENU:\n");
        printf("1. Task #1 (Sum after minimum)\n");
        printf("2. Task #2 (Create third stack ordered by merging two stacks)\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &mainChoice) != 1) {
            printf("Input error!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (mainChoice) {
        case 1: {
            int value;
            printf("Enter elements for Stack 1 (enter 'q' to stop): \n");
            while (1) {
                printf("Enter an integer: ");
                if (scanf("%d", &value) != 1) {
                    char buffer[10];
                    if (scanf("%s", buffer) == 1 && buffer[0] == 'q') {
                        break;
                    }
                    printf("Invalid input, please enter an integer or 'q' to quit.\n");
                    while (getchar() != '\n');
                    continue;
                }
                push(&stack1, value);
            }
            printf("Sum after minimum in Stack 1: %d\n", sumAfterMin(&stack1));
            break;
        }
        case 2: {
            int value;
            int prevValue = -2147483648;

            printf("Enter elements for Stack 1 (enter 'q' to stop): \n");
            while (1) {
                printf("Enter an integer: ");
                if (scanf("%d", &value) != 1) {
                    char buffer[10];
                    if (scanf("%s", buffer) == 1 && buffer[0] == 'q') {
                        break;
                    }
                    printf("Invalid input, please enter an integer or 'q' to quit.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (value <= prevValue) {
                    printf("Value must be greater than the previous one. Please enter a larger value.\n");
                    continue;
                }

                prevValue = value;
                push(&stack1, value);
            }

            prevValue = -2147483648;

            printf("Enter elements for Stack 2 (enter 'q' to stop): \n");
            while (1) {
                printf("Enter an integer: ");
                if (scanf("%d", &value) != 1) {
                    char buffer[10];
                    if (scanf("%s", buffer) == 1 && buffer[0] == 'q') {
                        break;
                    }
                    printf("Invalid input, please enter an integer or 'q' to quit.\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (value <= prevValue) {
                    printf("Value must be greater than the previous one. Please enter a larger value.\n");
                    continue;
                }

                prevValue = value;
                push(&stack2, value);
            }

            mergeStacksInOrder(&stack1, &stack2, &resultStack);

            printf("Merged and sorted third stack: ");
            displayStack(&resultStack);
            break;
        }
        case 0:
            printf("Program finished.\n");
            break;
        default:
            printf("Unknown menu option, please try again.\n");
            break;
        }
    } while (mainChoice != 0);

    free(stack1.array);
    free(stack2.array);
    free(resultStack.array);

    return 0;
}
