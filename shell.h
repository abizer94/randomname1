#pragma once

#include <stdint.h>
#include "drivers/keyboard.h"
#include "mem.h"
#include "drivers/disp.h"

void add(char* arg);
void sub(char* arg);
void mult(char* arg);
void div(char* arg);
void exec(char* in);
int checkifcmdoropr(char* in,int* funcno,int* indx);
int turntointarr(const char *input, int *output, int max_size);
int string_to_int(const char *str, int *result);
int is_digit(char c) ;
void inttostr(int num, char* str);
void allocate(char* arg);

