#pragma once
#include "EnergyState.h"
#include "stdafx.h"

enum inputState:uint8_t {
	
	INPUT_LAN_PROTECTION_FAIL = 1, 
	INPUT_DIESEL_PROTECTION_FAIL = 2,
	INPUT_LAN_GOOD = 4,
	INPUT_DIESEL_GOOD = 8,
	INPUT_PIN_5_NOT_USED = 16,
	INPUT_PIN_6_NOT_USED = 32,
	INPUT_PIN_7_NOT_USED = 64,
	INPUT_PIN_8_NOT_USED = 128,
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
