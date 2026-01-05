#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "HD44780.hpp"
#include "libADC.hpp"
#include "uart_buffer.hpp"


#define OUTPUT_PORT PORTB
#define OUTPUT_DIR  DDRB
#define LED_GREEN   (1 << PB2)
#define LED_BLUE    (1 << PB3)
#define LED_RED     (1 << PB4)
#define BUZZER_PIN  (1 << PB5)


float ADC_to_Temperature(int adc_value) {

    const float BETA = 3950.0;      

    if (adc_value == 0) return -273.15;  

    float tempK = 1.0 / ( log(1.0 / (1023.0 / adc_value - 1.0)) / BETA + (1.0 / 298.15) );
    float tempC = tempK - 273.15;

    return tempC;
}



void Control_Temp(double temp) {

    OUTPUT_PORT &= ~(LED_GREEN | LED_BLUE | LED_RED | BUZZER_PIN);

    char uart_buffer[64];
    char lcd_buffer[32];

    if (temp >= 0 && temp <= 25) {

        OUTPUT_PORT |= LED_GREEN;

        sprintf(uart_buffer, "TEMPERATURE: %.2f C | NORMAL\r\n", temp);
        sprintf(lcd_buffer,  "T: %.1f C ", temp);

    } 
    else if (temp > 25 && temp <= 50) {

        OUTPUT_PORT |= (LED_GREEN | LED_BLUE);

        sprintf(uart_buffer, "TEMPERATURE: %.2f C | WARNING\r\n", temp);
        sprintf(lcd_buffer,  "T: %.1f C ", temp);

    } 
    else {

        OUTPUT_PORT |= (LED_GREEN | LED_BLUE | LED_RED | BUZZER_PIN);

        sprintf(uart_buffer, "TEMPERATURE: %.2f C | DANGER!\r\n", temp);
        sprintf(lcd_buffer,  "T: %.1f C ", temp);
    }

    LCD_GoTo(0, 1);
    LCD_WriteText(lcd_buffer);

    uart_send_string((uint8_t*)uart_buffer);
}



int main(void) {

    OUTPUT_DIR |= (LED_GREEN | LED_BLUE | LED_RED | BUZZER_PIN);

    ADC_Init();
    LCD_Initalize();
    uart_init(9600, 0);
    sei();

    int adc_value;
    double current_temp;

    while (1) {

        adc_value = ADC_conversion();        
        current_temp = ADC_to_Temperature(adc_value);   
        Control_Temp(current_temp);         

        _delay_ms(1000);
    }
}
