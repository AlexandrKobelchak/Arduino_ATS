#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>
#include <WString.h>

#include "Plot.h"

extern volatile bool g_bLedFlag;
extern LiquidCrystal_I2C  lcd;
extern int g_lcdWidth;
DS3231 g_clock;

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

    int n = (g_lcdWidth == 20 ? 20 : 15);
    if (seconds % n==0) {
        lcd.setCursor(0, 1);
        lcd.print("                    ");
    }
    lcd.setCursor(0, 1);
    for (int i = 0; i < seconds % n; ++i) {
        
        lcd.setCursor(i % n, 1);
        lcd.write(0);
    }


    lcd.setCursor(10, 0);
    if(minutes % 2) 
        lcd.print("DIESEL");
    else 
        lcd.print("EXTERN");

    //Serial.print(g_clock.getYear(), DEC);
    //Serial.print("-");
    //Serial.print(g_clock.getMonth(century), DEC);
    //Serial.print("-");
    //Serial.print(g_clock.getDate(), DEC);
    //Serial.print(" ");
    //Serial.print(g_clock.getHour(h12Flag, pmFlag), DEC); //24-hr
    //Serial.print(":");
    //Serial.print(g_clock.getMinute(), DEC);
    //Serial.print(":");
    //Serial.print(g_clock.getSecond(), DEC);

    //Serial.print(" ");
    //Serial.println(g_clock.getTemperature(), DEC);
}