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
char *gTopic;
char *gPayload;

void setupCom() {
	Serial.begin(9600);
	gBufferLength = 0;
}

void sendHelloAndCheckAnswer() {
	debug("sending HELLO to tcpardu...");
	Serial.print("HELLO\n");
	int numRead = readSerialStringToBuffer();
	if (numRead > 0) {
		checkHelloAnswer();
	}
}

int readSerialStringToBuffer() {
	while (Serial.available() > 0) {
		if (gBufferLength + 1 == IN_BUFFER_LENGTH) {
			// overflow
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
			debugStr("Received raw message before parsing: ", gSerialInput);
			debugInt("Raw message length is ", gBufferLength);

			parseReceivedBufferToParts();
			char spfBuffer[200];
			sprintf(spfBuffer,
					"%s received message type [%s] topic [%s] payload [%s].",
					WHOAMI, gMessageType == NULL ? "" : gMessageType,
					gTopic == NULL ? "" : gTopic,
					gPayload == NULL ? "" : gPayload);
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
	gTopic = NULL;
	gPayload = NULL;
	int i = 0;
	for (int part = 0; part < 3; part++) {
		if (gSerialInput[i] == 0)
			return;
		if (part == 0) {
			gMessageType = gSerialInput;
		} else if (part == 1) {
			gTopic = gSerialInput + i;
		} else if (part == 2) {
			gPayload = gSerialInput + i;
		}
		while (gSerialInput[i] != 0 && i < IN_BUFFER_LENGTH) {
			if (gSerialInput[i] == ':' && part < 2) {
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
		debugStr(
				"ARDUINO got valid TcpArdu response, sending subscribe request. The arduino is ",
				WHOAMI);
		doubleBeep();
		orderMessages();
	}
}

boolean compareReceivedTopic(char *arg) {
	return compareStr(arg, gTopic);
}

boolean compareReceivedPayload(char *arg) {
	return compareStr(arg, gPayload);
}

boolean isTwoPartsPayload(char *firstPart, char *secondPart) {
	int i = 0;
	int secondPartIndex = 0;
	while (gPayload[i] != 0 && i < IN_BUFFER_LENGTH) {
		if (gPayload[i] == ':') {
			if (secondPartIndex > 0) {
				return 0;
			}
			secondPartIndex = ++i + 1;
		}
		i++;
	}
	if (secondPartIndex > 0) {
		strncpy(firstPart, gPayload, secondPartIndex);
		firstPart[secondPartIndex - 2] = 0;
		strcpy(secondPart, gPayload + secondPartIndex - 1);
		//debugStr("1st part ", firstPart);
		//debugStr("2nd part ", secondPart);
		return 1;
	} else {
		return 0;
	}
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
	Serial.print("MS:");
	Serial.print(SUBSCRIBE_TOPIC);
	Serial.print("\n");
}

void checkAndProcessMessage() {
	int numRead = readSerialStringToBuffer();
	if (numRead > 0 && gMessageType != NULL && gTopic != NULL
			&& gPayload != NULL) {
		if (compareStr("MM", gMessageType)) {
			processCommand();
		} else {
			debug("Wrong message");
		}
	}
}

void sendMessageInt(char* topic, int value) {
	Serial.print("MP:");
	Serial.print(topic);
	Serial.print(":");
	Serial.println(value);
}

void sendMessageIntInt(char* topic, int value1, int value2) {
	Serial.print("MP:");
	Serial.print(topic);
	Serial.print(":");
	Serial.print(value1);
	Serial.print(":");
	Serial.println(value2);
}

void sendMessageString(char* topic, char* value) {
	Serial.print("MP:");
	Serial.print(topic);
	Serial.print(":");
	Serial.println(value);
}

boolean isConnected() {
	return gConnected;
}

char *getPayload() {
	return gPayload;
}
