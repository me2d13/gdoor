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

#define MESSAGE_SEPARATOR_CHAR '#'

int readSerialStringToBuffer();
void sendHelloAndCheckAnswer();
void parseReceivedBufferToParts();
void checkHelloAnswer();
boolean compareReceivedCommand(char *arg);
boolean compareReceivedTo(char *arg);
boolean compareStr(char *str1, char *str2);
boolean isConnected();
void orderMessages();
void checkAndProcessMessage();
void sendStatusInt(char *unit, int value);
void sendStatusIntInt(char* unit, int value1, int value2);
void sendStatusString(char *unit, char *value);
void processCommand();
void processStatus();
void setupCom();

char *getComValue();



#endif /* SRC_COM_H_ */
