#if !defined (MSPEXP430G2_API_h)
#define MSPEXP430G2_API_h

#include <msp430.h>

void initialize_hardware(void);

void P1_0_ON();
void P1_1_ON();
void P1_2_ON();
void P1_3_ON();
void P1_4_ON();
void P1_5_ON();
void P1_6_ON();
void P1_7_ON();

void P1_0_OFF();
void P1_1_OFF();
void P1_2_OFF();
void P1_3_OFF();
void P1_4_OFF();
void P1_5_OFF();
void P1_6_OFF();
void P1_7_OFF();

void P1_all_OFF();

#endif

