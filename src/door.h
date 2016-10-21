/*
 * door.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_DOOR_H_
#define SRC_DOOR_H_

#define GDOORPIN 9
#define HALLPINOPEN 3
#define HALLPINCLOSED 2

#define GDOOR_COMMAND_TOPIC "/garage/ard1/command/door"
#define GDOOR_STATUS_TOPIC "/garage/ard1/status/door"

#define OPEN_STATUS_STRING "OPENED"
#define CLOSE_STATUS_STRING "CLOSED"
#define BETWEEN_STATUS_STRING "BETWEEN"

#define PUSH_MS 400


void processDoorCommand();
void setupDoor();
void pushGarageDoorButton();
void tickDoors();
void sendGarageDoorStatus();

#endif /* SRC_DOOR_H_ */
