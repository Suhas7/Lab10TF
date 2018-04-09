To create a logo for LM1968 or LM3S8962
Jonathan Valvano, 11/12/2012
See LogoDump.c for how it works
1) Create a bmp file
   4-bit color, 16-color bmp
   width less than or equal to 128 pixels
   height less than or equal 80 pixels
   width must be even
   save the image as a 16-color bmp file
   store in same directory as BmpConvert.exe
2) Execute BmpConvert.exe
   Type the image name 
   E.g., if the file is horse.bmp, then type horse
3) Open the corresponding txt file, select all, copy
4) Open uVision compiler
   paste new image as a data constant
5) Draw the image by calling RIT128x96x4_BMP
   E.g., place lower left corner at 20,70)
         RIT128x96x4_BMP(20, 70, Horse);

