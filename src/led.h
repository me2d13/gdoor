/*
 * led.h
 *
 *  Created on: 18. 4. 2016
 *      Author: petr
 */

#ifndef SRC_LED_H_
#define SRC_LED_H_

#define LEDPIN 5
#define LED_CEIL_UNIT_NAME "GA0LEDCEIL"

#define LED_STEP 5

void tickLed();
void processLedCommand();
void setupLed();
void setLedTargetIntensity(int targetIntensity);

#endif /* SRC_LED_H_ */
