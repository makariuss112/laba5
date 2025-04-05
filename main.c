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
    Дата написания кода: 31.03.2025

    Дополнительно:
    - Названия переменных и функций отражают их назначение.
    - Перед любым запросом на ввод выводится сообщение с описанием требуемых данных.
    - Реализованы проверки корректности ввода.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/* ------------------------------------------------------
 * Структура для работы со стеком на массиве
 * ------------------------------------------------------ */
typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

/* ------------------------------------------------------
 * Функции работы со стеком
 * ------------------------------------------------------ */

// Инициализация стека
bool initStack(Stack *st, int capacity)
{
    if (!st || capacity <= 0)
    {
        return false;
    }
    st->data = (int *)malloc(capacity * sizeof(int));
    if (!st->data)
    {
        return false;
    }
    st->top = -1;
    st->capacity = capacity;
    return true;
}

bool isEmpty(const Stack *st)
{
    return (st->top < 0);
}

bool isFull(const Stack *st)
{
    return (st->top >= st->capacity - 1);
}

bool push(Stack *st, int value)
{
    if (isFull(st))
    {
        return false;
    }
    st->top++;
    st->data[st->top] = value;
    return true;
}

bool pop(Stack *st, int *pValue)
{
    if (isEmpty(st))
    {
        return false;
    }
    if (pValue)
    {
        *pValue = st->data[st->top];
    }
    st->top--;
    return true;
}

// Посмотреть верхний элемент (без извлечения)
bool peek(const Stack *st, int *pValue)
{
    if (isEmpty(st))
    {
        return false;
    }
    if (pValue)
    {
        *pValue = st->data[st->top];
    }
    return true;
}

void freeStack(Stack *st)
{
    if (!st)
        return;
    if (st->data)
    {
        free(st->data);
        st->data = NULL;
    }
    st->top = -1;
    st->capacity = 0;
}

/* ------------------------------------------------------
 * Задача 1:
 * 1) Создать стек целых чисел, размер задаётся с клавиатуры.
 * 2) Найти сумму элементов, идущих после минимального
 *    элемента стека (если таких нет — сумма 0).
 * ------------------------------------------------------ */
void task1(void)
{
    int maxSize;
    printf("\n--- ЗАДАНИЕ 1 ---\n");
    printf("Введите максимальный размер стека (целое число > 0): ");
    if (scanf("%d", &maxSize) != 1 || maxSize <= 0)
    {
        fprintf(stderr, "Некорректный ввод размера стека!\n");
        while (getchar() != '\n');
        return;
    }

    Stack st;
    if (!initStack(&st, maxSize))
    {
        fprintf(stderr, "Ошибка инициализации стека!\n");
        return;
    }

    int count;
    printf("Сколько целых чисел вы хотите поместить в стек? ");
    if (scanf("%d", &count) != 1 || count < 0)
    {
        fprintf(stderr, "Некорректный ввод!\n");
        freeStack(&st);
        while (getchar() != '\n')
            ;
        return;
    }
    while (getchar() != '\n');

    if (count > maxSize)
    {
        printf("Превышено максимальное число элементов! Будет добавлено только %d.\n", maxSize);
        count = maxSize;
    }

    for (int i = 0; i < count; i++)
    {
        int val;
        printf("Введите целое число #%d: ", i + 1);
        while (scanf("%d", &val) != 1)
        {
            fprintf(stderr, "Некорректный ввод! Повторите: ");
            while (getchar() != '\n')
                ;
        }
        while (getchar() != '\n')
            ;
        push(&st, val);
    }

    if (isEmpty(&st))
    {
        printf("Стек пуст! Сумма = 0.\n");
        freeStack(&st);
        return;
    }

    int minValue = INT_MAX;
    int minIndex = -1;

    for (int i = st.top; i >= 0; i--)
    {
        if (st.data[i] < minValue)
        {
            minValue = st.data[i];
            minIndex = i;
        }
    }

    int sumAfterMin = 0;
    for (int i = st.top; i > minIndex; i--)
    {
        sumAfterMin += st.data[i];
    }

    printf("Минимальный элемент стека: %d\n", minValue);
    printf("Сумма элементов, идущих после минимального: %d\n", sumAfterMin);

    freeStack(&st);
}

/* ------------------------------------------------------
 * Задача 2:
 * 1) Создать два стека для целых чисел. Каждый стек
 *    заполняется по возрастанию (то есть при вводе
 *    гарантировать, что каждое следующее число не меньше предыдущего).
 * 2) Без сортировок и переворота исходных стеков сформировать
 *    третий стек, упорядоченный по возрастанию.
 *
 * Идея реализации:
 *  - В каждом стеке вершина — это последний добавленный (т.е. максимальный).
 *  - При слиянии, сравниваем вершины: меньшую вершину нужно
 *    класть в третий стек, однако при обычном push в стек
 *    новый элемент окажется сверху, что даст обратный порядок.
 *  - Поэтому после слияния получим третий стек в обратном порядке.
 *  - "Переворачивать" исходные стеки запрещено, но можно
 *    перевернуть (или перекинуть) итоговый стек, т.к. условие
 *    не ограничивает операции над новым стеком.
 * ------------------------------------------------------ */

