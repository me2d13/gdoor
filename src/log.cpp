/*
 * log.cpp
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#include "Arduino.h"

void debug(char *arg) {
  Serial.print("DEBUG:");
  Serial.println(arg);
}

void debugInt(char *arg, int value) {
  Serial.print("DEBUG:");
  Serial.print(arg);
  Serial.println(value);
}

void debugStr(char *arg, char *value) {
	  Serial.print("DEBUG:");
	  Serial.print(arg);
	  Serial.println(value);
	}
