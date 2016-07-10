#include "MSP-EXP430G2_API.h"

void initialize_hardware()
{
	WDTCTL = WDTPW + WDTHOLD; //Stop the WDT to prevent reset
	P1DIR = BIT0 + BIT1 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	//P1IE |= BIT3; // P1.3 interrupt enabled
	//P1IFG &= ~BIT3; // P1.3 IFG cleared
	//WDTCTL = WDT_ADLY_16;
	//IE1 |= WDTIE;
}

void P1_0_ON() { P1OUT |= 0x01; }
void P1_1_ON() { P1OUT |= 0x02; }
void P1_2_ON() { P1OUT |= 0x04; }
void P1_3_ON() { P1OUT |= 0x08; }
void P1_4_ON() { P1OUT |= 0x10; }
void P1_5_ON() { P1OUT |= 0x20; }
void P1_6_ON() { P1OUT |= 0x40; }
void P1_7_ON() { P1OUT |= 0x80; }

void P1_0_OFF() { P1OUT &= 0xfe; } // 1111 1110
void P1_1_OFF() { P1OUT &= 0xfd; } // 1111 1101
void P1_2_OFF() { P1OUT &= 0xfb; } // 1111 1011
void P1_3_OFF() { P1OUT &= 0xf7; } // 1111 0111
void P1_4_OFF() { P1OUT &= 0xef; } // 1110 1111
void P1_5_OFF() { P1OUT &= 0xdf; } // 1101 1111
void P1_6_OFF() { P1OUT &= 0xbf; } // 1011 1111
void P1_7_OFF() { P1OUT &= 0x7f; } // 0111 1111

void P1_all_OFF()
{
	P1OUT = 0x00;
}

