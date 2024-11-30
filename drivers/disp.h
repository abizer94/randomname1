#pragma once
#define VGA_CTR_REG 0x3d4
#define VGA_DATA_REG 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define V_ADDR 0xb8000
#define MAX_R 25
#define MAX_C 80
#define W_ON_B 0x0f
#include "io.h"
			   
void set_cursor(int offset);
     
int get_cursor();


void set_char_in_mem(char c,int offset);


int get_row_from_offset(int offset);


int get_offset(int col, int row);


int mov_offset_nl(int offset);


void cpy_chk(char * src,char*dst,int nbytes);

int scr_ln(int offset);

void cls();

void print_back();

void print_s(char* s);

void print_c(char c);

void nl();

void pribnr();
