#pragma once

// Teensy Audio library configuration generated with:
// https://www.pjrc.com/teensy/gui/index.html

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav2;     //xy=99,267
AudioPlaySdWav           playSdWav1;     //xy=101,184
AudioPlaySdWav           playSdWav3;     //xy=105,346
AudioPlaySdWav           playSdWav4;     //xy=106,408
AudioPlaySdWav           playSdWav5;     //xy=108,474
AudioPlaySdWav           playSdWav6;     //xy=108,538
AudioPlaySdWav           playSdWav7;     //xy=114,589
AudioPlaySdWav           playSdWav8;     //xy=114,639
AudioMixer4              mixer2;         //xy=378,480
AudioMixer4              mixer1;         //xy=383,197
AudioMixer4              mixer3;         //xy=633,344
AudioOutputI2S           i2s1;           //xy=872,401
AudioConnection          patchCord1(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord2(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord3(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord5(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord6(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord7(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord8(playSdWav8, 0, mixer2, 3);
AudioConnection          patchCord9(mixer2, 0, mixer3, 1);
AudioConnection          patchCord10(mixer1, 0, mixer3, 0);
AudioConnection          patchCord11(mixer3, 0, i2s1, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=301,90
// GUItool: end automatically generated code
