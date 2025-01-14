/*
 * Copyright (c) 2023 ivfzhou
 * clib is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 */

// 算术表达式运算

#include <string.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>

#include "stack.c"

static _Bool isOperator(char c);

static int isPrecede(char s1, char s2);

static long double calculate(long double x, char optr, long double y);

long double expression_calculate(const char *expr) {
    Stack *operator = stack_alloc(sizeof(char), 1024);
    Stack *operand = stack_alloc(sizeof(long double), 1024);

    size_t len = strlen(expr);
    for (int i = 0; i < len; i++) {
        char c = expr[i];
        if (!isOperator(c)) {
            char tmp[] = {c, '\0'};
            long double num = strtold(tmp, NULL);
            stack_push(operand, &num);
        } else {
            char optr;
            if (stack_peekTop(operator, &optr)) optr = '\0';
            switch (isPrecede(optr, c)) {
                case 1:
                    stack_pop(operator, &optr);
                    long double x, y;
                    stack_pop(operand, &x);
                    stack_pop(operand, &y);
                    long double res = calculate(y, optr, x);

                    // 去除括号
                    if (c == ')') {
                        stack_pop(operator, &optr);
                        if (optr != '(') {
                            fprintf(stderr, "括号不匹配");
                            raise(SIGALRM);
                        }
                    }

                    stack_push(operand, &res);
                    break;
                case -1:
                    stack_push(operator, &c);
                    break;
                case 0:
                    stack_pop(operator, &optr);
                    break;
            }
        }
    }

    while (!stack_isEmpty(operator)) {
        char optr;
        stack_pop(operator, &optr);
        long double x, y;
        stack_pop(operand, &x);
        stack_pop(operand, &y);
        long double res = calculate(y, optr, x);
        stack_push(operand, &res);
    }

    long double count = 0;
    stack_pop(operand, &count);

    if (!stack_isEmpty(operator) || !stack_isEmpty(operand)) {
        fprintf(stderr, "算式非法");
        raise(SIGALRM);
    }

    stack_free(operand);
    stack_free(operator);
    return count;
}

static _Bool isOperator(char c) {
    const static char operators[] = "+-*/()";
    int i = 0;
    char o;
    while ((o = operators[i++])) if (c == o) return 1;
    return 0;
}

static int isPrecede(char s1, char s2) {
    if (!s1) return -1;
    switch (s1) {
        case '+':
        case '-':
            switch (s2) {
                case '+':
                case '-':
                case ')':
                    return 1;
                case '/':
                case '(':
                case '*':
                    return -1;
            }
            break;
        case '/':
        case '*':
            switch (s2) {
                case '+':
                case '-':
                case ')':
                    return 1;
                case '(':
                case '/':
                case '*':
                    return -1;
            }
            break;
        case '(':
            switch (s2) {
                case ')':
                    return 0;
                default:
                    return -1;
            }
        case ')':
            return 1;
    }
    raise(SIGABRT);
    return 0;
}

static long double calculate(long double x, char optr, long double y) {
    switch (optr) {
        case '+':
            return x + y;
        case '-':
            return x - y;
        case '/':
            return x / y;
        case '*':
            return x * y;
    }
    raise(SIGABRT);
    return 0;
}

int main(void) {
    assert(expression_calculate("1+1") == 2);
    assert(expression_calculate("1-1") == 0);
    assert(expression_calculate("9/3") == 3);
    assert(expression_calculate("3*3") == 9);
    assert(expression_calculate("3+3/3") == 4);
    assert(expression_calculate("(1+3)*4") == 16);
    assert(expression_calculate("((1+3)/2)*4") == 8);
    assert(expression_calculate("((1+3)/2)*(4-2)") == 4);
}
