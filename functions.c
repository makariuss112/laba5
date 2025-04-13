#include "functions.h"

int initStack(struct Stack* stack, int size) {
    if (size <= 0) {
        printf("Error: Stack size must be a positive integer.\n");
        return 0;
    }
    stack->array = (int*)malloc(size * sizeof(int));
    if (stack->array == NULL) {
        printf("Memory allocation failed!\n");
        return 0;
    }
    stack->topElement = -1;
    stack->stackSize = size;
    return 1;
}

int isFull(struct Stack* stack) {
    return stack->topElement == stack->stackSize - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->topElement == -1;
}

void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow! Cannot push %d\n", value);
    } else {
        stack->array[++stack->topElement] = value;
        printf("Pushed %d into stack\n", value);
    }
}

int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow! Cannot pop\n");
        return -1;
    } else {
        return stack->array[stack->topElement--];
    }
}

int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return -1;
    } else {
        return stack->array[stack->topElement];
    }
}

int sumAfterMin(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return 0;
    }

    int min = stack->array[0];
    int minIndex = 0;

    for (int i = 1; i <= stack->topElement; i++) {
        if (stack->array[i] < min) {
            min = stack->array[i];
            minIndex = i;
        }
    }

    int sum = 0;
    for (int i = minIndex + 1; i <= stack->topElement; i++) {
        sum += stack->array[i];
    }

    return sum;
}

void mergeStacksInOrder(struct Stack* stack1, struct Stack* stack2, struct Stack* result) {
    int i = 0, j = 0, k = 0;

    while (i <= stack1->topElement && j <= stack2->topElement) {
        if (stack1->array[i] < stack2->array[j]) {
            result->array[k++] = stack1->array[i++];
        } else {
            result->array[k++] = stack2->array[j++];
        }
    }

    while (i <= stack1->topElement) {
        result->array[k++] = stack1->array[i++];
    }

    while (j <= stack2->topElement) {
        result->array[k++] = stack2->array[j++];
    }

    result->topElement = k - 1;
}

void displayStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements: ");
        for (int i = 0; i <= stack->topElement; i++) {
            printf("%d ", stack->array[i]);
        }
        printf("\n");
    }
}