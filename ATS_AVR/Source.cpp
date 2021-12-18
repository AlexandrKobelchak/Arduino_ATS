#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>
#include <WString.h>

#include "Plot.h"
#include "EnergyState.h"

extern volatile bool g_bLedFlag;
extern  LiquidCrystal_I2C  lcd;
extern int g_lcdWidth;
extern DS3231 g_clock;


void initLcd() {
    
    lcd.init();
    initPlot();
}


void initPlot() {
    // необходимые символы для работы
    // создано в http://maxpromer.github.io/LCD-Character-Creator/
    byte row8[8] = { 0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111 };
    byte row7[8] = { 0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111 };
    byte row6[8] = { 0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111 };
    byte row5[8] = { 0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111 };
    byte row4[8] = { 0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111 };
    byte row3[8] = { 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111 };
    byte row2[8] = { 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111 };
    byte row1[8] = { 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111 };

    lcd.createChar(0, row8);
    lcd.createChar(1, row1);
    lcd.createChar(2, row2);
    lcd.createChar(3, row3);
    lcd.createChar(4, row4);
    lcd.createChar(5, row5);
    lcd.createChar(6, row6);
    lcd.createChar(7, row7);
}

void showAnimation() {
    
    lcd.setCursor(0, 1);
    static int tick = 0;
}

void showProgress() {

    lcd.setCursor(0, 1);
    static int tick = 0;
    for (int i = 0; i <= tick; ++i) {
        lcd.write(0);
    }
    for (int i = tick+1; i < g_lcdWidth; ++i) {
        lcd.print(' ');
    }
    ++tick;
    if (tick == g_lcdWidth) {
        tick = 0;
    }
}

void showEnergyState(energyState state) {

    lcd.setCursor(10, 0);
    switch (state)
    {
    case EXTERN:
        lcd.print("EXTERN");
        break; 
    case STARTING:
        lcd.print(" START");
        break;
    case DIESEL:
        lcd.print("DIESEL");
        break;   
    case ERROR:
        lcd.print(" ERROR");
        break;
    }
}

void showTime() {
 
    static char zn = ':';
    static bool century = false;
    static bool h12Flag;
    static bool pmFlag;
   
    zn = zn == ':' ? ' ' : ':';
    int hours = g_clock.getHour(h12Flag, pmFlag);
    int minutes = g_clock.getMinute();
    int seconds = g_clock.getSecond();
    String str;
    if(hours < 10)
        str.concat(' ');
    str.concat(hours);
    str.concat(zn);
    if (minutes < 10)
        str.concat('0');
    str.concat(minutes);
    str.concat(zn);
    if (seconds < 10)
        str.concat('0');
    str.concat(seconds);

    lcd.setCursor(0, 0);
    lcd.setBacklight(255);
    lcd.print(str);
}