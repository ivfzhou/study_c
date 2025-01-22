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

#include <stdarg.h>
#include <stdio.h>

#include "list.h"

// 项。
typedef struct {
    long double coefficient;
    int exponent;
} item;

// 多项式。
typedef list polynomial;

static void add(polynomial* poly, item* itm) {
    if (itm->coefficient == 0.0)
        return;
    size_t len = list_len(poly);

    item tmp;
    for (int i = 0; i < len; i++) {
        list_get(poly, i, &tmp);
        if (tmp.exponent == itm->exponent) {
            long double coefficient = tmp.coefficient + itm->coefficient;
            if (coefficient != 0.0) {
                item newItem = {
                    .coefficient = coefficient,
                    .exponent = tmp.exponent,
                };
                list_set(poly, i, &newItem);
            }
            else {
                list_del(poly, i);
            }
            return;
        }
        else if (tmp.exponent > itm->exponent) {
            list_insert(poly, i, itm);
            return;
        }
    }

    list_rpush(poly, itm);
}

// 新建多项式。
polynomial* polynomial_new(int num, ...) {
    va_list args;
    va_start(args, num);

    list* newPolynomial = list_alloc(sizeof(item), list_impl_type_array);

    for (int i = 0; i < num; i++) {
        item* itm = va_arg(args, item *);
        add(newPolynomial, itm);
    }

    va_end(args);
    return newPolynomial;
}

// 销毁多项式。
void polynomial_free(polynomial* poly) {
    list_free(poly);
}

// 多项式相加。
polynomial* polynomial_add(const polynomial* x, const polynomial* y) {
    polynomial* newPolynomial = list_alloc(sizeof(item), list_impl_type_array);

    size_t len = list_len(x);
    for (int i = 0; i < len; i++) {
        item item;
        list_get(x, i, &item);
        add(newPolynomial, &item);
    }

    len = list_len(y);
    for (int i = 0; i < len; i++) {
        item item;
        list_get(y, i, &item);
        add(newPolynomial, &item);
    }

    return newPolynomial;
}

// 多项式相减。
polynomial* polynomial_subtract(const polynomial* x, const polynomial* y) {
    polynomial* newPolynomial = list_alloc(sizeof(item), list_impl_type_array);

    size_t len = list_len(x);
    item item;
    for (int i = 0; i < len; i++) {
        list_get(x, i, &item);
        add(newPolynomial, &item);
    }

    len = list_len(y);
    for (int i = 0; i < len; i++) {
        list_get(y, i, &item);
        item.coefficient = -item.coefficient;
        add(newPolynomial, &item);
    }

    return newPolynomial;
}

// 多项式相乘。
polynomial* polynomial_multiply(const polynomial* x, const polynomial* y) {
    polynomial* newPolynomial = list_alloc(sizeof(item), list_impl_type_array);

    size_t lenX = list_len(x);
    size_t lenY = list_len(y);
    item itemX;
    item itemY;
    for (int i = 0; i < lenX; i++) {
        list_get(x, i, &itemX);
        for (int j = 0; j < lenY; j++) {
            list_get(y, j, &itemY);
            item newItem = {
                .coefficient = itemX.coefficient * itemY.coefficient,
                .exponent = itemX.exponent * itemY.exponent,
            };
            add(newPolynomial, &newItem);
        }
    }

    return newPolynomial;
}

// 打印多项式。
void polynomial_fprint(const polynomial* poly, FILE* f) {
    size_t len = list_len(poly);

    for (int i = 0; i < len; i++) {
        item item;
        list_get(poly, i, &item);

        if (item.coefficient > 0) {
            if (i != 0)
                fprintf(f, " + %.2Lf", item.coefficient);
            else
                fprintf(f, "%.2Lf", item.coefficient);
        }
        else {
            if (i == 0)
                fprintf(f, "-%.2Lf", -item.coefficient);
            else
                fprintf(f, " - %.2Lf", -item.coefficient);
        }

        if (item.exponent != 0) {
            fprintf(f, "x");
            int max = 10;
            while (item.exponent / max != 0)
                max *= 10;
            if (item.exponent < 0)
                fprintf(f, "⁻");
            // else fprintf(f, "⁺");
            do {
                switch ((item.exponent < 0 ? -item.exponent : item.exponent) / (max / 10) % 10) {
                case 0:
                    fprintf(f, "%s", "⁰");
                    break;
                case 1:
                    fprintf(f, "%s", "¹");
                    break;
                case 2:
                    fprintf(f, "%s", "²");
                    break;
                case 3:
                    fprintf(f, "%s", "³");
                    break;
                case 4:
                    fprintf(f, "%s", "⁴");
                    break;
                case 5:
                    fprintf(f, "%s", "⁵");
                    break;
                case 6:
                    fprintf(f, "%s", "⁶");
                    break;
                case 7:
                    fprintf(f, "%s", "⁷");
                    break;
                case 8:
                    fprintf(f, "%s", "⁸");
                    break;
                case 9:
                    fprintf(f, "%s", "⁹");
                    break;
                }
            }
            while ((max /= 10) != 1);
        }
    }
    puts("");
}

int main() {
    polynomial* poly = polynomial_new(3,
                                      &(item){
                                          .coefficient = 2,
                                          .exponent = 1,
                                      },
                                      &(item){
                                          .coefficient = 3,
                                          .exponent = 2,
                                      },
                                      &(item){
                                          .coefficient = 4,
                                          .exponent = -3,
                                      });
    polynomial* poly0 = polynomial_new(3,
                                       &(item){
                                           .coefficient = 2,
                                           .exponent = 1,
                                       },
                                       &(item){
                                           .coefficient = -3,
                                           .exponent = 2,
                                       },
                                       &(item){
                                           .coefficient = 4,
                                           .exponent = -3,
                                       });

    polynomial* poly1 = polynomial_add(poly, poly0);
    // polynomial_fprint(poly1, stdout);

    polynomial* poly2 = polynomial_multiply(poly, poly0);
    // polynomial_fprint(poly2, stdout);

    polynomial* poly3 = polynomial_subtract(poly, poly0);
    // polynomial_fprint(poly3, stdout);

    polynomial_free(poly);
    polynomial_free(poly0);
    polynomial_free(poly1);
    polynomial_free(poly2);
    polynomial_free(poly3);
}
