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
      sendStatusInt(LED_CEIL_UNIT_NAME, gLedCurrentIntensity);
    }
  }
}


void processLedCommand() {
  if (compareReceivedCommand("SET")) {
    if (getComValue() == NULL) {
      debug("Received LED set command with no value");
    } else {
      gLedTargetIntensity = atoi(getComValue());
    }
  } else if (compareReceivedCommand("ON")) {
	  gLedTargetIntensity = 255;
  } else if (compareReceivedCommand("OFF")) {
	  gLedTargetIntensity = 0;
  } else {
    debug("Unknown LED command");
  }
}

void setLedTargetIntensity(int targetIntensity) {
	gLedTargetIntensity = targetIntensity;
}
