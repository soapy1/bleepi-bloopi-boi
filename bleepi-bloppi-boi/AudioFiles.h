#pragma once

// Singleton class to hold audio file names
class AudioFiles {
 private:
  AudioFiles() {}

 public:
  // Call this to get the only instance of this class.
  static AudioFiles& instance() {
    static AudioFiles inst;
    return inst;
  }

  const char* const drum0 = "drum0.wav";
  const char* const drum1 = "drum1.wav";
  const char* const drum2 = "drum2.wav";
  const char* const slot1 = "slot1.wav";
  const char* const slot2 = "slot2.wav";
  const char* const slot3 = "slot3.wav";
  const char* const slot4 = "slot4.wav";
};

static auto AudioFiles = AudioFiles::instance();
