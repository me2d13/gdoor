/*
 * temperature.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_TEMPERATURE_H_
#define SRC_TEMPERATURE_H_

#define DHT22_PIN 4
#define TEMPERATURE_COMMAND_TOPIC "/garage/ard1/command/temperature"
#define TEMPERATURE_STATUS_TOPIC "/garage/ard1/status/temperature"


void processTemperature();
void setupTemperature();
void readTemperature();

#endif /* SRC_TEMPERATURE_H_ */
