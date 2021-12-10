#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>
#include <WString.h>

extern volatile bool g_bLedFlag;
extern LiquidCrystal_I2C  lcd;
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
    lcd.print(str);


    lcd.setCursor(10, 0);
    lcd.print("/^\\");

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