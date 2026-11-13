#include <SPI.h>
#include <SD.h>

#include "AudioTools.h"
#include "AudioTools/Disk/AudioSourceSD.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"

using namespace audio_tools;

// XIAO ESP32-S3 Sense microSD pins
#define SD_CS   21
#define SD_SCK  7
#define SD_MISO 8
#define SD_MOSI 9

// PWM audio output pins
#define PWM_LEFT  D0
#define PWM_RIGHT D1

// MP3 files go directly inside /music
#define MUSIC_DIR "/music"

AudioSourceSD source(MUSIC_DIR, ".mp3", SD_CS);
PWMAudioOutput pwm;
MP3DecoderHelix decoder;
AudioPlayer player(source, pwm, decoder);

bool sdReady = false;
bool playerReady = false;

int trackCount = 0;
int currentTrack = 0;

String commandBuffer;

// --------------------
// Serial command help
// --------------------

void printHelp() {
  Serial.println();
  Serial.println("===== TV MAN PLAYER v0.3 =====");
  Serial.println("help       - Show commands");
  Serial.println("list       - List MP3 files");
  Serial.println("play       - Play/resume");
  Serial.println("play N     - Play track number N");
  Serial.println("pause      - Pause playback");
  Serial.println("resume     - Resume playback");
  Serial.println("stop       - Stop and reset track");
  Serial.println("next       - Next track");
  Serial.println("prev       - Previous track");
  Serial.println("volume N   - Set volume (0-100)");
  Serial.println("status     - Show player status");
  Serial.println("==============================");
  Serial.println();
}

// --------------------
// List MP3 files
// --------------------

void listMusic() {
  if (!sdReady) {
    Serial.println("SD card unavailable.");
    return;
  }

  File folder = SD.open(MUSIC_DIR);

  if (!folder || !folder.isDirectory()) {
    Serial.println("Could not open /music.");
    return;
  }

  Serial.println();
  Serial.println("===== MUSIC LIBRARY =====");

  int found = 0;

  File entry = folder.openNextFile();

  while (entry) {
    if (!entry.isDirectory()) {
      String name = entry.name();
      String lower = name;
      lower.toLowerCase();

      if (lower.endsWith(".mp3")) {
        found++;
        Serial.print(found);
        Serial.print(". ");
        Serial.print(name);
        Serial.print(" (");
        Serial.print(entry.size());
        Serial.println(" bytes)");
      }
    }

    entry.close();
    entry = folder.openNextFile();
  }

  folder.close();

  Serial.print("Total MP3 files: ");
  Serial.println(found);
  Serial.println("=========================");
}

// --------------------
// Player status
// --------------------

void printStatus() {
  Serial.println();
  Serial.println("===== PLAYER STATUS =====");

  Serial.print("SD card: ");
  Serial.println(sdReady ? "READY" : "NOT READY");

  Serial.print("Player: ");
  Serial.println(playerReady ? "READY" : "NOT READY");

  Serial.print("Tracks indexed: ");
  Serial.println(trackCount);

  Serial.print("Current track index: ");
  Serial.println(currentTrack);

  if (playerReady) {
    Serial.print("Playback active: ");
    Serial.println(player.isActive() ? "YES" : "NO");

    Serial.print("Volume: ");
    Serial.println(player.volume());
  }

  Serial.println("=========================");
}

// --------------------
// Commands
// --------------------

void processCommand(String command) {
  command.trim();
  command.toLowerCase();

  if (command.length() == 0) return;

  if (command == "help") {
    printHelp();
  }

  else if (command == "list") {
    listMusic();
  }

  else if (command == "status") {
    printStatus();
  }

  else if (!playerReady) {
    Serial.println("Player not ready. Check SD card and MP3 files.");
  }

  else if (command == "play" || command == "resume") {
    player.play();
    Serial.println("Playback started/resumed.");
  }

  else if (command.startsWith("play ")) {
    int number = command.substring(5).toInt();

    if (number < 1 || number > trackCount) {
      Serial.println("Invalid track number.");
    } else {
      currentTrack = number - 1;
      player.begin(currentTrack, true);
      Serial.print("Playing track ");
      Serial.println(number);
    }
  }

  else if (command == "pause") {
    player.stop();
    Serial.println("Playback paused.");
  }

  else if (command == "stop") {
    player.stop();
    player.begin(currentTrack, false);
    Serial.println("Playback stopped.");
  }

  else if (command == "next") {
    player.next();
    currentTrack = source.index();
    Serial.println("Next track.");
  }

  else if (command == "prev") {
    player.previous();
    currentTrack = source.index();
    Serial.println("Previous track.");
  }

  else if (command.startsWith("volume ")) {
    int volume = command.substring(7).toInt();
    volume = constrain(volume, 0, 100);

    player.setVolume(volume / 100.0f);

    Serial.print("Volume set to ");
    Serial.print(volume);
    Serial.println("%");
  }

  else {
    Serial.println("Unknown command. Type 'help'.");
  }
}

// --------------------
// Serial input
// --------------------

void serialInput() {
  while (Serial.available()) {
    char incoming = Serial.read();

    if (incoming == '\n' || incoming == '\r') {
      if (commandBuffer.length() > 0) {
        processCommand(commandBuffer);
        commandBuffer = "";
      }
    }

    else if (commandBuffer.length() < 100) {
      commandBuffer += incoming;
    }
  }
}

// --------------------
// Setup
// --------------------

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       TV MAN PLAYER v0.3");
  Serial.println("       XIAO ESP32-S3");
  Serial.println("================================");

  // Initialize SD card
  Serial.println("Initializing microSD...");

  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  sdReady = SD.begin(SD_CS, SPI, 4000000);

  if (!sdReady) {
    Serial.println("SD initialization FAILED.");
  } else {
    Serial.println("SD card initialized.");
  }

  // Initialize PWM audio
  Serial.println("Initializing PWM audio...");

  auto config = pwm.defaultConfig(TX_MODE);

  config.sample_rate = 22050;
  config.channels = 2;
  config.bits_per_sample = 16;

  Pins pwmPins;
  pwmPins.push_back(PWM_LEFT);
  pwmPins.push_back(PWM_RIGHT);

  config.setPins(pwmPins);

  if (!pwm.begin(config)) {
    Serial.println("PWM initialization FAILED.");
  } else {
    Serial.println("PWM initialized.");
  }

  // Initialize MP3 source and player
  if (sdReady) {
    Serial.println("Indexing MP3 files...");

    playerReady = player.begin(0, false);

    if (playerReady) {
      trackCount = source.size();
      currentTrack = 0;

      player.setVolume(0.10f);

      Serial.print("Tracks found: ");
      Serial.println(trackCount);
    } else {
      trackCount = 0;
      Serial.println("No playable MP3 tracks found.");
    }
  }

  printHelp();

  Serial.println("System initialization complete.");
}

// --------------------
// Main loop
// --------------------

void loop() {
  serialInput();

  if (playerReady) {
    player.copy();
  }
}
