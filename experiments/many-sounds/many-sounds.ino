// Based on Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015


#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

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

Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(2, 15);  // 15 = 15 ms debounce time

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11 
#define SDCARD_SCK_PIN   13

#define LED_PIN    5

void setup() {
  Serial.begin(9600);
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
  delay(1000);
}

int filenumber = 0;  // while file to play
const int numFiles = 4;
const char * filelist[numFiles] = {
  "SDTEST1.WAV", "SDTEST2.WAV", "SDTEST3.WAV", "SDTEST4.WAV"
};

elapsedMillis blinkTime;

int nextVoiceIdx = numVoices - 1;

void loop() {
  
  // blink the LED without delays
  if (blinkTime < 250) {
    digitalWrite(LED_PIN, LOW);
  } else if (blinkTime < 500) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    blinkTime = 0; // start blink cycle over again
  }

  button0.update();
  if (button0.fallingEdge()) {
    voices[nextVoiceIdx]->stop();
    int fileIdx = nextVoiceIdx % numFiles;
    voices[nextVoiceIdx]->play(filelist[fileIdx]);
    nextVoiceIdx = (nextVoiceIdx + 1) % numVoices;
  }
  button1.update();
  if (button1.fallingEdge()) {
    for (int idx = 0; idx < numVoices; idx++) {
      voices[idx]->stop();
    }
    nextVoiceIdx = 0;
  }
  
}




