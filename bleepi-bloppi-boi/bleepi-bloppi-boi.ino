// Based on Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015

#include <Bounce.h>
#include "AudioSystemConfig.h"
#include "AudioFiles.h"

const int numVoices = 8;
AudioPlaySdWav* voices[numVoices] = {
  &playSdWav1,
  &playSdWav2,
  &playSdWav3,
  &playSdWav4,
  &playSdWav5,
  &playSdWav6,
  &playSdWav7,
  &playSdWav8,
};

Bounce btnDrum1 = Bounce(0, 15);
Bounce btnDrum2 = Bounce(2, 15);  // 15 = 15 ms debounce time
Bounce btnSlot1 = Bounce(3, 15); 
Bounce btnSlot2 = Bounce(17, 15); 
Bounce btnSlot3 = Bounce(16, 15); 
Bounce btnSlot4 = Bounce(14, 15);

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11 
#define SDCARD_SCK_PIN   13

#define LED_PIN    5

const int numReadings = 5;
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;            // the average
int radioKnobPin = A8;
int radioKnob = 0;

void setup() {
  Serial.begin(9600);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  pinMode(LED_PIN, OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);

  delay(1000);
}

elapsedMillis blinkTime;

int voice0Playing = 0;
const char* voice0file = AudioFiles.drum0;

int voice1Playing = 0;
int voice2Playing = 0;
int voice3Playing = 0;
int voice4Playing = 0;

const char* drum1sound = AudioFiles.drum1;
const char* drum2sound = AudioFiles.drum2;
const char* slot1sound = AudioFiles.slot1;
const char* slot2sound = AudioFiles.slot2;
const char* slot3sound = AudioFiles.slot3;
const char* slot4sound = AudioFiles.slot4;


void loop() {
  total = total - readings[readIndex];
  readings[readIndex] = analogRead(radioKnobPin);
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  radioKnob = total / numReadings;

  radioKnob = map(radioKnob, 0, 1023, 0, 3);

  if (radioKnob == 0) {
    drum1sound = AudioFiles.slot3;
    drum2sound = AudioFiles.slot3;
    slot1sound = AudioFiles.slot3;
    slot2sound = AudioFiles.slot3;
    slot3sound = AudioFiles.slot3;
    slot4sound = AudioFiles.slot3;
  } else if (radioKnob == 1) {
    drum1sound = AudioFiles.drum2;
    drum2sound = AudioFiles.drum2;
    slot1sound = AudioFiles.drum2;
    slot2sound = AudioFiles.drum2;
    slot3sound = AudioFiles.drum2;
    slot4sound = AudioFiles.drum2;
  } else if (radioKnob == 2) {
    drum1sound = AudioFiles.slot4;
    drum2sound = AudioFiles.slot4;
    slot1sound = AudioFiles.slot4;
    slot2sound = AudioFiles.slot4;
    slot3sound = AudioFiles.slot4;
    slot4sound = AudioFiles.slot4;
  } else {
    drum1sound = AudioFiles.slot1;
    drum2sound = AudioFiles.slot1;
    slot1sound = AudioFiles.slot1;
    slot2sound = AudioFiles.slot1;
    slot3sound = AudioFiles.slot1;
    slot4sound = AudioFiles.slot1;
  }
  
  // blink the LED without delays
  if (blinkTime < 250) {
    digitalWrite(LED_PIN, LOW);
  } else if (blinkTime < 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    blinkTime = 0; // start blink cycle over again
  }

  btnDrum1.update();
  if (btnDrum1.fallingEdge()) {
    if (voice0Playing == 0) {
      voice0Playing = 1;
      voice0file = drum1sound;
    } else {
      if (voice0file == drum1sound) {
        voice0Playing = 0;
        voices[0]->stop();
      } else {
        voice0file = drum1sound;
        voices[0]->stop();
        voices[0]->play(voice0file);
      }
    }
  }

  btnDrum2.update();
  if (btnDrum2.fallingEdge()) {
     if (voice0Playing == 0) {
      voice0Playing = 1;
      voice0file = drum2sound;
    } else {
      if (voice0file == drum2sound) {
        voice0Playing = 0;
        voices[0]->stop();
      } else {
        voice0file = drum2sound;
        voices[0]->stop();
        voices[0]->play(voice0file);
      }
    }
  }

  btnSlot1.update();
  if (btnSlot1.fallingEdge()) {
    if (voice1Playing == 0) {
      voice1Playing = 1;
    } else {
      voice1Playing = 0;
      voices[1]->stop();
    }
  }
  
  btnSlot2.update();
  if (btnSlot2.fallingEdge()) {
    if (voice2Playing == 0) {
      voice2Playing = 1;
    } else {
      voice2Playing = 0;
      voices[2]->stop();
    }
  }

  btnSlot3.update();
  if (btnSlot3.fallingEdge()) {
    if (voice3Playing == 0) {
      voice3Playing = 1;
    } else {
      voice3Playing = 0;
      voices[3]->stop();
    }
  }
  
  btnSlot4.update();
  if (btnSlot4.fallingEdge()) {
    if (voice4Playing == 0) {
      voice4Playing = 1;
    } else {
      voice4Playing = 0;
      voices[4]->stop();
    }
  }

  if (voice0Playing == 1) {
    if (voices[0]->isPlaying() == false) {
      voices[0]->play(voice0file);
    }
  }

  if (voice1Playing == 1) {
    if (voices[1]->isPlaying() == false) {
      voices[1]->play(slot1sound);
    }
  }

  if (voice2Playing == 1) {
    if (voices[2]->isPlaying() == false) {
      voices[2]->play(slot2sound);
    }
  }

  if (voice3Playing == 1) {
    if (voices[3]->isPlaying() == false) {
      voices[3]->play(slot3sound);
    }
  }

  if (voice4Playing == 1) {
    if (voices[4]->isPlaying() == false) {
      voices[4]->play(slot4sound);
    }
  }
}
