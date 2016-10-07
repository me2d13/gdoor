/*
 * com.c
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */
#include "Arduino.h"
#include "com.h"
#include "log.h"
#include "main.h"
#include "audio.h"

boolean gConnected = false;

char gSerialInput[IN_BUFFER_LENGTH];
int gBufferLength;
char *gMessageType;
char *gFrom;
char *gTo;
char *gCommand;
char *gValue;

void setupCom() {
	Serial.begin(9600);
	gBufferLength = 0;
}

void sendHelloAndCheckAnswer() {
	Serial.print("HELLO\n");
	int numRead = readSerialStringToBuffer();
	if (numRead > 0) {
		checkHelloAnswer();
	}
}

int readSerialStringToBuffer() {
	while (Serial.available() > 0) {
		if (gBufferLength + 1 == IN_BUFFER_LENGTH) {
			break;
		}
		gSerialInput[gBufferLength] = Serial.read();
		if (gSerialInput[gBufferLength] == MESSAGE_SEPARATOR_CHAR) {
			break;
		}
		gBufferLength++;
	}
	if (gSerialInput[gBufferLength] == MESSAGE_SEPARATOR_CHAR) {
		gSerialInput[gBufferLength] = 0;
		if (gBufferLength > 0) {
			debugStr("Unparsed message: ", gSerialInput);

			parseReceivedBufferToParts();
			char spfBuffer[200];
			sprintf(spfBuffer,
					"%s received message type [%s] from [%s] to [%s] code [%s] value [%s].",
					WHOAMI, gMessageType == NULL ? "" : gMessageType,
					gFrom == NULL ? "" : gFrom, gTo == NULL ? "" : gTo,
					gCommand == NULL ? "" : gCommand,
					gValue == NULL ? "" : gValue);
			debug(spfBuffer);
		}
		int readBytes = gBufferLength;
		gBufferLength = 0;
		return readBytes;
	}
	return 0;
}

void parseReceivedBufferToParts() {
	gMessageType = NULL;
	gFrom = NULL;
	gTo = NULL;
	gCommand = NULL;
	gValue = NULL;
	int i = 0;
	for (int part = 0; part < 5; part++) {
		if (gSerialInput[i] == 0)
			return;
		if (part == 0) {
			gMessageType = gSerialInput;
		} else if (part == 1) {
			gFrom = gSerialInput + i;
		} else if (part == 2) {
			gTo = gSerialInput + i;
		} else if (part == 3) {
			gCommand = gSerialInput + i;
		} else if (part == 4) {
			gValue = gSerialInput + i;
		}
		while (gSerialInput[i] != 0) {
			if (gSerialInput[i] == ':') {
				gSerialInput[i] = 0;
				i++;
				break;
			}
			i++;
		}
	}
}

void checkHelloAnswer() {
	if (compareStr("OLLEH", gMessageType)) {
		gConnected = true;
		debug(WHOAMI);
		doubleBeep();
		orderMessages();
	}
}

boolean compareReceivedTo(char *arg) {
	return compareStr(arg, gTo);
}

boolean compareReceivedCommand(char *arg) {
	return compareStr(arg, gCommand);
}

boolean compareStr(char *str1, char *str2) {
	int i = 0;
	while (str1[i] != 0) {
		if (str1[i] != str2[i] || str2[i] == 0) {
			return false;
		}
		i++;
	}
	return str2[i] == 0;
}

void orderMessages() {
	Serial.print("CMD:");
	Serial.print(WHOAMI);
	Serial.print(":MASTER:ORDER_COMMAND_FOR");
	for (int i = 0; i < NUMBER_OF_UNITS; i++) {
		Serial.print(":");
		Serial.print(getUnitName(i));
	}
	Serial.print("\n");
}

void checkAndProcessMessage() {
	int numRead = readSerialStringToBuffer();
	if (numRead
			> 0&& gMessageType != NULL && gFrom != NULL && gTo != NULL && gCommand != NULL) {
		if (compareStr("CMD", gMessageType)) {
			processCommand();
		} else if (compareStr("STS", gMessageType)) {
			processStatus();
		} else {
			debug("Wrong message");
		}
	}
}

void sendStatusInt(char* unit, int value) {
	Serial.print("STS:");
	Serial.print(unit);
	Serial.print("::");
	Serial.println(value);
}

void sendStatusIntInt(char* unit, int value1, int value2) {
	Serial.print("STS:");
	Serial.print(unit);
	Serial.print("::");
	Serial.print(value1);
	Serial.print(":");
	Serial.println(value2);
}

void sendStatusString(char* unit, char* value) {
	Serial.print(unit);
	Serial.print(':');
	Serial.println(value);
}

char *getComValue() {
	return gValue;
}

boolean isConnected() {
	return gConnected;
}
