/*
 * temperature.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_TEMPERATURE_H_
#define SRC_TEMPERATURE_H_

#define DHT22_PIN 4
#define TEMPERATURE_UNIT_NAME "GA0TEMPERATURE"

void processTemperature();
void setupTemperature();
void readTemperature();

#endif /* SRC_TEMPERATURE_H_ */
