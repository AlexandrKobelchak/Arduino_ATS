/*
 Name:		ATS_AVR.ino
 Created:	12/10/2021 10:22:21 AM
 Author:	Alexandr Kobelchak
*/

#include <Adafruit_Sensor.h>
#include <Adafruit_MCP23008.h>
#include <DS3231.h>
#include <LiquidCrystal_I2C.h>
#include "stdafx.h"
#include "Source.h"
#include "EnergyState.h"
#include "Plot.h"

int g_lcdWidth = 8;
const int g_lcgHeight = 2;

const int g_time_value = 34285; //Preload timer value (34285 for 0.5 seconds)

volatile bool g_bLedFlag = false;
volatile bool g_bActionFlag = false;


LiquidCrystal_I2C lcd(0x27 /*0x3F*/, g_lcdWidth, g_lcgHeight);
DS3231 g_clock;
Adafruit_MCP23008 g_CommandBlock;

// ��������� ��������� ���������� ������������ ��������
ISR(TIMER1_OVF_vect)         
{ 
    cli();                   //��������� ����������	

    TCNT1 = g_time_value;    // set preload timer
    g_bLedFlag = !g_bLedFlag;
    g_bActionFlag = true;

    sei();                   //��������� ����������
}


void setTimerInterrupt() {

    cli();                    //��������� ����������	
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = g_time_value;     // set preload timer
    TCCR1B |= (1 << CS12);    // 256 prescaler (����������� ������� ������������)
    TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt ISR (��������� ����� ��������� ��������� ���������� ������������ ��������)
    sei();                    // ��������� ����������
}


// the setup function runs once when you press reset or power the board
void setup() {   

    initLcd();
    initCommandBlock();
    setTimerInterrupt();
    sleep_enable();    
    //Init LED 
    DDRB |= (1 << 5);//= 0xFF;
    wdt_enable(WDTO_2S); // ���������� ������ �������� �� ������� � 2 �������
    //Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
    sleep_cpu();
    static int mode = 0;

    if (g_bActionFlag) {
        
        wdt_reset(); // ���������� ���������� ������
        g_bActionFlag = false;
        
        showTime();
        showProgress();
        showEnergyState(DIESEL);

        blinkLed();
  
        static int counter = 0;
        if (counter++ == 3) {
            for (int i = 0; i < 4; ++i) {
                g_CommandBlock.digitalWrite(i, 0);
            }
            //g_CommandBlock.digitalWrite(mode++, 1);
            if (mode == 4) mode = 0;
            
            counter = 0;
        }
      
    }
}

