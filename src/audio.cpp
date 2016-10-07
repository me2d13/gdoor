/*
 * audio.cpp
 *
 *  Created on: Apr 19, 2016
 *      Author: petr
 */

#include "Arduino.h"
#include "audio.h"
#include "log.h"
#include "com.h"

typedef struct
{
    long when;
    short value;
} AudioCommand;

AudioCommand gAudioQueue[10];
int gAudioQueueLength = 0;

void setupAudio() {
	pinMode(SIREN_PIN, OUTPUT);
	pinMode(BUZZER_PIN, OUTPUT);
}

void processAudioCommand() {
	  if (compareReceivedCommand("BEEP")) {
	    beep();
	  } else if (compareReceivedCommand("DOUBLEBEEP")) {
		  doubleBeep();
	  } else {
	    debug("Unknown audio command");
	  }
}

void tickAudio() {
	if (gAudioQueueLength > 0) {
		if (millis() > gAudioQueue->when) {
			// pop
			digitalWrite(BUZZER_PIN, gAudioQueue->value ? HIGH : LOW);
			for (int i = 1; i < gAudioQueueLength; i++) {
				gAudioQueue[i-1] = gAudioQueue[i];
			}
			gAudioQueueLength--;
		}
	}
}

void pushBeepFromQueuIndex(short index, long timeOffsetInMs) {
	gAudioQueue[index].when = millis() + timeOffsetInMs;
	gAudioQueue[index].value = 1;
	gAudioQueue[index+1].when = millis() + timeOffsetInMs + BEEP_LENGTH_MS;
	gAudioQueue[index+1].value = 0;
	gAudioQueueLength += 2;
}


void beep() {
	gAudioQueueLength = 0;
	pushBeepFromQueuIndex(0, 0);
}

void doubleBeep() {
	beep();
	pushBeepFromQueuIndex(2, 4*BEEP_LENGTH_MS);
}
