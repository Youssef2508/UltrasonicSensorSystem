/******************************************************************************
 *  Car Parking Sensor System
 *
 *  Description: Main application file for car parking sensor using ATmega32,
 *  ultrasonic sensor, LCD display, LEDs, and buzzer.
 *
 *  Created on: Oct 9, 2024
 *  Author: Youssef Hassan
 *******************************************************************************/

#include "lcd.h"
#include "ultrasonic.h"
#include "led_driver.h"
#include "buzzer.h"
#include <util/delay.h>
#include <avr/io.h> /* To use the SREG register */

volatile unsigned char buzzerTriggered = 0; // Flag to check if the buzzer triggered

int main(void) {
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

    /* Initialize all the peripherals */
    LCD_init();             // Initialize the LCD display
    Ultrasonic_init();      // Initialize the ultrasonic sensor
    LEDS_init();            // Initialize the LEDs (Red, Green, Blue)
    Buzzer_init();          // Initialize the buzzer

    uint16 distance;        // Variable to store the distance measured by the ultrasonic sensor

    /* Main loop */
    while (1) {
        /* Read distance from the ultrasonic sensor */
        distance = Ultrasonic_readDistance();

        /* Display the distance on the LCD */
        LCD_displayStringRowColumn(0, 0, "Distance= ");  // Display "Distance ="
        if(distance >= 100){
        	LCD_intgerToString(distance);                // Display the measured distance
        	LCD_displayString("cm");                 	 // Display the unit "cm"
        }
        else if (distance >= 10){
        	LCD_intgerToString(distance);             	 // Display the measured distance
        	LCD_displayString(" cm");               	 // Display the unit "cm"
        }
        else{
        	LCD_intgerToString(distance);            	 // Display the measured distance
        	LCD_displayString("  cm");              	 // Display the unit "cm"
        }

        /* Handle distance-to-LED and buzzer mapping */
        if (distance <= 5) {
            /* Distance <= 5 cm: All LEDs flashing, Buzzer ON, LCD displays "Stop" */
            LCD_displayStringRowColumn(1, 6, "STOP!");
            LED_on(RED_LED);
            LED_on(GREEN_LED);
            LED_on(BLUE_LED);
            Buzzer_on();     // Buzzer ON
            buzzerTriggered = 1;
            _delay_ms(500);
            LED_off(RED_LED);
            LED_off(GREEN_LED);
            LED_off(BLUE_LED);
            _delay_ms(500);  // Flashing delay
        }
        else if (distance <= 10) {
            /* 6 cm <= Distance <= 10 cm: All LEDs ON, Buzzer OFF */
        	LCD_displayStringRowColumn(1, 6, "     ");
            LED_on(RED_LED);
            LED_on(GREEN_LED);
            LED_on(BLUE_LED);
            if(buzzerTriggered == 1){
            	Buzzer_off();  // Buzzer OFF
            	buzzerTriggered = 0;
            }
        }
        else if (distance <= 15) {
            /* 11 cm <= Distance <= 15 cm: Red and Green LEDs ON, Blue LED OFF */
        	LCD_displayStringRowColumn(1, 6, "     ");
            LED_on(RED_LED);
            LED_on(GREEN_LED);
            LED_off(BLUE_LED);
            if(buzzerTriggered == 1){
            	Buzzer_off();  // Buzzer OFF
            	buzzerTriggered = 0;
            }
        }
        else if (distance <= 20) {
            /* 16 cm <= Distance <= 20 cm: Only Red LED ON, others OFF */
        	LCD_displayStringRowColumn(1, 6, "     ");
            LED_on(RED_LED);
            LED_off(GREEN_LED);
            LED_off(BLUE_LED);
            if(buzzerTriggered == 1){
            	Buzzer_off();  // Buzzer OFF
            	buzzerTriggered = 0;
            }
        }
        else {
            /* Distance > 20 cm: All LEDs OFF, Buzzer OFF */
        	LCD_displayStringRowColumn(1, 6, "     ");
            LED_off(RED_LED);
            LED_off(GREEN_LED);
            LED_off(BLUE_LED);
            if(buzzerTriggered == 1){
            	Buzzer_off();  // Buzzer OFF
            	buzzerTriggered = 0;
            }
        }


    }

    return 0;
}
