/*
 * power.h
 *
 *  Created on: May 7, 2016
 *      Author: petr
 */

#ifndef SRC_POWER_H_
#define SRC_POWER_H_

#define AC_POWER_PIN 7
#define AC_POWER_UNIT_NAME "GA0ACPOWER"

void tickPower();
void processPowerCommand();
void setupPower();


#endif /* SRC_POWER_H_ */
