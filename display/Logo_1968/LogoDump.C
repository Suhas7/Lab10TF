// ****************************** LogoDump.c ****************************
// Purpose: convert bmp into C constants for LM3S8962 graphics
// simple binary to ASCII hex converter
// Last modified 11/12/12 by Jonathan W. Valvano

// Copyright 2012 by Jonathan W. Valvano, valvano@mail.utexas.edu
//    You may use, edit, run or distribute this file
//    as long as the above copyright notice remains
/* To create a logo for LM3S1968 or LM3S8962
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
#include <string.h>

// 4-bit color depth bmp files
unsigned char BMPname[48];
unsigned char TXTname[48];
unsigned char name[48];
#define NUMBERS_PER_LINE 32  
void main(void){ unsigned char data; int i;
  unsigned char nibble;  unsigned char letter;
  FILE *in, *out;
  printf("This program converts a 16-color BMP into C source code for OLED\n");
  printf("Enter file: ");
  scanf("%s", BMPname);
  strcpy(name,"const unsigned char ");
  strcat(name,BMPname);
  strcat(name,"[] ={");
  strcpy(TXTname,BMPname);
  strcat(BMPname,".bmp");
  strcat(TXTname,".txt");
  printf("Converting file %s to file %s\n ",BMPname, TXTname);

  if((in = fopen(BMPname, "rt"))== NULL){
    fprintf(stderr, "Cannot open bmp file.\n");
    scanf("%d",&data); 
    return;
  }
  if((out = fopen(TXTname, "wt")) == NULL){
    fprintf(stderr, "Cannot open txt file.\n");
    scanf("%d",&data); 
    return;
  }
  i = 0;
  while(name[i]){
    fputc(name[i], out);
    i++;
  }
  fputc(10, out);     // Line feed
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
  fputc(13, out);
  fputc(10, out);
  fputc('}', out);
  fputc(';', out);
  fclose(in);
  fputc(13, out);
  fputc(10, out);
  fclose(out);



}

