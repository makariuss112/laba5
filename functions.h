#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack 
{
    int stackSize, topElement, *array;

};

int initStack(struct Stack* stack, int size);
void push(struct Stack* stack, int value);
int pop(struct Stack* stack);
int peek(struct Stack* stack);

int isFull(struct Stack* stack);
int isEmpty(struct Stack* stack);

int sumAfterMin(struct Stack* stack);

void mergeStacksInOrder(struct Stack* stack1, struct Stack* stack2, struct Stack* result);
void displayStack(struct Stack* stack);

#endif