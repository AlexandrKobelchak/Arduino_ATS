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

DS3231 g_clock;
volatile int g_bFlag = 0;
const int g_time_value = 34285; //Preload timer value (34285 for 0.5 seconds)

// процедура обработки прерывания переполнения счетчика
ISR(TIMER1_OVF_vect)         
{
    TCNT1 = g_time_value;    // set preload timer
  
    cli();                   //запрещаем прерывания	
    g_bFlag = !g_bFlag;
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

// the setup function runs once when you press reset or power the board
void setup() {

    setTimerInterrupt();
    sleep_enable();
    Serial.begin(9600);
    DDRB |= (1 << 5);//= 0xFF;
}

// the loop function runs over and over again until power down or reset
void loop() {
  
    sleep_cpu();

    if (g_bFlag)
        PORTB |= (1 << 5);
    else
        PORTB &= ~(1 << 5);

  
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
