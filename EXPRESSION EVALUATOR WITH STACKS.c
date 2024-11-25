#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == (MAX - 1)) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

char peek() {
    return stack[top];
}

int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void reverse(char *exp) {
    int length = strlen(exp);
    for (int i = 0; i < length / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[length - i - 1];
        exp[length - i - 1] = temp;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char c;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while ((c = pop()) != '(') {
                postfix[j++] = c;
            }
        } else {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }
    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void infixToPrefix(char infix[], char prefix[]) {
    int length = strlen(infix);
    reverse(infix);
    for (int i = 0; i < length; i++) {
        if (infix[i] == '(') {
            infix[i] = ')';
        } else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }
    infixToPostfix(infix, prefix);
    reverse(prefix);
}

void postfixToInfix(char postfix[], char infix[]) {
    char stack[MAX][MAX];
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op2[MAX];
            strcpy(op2, stack[top--]);
            char op1[MAX];
            strcpy(op1, stack[top--]);
            char expr[MAX] = "(";
            strcat(expr, op1);
            strncat(expr, &postfix[i], 1);
            strcat(expr, op2);
            strcat(expr, ")");
            strcpy(stack[++top], expr);
        }
    }
    strcpy(infix, stack[top]);
}

void postfixToPrefix(char postfix[], char prefix[]) {
    char infix[MAX];
    postfixToInfix(postfix, infix);
    infixToPrefix(infix, prefix);
}

void prefixToInfix(char prefix[], char infix[]) {
    char stack[MAX][MAX];
    int top = -1;
    int length = strlen(prefix);
    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            strcpy(stack[++top], operand);
        } else {
            char op1[MAX];
            strcpy(op1, stack[top--]);
            char op2[MAX];
            strcpy(op2, stack[top--]);
            char expr[MAX] = "(";
            strcat(expr, op1);
            strncat(expr, &prefix[i], 1);
            strcat(expr, op2);
            strcat(expr, ")");
            strcpy(stack[++top], expr);
        }
    }
    strcpy(infix, stack[top]);
}

void prefixToPostfix(char prefix[], char postfix[]) {
    char infix[MAX];
    prefixToInfix(prefix, infix);
    infixToPostfix(infix, postfix);
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    int choice;
    
    while (1) {
        printf("\nEnter your choice:\n");
        printf("1. Infix to Postfix\n");
        printf("2. Infix to Prefix\n");
        printf("3. Postfix to Infix\n");
        printf("4. Postfix to Prefix\n");
        printf("5. Prefix to Infix\n");
        printf("6. Prefix to Postfix\n");
        printf("7. Exit\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;
            case 2:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPrefix(infix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;
            case 3:
                printf("Enter postfix expression: ");
                scanf("%s", postfix);
                postfixToInfix(postfix, infix);
                printf("Infix Expression: %s\n", infix);
                break;
            case 4:
                printf("Enter postfix expression: ");
                scanf("%s", postfix);
                postfixToPrefix(postfix, prefix);
                printf("Prefix Expression: %s\n", prefix);
                break;
            case 5:
                printf("Enter prefix expression: ");
                scanf("%s", prefix);
                prefixToInfix(prefix, infix);
                printf("Infix Expression: %s\n", infix);
                break;
            case 6:
                printf("Enter prefix expression: ");
                scanf("%s", prefix);
                prefixToPostfix(prefix, postfix);
                printf("Postfix Expression: %s\n", postfix);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    }

    return 0;
}