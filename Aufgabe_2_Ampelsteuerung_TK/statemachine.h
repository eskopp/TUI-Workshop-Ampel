#if !defined(statemachine_header)
#define statemachine_header

//
// states
//
#define ALLES_STOP1			1
#define Horiz_RotGelb		2
#define Horiz_Gruen			3
#define Horiz_Gelb			4
#define ALLES_STOP2			5
#define Vert_RotGelb		6
#define Vert_Leer			7
#define Vert_Gelb			8
#define Fussg_Gruen1		9
#define Fussg_Gruen2		10
#define S_FINAL				99

//
// actions
//
#define A_NOACTION				0
#define A_SHOWSTATE				1
#define A_SET_PED_DELAY			2
#define A_DEC_PED_WAIT_CYCLES 	3

//
// guards
//
#define G_PEDREQUEST_TRUE		100
#define G_NOGUARD				101
#define G_PED_DELAY_NOT_ENDED	102

#define STATE		0
#define EVENT		1
#define NEXT_STATE	2
#define ACTION		3
#define GUARD		4

void Do_Step(unsigned char byte);
unsigned char checkGuard(unsigned char guard);
void performAction(unsigned char action);
void init_statemachine();

#endif

