#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>



DS3231 g_clock;

void showTime() {

    bool century = false;
    bool h12Flag;
    bool pmFlag;



    Serial.print(g_clock.getYear(), DEC);
    Serial.print("-");
    Serial.print(g_clock.getMonth(century), DEC);
    Serial.print("-");
    Serial.print(g_clock.getDate(), DEC);
    Serial.print(" ");
    Serial.print(g_clock.getHour(h12Flag, pmFlag), DEC); //24-hr
    Serial.print(":");
    Serial.print(g_clock.getMinute(), DEC);
    Serial.print(":");
    Serial.print(g_clock.getSecond(), DEC);

    Serial.print(" ");
    Serial.println(g_clock.getTemperature(), DEC);
}