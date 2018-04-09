// Lab6.c
// Runs on LM4F120 or TM4C123
// Use SysTick interrupts to implement a 3-key digital piano
// MOOC lab 13 or EE319K lab6 starter
// Program written by: Suhas Raja, Sanika Phanse
// Date Created: 3/6/17 
// Last Modified: 3/5/18 
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "dac.h"
#include "TExaS.h"
#define BPM 60 
#define songlen 115

//const note song1[songlen]={{B,4},{A,4},{G,6},{B,4},{A,4},{G,6},{G,2},{REST,2},{G,2},{REST,2},{G,2},{REST,2},{G,2},{REST,2},{A,2},{REST,2},{A,2},{REST,2},{A,2},{REST,2},{A,2},{REST,2}};
const note song[songlen] ={
	{D7, 1},
	{REST, 2},
	{D7, 1},
	{REST, 2},
	{D7, 2},
	ntbreak,
	{D7, 2},
	ntbreak,
	{E7, 2},
	{F7, 6},
	{G7, 6},
	{BF7, 6},
	ntbreak,	
	{BF7, 6},
	{C7, 6},
	{E0, 6},
	{A0, 6},
	ntbreak,
	{A0, 1},
	ntbreak,
	{A0, 2},
	ntbreak,
	{A0, 2},
	{G0, 1},
	{F0, 2},
	{D0, 2},
	{E0, 2},
	{F0, 2},
	{A0, 1},
	ntbreak,
	{A0, 2},
	ntbreak,
	{A0, 2},
	ntbreak,
	{G0, 1},
	{F0, 2},
	{D0, 2},
	{E0,1},
	{F0,1},
	{A0, 1},
	ntbreak,
	{A0, 2},
	ntbreak,
	{A0, 2},
	ntbreak,
	{G0, 1},
	{F0, 2},
	{D0, 2},
	{E0, 1},
	{F0, 1},
	{G0, 1},
	{A0, 2},
	{BF0, 2},
	{A0, 1},
	{G0, 2},
	{D0, 2},
	{F0, 2},
	{D0, 6},
	{A0, 6},
	{G0, 2},
	{F0, 2},
	{E0, 2},
	{D0, 4},
	{E0, 2},
	{F0, 6},
	{A0, 6},
	{G0, 6},
	{C, 6},
	{D0, 6},
	{A0, 6},
	{G0, 2},
	{F0, 2},
	{E0, 2},
	{D0, 4},
	{E0, 2},
	{F0, 4},
	{E0, 1},
	{D0, 1},
	{E0, 2},
	{D0, 2},
	{C0, 2},
	{D0, 2},
	ntbreak,
	{D0, 6},
	ntbreak,
	{D0, 6},
	{A0, 6},
	{G0, 2},
	{F0, 2},
	{E0, 2},
	{D0, 4},
	{E0, 2},
	{F0, 6},
	{A0, 6},
	{G0, 6},
	{C, 6},
	{D, 6},
	{C, 2},
	{A0, 4},
	{C, 2},
	{D, 2},
	{C, 4},
	{A0, 2},
	{D0, 2},
	{E0, 2},
	{F0, 4},
	{E0, 1},
	{D0, 1},
	{E0, 2},
	{D0, 2},
	{C0, 2},
	{D0, 6},
	ntbreak,
	{D0, 6}
};
	
	
// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void Timer1A_Handler(void){
	static int j = 0;
	j %= songlen;
	Sound_Play2(song[j]);
	j++;
}


int main(void){
	unsigned long in, last;
  int counter=0;
	TExaS_Init(SW_PIN_PE3210,DAC_PIN_PB3210,ScopeOn);    // bus clock at 80 MHz
  Piano_Init();
  Sound_Init();
	DAC_Init();
	last = 0;
  EnableInterrupts();
	while(1){
		if(counter>=1000000){
			GPIO_PORTF_DATA_R^=0x02;
			counter=0;
		}
		in = Piano_In();
		counter++;
		if(in&&(last==0)){
			if(in==1){Sound_Play(B);}
			if(in==2){Sound_Play(A);}
			if(in==4){Sound_Play(G);}
			if(in==8){Timer1A_Handler();}
			EnableInterrupts();
		}else if((in==0)&&last){Stop();}
		last = in;
	}
}



