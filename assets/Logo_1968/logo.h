// Logo.h
// Runs on LM3S1968 or LM3S8962
// Jonathan Valvano
// November 12, 2012

/* This example accompanies the books
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2012
   
   "Embedded Systems: Introduction to Arm Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2012
 Copyright 2012 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */


// //*************RIT128x96x4_Logo********************************************
// //  Displays the 4-bit color BMP image stored in LogoBuffer
// //  Inputs: ypos (94 is bottom, 80 is near the bottom)
// //  Outputs: none
// //  Must be less than or equal to 128 pixels wide by 80 rows high
// //  The width must be an even number
// void RIT128x96x4_Logo(unsigned long ypos);

//*************RIT128x96x4_BMP********************************************
//  Displays the 4-bit color BMP image 
//  Inputs: xpos horizontal position to display this image, columns from the left edge 
//          ypos (94 is bottom, 80 is near the bottom)
//          pointer to a BMP image
//  Outputs: none
//  Must be less than or equal to 128 pixels wide by 80 rows high
//  The width must be an even number
void RIT128x96x4_BMP(unsigned long xpos, unsigned long ypos, const unsigned char *Buffer);

