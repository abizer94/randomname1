#include <stdint.h>
#include "shell.h"



typedef void (*CommandFunc)();

CommandFunc cmdl[] = {add,freee,print_s};
char* commands[] ={"ADD","FREE","PRINTS"};


void inttostr(int num, char* str) {
    int i = 0, temp, len = 0;
    char buffer[20];  // Sufficient for up to 32-bit integer

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    while (num > 0) {
        buffer[len++] = (num % 10) + '0';
        num /= 10;
    }

    for (int j = 0; j < len; j++) {
        str[j] = buffer[len - 1 - j];
    }
    str[len] = '\0';
    return;
}


int checkifcmdoropr(char* in, int* funcno, int* indx) {
    for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
        int j = 0;
        while (in[j] != ' ' && in[j] != '\0' && commands[i][j] != '\0') {
            if (commands[i][j] != in[j]) {
                break;
            }
            j++;
        }
        if ((in[j] == ' ' || in[j] == '\0') && commands[i][j] == '\0') {
            *funcno = i;
            *indx = j + 1;
            return 1;
        }
    }
    return 0;
}


void exec(char* in){
    int* funcno;
    int* indx;
    
    if(!checkifcmdoropr(in,funcno,indx))return;
    int arg1 = in[*indx];
    cmdl[(int)*funcno](arg1);
    return;

}

int is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Convert a numeric string to an integer from scratch
int string_to_int(const char *str, int *result) {
    int sign = 1;
    int value = 0;

    // Check for optional sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Convert character digits to integer
    while (*str) {
        if (!is_digit(*str)) {
            return 0; // Not a valid number
        }
        value = value * 10 + (*str - '0');
        str++;
    }

    *result = value * sign;
    return 1; // Success
}

int turntointarr(const char *input, int *output, int max_size) {
    int count = 0;
    char temp[20]; // Temporary buffer for numbers
    int i = 0;

    while (*input) {
        if (*input == ' ') {
            if (i > 0) { 
                temp[i] = '\0'; 
                int num;
                if (string_to_int(temp, &num)) {
                    if (count < max_size) {
                        output[count++] = num; 
                    } else {
                        return -1;
                    }
                } else {
                    return -1; 
                }
                i = 0;
            }
        } else {
            if (i < sizeof(temp) - 1) {
                temp[i++] = *input; 
            } else {
                return -1; 
            }
        }
        input++;
    }

    if (i > 0) {
        temp[i] = '\0';
        int num;
        if (string_to_int(temp, &num)) {
            if (count < max_size) {
                output[count++] = num;
            } else {
                return -1;
            }
        } else {
            return -1;
        }
    }

    return count;
}

void add(char* arg){
    int sum = 0;
    int out[10]; 
    int i = turntointarr(arg,out,10);
    while(i>0){
        sum +=out[i];
        i--;
    }
    char str[10];
    inttostr(sum,str);
    print_s(str);
    return;
}



