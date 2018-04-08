To create a logo for LM1968 or LM3S8962
Jonathan Valvano, 8/8/2012
See LogoDump.c for more details
1) Create a bmp file
   4-bit color
   width less than or equal to 128 pixels
   height less than or equal 80 pixels
   width must be even
   name the picture file logo.bmp
   store in same directory as LogoDump.exe
   (or BmpConvert.exe)
2) Delete any old logo.txt file in directory
3) Execute LogoDump.exe
4) Open logo.txt, select all, copy
5) Open uVision compiler
   paste new image into this data constant
   const unsigned char LogoBuffer[] =

