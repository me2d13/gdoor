/*
 * com.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_COM_H_
#define SRC_COM_H_


#define IN_BUFFER_LENGTH 50

#define WHOAMI "GDOOR"
#define SUBSCRIBE_TOPIC "/garage/ard1/cmd/#"

#define MESSAGE_SEPARATOR_CHAR 30

void setupCom();
void sendHelloAndCheckAnswer();
int readSerialStringToBuffer();
void parseReceivedBufferToParts();
void checkHelloAnswer();
boolean compareReceivedTopic(char *arg);
boolean compareReceivedPayload(char *arg);
boolean compareStr(char *str1, char *str2);
void orderMessages();
boolean isConnected();
void checkAndProcessMessage();
void sendMessageInt(char* topic, int value);
void sendMessageIntInt(char* topic, int value1, int value2);
void sendMessageString(char* topic, char* value);
char *getPayload();
boolean isTwoPartsPayload(char *firstPart, char *secondPart);


#endif /* SRC_COM_H_ */
