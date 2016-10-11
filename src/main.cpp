#include "Arduino.h"

#include "main.h"
#include "com.h"
#include "led.h"
#include "door.h"
#include "log.h"
#include "audio.h"
#include "temperature.h"
#include "power.h"

#define UNIT_INDEX_DOOR 0
#define UNIT_INDEX_LED 1
#define UNIT_INDEX_AUDIO 2
#define UNIT_INDEX_TEMPERATURE 3
#define UNIT_INDEX_POWER 4
char *cUnits[NUMBER_OF_UNITS] = { GDOOR_COMMAND_TOPIC, LED_CEIL_COMMAND_TOPIC,
		AUDIO_COMMAND_TOPIC, TEMPERATURE_COMMAND_TOPIC, AC_POWER_COMMAND_TOPIC };

void setup() {
	setupCom();
	setupDoor();
	setupAudio();
	setupLed();
	setupTemperature();
	setupPower();
}

void loop() {
	if (isConnected()) {
		checkAndProcessMessage();
		tickDoors();
		tickLed();
		tickAudio();
		tickPower();
		delay(50);
	} else {
		sendHelloAndCheckAnswer();
		delay(5000);
	}
}

void processCommand() {
	for (int i = 0; i < NUMBER_OF_UNITS; i++) {
		if (compareReceivedTopic(cUnits[i])) {
			switch (i) {
			case UNIT_INDEX_DOOR:
				processDoorCommand();
				break;
			case UNIT_INDEX_LED:
				processLedCommand();
				break;
			case UNIT_INDEX_AUDIO:
				processAudioCommand();
				break;
			case UNIT_INDEX_TEMPERATURE:
				processTemperature();
				break;
			case UNIT_INDEX_POWER:
				processPowerCommand();
				break;
			default:
				debug("Unknown command");
			}
		}
	}
}

void processStatus() {

}

char *getUnitName(int index) {
	return cUnits[index];
}
