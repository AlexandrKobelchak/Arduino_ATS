#pragma once
#include "EnergyState.h"
#include "stdafx.h"

enum inputState:uint8_t {
	
	INPUT_PIN_1 = 1, 
	INPUT_PIN_2 = 2,
	INPUT_PIN_3 = 4,
	INPUT_PIN_4 = 8,
	INPUT_PIN_5 = 16,
	INPUT_PIN_6 = 32,
	INPUT_PIN_7 = 64,
	INPUT_PIN_8 = 128,
};

enum commadBlockOut:uint8_t {
	
	RELEY_LITE_ON_OFF = 3,
	RELEY_SWITCH_ON_OFF = 2,	
	RELEY_ENGINE_START = 1,
	RELEY_ENGINE_OFF = 0,
};

void initLcd();
void showEnergyState(energyState state);
void showTime();
void showProgress();
void showAnimation();
void blinkLed();
void initCommandBlock();
void initInput();
uint8_t getInputState();
void setCommandBlockOn(commadBlockOut pin);
void setCommandBlockOff(commadBlockOut pin);
