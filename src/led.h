/*
 * led.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#define LEDPIN 5
#define LED_CEIL_COMMAND_TOPIC "/garage/ard1/command/led"
#define LED_CEIL_STATUS_TOPIC "/garage/ard1/status/led"

#define LED_STEP 5

void tickLed();
void processLedCommand();
void setupLed();
void setLedTargetIntensity(int targetIntensity);

#endif /* SRC_LED_H_ */
