/*
 Name:		ATS_AVR.ino
 Created:	12/10/2021 10:22:21 AM
 Author:	kobel
*/

#include <Adafruit_MCP23008.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>
#include "Source.h"
#include "EnergyState.h"
#include "Plot.h"

int g_lcdWidth = 16;
const int g_lcgHeight = 2;

const int g_time_value = 34285; //Preload timer value (34285 for 0.5 seconds)

volatile bool g_bLedFlag = false;
volatile bool g_bActionFlag = false;


LiquidCrystal_I2C lcd(0x27 /*0x3F*/, g_lcdWidth, g_lcgHeight);
DS3231 g_clock;
Adafruit_MCP23008 g_CommandBlock;

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
    sei();                    // разрешаем прерывания
}



// the setup function runs once when you press reset or power the board
void setup() {   
    g_CommandBlock.begin(0);      // use default address 0
    g_CommandBlock.pinMode(0, OUTPUT);
    g_CommandBlock.pinMode(1, OUTPUT);
    g_CommandBlock.pinMode(2, OUTPUT);
    g_CommandBlock.pinMode(3, OUTPUT);

    initLcd();

    setTimerInterrupt();
    sleep_enable();
    //Serial.begin(9600);
    DDRB |= (1 << 5);//= 0xFF;
}

// the loop function runs over and over again until power down or reset
void loop() {
  
    sleep_cpu();

    static int mode = 0;

    if (g_bActionFlag) {
        
        g_bActionFlag = false;
        
        showTime();
        showProgress();
        showEnergyState(DIESEL);

        //blink led:
        if (g_bLedFlag)
            PORTB |= (1 << 5);
        else
            PORTB &= ~(1 << 5);
  
        static int counter = 0;
        if (counter++ == 3) {
            for (int i = 0; i < 4; ++i) {
                g_CommandBlock.digitalWrite(i, 0);
            }
            g_CommandBlock.digitalWrite(mode++, 1);
            if (mode == 4) mode = 0;
            
            counter = 0;
        }
      
    }
}

