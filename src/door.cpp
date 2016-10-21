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

int gHallOpen = HIGH; // high means no magnetic field
int gHallClosed = HIGH;

long gButtonDownTime = 0;

void setupDoor() {
	  pinMode(HALLPINOPEN, INPUT);
	  pinMode(HALLPINCLOSED, INPUT);
	  pinMode(GDOORPIN, OUTPUT);
	  digitalWrite(GDOORPIN, HIGH); // pin is inverted
}

void processDoorCommand() {
	  if (compareReceivedPayload("push")) {
		  pushGarageDoorButton();
	  } else if (compareReceivedPayload("get")) {
		  sendGarageDoorStatus();
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
		sendGarageDoorStatus();
	}
	if (gButtonDownTime != 0 && gButtonDownTime + PUSH_MS < millis()) {
		digitalWrite(GDOORPIN, HIGH);
		debugInt("Garage button relay OFF at ", millis());
		gButtonDownTime = 0;
	}
}

void sendGarageDoorStatus() {
	if (gHallOpen && gHallClosed) {
		sendMessageString(GDOOR_STATUS_TOPIC, BETWEEN_STATUS_STRING);
	} else if (!gHallOpen) {
		sendMessageString(GDOOR_STATUS_TOPIC, OPEN_STATUS_STRING);
	} else if (!gHallClosed) {
		sendMessageString(GDOOR_STATUS_TOPIC, CLOSE_STATUS_STRING);
	} else {
		sendMessageString(GDOOR_STATUS_TOPIC, "ERROR");
	}
}
