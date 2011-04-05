/*****************************************************************************
* Odense University College of Enginerring
* Embedded C Programming (ECP)
*
* MODULENAME.: cpu.c
*
* PROJECT....: ECP
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 050128  KA    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "inc/lm3s6965.h"
#include "../inc/emp_type.h"
//#include "../inc/glob_def.h"
#include "../inc/binary.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/



void init_spi()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT8U dummy;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD | SYSCTL_RCGC2_GPIOG | SYSCTL_RCGC2_GPIOF; // Enable the port for the red LED
	dummy = SYSCTL_RCGC2_R;

	SET_BIT(GPIO_PORTD_DIR_R, RED_LED_PIN);
	SET_BIT(GPIO_PORTD_DEN_R, RED_LED_PIN);
	SET_BIT(GPIO_PORTG_DIR_R, GREEN_LED_PIN);
	SET_BIT(GPIO_PORTG_DEN_R, GREEN_LED_PIN);
	SET_BIT(GPIO_PORTG_DIR_R, YELLOW_LED_PIN);
	SET_BIT(GPIO_PORTG_DEN_R, YELLOW_LED_PIN);
	SET_BIT(GPIO_PORTF_DIR_R, STATUS_LED_PIN);
	SET_BIT(GPIO_PORTF_DEN_R, STATUS_LED_PIN);

	led_red_off();
	led_yellow_off();
	led_green_off();
	led_status_off();
}

/****************************** End Of Module *******************************/
