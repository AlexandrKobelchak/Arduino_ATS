#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <Arduino.h>

#include "Plot.h"

extern LiquidCrystal_I2C  lcd;

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
