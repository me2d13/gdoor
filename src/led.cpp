/*
 * led.c
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#include "Arduino.h"
#include "led.h"
#include "com.h"
#include "log.h"

int gLedCurrentIntensity = 0;
int gLedTargetIntensity = 0;

void setupLed() {
	pinMode(LEDPIN, OUTPUT);
}

void tickLed() {
	if (gLedCurrentIntensity != gLedTargetIntensity) {
		if (gLedCurrentIntensity < gLedTargetIntensity) {
			gLedCurrentIntensity += LED_STEP;
			if (gLedCurrentIntensity > gLedTargetIntensity) {
				gLedCurrentIntensity = gLedTargetIntensity;
			}
		} else if (gLedCurrentIntensity > gLedTargetIntensity) {
			gLedCurrentIntensity -= LED_STEP;
			if (gLedCurrentIntensity < gLedTargetIntensity) {
				gLedCurrentIntensity = gLedTargetIntensity;
			}
		}
		debugInt("Setting current LED intensity to ", gLedCurrentIntensity);
		analogWrite(LEDPIN, gLedCurrentIntensity);
		if (gLedCurrentIntensity == gLedTargetIntensity) {
			sendMessageInt(LED_CEIL_UNIT_NAME, gLedCurrentIntensity);
		}
	}
}

void processLedCommand() {
	char firstPart[50]; //opening doors to crash this code
	char secondPart[50]; //opening doors to crash this code
	if (isTwoPartsPayload(firstPart, secondPart)) {
		if (compareStr(firstPart, "set")) {
			gLedTargetIntensity = atoi(secondPart);
		} else {
			debugStr("Unexpected LED command ", firstPart);
		}
	} else if (compareReceivedPayload("on")) {
		debug("Turning LEDs on");
		gLedTargetIntensity = 255;
	} else if (compareReceivedPayload("off")) {
		debug("Turning LEDs off");
		gLedTargetIntensity = 0;
	} else {
		debug("Unknown LED command");
	}
}

void setLedTargetIntensity(int targetIntensity) {
	gLedTargetIntensity = targetIntensity;
}
