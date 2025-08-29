#pragma once
#include <stdbool.h>
#define IRQ1 33

void exec(char* in);
bool backspace(char s[]);
int compare(char s1[] ,char s2[]);
bool append(char s[] , char n);
int strl(char s[]);
void init_keyboard();
