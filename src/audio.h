/*
 * audio.h
 *
 *  Created on: Apr 19, 2016
 *      Author: petr
 */

#ifndef SRC_AUDIO_H_
#define SRC_AUDIO_H_

#define SIREN_PIN 6
#define BUZZER_PIN 8

#define BEEP_LENGTH_MS 50

#define AUDIO_UNIT_NAME "GA0AUDIO"

void setupAudio();
void processAudioCommand();
void tickAudio();
void beep();
void doubleBeep();


#endif /* SRC_AUDIO_H_ */
