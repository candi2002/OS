// calc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"
#include "operations.h"

#define MAX_INPUT 50

void clear_screen() {
    printf("\033[H\033[J");
}

int main() {
    char input[MAX_INPUT];
    double ANS = 0;
    double num1, num2, result;
    char op;
    
    while (1) {
        printf(">> ");
        fgets(input, MAX_INPUT, stdin);
        input[strcspn(input, "\n")] = 0;
        
        if (strcmp(input, "EXIT") == 0) {
            break;
        }
        
        if (strstr(input, "ANS")) {
            char temp[MAX_INPUT];
            snprintf(temp, MAX_INPUT, "%lf", ANS);
            char *pos = strstr(input, "ANS");
            memmove(pos + strlen(temp), pos + 3, strlen(pos + 3) + 1);
            memcpy(pos, temp, strlen(temp));
        }
        
        if (sscanf(input, "%lf %c %lf", &num1, &op, &num2) != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }
        
        switch (op) {
            case '+': result = add(num1, num2); break;
            case '-': result = subtract(num1, num2); break;
            case 'x': result = multiply(num1, num2); break;
            case '/': 
                if (num2 == 0) {
                    printf("MATH ERROR\n");
                    continue;
                }
                result = divide(num1, num2);
                break;
            case '%':
                if ((int)num2 == 0) {
                    printf("MATH ERROR\n");
                    continue;
                }
                result = modulo((int)num1, (int)num2);
                break;
            default:
                printf("SYNTAX ERROR\n");
                continue;
        }
        
        printf("%.2lf\n", result);
        ANS = result;
        getchar(); // Chờ nhập phím trước khi xóa màn hình
        clear_screen();
    }
    
    return 0;
}
