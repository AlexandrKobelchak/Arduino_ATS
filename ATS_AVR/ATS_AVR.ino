/*
 Name:		ATS_AVR.ino
 Created:	12/10/2021 10:22:21 AM
 Author:	kobel
*/

#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>

#include "Plot.h"

int g_lcdWidth = 16;
const int g_lcgHeight = 2;

const int g_time_value = 34285; //Preload timer value (34285 for 0.5 seconds)

volatile bool g_bLedFlag = false;
volatile bool g_bActionFlag = false;


LiquidCrystal_I2C lcd(0x27 /*0x3F*/, g_lcdWidth, g_lcgHeight);

void showTime();


// процедура обработки прерывания переполнения счетчика
ISR(TIMER1_OVF_vect)         
{ 
    cli();                   //запрещаем прерывания	

    TCNT1 = g_time_value;    // set preload timer
    g_bLedFlag = !g_bLedFlag;
    g_bActionFlag = true;

    sei();                   //разрешаем прерывания
}


void setTimerInterrupt() {

    cli();                    //запрещаем прерывания	
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = g_time_value;     // set preload timer
    TCCR1B |= (1 << CS12);    // 256 prescaler (коэффициент деления предделителя)
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt ISR (разрешаем вызов процедуры обработки прерывания переполнения счетчика)
    sei();                    //разрешаем прерывания
}

extern DS3231 g_clock;

// the setup function runs once when you press reset or power the board
void setup() {   

    lcd.init(); 
    void initPlot();
    setTimerInterrupt();
    sleep_enable();
    Serial.begin(9600);
    DDRB |= (1 << 5);//= 0xFF;
}

// the loop function runs over and over again until power down or reset
void loop() {
  
    sleep_cpu();

    if (g_bActionFlag) {
        
        g_bActionFlag = false;
        
        showTime();

        //blink led:
        if (g_bLedFlag)
            PORTB |= (1 << 5);
        else
            PORTB &= ~(1 << 5);
    }
}

