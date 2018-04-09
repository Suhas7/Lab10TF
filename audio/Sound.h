// Sound.h
// This module contains the SysTick ISR that plays sound
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
#include <stdint.h>
#define ntbreak {-1, .05}
#define REST -1
// Header files contain the prototypes for public functions
// this file explains what the module does

// **************Sound_Init*********************
// Initialize digital outputs and SysTick timer
// Called once, with sound/interrupts initially off
// Input: none
// Output: none
void Sound_Init(void);
// **************Sound_Play*********************
// Start sound output, and set Systick interrupt period 
// Sound continues until Sound_Play called again
// This function returns right away and sound is produced using a periodic interrupt
// Input: interrupt period
//           Units of period to be determined by YOU
//           Maximum period to be determined by YOU
//           Minimum period to be determined by YOU
//         if period equals zero, disable sound output
// Output: none
typedef struct {
	int pitch;
	double len;
}note;
void Sound_Play(int pitch); //sets systick to that pitch
void Sound_Play2(note a);   //helper function for timer1a handler
// example periods associated with various notes
// these constants will be a function of bus period and number of elements in your sine table
#define C1   0   // 2093 Hz  //all the notes
#define B1   1   // 1975.5 Hz
#define BF1  2   // 1864.7 Hz
#define A1   3   // 1760 Hz
#define AF1  4   // 1661.2 Hz
#define G1   5   // 1568 Hz
#define GF1  6   // 1480 Hz
#define F1   7   // 1396.9 Hz
#define E1   8   // 1318.5 Hz
#define EF1  9   // 1244.5 Hz
#define D1   10   // 1174.7 Hz
#define DF1  11   // 1108.7 Hz
#define C    12   // 1046.5 Hz
#define B    13   // 987.8 Hz
#define BF   14   // 932.3 Hz
#define A    15   // 880 Hz
#define AF   16   // 830.6 Hz
#define G    17   // 784 Hz
#define GF  18   // 740 Hz
#define F   19   // 698.5 Hz
#define E   20   // 659.3 Hz
#define EF  21   // 622.3 Hz
#define D   22   // 587.3 Hz
#define DF  23   // 554.4 Hz
#define C0  24   // 523.3 Hz
#define B0  25   // 493.9 Hz
#define BF0 26   // 466.2 Hz
#define A0  27   // 440 Hz
#define AF0 28   // 415.3 Hz
#define G0  29   // 392 Hz
#define GF0 30   // 370 Hz
#define F0  31   // 349.2 Hz
#define E0  32   // 329.6 Hz
#define EF0 33   // 311.1 Hz
#define D0  34   // 293.7 Hz
#define DF0 35   // 277.2 Hz
#define C7  36   // 261.6 Hz
#define B7  37   // 246.9 Hz
#define BF7 38   // 233.1 Hz
#define A7  39   // 220 Hz
#define AF7 40   // 207.7 Hz
#define G7  41   // 196 Hz
#define GF7 42   // 185 Hz
#define F7  43   // 174.6 Hz
#define E7  44   // 164.8 Hz
#define EF7 45   // 155.6 Hz
#define D7  46   // 146.8 Hz
#define DF7 47   // 138.6 Hz
#define C6  48   // 130.8 Hz
