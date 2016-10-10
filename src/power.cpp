/*
 * power.cpp
 *
 *  Created on: May 7, 2016
 *      Author: petr
 */

#include "Arduino.h"
#include "power.h"
#include "com.h"
#include "log.h"

short gPowerStatus;

void tickPower(short explicitSend) {
	short lPowerStatus = digitalRead(AC_POWER_PIN);
	if (lPowerStatus != gPowerStatus) {
		gPowerStatus = lPowerStatus;
		debugInt("AC power changed to ", lPowerStatus);
		sendMessageInt(AC_POWER_UNIT_NAME, gPowerStatus);
	} else {
		if (explicitSend) {
			sendMessageInt(AC_POWER_UNIT_NAME, gPowerStatus);
		}
	}
}

void tickPower() {
	tickPower(0);
}

void processPowerCommand() {
	if (compareReceivedTopic("GET")) {
		tickPower(1);
	} else {
		debug("Unknown POWER command (use GET)");
	}
}

void setupPower() {
	pinMode(AC_POWER_PIN, INPUT);
	gPowerStatus = HIGH;
}

