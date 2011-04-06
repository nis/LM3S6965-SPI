/**
 * Name        : main.c
 * Version     :
 * Description : main definition for FreeRTOS application
 */

/*
 * FreeRTOS includes
 */
#include "FreeRTOS.h"
#include "Task.h"
#include "queue.h"
#include "semphr.h"
#include "cpu/cpu.h"
#include "led/led.h"
#include "spi/spi.h"
#include "inc/lm3s6965.h"
#include "lcd/lcd.h"
//#include "pot/pot.h"
#include "buttons/buttons.h"

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE

void __error__(char *pcFilename, unsigned long ulLine) {
}

static void setupHardware(void) {
	// TODO: Put hardware configuration and initialisation in here
	disable_global_int();
	clk_system_init();
	init_leds();
	//init_pot();
	init_buttons();
	init_spi();
	init_lcd_write_task();
	enable_global_int();
	// Warning: If you do not initialize the hardware clock, the timings will be inaccurate
}

/**
 * Simple task that just toggles between to states
 */
void vUserTask1(void *pvParameters) {

	while (1) {
		
		button_task();
		
		INT8U up_clicks = get_up_clicks();
		//INT8U down_clicks = get_down_clicks();
		
		if(up_clicks)
		{
			led_all_toggle();
		}
		
		vTaskDelay(20);
	}
}

/**
 * Alive task. Blinks the status LED 4 at 4Hz.
 */
void vUserTask2(void *pvParameters) {
	while (1) {
		led_status_toggle();
		vTaskDelay(250) ;
	}
}

/**
 * Counter sent out via SPI.
 */
void vUserTask3(void *pvParameters) {
	INT8U counter = 0;
	
	while (1) {
		SSI0_DR_R = counter;
		counter++;
		vTaskDelay(250) ;
	}
}

/**
 * LCD task
 */
void vUserTask4(void *pvParameters) {
	INT8U counter = 0;
	
	while (1) {
		counter++;
		
		INT8U c1 = int_to_ascii((counter / 100) % 10);
		INT8U c2 = int_to_ascii((counter / 10) % 10);
		INT8U c3 = int_to_ascii((counter / 1) % 10);
		
		if(c1 == 0x30)
		{
			c1 = 0x20;
			if(c2 == 0x30)
			{
				c2 = 0x20;
			}
		}
		
		lcd_add_char_to_buffer(5, 0, c1);
		lcd_add_char_to_buffer(6, 0, c2);
		lcd_add_char_to_buffer(7, 0, c3);
		
		lcd_write_task();
		
		vTaskDelay(10) ;
	}
}

/**
 * Program entry point 
 */
int main(void) {
	setupHardware();

	/* 
	 * Start the tasks defined within this file/specific to this demo. 
	 */
	xTaskCreate( vUserTask1, ( signed portCHAR * ) "Task1", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( vUserTask2, ( signed portCHAR * ) "Task2", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( vUserTask3, ( signed portCHAR * ) "Task3", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( vUserTask4, ( signed portCHAR * ) "Task4", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	/* 
	 * Start the scheduler. 
	 */
	vTaskStartScheduler();

	/* 
	 * Will only get here if there was insufficient memory to create the idle task. 
	 */
	return 1;
}
