/*
 * lcd.h
 *
 *  Created on: 23/02/2011
 *      Author: NS
 */

#ifndef POT_H_
#define POT_H_

INT8U get_pot_value(void);
/*****************************************************************************
*   Function : Returns the value of the POT. 0-100.
*****************************************************************************/

void pot_task(void);
/*****************************************************************************
*   Function : Called every 10ms. Gets the value of the Pot.
*****************************************************************************/

void init_pot(void);
/*****************************************************************************
*   Function : Initializes the POT & ADC.
*****************************************************************************/


#endif /* POT_H_ */