bool fillStackAscending(Stack *st, int n)
{
    if (!st || n < 0)
    {
        return false;
    }
    int prevValue = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        int val;
        printf("Введите целое число #%d (>= %d): ", i + 1, prevValue);
        while (scanf("%d", &val) != 1)
        {
            fprintf(stderr, "Некорректный ввод! Повторите: ");
            while (getchar() != '\n')
                ;
        }
        while (getchar() != '\n')
            ;
        if (val < prevValue)
        {
            printf("Ошибка: число должно быть не меньше предыдущего!\n");
            i--;
            continue;
        }
        if (!push(st, val))
        {
            printf("Стек переполнен!\n");
            return false;
        }
        prevValue = val;
    }
    return true;
}

void mergeTwoStacks(const Stack *s1, const Stack *s2, Stack *result)
{
    // Вспомогательные индексы
    int i = s1->top;
    int j = s2->top;

    while (i >= 0 && j >= 0)
    {
        if (s1->data[i] < s2->data[j])
        {
            push(result, s1->data[i]);
            i--;
        }
        else
        {
            push(result, s2->data[j]);
            j--;
        }
    }
    while (i >= 0)
    {
        push(result, s1->data[i]);
        i--;
    }
    while (j >= 0)
    {
        push(result, s2->data[j]);
        j--;
    }
}

void flipStack(Stack *src, Stack *dest)
{
    int val;
    while (pop(src, &val))
    {
        push(dest, val);
    }
}

void task2(void)
{
    printf("\n--- ЗАДАНИЕ 2 ---\n");
    int n1, n2;
    printf("Введите размер первого стека: ");
    if (scanf("%d", &n1) != 1 || n1 < 0)
    {
        fprintf(stderr, "Некорректный ввод!\n");
        while (getchar() != '\n')
            ;
        return;
    }
    printf("Введите размер второго стека: ");
    if (scanf("%d", &n2) != 1 || n2 < 0)
    {
        fprintf(stderr, "Некорректный ввод!\n");
        while (getchar() != '\n');
        return;
    }

    Stack st1, st2;
    if (!initStack(&st1, n1) || !initStack(&st2, n2))
    {
        fprintf(stderr, "Ошибка инициализации одного из стеков.\n");
        freeStack(&st1);
        freeStack(&st2);
        return;
    }

    printf("\n--- Заполнение первого стека (возрастание) ---\n");
    if (!fillStackAscending(&st1, n1))
    {
        freeStack(&st1);
        freeStack(&st2);
        return;
    }

    printf("\n--- Заполнение второго стека (возрастание) ---\n");
    if (!fillStackAscending(&st2, n2))
    {
        freeStack(&st1);
        freeStack(&st2);
        return;
    }

    Stack st3;
    if (!initStack(&st3, n1 + n2))
    {
        fprintf(stderr, "Ошибка инициализации третьего стека.\n");
        freeStack(&st1);
        freeStack(&st2);
        return;
    }

    mergeTwoStacks(&st1, &st2, &st3);

    Stack st4;
    if (!initStack(&st4, n1 + n2))
    {
        fprintf(stderr, "Ошибка инициализации вспомогательного стека.\n");
        freeStack(&st1);
        freeStack(&st2);
        freeStack(&st3);
        return;
    }
    flipStack(&st3, &st4);

    printf("\nТретий стек (упорядочен по возрастанию, снизу → вверх):\n");
    while (!isEmpty(&st4))
    {
        int val;
        pop(&st4, &val);
        printf("%d ", val);
    }
    printf("\n");

    freeStack(&st1);
    freeStack(&st2);
    freeStack(&st3);
    freeStack(&st4);
}

/* ------------------------------------------------------
 * Функция main: организует меню для двух задач
 * ------------------------------------------------------ */
int main(void)
{
    setbuf(stdout, NULL);

    while (true)
    {
        printf("\nГЛАВНОЕ МЕНЮ:\n");
        printf("1. Задача №1 (найти сумму после минимального элемента стека)\n");
        printf("2. Задача №2 (слияние двух стеков в возрастающем порядке)\n");
        printf("0. Выход\n");
        printf("Выберите пункт меню: ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            fprintf(stderr, "Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice)
        {
        case 0:
            printf("Завершение программы.\n");
            return 0;
        case 1:
            task1();
            break;
        case 2:
            task2();
            break;
        default:
            printf("Неизвестный пункт меню. Повторите выбор.\n");
            break;
        }
    }
    return 0;
}
