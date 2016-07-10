/*
 * ======== Standard MSP430 includes ========
 */
#include "msp430g2553.h"
#include "MSP-EXP430G2_API.h"
#include "statemachine.h"

#define TIMESTEP_STATEMACHINE 3;

extern unsigned char current_state;
extern unsigned char ped_request;

void ShowState(unsigned char);

/*
 * Global variables
 */
unsigned int system_tick_count = TIMESTEP_STATEMACHINE
unsigned char performNextStep=0;				// flag to indicate "start the next step in our statemachine

unsigned char PSTATES=0;
/*
 *  ======== main ========
 *  everything starts here.
 */
int main(int argc, char *argv[])
{	initialize_hardware();
    __enable_interrupt();           			// Set global interrupt enable

    ShowState(current_state);
    // start an endless loop to operate as defined
    // in the statemachine
    //
    while(1)
    {
    	if(performNextStep)
    	{
    		performNextStep=0;
			Do_Step('x');
    	}
    }
}

void Ampel1_rot()		{ P1_0_ON();  P1_1_OFF(); P1_2_OFF(); }
void Ampel1_rotgelb()	{ P1_0_ON();  P1_1_ON();  P1_2_OFF(); }
void Ampel1_gelb()		{ P1_0_OFF(); P1_1_ON();  P1_2_OFF(); }
void Ampel1_gruen()		{ P1_0_OFF(); P1_1_OFF(); P1_2_ON(); }

void Ampel2_rot()		{ P1_4_ON();  P1_5_OFF(); }
void Ampel2_rotgelb()	{ P1_4_ON();  P1_5_ON();  }
void Ampel2_gelb()		{ P1_4_OFF(); P1_5_ON();  }
void Ampel2_leer()		{ P1_4_OFF(); P1_5_OFF(); }

void FussgAmpel_rot()	{ P1_6_ON();  P1_7_OFF(); }
void FussgAmpel_gruen()	{ P1_6_OFF(); P1_7_ON();  }

void ShowState(unsigned char state)
{
	P1OUT &= 0x0F;			// reset Bits 7,6,5,4,-,-,-,-
	switch(state)
	{
		case ALLES_STOP1	:	Ampel1_rot();		Ampel2_rot();		FussgAmpel_rot();  	break;
		case Horiz_RotGelb	:	Ampel1_rotgelb();	Ampel2_rot();		FussgAmpel_rot();	break;
		case Horiz_Gruen	:	Ampel1_gruen();		Ampel2_rot();		FussgAmpel_rot();	break;
		case Horiz_Gelb		:	Ampel1_gelb();		Ampel2_rot();		FussgAmpel_rot();	break;
		case ALLES_STOP2 	:	Ampel1_rot();		Ampel2_rot();		FussgAmpel_rot();	break;
		case Vert_RotGelb 	:	Ampel1_rot();		Ampel2_rotgelb();	FussgAmpel_rot();	break;
		case Vert_Leer		:	Ampel1_rot();		Ampel2_leer();		FussgAmpel_rot();	break;
		case Vert_Gelb		:	Ampel1_rot();		Ampel2_gelb();		FussgAmpel_rot();	break;
		case Fussg_Gruen1	:	Ampel1_rot();		Ampel2_rot();		FussgAmpel_gruen();	break;
		case Fussg_Gruen2	:	Ampel1_rot();		Ampel2_rot();		FussgAmpel_gruen();	break;
		default: break;
	}
}



// interrupt handler for the S2 button (the button on the board, see notes on the board)
//
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void)
{
	  ped_request = 1;
	  P1IFG = 0x00;
}


/*
 *  ======== Watchdog Timer Interval Interrupt Handler Generation ========
 */
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR_HOOK(void)
{
	system_tick_count--;
	if (system_tick_count == 0)
	   {
		system_tick_count=TIMESTEP_STATEMACHINE;
		performNextStep=1;
	   }
}

