//#include "statemachine_data.h"
#include "statemachine.h"

extern void ShowState(unsigned char);

//! The state transition table to be executed.
/*! This table holds all states and transitions to be executed.
 *
 * \image html Statechart.png
 * \image latex Statechart.png "My application" width=12cm
 *  Format:
 *
 *  <table border="1">
 *	<tr>
 *		<th>State</th>
 * 		<th>on_input_byte</th>
 *		<th>next_state</th>
 *		<th>action</th>
 *		<th>guard</th>
 *	</tr>
  *	<tr>
 *		<td>from this state</td>
 * 		<td>if this byte is received</td>
 *		<td>change to this state</td>
 *		<td>and execute this action</td>
 *	</tr>
 * </table>
 *
 * Example: \n
 *  { S_START,     'l',  S_LANGSAM,   M_PSTATE, G_NOGUARD} \n
 *
 *  means: if G_NOGUARD is true the statemachine is in state S_START
 *         and event 'l' was sent the statemachine changes
 *         to state S_LANGSAM and will perfom the action
 *         in correspondence to M_PSTATE
 *
 *   S_FINAL is an internal marker to identify the end of the table!
 */
const unsigned char statechart[][5] = {

	 { ALLES_STOP1,   'x',  Horiz_RotGelb, 	A_SHOWSTATE, 			G_NOGUARD},
	 { Horiz_RotGelb, 'x',  Horiz_Gruen,  	A_SHOWSTATE, 			G_NOGUARD},
	 { Horiz_Gruen,   'x',  Horiz_Gelb,  	A_SHOWSTATE, 			G_NOGUARD},
	 { Horiz_Gelb,    'x',  ALLES_STOP2,  	A_SHOWSTATE, 			G_NOGUARD},

	 { ALLES_STOP2,   'x',  Vert_RotGelb,  	A_SHOWSTATE, 			G_NOGUARD},
	 { Vert_RotGelb,  'x',  Vert_Leer,  	A_SHOWSTATE, 			G_NOGUARD},
	 { Vert_Leer,     'x',  Vert_Gelb,  	A_SHOWSTATE, 			G_NOGUARD},
	 { Vert_Gelb,     'x',  ALLES_STOP1, 	A_SHOWSTATE, 			G_NOGUARD},

	{ S_FINAL, 0, 0, 0, G_NOGUARD}
};

unsigned char current_state = ALLES_STOP1;				/*!< The global state.*/
unsigned char ped_request=0;
unsigned char ped_wait_cylces=0;

/*! \brief Process incoming bytes as modeled by a statechart.
 *  
 *  For each byte to trigger a transition this function searches a correspondence
 *  current state - byte sent in the statechart table and will upon success
 *  execute the FIRST FOUND entry in the table!
 *
 *  \param byte The byte to be processed.
 */
void Do_Step(unsigned char byte)
{
	int j=0;
	char process_only_first_matching_statechart_entry=1;

	// S_FINAL indicates the end of the statechart data structure!
	// iterate through all states in the statechart table: statechart
	//
	while(statechart[j][STATE]!=S_FINAL && process_only_first_matching_statechart_entry)
	{
		//
		//  if the current_state could react on the next byte
		//  "execute" what is in the statemachine
		//
		if( statechart[j][STATE] == current_state &&
			(  statechart[j][EVENT] == byte ) &&
			checkGuard(statechart[j][GUARD]) == 1 )
		{				
			// move to the next state
			current_state = statechart[j][NEXT_STATE];

			// perform an action
			//
			performAction(statechart[j][ACTION]);
			process_only_first_matching_statechart_entry=0;
		}
		j++;
	}
}

/*! \brief evaluate the guard condition
 *
 *  \param guard One of the pre-defined guards (see #defines in statemachine.h)
 */
unsigned char checkGuard(unsigned char guard)
{
	unsigned char retValue=0;
	switch(guard)
	{
	case G_NOGUARD :
					retValue=1; break;

	case G_PEDREQUEST_TRUE :						// in case the pedestrian request was "klicked"
					if(ped_request)					// this guard evaluates to TRUE in all other cases
					{ ped_request=0; retValue=1; }	// to FALSE
					else { retValue=0; }
					break;

	case G_PED_DELAY_NOT_ENDED:						// countdown for the pedestrian lights
					if(ped_wait_cylces>0)			// to ensure the road can be crossed
					{	retValue=1; }
					else { retValue=0; }
					break;

	default : retValue=0;
	}

	return retValue;
}

/*! \brief Execute the action defined in statemachine.h
 *
 *  \param action One of the pre-defined actions (see #defines in statemachine.h)
 */
void performAction(unsigned char action)
{
	switch(action)
	{
		case A_NOACTION	 :
			break;

		case A_SHOWSTATE :
			ShowState(current_state);
			break;

		case A_DEC_PED_WAIT_CYCLES :
			ped_wait_cylces--;
			break;

		case A_SET_PED_DELAY :
			// wait three cycles
			ShowState(current_state);
			ped_wait_cylces=3;
			break;

		default :
			break;
	}
}


