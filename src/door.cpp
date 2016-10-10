/*
 * door.c
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#include "Arduino.h"
#include "door.h"
#include "log.h"
#include "com.h"

int gHallOpen = LOW;
int gHallClosed = LOW;

long gButtonDownTime = 0;

void setupDoor() {
	  pinMode(HALLPINOPEN, INPUT);
	  pinMode(HALLPINCLOSED, INPUT);
	  pinMode(GDOORPIN, OUTPUT);
	  digitalWrite(GDOORPIN, HIGH); // pin is inverted
}

void processDoorCommand() {
	  if (compareReceivedTopic("PUSH")) {
		  pushGarageDoorButton();
	  } else {
	    debug("Unknown DOOR command (use PUSH)");
	  }
}

void pushGarageDoorButton() {
	if (gButtonDownTime == 0) {
		digitalWrite(GDOORPIN, LOW);
		gButtonDownTime = millis();
		debugInt("Garage button relay ON at ", gButtonDownTime);
	}
}

void tickDoors() {
	int lHallOpen = digitalRead(HALLPINOPEN);
	int lHallClosed = digitalRead(HALLPINCLOSED);
	if (lHallClosed != gHallClosed || lHallOpen != gHallOpen) {
		gHallClosed = lHallClosed;
		gHallOpen = lHallOpen;
		int status = (gHallOpen ? 1 : 0) + (gHallClosed ? 2 : 0);
		sendMessageInt(GDOOR_UNIT_NAME, status);
	}
	if (gButtonDownTime != 0 && gButtonDownTime + PUSH_MS < millis()) {
		digitalWrite(GDOORPIN, HIGH);
		debugInt("Garage button relay OFF at ", millis());
		gButtonDownTime = 0;
	}
}

