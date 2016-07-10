//#include <msp430.h>
#include <msp430g2553.h>
#include "MSP-EXP430G2_API.h"

unsigned int i = 0;                         // Initialize variables. This will keep count of how many cycles between LED toggles
unsigned int x=0;


void main(void)
{
	initialize_hardware();
	for (;;)                                  // This empty for-loop will cause the lines of code within to loop infinitely
	{
		switch(i)
		{
		case 0:
			P1_0_ON();
			i++;
			break;

		case 1:
			P1_all_OFF();
			P1_1_ON();
			i++;
			break;

		case 2:
			P1_all_OFF();
			P1_2_ON();
			i++;
			break;

		case 3:
			P1_all_OFF();
			P1_4_ON();
			i=0;
			break;

		default: break;
		}

		for(x=0; x< 60000; x++);    // Delay between LED toggles. This for-loop will run until the condition is met.
									//In this case, it will loop until the variable i increments to 20000.
	}
}
