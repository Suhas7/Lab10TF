// ****************************** LogoDump.c ****************************
// Purpose: convert bmp into C constants for LM3S8962 graphics
// simple binary to ASCII hex converter
// Last modified 7/16/11 by Jonathan W. Valvano

// Copyright 2011 by Jonathan W. Valvano, valvano@mail.utexas.edu
//    You may use, edit, run or distribute this file
//    as long as the above copyright notice remains
/* To create a logo for LM3S8962
1) Create a bmp file
   4-bit color
   length less than 128 pixels
   height less than 80 pixels
   length must be even
   name the logo.bmp
   store in same directory as LogoDump.exe
2) Delete any old logo.txt file in directory
3) Execute LogoDump.exe
4) Open logo.txt, select all, copy
5) Open uVision compiler
   paste new image into this data constant
   const unsigned char g_pucLogo[] =
*/

#include <stdlib.h>
#include <stdio.h>

// 4-bit color depth bmp files
#define NUMBERS_PER_LINE 32  
void main(void){ unsigned char data; int i;
  unsigned char nibble;  unsigned char letter;
  FILE *in, *out;
  if((in = fopen("logo.bmp", "rt"))== NULL){
    fprintf(stderr, "Cannot open logo.bmp file.\n");
    return;
  }
  if((out = fopen("logo.txt", "wt")) == NULL){
    fprintf(stderr, "Cannot open logo.txt file.\n");
    return;
  }
  i = 0;
  while (!feof(in)){
    data = fgetc(in);
    fputc(32, out);
    fputc('0', out);
    fputc('x', out);
    nibble = data/16; // top 4 bits
    if(nibble<10){
       letter = '0'+nibble;
    }
    else{
      letter = 'A'+nibble-10;
    }
    fputc(letter, out);
  
    nibble = data%16;  // bottom 4 bits
    if(nibble<10){
      letter = '0'+nibble;
    }
    else {
      letter = 'A'+nibble-10;
    }
    fputc(letter, out);
    fputc(',', out);
    i++;
    if((i%NUMBERS_PER_LINE)==0){
      fputc(10, out);     // Line feed
    }
  }
  fclose(in);
  fputc(13, out);
  fputc(10, out);
  fclose(out);


}

