/*
 * door.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_DOOR_H_
#define SRC_DOOR_H_

#define GDOORPIN 9
#define HALLPINOPEN 2
#define HALLPINCLOSED 3

#define GDOOR_UNIT_NAME "GA0DOOR"

#define PUSH_MS 400


void processDoorCommand();
void setupDoor();
void pushGarageDoorButton();
void tickDoors();

#endif /* SRC_DOOR_H_ */