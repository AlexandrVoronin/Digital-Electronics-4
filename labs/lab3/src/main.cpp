#include <Arduino.h>

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5     // AVR pin where green LED is connected
#define BLINK_DELAY 500
#define BTN         PD5
#define LED_RED     PB4
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <gpio.h>          // GPIO library for AVR-GCC

int main(void)
{
    /* GREEN LED */
    GPIO_config_output(&DDRB, LED_GREEN);
    GPIO_write_low(&PORTB, LED_GREEN);

    /* RED LED */
    GPIO_config_output(&DDRB, LED_RED);
    GPIO_write_low(&PORTB, LED_RED);

    /* push button */
    GPIO_config_input_pullup(&DDRD, BTN);

    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(BLINK_DELAY);
        if (!GPIO_read(&PIND,BTN))
        {
          GPIO_toggle(&PORTB,LED_GREEN);//toggle leds
          GPIO_toggle(&PORTB,LED_RED);
        }
        if (GPIO_read(&PIND,BTN))
        {
          GPIO_write_low(&PORTB,LED_GREEN);//turn off if button isnt pushed
          GPIO_write_low(&PORTB,LED_RED);
        }

    }

    // Will never reach this
    return 0;
}