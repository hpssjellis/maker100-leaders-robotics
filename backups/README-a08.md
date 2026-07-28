# maker100-leaders-robotics
maker100-leaders-robotics machine learning sensor actuator IoT for high school students in the global south.


Price list at  [https://hpssjellis.github.io/maker100-leaders-robotics/](https://hpssjellis.github.io/maker100-leaders-robotics/price-list-2026.html)

The entire course is the same as [https://github.com/hpssjellis/maker100-xiaoML-kit](https://github.com/hpssjellis/maker100-xiaoML-kit) just reorganized for better communication.





## Maker100-xiaoML-kit Robotics, IoT and TinyML Machine Learning course is ready!

## 2026 Version

## [XIAOML-Kit youtube playlist](https://www.youtube.com/watch?v=EvNXQ0sk5Ec&list=PL57Dnr1H_egtkBZJku20Bo2zaR8KUJGpa&index=1&pp=gAQBiAQB)

## [2026 Price List](https://hpssjellis.github.io/maker100-leaders-robotics/price-list-2026.html)

This course is all about the Seeedstudio $38.90 USD [The-XIAOML-Kit](https://www.seeedstudio.com/The-XIAOML-Kit.html) which has the $22 dollar kit with a $16.90 sdCard + Cables kit.

<img width=400 src="https://github.com/user-attachments/assets/03d4d927-a35c-40cd-be88-ebe627d7b040">

For which the main Getting Started page is at [xiao_esp32s3_getting_started](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/).
Any specialty code for this specific ML kit will be here on this page or at the Harvard [mlsysbook.ai](https://mlsysbook.ai/contents/labs/seeed/xiao_esp32s3/xiao_esp32s3.html) free online book labs section.

---

# General

The curriculum for this course is at [maker100-curriculum](https://github.com/hpssjellis/maker100-curriculum)

The old version of this course: Seeedstudio [maker100-eco](https://github.com/hpssjellis/maker100-eco)

An economical version of my successful Arduino PortentaH7 [Maker100](https://github.com/hpssjellis/maker100) Robotics, IoT and TinyML Machine Learning in-person course, this time using less expensive hardware such as the [$13.99 USD Seeedstudio XiaoEsp32s3](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/) for the course basics and some [EdgeImpulse.com](https://edgeimpulse.com/) cell phone assisted machine learning.

Views better using the README.md [here](README.md)

This is not an online course; it is expected to be taught by a teacher or professor. Some students might be able to do the course on their own, but many learning opportunities may be missed.

Price list for the equipment I will be using in 2026: [price-list-2026.html](https://hpssjellis.github.io/maker100-leaders-robotics/price-list-2026.html) (Many other devices could be used but the videos then will not be accurate for those devices.)

Note: April 2026 new Technique [webmcu-ai](https://github.com/webmcu-ai) demo page at [https://webmcu-ai.github.io/webmcu-vision-web/index.html](https://webmcu-ai.github.io/webmcu-vision-web/index.html)

Note: Student Ryan H found the [Arduino Droid](https://play.google.com/store/apps/details?id=name.antonsmirnov.android.arduinodroid2&hl=en) for android phones. The student needed a serial monitor on his phone to test the GPS while outside and he found this app. I have never tried it. There does not seem to be the equivalent for Mac, although Arduino has an online version of its software. I prefer platformIO if you have internet.

**Teacher Extras:** [See Appendix A](#appendix-a-teacher-extras---why-not-use-the-xiao-expansion-board-and-round-display)

**Teacher Tips:** [See Appendix B](#appendix-b-teacher-tips---teaching-guidelines-and-best-practices)

**Why Maker100-xiaoML-kit?** [See Appendix C](#appendix-c-why-maker100-xiaoml-kit)

**How much cheaper is the XIAOML kit version?** [See Appendix D](#appendix-d-price-comparison---how-much-cheaper-is-the-xiaoml-kit-version)

**Useful Links:** [See Appendix E](#appendix-e-useful-links)

---

## General Assignment Steps

1. Look at the GitHub code and hand-write a short pseudocode explanation (New 2026 — to prevent students going to an LLM first instead of reading the code).
2. For many assignments, first compile and upload the C++/C code (Arduino Sketch).
3. Unplug your device.
4. Then have a classmate or teacher check your hand-drawn, named circuit diagram before connecting any wires.
5. When the diagram is OK, wire up the device and have it checked again before connecting ANY power (battery and/or USB-C power).
6. Check the serial monitor if applicable.
7. Make a very short video that shows your name(s), circuit diagram, the board, and the serial monitor as proof of it working.

---

<br><br>

# Course Sampler — Try One from Each Area First

> **Start here.** Before diving into any section, try one assignment from each category below. Each assignment number matches its home section so you can jump straight to the details. The goal is to make sure students are not scared to explore all areas — try one, succeed, move on. Then return to each section in depth.

| # | Category | Assignment | Quick Link |
| :--- | :--- | :--- | :--- |
| [a00-test](#a00-test) | **Hardware Check** | Test your XIAO ML Kit — camera, mic, IMU and OLED all at once | [xiaoml-kit-esp32-web-tool](https://hpssjellis.github.io/xiaoml-kit-esp32-web-tool/public/index.html) |
| [a03-blink-serial](#a03-blink-serial) | **Basics / Coding** | Blink + Serial Print on Arduino IDE and PlatformIO | [seeed-blink-serial.ino](seeed-sketches/seeed-blink-serial.ino) |
| [a07-button](#a07-button) | **Sensors** | Button controls LED — your first sensor + actuator | [seeed-led-button.ino](seeed-sketches/seeed-led-button.ino) |
| [a19-servo](#a19-servo) | **Actuators** | Servo motor | [seeed-servo-needs-ESP32Servo-include.ino](seeed-sketches/seeed-servo-needs-ESP32Servo-include.ino) |
| [a36-camera-web-server](#a36-camera-web-server) | **IoT** | Camera web server streaming over WiFi | Arduino IDE → Examples → ESP32 → Camera → CameraWebServer |
| [a56-handpose](#a56-handpose) | **WebAI** | HandPose in the browser — no hardware needed | [handpose](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/handpose/index.html) |
| [a02-sensecraft](#a02-sensecraft) | **Machine Learning** | Seeed SenseCraft — install a pre-built ML model | [sensecraft.seeed.cc](https://sensecraft.seeed.cc/ai/#/home) |

---

<br><br>

# Section 1 — Basics

For the full curriculum basics reference see [maker100-curriculum Basics](https://github.com/hpssjellis/maker100-curriculum#basics).

<a name="a00-test"></a>
## a00 — Test Your XIAO ML Kit

No grade — do this first to confirm your board is working. Flashes a binary to the device then reads the camera, mic and IMU all live.

| Tool | Link | Notes |
| :--- | :--- | :--- |
| Web flash + live test | [xiaoml-kit-esp32-web-tool](https://hpssjellis.github.io/xiaoml-kit-esp32-web-tool/public/index.html) | Can also view and change the SD card. Use this to verify camera, mic, IMU, OLED and SD card are all working. |
| WebSerial Variable Tracer | [webserial-variable-trace](https://hpssjellis.github.io/xiaoml-kit-webserial-variable-trace/webtracer.html) — GitHub: [xiaoml-kit-webserial-variable-trace](https://github.com/hpssjellis/xiaoml-kit-webserial-variable-trace) | Fancy data plotter; can peek and set memory items. Careful setting memory — you could brick your MCU. |

---

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a01-on-device-ml" href="README.md#a01-on-device-ml">`a01-on-device-ml`</a> PlatformIO and Arduino IDE on-device-ML with u8g2 OLED include library | Hard first day: [esp-all-menu-A0-image-train-infer.txt](https://github.com/hpssjellis/my-examples-of-tensorflowjs-for-tinytorch/blob/main/esp-on-device-train-one-program/esp-all-menu-A0-image-train-infer.txt), or try the easier first day which is the same as a03-blink-serial but on both PlatformIO and the Arduino IDE: [seeed-blink-serial.ino](seeed-sketches/seeed-blink-serial.ino) | This assignment covers the [Maker100-Curriculum Basics](https://github.com/hpssjellis/maker100-curriculum#basics) Base01–Base05, Base07 Assignments | See [Tutorial ml16](#tutorial-ml16) |
| <a name="a02-sensecraft" href="README.md#a02-sensecraft">`a02-sensecraft`</a> Follow the SenseCraft Vision example | [wiki.seeedstudio.com/sscma/](https://wiki.seeedstudio.com/sscma/) — direct webpage: [sensecraft.seeed.cc](https://sensecraft.seeed.cc/ai/#/home) | This assignment covers the start of the [Maker100-curriculum Machine Learning](https://github.com/hpssjellis/maker100-curriculum#machine-learning) | |
| <a name="a03-blink-serial" href="README.md#a03-blink-serial">`a03-blink-serial`</a> XIAO ESP32S3 LED Blink and Serial Print on both PlatformIO and the Arduino IDE | [seeed-blink-serial.ino](seeed-sketches/seeed-blink-serial.ino) | ![blink-serial3](https://github.com/user-attachments/assets/eae5ad75-3f34-40c6-8f20-8f4a9b95b8fb) [wokwi Serial](https://wokwi.com/projects/454549337599230977) <img src="https://img.youtube.com/vi/0OLsLl-CBHQ/hqdefault.jpg" width=100 /> <img src="https://img.youtube.com/vi/3E5KUT115xY/hqdefault.jpg" width=300 /> | THIS IS THE CODE YOU SHOULD COMPILE ONTO YOUR XIAO AFTER DOING EVERY ASSIGNMENT TO CLEAR YOUR WORK! Print other things and change the pattern of blinking delay times. Always leave this on the XIAO ML Kit so you know it works. |
| <a name="a04-serial-putty" href="README.md#a04-serial-putty">`a04-serial-putty`</a> Serial Putty or Linux "screen" | A program to load on your computer that replaces the Arduino serial monitor | If no access to PowerShell or the DOS prompt, load the Arduino IDE to find the port number (COM3, COM7, etc.). Then CLOSE the Arduino IDE and load Putty. Set to Serial and baud rate 115200. | Fairly easy once Putty is installed. Load PowerShell, type `mode` with your board programmed with a serial monitor program, find the port. Switch to Serial on Putty and set the correct COM port. Open and see serial output. |

---

<br><br>

# Section 2 — Coding

For the full curriculum coding reference see [maker100-curriculum Coding](https://github.com/hpssjellis/maker100-curriculum#coding).

Note: VIDEO FLAC = Variables, Input/Output, Decisions, Events, Objects (Structs), Functions, Loops, Arrays, Classes (Properties and Methods).

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a05-flash-sos" href="README.md#a05-flash-sos">`a05-flash-sos`</a> Flash SOS | [dot71-sos](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot7-coding-curriculum/dot71-sos/dot71-sos.ino) | <img src="https://img.youtube.com/vi/lvEuArebVuA/hqdefault.jpg" width=300 /> <img src="https://img.youtube.com/vi/iDC3vuBGGcg/hqdefault.jpg" width=300 /> | Your first Coding example from the [Maker100-Curriculum on Coding](https://github.com/hpssjellis/maker100-curriculum#coding). Flash LED_BUILTIN in an SOS pattern: 3 short, 3 long, 3 short, then a 5-second rest. |
| <a name="a06-coding-assignments" href="README.md#a06-coding-assignments">`a06-coding-assignments`</a> All Coding Assignments | Install the Arduino library ([Portenta Pro Community Solutions](https://github.com/hpssjellis/portenta-pro-community-solutions/tree/main/examples/dot7-coding-curriculum)) and load, change and video all Coding assignments dot72–dot79. You can copy them directly from GitHub or from the library examples. | VIDEO FLAC is basic coding skills: Variables, Input/Output, Decisions, Events, Objects (Structs), Functions, Loops, Arrays, Classes (Properties and Methods). | One of the few assignments that may need its own folder, but the video gets copied into the main folder. Slightly change each program. 9 programs, one grade. |

---

<br><br>

# Section 3 — Sensors

For the full curriculum sensors reference see [maker100-curriculum Sensors](https://github.com/hpssjellis/maker100-curriculum#sensors).

**Reminder: all these assignments need a drawn and checked circuit diagram before you connect any wires to the microcontroller.**

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a07-button" href="README.md#a07-button">`a07-button`</a> Button causes LED to blink | [seeed-led-button.ino](seeed-sketches/seeed-led-button.ino) | This is actually an example of an absolute basic final project — sensor (button), microcontroller (XIAO ESP32S3), and actuator (LED). Your first [maker100-curriculum sensor](https://github.com/hpssjellis/maker100-curriculum#sensors) assignment. <img src="https://img.youtube.com/vi/SkTqOthK3JM/hqdefault.jpg" width=300 /> <img src="https://img.youtube.com/vi/wFw-AF8gwiY/hqdefault.jpg" width=300 /> | <img src="media/b-b-h-button-control-led.jpg" width=200/> Control the LED with the button, then control multiple LEDs with multiple buttons. Note: Cannot control large current-flow devices — why? Could you make the external LED interact like the internal LED? |
| <a name="a08-oled-hello" href="README.md#a08-oled-hello">`a08-oled-hello`</a> XIAO ML Kit OLED Hello | The blink-serial program for the XIAO ML Kit — says hello on the OLED: [xiaoML-good-serial-blink-oled-digital-read.ino](https://github.com/hpssjellis/maker100-xiaoML-kit/blob/main/xiaoML-kit/xiaoML-good-serial-blink-oled-digital-read.ino) | If you have the XIAO ML Kit, this is the best program to leave on the device after assignments. Just plug it into power and you can see the board works. | Careful with the OLED — if you bend it too often the connection weakens. |
| <a name="a09-imu-motion" href="README.md#a09-imu-motion">`a09-imu-motion`</a> Basic X, Y, Z Motion | Basic x, y, z motion with the XIAO ML Kit: [xiaoML-6dof-imu-basics.ino](https://github.com/hpssjellis/maker100-xiaoML-kit/blob/main/xiaoML-kit/xiaoML-6dof-imu-basics.ino) | A good assignment to try to put the results onto the OLED. Currently only showing on the serial monitor. | |
| <a name="a10-voltage-divider" href="README.md#a10-voltage-divider">`a10-voltage-divider`</a> Analog Read (Voltage divider for flex sensor, photoresistor, touch/pressure sensor) | [dot211-any-variable-resistor-sensor.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot21-sensors/dot211-any-variable-resistor-sensor/dot211-any-variable-resistor-sensor.ino) | [![video](https://img.youtube.com/vi/wA6JB-PzuUs/hqdefault.jpg)](https://www.youtube.com/watch?v=wA6JB-PzuUs&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=3&pp=gAQBiAQB) [![video](https://img.youtube.com/vi/GR3D8C6dOl8/hqdefault.jpg)](https://www.youtube.com/watch?v=GR3D8C6dOl8&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=3) | Change the resistor amount and which resistor is attached to 3V3 to get the largest, most sensible range of readings. |
| <a name="a11-two-wire" href="README.md#a11-two-wire">`a11-two-wire`</a> Another Two-Wire Sensor | | | Figure out how to read another variable-resistor sensor like a flex sensor, photoresistor, or pressure sensor. |
| <a name="a12-joystick" href="README.md#a12-joystick">`a12-joystick`</a> Game Controller / Joystick | | | Figure out how to use the 3 wires (3V3, GND, A0) for one dimension of a joystick. |
| <a name="a13-rangefinder" href="README.md#a13-rangefinder">`a13-rangefinder`</a> Rangefinder — WAIT until voltage divider is tested. Watch [this video first](https://youtu.be/SIc6zj06bhQ?si=m28UJreFCBhAaYBn&t=193), then load [wokwi-rangefinder](https://wokwi.com/projects/455728225241458689) | [dot214-RangeFinder.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot21-sensors/dot214-RangeFinder/dot214-RangeFinder.ino) | <img width="400" alt="rangefinder" src="https://github.com/user-attachments/assets/fd24013f-a89b-4818-b8a0-0011e5b0c81e" /> [![video](https://img.youtube.com/vi/TwHTtcjS2T8/hqdefault.jpg)](https://www.youtube.com/watch?v=TwHTtcjS2T8&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=13&pp=iAQB) [![video](https://img.youtube.com/vi/E1B_iE171E8/hqdefault.jpg)](https://www.youtube.com/watch?v=E1B_iE171E8&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=13) | A variable in the code can be changed to make the range finder work at a greater distance. |
| <a name="a14-image-to-sd" href="README.md#a14-image-to-sd">`a14-image-to-sd`</a> XIAO ESP32S3 Image to SD Card | [seeed-cam-to-sd-card.ino](seeed-sketches/seeed-cam-to-sd-card.ino) — allows pictures in JPG format to be saved to the SD card on a user-set delay. | | You will need a micro SD card. |
| <a name="a15-video-to-sd" href="README.md#a15-video-to-sd">`a15-video-to-sd`</a> XIAO ESP32S3 Video to SD Card | [seeed-video-to-sd-card.ino](seeed-sketches/seeed-video-to-sd-card.ino) — allows video in MPEG format to be saved to the SD card. | | You will need a micro SD card. |
| <a name="a16-sound-to-sd" href="README.md#a16-sound-to-sd">`a16-sound-to-sd`</a> XIAO ESP32S3 Sound to SD Card | [a02-sound-to-sd-card.ino](seeed-sketches/a02-sound-to-sd-card.ino) Needs the latest board version, presently 3.2.0. Fixed by @packetbytebuf. Read the first few lines. | | |
| <a name="a17-pixy2" href="README.md#a17-pixy2">`a17-pixy2`</a> Serial SPI Pixy2 | [dot212-pixy2-SPI.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot21-sensors/dot212-pixy2-SPI/dot212-pixy2-SPI.ino) Note: the dot212 Pixy example using the Portenta Pro Community Solutions library will be pre-setup with the Pixy include files! | [![video](https://img.youtube.com/vi/Op5XIiGr0Q0/hqdefault.jpg)](https://www.youtube.com/watch?v=Op5XIiGr0Q0&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=8&pp=iAQB) [![video](https://img.youtube.com/vi/p8KmFFqqU6U/hqdefault.jpg)](https://www.youtube.com/watch?v=p8KmFFqqU6U&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=14) | <img src="media/pixy-connector.png" width=200/> The Pixy2 is so cool students will have no problem coming up with things to detect. Great for a final project — students just need to connect an actuator. Example: when you see the "orange" cat, have a servo open a lever to feed it. |
| <a name="a18-gps" href="README.md#a18-gps">`a18-gps`</a> GPS | [./xiaoML-kit/air530-gps04.txt](./xiaoML-kit/air530-gps04.txt) | New code works great — interesting to connect the Grove OLED to display Lat and Long values. | Plug the Lat and Long values into Google Maps to find out where you are. |

---

<br><br>

# Section 4 — Actuators

For the full curriculum actuators reference see [maker100-curriculum Actuators](https://github.com/hpssjellis/maker100-curriculum#actuators-motors-leds-etc).

**Reminder: all these assignments need a drawn and checked circuit diagram before you connect any wires to the microcontroller.**

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a19-servo" href="README.md#a19-servo">`a19-servo`</a> Servo | [seeed-servo-needs-ESP32Servo-include.ino](seeed-sketches/seeed-servo-needs-ESP32Servo-include.ino) | Your first [Maker100-Curriculum Actuator](https://github.com/hpssjellis/maker100-curriculum?tab=readme-ov-file#actuators-motors-leds-etc) Assignment. <img src="https://img.youtube.com/vi/c3j7Vi28n24/hqdefault.jpg" width=300 /> <img src="https://img.youtube.com/vi/4p3yIF_4pk8/hqdefault.jpg" width=300 /> | MUST HAVE AN EXTERNAL BATTERY TO RUN THE 6V SERVO! The negative GND from the external battery must run to both the XIAO and the servo. Find the library and include it: `#include <ESP32Servo.h>`. Connect XIAO D5 (orange wire) and GND (brown wire) to the servo, 6V battery positive (red) and negative (brown) to servo. A 470 µF capacitor as close to the servo as possible really helps with jitter. |
| <a name="a20-pnp" href="README.md#a20-pnp">`a20-pnp`</a> PNP Transistor | [dot224-pwm-transistor.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot224-pwm-transistor/dot224-pwm-transistor.ino) | [![video](https://img.youtube.com/vi/XqxTnUFlMnY/hqdefault.jpg)](https://www.youtube.com/watch?v=XqxTnUFlMnY&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=17) | <img src="https://user-images.githubusercontent.com/5605614/156191081-89142347-8494-46d0-ae48-53566c884bc9.png" width=200/> Make either a PNP transistor with a small motor. |
| <a name="a21-npn" href="README.md#a21-npn">`a21-npn`</a> NPN Transistor | [dot224-pwm-transistor.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot224-pwm-transistor/dot224-pwm-transistor.ino) | [![video](https://img.youtube.com/vi/XqxTnUFlMnY/hqdefault.jpg)](https://www.youtube.com/watch?v=XqxTnUFlMnY&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=17) | <img src="https://user-images.githubusercontent.com/5605614/156191554-49bd23c3-d38c-4fc5-b04f-8ec9add68763.png" width=200/> Make an NPN transistor with a small motor. |
| <a name="a22-small-dc-motor" href="README.md#a22-small-dc-motor">`a22-small-dc-motor`</a> Small Dual DC Motor Driver | [dot226-small-dual-dc-motor-driver.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot226-small-dual-dc-motor-driver/dot226-small-dual-dc-motor-driver.ino) | [![video](https://img.youtube.com/vi/dQZzMBJbSXk/hqdefault.jpg)](https://www.youtube.com/watch?v=dQZzMBJbSXk&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=15&pp=iAQB) [![video](https://img.youtube.com/vi/lUE-hmAddhY/hqdefault.jpg)](https://www.youtube.com/watch?v=lUE-hmAddhY&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=5) | <img src="media/b-b-f-small-dual-dc-motor-driver.png" width=200/> Get a small motor working using its own power supply and change the code so it does what you want. Pololu #2135 DRV8835 Dual Motor Driver Carrier [here](https://www.pololu.com/product/2135). |
| <a name="a23-large-dc-motor" href="README.md#a23-large-dc-motor">`a23-large-dc-motor`</a> Large DC Motor Driver | Not-working → [dot227-big-dc-motor-driver.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot227-big-dc-motor-driver/dot227-big-dc-motor-driver.ino). Working (checked by Seth and Jade): [seeed-sketches/a35-new-big-motor.ino](seeed-sketches/a35-new-big-motor.ino) | [![video](https://img.youtube.com/vi/hE4dZ66sOWw/hqdefault.jpg)](https://www.youtube.com/watch?v=hE4dZ66sOWw&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=16&pp=iAQB) [![video](https://img.youtube.com/vi/YcRQSFhr8MY/hqdefault.jpg)](https://www.youtube.com/watch?v=YcRQSFhr8MY&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=7) | <img src="media/b-b-g-big-dc-motor-driver.png" width=200/> Get a 6V motor running and change code for it to do what you want. Protect the XIAO from the 6V motor side. Pololu 1451 VNH5019 Motor Driver Carrier [here](https://www.pololu.com/product/1451). |
| <a name="a24-stepper-motor" href="README.md#a24-stepper-motor">`a24-stepper-motor`</a> Stepper Motor | [dot225-stepper-motor.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot225-stepper-motor/dot225-stepper-motor.ino) | [![video](https://img.youtube.com/vi/Fru6QtzLnrI/hqdefault.jpg)](https://www.youtube.com/watch?v=Fru6QtzLnrI&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=4) | <img src="media/b-b-e-stepper-motor.png" width=200/> Note: This stepper needs 6V. Change code to do what you want. Pololu 2134 DRV8834 Low-Voltage Stepper Motor Driver Carrier [here](https://www.pololu.com/product/2134). |
| <a name="a25-multiplexer" href="README.md#a25-multiplexer">`a25-multiplexer`</a> Multiplexer (mux) — Presently not working; make this optional | | | Connect the XIAO using I2C to a multiplexer — a device that allows more pins to be used when your board runs out. Typically for a large project. |
| <a name="a26-xiao-i2c" href="README.md#a26-xiao-i2c">`a26-xiao-i2c`</a> Use a 2nd XIAO as an I2C multiplexer | Thanks Leander and Giorgio. I2C receiver: [seeed-i2c-2xiao-receiver.ino](seeed-sketches/seeed-i2c-2xiao-receiver.ino). I2C transmitter: [seeed-i2c-2xiao-transmitter.ino](seeed-sketches/seeed-i2c-2xiao-transmitter.ino) | | On the first XIAO you must have a 4.7 kΩ pull-up resistor between SDA and 3V3 and also between SCL and 3V3. On all XIAO boards I2C SDA is D4 and SCL is D5 — just connect them on each board. To power the second board from the first, connect GND to GND and 3V3 to 3V3. For advanced ability, try 2-way communication. |
| <a name="a27-xiao-uart" href="README.md#a27-xiao-uart">`a27-xiao-uart`</a> Use a 2nd XIAO as a UART Serial multiplexer | UART receiver: [2xiao-uart-receive.ino](seeed-sketches/2xiao-uart-receive.ino). UART transmitter: [2xiao-uart-transmit.ino](seeed-sketches/2xiao-uart-transmit.ino) | | Connect the transmitter TX pin (D6) to the receiver RX pin (D7). To power the second board from the first, connect GND to GND and 3V3 to 3V3. For advanced ability, try 2-way communication. |
| <a name="a28-i2c-oled" href="README.md#a28-i2c-oled">`a28-i2c-oled`</a> Serial I2C OLED | [dot222-I2C-grove-OLED.ino](https://github.com/hpssjellis/portenta-pro-community-solutions/blob/main/examples/dot2-portenta-h7-with-accessories/dot22-actuators/dot222-I2C-grove-OLED/dot222-I2C-grove-OLED.ino) | [![video](https://img.youtube.com/vi/rzmIUCMhakk/hqdefault.jpg)](https://www.youtube.com/watch?v=rzmIUCMhakk&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=10&pp=iAQB) [![video](https://img.youtube.com/vi/ruykYcViWo0/hqdefault.jpg)](https://www.youtube.com/watch?v=ruykYcViWo0&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=10) | <img src="media/b-b-b-I2C-grove-OLED.png" width=200/> Have fun with this. Have it say what you want, where you want it, and for how long. |
| <a name="a29-grayscale-oled" href="README.md#a29-grayscale-oled">`a29-grayscale-oled`</a> XIAO ESP32S3 Waveshare Greyscale OLED | [seeed-waveshare-grayscale-oled.ino](seeed-sketches/seeed-waveshare-grayscale-oled.ino) | [![video](https://img.youtube.com/vi/p4cxKxLqy3g/hqdefault.jpg)](https://www.youtube.com/watch?v=p4cxKxLqy3g&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=11&pp=iAQB) | Get the Grayscale Waveshare 128×128 OLED working. |
| <a name="a30-cam-grayscale-oled" href="README.md#a30-cam-grayscale-oled">`a30-cam-grayscale-oled`</a> XIAO ESP32S3 Camera 96×96 to Waveshare Greyscale OLED | [seeed-camera-grayscale-waveshare-oled.ino](seeed-sketches/seeed-camera-grayscale-waveshare-oled.ino) | [![video](https://img.youtube.com/vi/l0H5UnE7HRc/hqdefault.jpg)](https://www.youtube.com/watch?v=l0H5UnE7HRc&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=12&pp=iAQB) | Get the XIAO Camera working with the Grayscale Waveshare 128×128 OLED. Note: The camera can do much better resolution than 96×96, but that is one of the best resolutions for Machine Learning. |
| <a name="a31-e-ink-display" href="README.md#a31-e-ink-display">`a31-e-ink-display`</a> e-Ink Display | New displays with ESP32S3 driver board. Getting Started [here](https://wiki.seeedstudio.com/epaper_ee04/). Library: [Seeed_GFX](https://github.com/Seeed-Studio/Seeed_GFX). Configuration webpage [here](https://seeed-studio.github.io/Seeed_GFX/) helps set up a driver.h file (only one student probably has to do this). | | Once installed, look in the Arduino IDE: Examples → Seeed_GFX → ePaper → Basic → HelloWorld. |
| <a name="a32-round-touch-screen" href="README.md#a32-round-touch-screen">`a32-round-touch-screen`</a> Seeed RGB Round Touch Screen | [./round-display/camera-to-round-with-touch02.txt](./round-display/camera-to-round-with-touch02.txt) | [![video](https://img.youtube.com/vi/SvW3U7YzV0Y/hqdefault.jpg)](https://www.youtube.com/watch?v=SvW3U7YzV0Y&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=16) | A bit tricky to get ready. Read the round display [README.md file](https://github.com/hpssjellis/maker100-xiaoML-kit/tree/main/round-display/README.md). |
| <a name="a33-pcb-board" href="README.md#a33-pcb-board">`a33-pcb-board`</a> PCB Board Build using [easyEDA](https://easyeda.com/) | Great starter tutorial to make a PCB with a battery holder, resistor and light: [![video](https://img.youtube.com/vi/gjPNYMRA0m8/hqdefault.jpg)](https://www.youtube.com/watch?v=gjPNYMRA0m8&list=PLbKMtvtYbdPMZfzGuVTdc0MWKrFvU4nsu&index=2) | | This short video works well even for animation students — they can follow it quickly to make their own board using easyEDA. |
| <a name="a34-lidar" href="README.md#a34-lidar">`a34-lidar`</a> Lidar Basics | [seeed-lidar-serial.ino](seeed-sketches/seeed-lidar-serial.ino) IMPORTANT: on the Lidar, GND is the yellow wire! Needs 5V to run. Connect the green wire to XIAO ESP32S3 RX (D7) to receive data. | | Try the first code to see if the Lidar works over the serial monitor, then try the second code below. |
| <a name="a35-lidar-grayscale-oled" href="README.md#a35-lidar-grayscale-oled">`a35-lidar-grayscale-oled`</a> Lidar with Grayscale OLED | [seeed-lidar-oled.ino](seeed-sketches/seeed-lidar-oled.ino) IMPORTANT: on the Lidar, GND is the yellow wire! Both Lidar and OLED need 5V. Connect green wire to XIAO RX (D7). Grayscale OLED connections in the code: red 5V, GND to GND, blue D10, yellow D8, green D0, orange D1. | ![lidar-oled](https://github.com/hpssjellis/maker100-eco/assets/5605614/ac08d4cb-ec1f-46a5-8dec-737eb237dc4b) | [D100 lidar datasheet](https://github.com/ldrobotSensorTeam/DeveloperKit/blob/master/D100Kit.md) |

---

<br><br>

# Section 5 — IoT (Internet of Things)

For the full curriculum IoT reference see [maker100-curriculum IoT](https://github.com/hpssjellis/maker100-curriculum/blob/main/README.md#iot-internet-of-things-connectivity).

| Topic | Example Code | Video | Instructions |
| :--- | :--- | :--- | :--- |
| <a name="a36-camera-web-server" href="README.md#a36-camera-web-server">`a36-camera-web-server`</a> Camera Web Server | Arduino IDE → Examples → ESP32 → Camera → CameraWebServer (make settings for XIAO ESP32S3 type in the code). Also try Riley's simplified [./seeed-sketches/a48-camera-streaming.ino](./seeed-sketches/a48-camera-streaming.ino). | Make a video of the default ESP32S3 Camera streaming webserver. You can use the class hotspot or your own cell phone hotspot — enter the SSID and password. Ask the teacher to put those on the board. | Your first [Maker100-Curriculum IoT](https://github.com/hpssjellis/maker100-curriculum/blob/main/README.md#iot-internet-of-things-connectivity) assignment — needs some kind of communication between devices. |
| <a name="a37-wifi-webserver" href="README.md#a37-wifi-webserver">`a37-wifi-webserver`</a> WiFi WebServer | [seeed-wifi-server.ino](seeed-sketches/seeed-wifi-server.ino) | [![video](https://img.youtube.com/vi/oygGsGLLLGM/hqdefault.jpg)](https://www.youtube.com/watch?v=oygGsGLLLGM&list=PL57Dnr1H_egv1FVzAcCZVeANJMs3Hta05&index=9) | You will need to set up a hotspot with an SSID and password on a local network, then go to the URL in the serial monitor on a computer or cell phone connected to the same local network. |
| <a name="a38-camera-streaming" href="README.md#a38-camera-streaming">`a38-camera-streaming`</a> Camera Streaming | Try Riley's solution: [seeed-sketches/a48-camera-streaming.ino](seeed-sketches/a48-camera-streaming.ino) | | Load the XIAO_ESP32S3 board in the Arduino IDE, then look for Examples → ESP32 → Camera → CameraWebServer. |
| <a name="a39-sound-streaming" href="README.md#a39-sound-streaming">`a39-sound-streaming`</a> Sound Streaming | [new2026/sound-wifi-stream02.txt](./new2026/sound-wifi-stream02.txt). Use a school hotspot or make your own. The serial monitor shows the URL — the web browser MUST be on the same hotspot. | Easiest from your own cell phone: make the hotspot and view the webpage while the XIAO ML Kit is connected to your computer. The device connects almost immediately — if it doesn't connect, power cycle it. | Mason: try this on the iPhone [./new2026/sound-wifi-stream-v04-iphone.txt](./new2026/sound-wifi-stream-v04-iphone.txt). Everyone else: remember to change the hotspot SSID and password in the code. |
| <a name="a40-lora-meshtastic" href="README.md#a40-lora-meshtastic">`a40-lora-meshtastic`</a> Flash [LoRa Meshtastic](https://flasher.meshtastic.org/) code and install Meshtastic on a cell phone | [Cell Phone Meshtastic app download](https://meshtastic.org/downloads/) | When you boot the device you should be able to connect over Bluetooth to set up the phone app, then LoRa can be sent and received from the LoRa module. This allows your cell phone to send LoRa text anywhere, with or without cell reception. | Advanced: try other LoRa P2P protocols and perhaps get the OLED working. Also a possibility of getting the IMU working with EdgeImpulse to send motion data over LoRa. |
| <a name="a41-adafruit-io" href="README.md#a41-adafruit-io">`a41-adafruit-io`</a> Web AdafruitIO Connectivity | MQTT-ESP32-Websocket: [seeed-adafruit-mqtt-g.ino](seeed-sketches/seeed-adafruit-mqtt-g.ino). The MQTT library to install was written by Joel Gaehwiler and is way down on the Arduino library install list. | First [Adafruit login](https://accounts.adafruit.com/users/sign_in). Then set up a webpage websocket to see how things work: [ada-websocket02.html](https://hpssjellis.github.io/my-examples-of-iot-platforms/public/ada-websocket02.html). Use the key and username from the Adafruit IO site. Lots of information for the PortentaH7 at [Adafruit-Connectivity](https://hpssjellis.github.io/my-examples-of-iot-platforms/public/index.html). | This is a good but large project — a lot to learn here. |
| <a name="a42-ble" href="README.md#a42-ble">`a42-ble`</a> Bluetooth Connectivity — do this later; not yet tested | [seeed-draft-BLE.ino](seeed-sketches/seeed-draft-BLE.ino) | | The ESP library should have some BLE code. You will need an app like NRF Connect by Nordic Semiconductor to see the BLE connection. |

---

<br><br>

# Section 6 — Machine Learning

For the full curriculum ML reference see [maker100-curriculum Machine Learning](https://github.com/hpssjellis/maker100-curriculum#machine-learning).

Note: These assignments should be done as a break from the regular course throughout the course assignments — it is a bit heavy to do all of these back to back.

## webmcu-ai Repositories

The [webmcu-ai](https://github.com/webmcu-ai) organisation collects open-source work at the intersection of TinyML (machine learning on microcontrollers) and WebAI (machine learning in the browser via TensorFlow.js and the WebSerial API). All repos use the XIAO ESP32-S3 platform. The most important active demo is at [webmcu-ai.github.io/webmcu-vision-web/index.html](https://webmcu-ai.github.io/webmcu-vision-web/index.html).

| Repo | What it does |
| :--- | :--- |
| [on-device-vision-ai](https://github.com/webmcu-ai/on-device-vision-ai) | Complete on-device CNN training and inference. Single `.ino` file, MIT licensed. Paper 1 — arXiv April 2026. |
| [webmcu-vision-web](https://github.com/webmcu-ai/webmcu-vision-web) | Browser companion: single `index.html`, no install, WebSerial + TensorFlow.js. Working demo at [webmcu-ai.github.io/webmcu-vision-web/index.html](https://webmcu-ai.github.io/webmcu-vision-web/index.html). Paper 2 — arXiv April 2026. |
| [on-device-fomo](https://github.com/webmcu-ai/on-device-fomo) | On-device Vision FOMO (Faster Objects More Objects) — object detection with x,y centroid location, capable of multiple detections. |
| [on-device-regression](https://github.com/webmcu-ai/on-device-regression) | On-device Vision Regression — each trained class is an integer. Allows distance or size measurement based on object size from the camera. Now has an extrapolation linear equation. |
| [on-device-vision-anomaly](https://github.com/webmcu-ai/on-device-vision-anomaly) | On-device vision anomaly detection. |
| [on-device-motion](https://github.com/webmcu-ai/on-device-motion) | On-device motion using the IMU. Collects 3×40 samples of x,y,z acceleration data. Basic start of a sensor fusion model. |
| [on-device-sound](https://github.com/webmcu-ai/on-device-sound) | On-device sound machine learning model using FFT. Install the firmware on the XIAO ESP32S3 Sense (has a microphone). |

---

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a43-edgeimpulse-vision" href="README.md#a43-edgeimpulse-vision">`a43-edgeimpulse-vision`</a> Follow the EdgeImpulse Vision Classification ML model | You make the code and download it as an Arduino Library from EdgeImpulse. | [edgeimpulse.com](https://edgeimpulse.com/) — full playlist, many other videos here may help. <img src="https://img.youtube.com/vi/wbX_-No8kIw/hqdefault.jpg" width=300 /> | Good starting point: [multi-language-edgeimpulse-tutorial-vision-cell-phone](https://hpssjellis.github.io/multi-language-edgeimpulse-tutorial-vision-cell-phone/). For this assignment we are not using the microcontroller. [See Appendix F](#appendix-f-edgeimpulse-vision-model---instructions-and-chatgpt-prompt) |
| <a name="a44-webmcu-ai" href="README.md#a44-webmcu-ai">`a44-webmcu-ai`</a> On-device training with webpage support and flashing | Try the webpage [here](https://webmcu-ai.github.io/webmcu-vision-web/index.html) with a fully set-up [XIAO ML Kit](https://www.seeedstudio.com/The-XIAOML-Kit.html). Also works with just the XIAO ESP32S3 and the serial monitor, but the OLED is a nice bonus. | Watch the video — the webpage may have changed slightly, but you can do all image collection, training and inference on the webpage, then transfer to the device manually (SD card) or by clicking buttons. [![video](https://img.youtube.com/vi/WydSCn5kIFM/hqdefault.jpg)](https://youtu.be/WydSCn5kIFM?si=XoQ2vJx4zognouky) | |
| <a name="a45-xiao-motion" href="README.md#a45-xiao-motion">`a45-xiao-motion`</a> Load a three-class motion model on the XIAO ML Kit | New: run this code on the XIAO ML Kit (needs the IMU): [webmcu-ai/on-device-motion/firmware.ino](https://github.com/webmcu-ai/on-device-motion/blob/main/firmware.ino) — follow the menu, train several times. OLD: (1) Generate a CSV file with motion data: [motion-to-sd-as-csv02.txt](./xiaoML-kit/motion-to-sd-as-csv02.txt) — power cycle the XIAO between classes so each class has its own 4-digit number. (2) Upload data for each class (0still, 2punch, 3wave) to [EdgeImpulse](https://studio.edgeimpulse.com/login). (3) Download the deployment include file and install on the Arduino IDE. (4) Load this code with your include file: [motion-edgeimpulse-xiao01.txt](./xiaoML-kit/motion-edgeimpulse-xiao01.txt) | <img src="https://img.youtube.com/vi/7Aucyd10Mtw/hqdefault.jpg" width=300 /> Full playlist; many other videos here may help. <img src="https://img.youtube.com/vi/wbX_-No8kIw/hqdefault.jpg" width=300 /> Probably best to do a52-cell-motion first. | Book view: [mlsysbook motion_classification](https://mlsysbook.ai/kits/contents/seeed/xiao_esp32s3/motion_classification/motion_classification.html) and Marcello's GitHub: [XIAOML_Kit_code](https://github.com/Mjrovai/XIAO-ESP32S3-Sense/tree/main/XIAOML_Kit_code) |
| <a name="a46-xiao-classify" href="README.md#a46-xiao-classify">`a46-xiao-classify`</a> Needs old 2.0.17 ESP32 Board. Put the Vision Classification model on the XIAO ESP32S3 | Needs board version 2.0.15: [seeed-edgeimpulse-vision-fomo.ino](./seeed-sketches/seeed-edgeimpulse-vision-fomo.ino). Advanced: fix the code for the latest board ≥ 3.2.0. | <img src="https://img.youtube.com/vi/i2xg_wxBGdc/hqdefault.jpg" width=300 /> | Set Arduino Tools → PSRAM → OPI PSRAM. For Vision must presently use the old Arduino IDE ~1.8.19. Note: on EdgeImpulse, turn off the EON compiler before exporting the library. |
| <a name="a47-cell-fomo" href="README.md#a47-cell-fomo">`a47-cell-fomo`</a> Use your cell phone to make a FOMO model | | | No unknown and must choose bounding boxes. Still use grayscale and 96×96 resolution. |
| <a name="a48-xiao-fomo" href="README.md#a48-xiao-fomo">`a48-xiao-fomo`</a> Put the FOMO model onto the XIAO ESP32S3 — Needs old 2.0.17 ESP32 Board. See [Appendix F](#appendix-f-edgeimpulse-vision-model---instructions-and-chatgpt-prompt). | Needs board version 2.0.17. Works on both new and old Arduino IDE: [seeed-edgeimpulse-vision-fomo.ino](./seeed-sketches/seeed-edgeimpulse-vision-fomo.ino). Also try this for the XIAO ML Kit: [xiaoml-96x96-rgb-fomo-eyes-oled.ino](xiaoML-kit/xiaoml-96x96-rgb-fomo-eyes-oled.ino) | <img src="https://img.youtube.com/vi/i2xg_wxBGdc/hqdefault.jpg" width=300 /> | Must download the deployment Arduino library from EdgeImpulse and see the example to get the include filename, then copy that include filename to the code. |
| <a name="a49-cell-wake-word" href="README.md#a49-cell-wake-word">`a49-cell-wake-word`</a> Use your cell phone to make a Yes/No/unknown Sound Model | | | Follow the wizard on EdgeImpulse to make a verbal ML model using your cell phone. Then download the Arduino deployment, install the zipped Arduino library and choose the default Portenta Sound example. Talk into your Portenta and view the serial monitor. Then get the onboard LED to respond to your voice. |
| <a name="a50-xiao-wake-word" href="README.md#a50-xiao-wake-word">`a50-xiao-wake-word`</a> Put the Sound (wake word) model onto the XIAO ESP32S3 — Needs old 2.0.17 ESP32 Board. See [Appendix F](#appendix-f-edgeimpulse-vision-model---instructions-and-chatgpt-prompt). | As far as I can tell student Riley fixed this one: [seeed-edgeimpulse-sound.ino](./seeed-sketches/seeed-edgeimpulse-sound.ino) | | Make the normal EdgeImpulse sound model, then deployment → Arduino and add the zipped library to the Arduino IDE. View the example to get the proper include filename and use that filename with the code provided. |
| <a name="a51-cli" href="README.md#a51-cli">`a51-cli`</a> (optional) Try the EdgeImpulse connection method | [edgeimpulse.com](https://studio.edgeimpulse.com/login) | | |
| <a name="a52-cell-motion" href="README.md#a52-cell-motion">`a52-cell-motion`</a> EdgeImpulse cell phone motion x,y,z model | | | Do this for later in the course when we use the RAK2270StickerTracker. If you have a motion sensor for the XIAO ESP32S3-Sense you could upload this model to it, but that is optional. |
| <a name="a53-vision-regression" href="README.md#a53-vision-regression">`a53-vision-regression`</a> Vision Regression Analysis | Have it work on your cell phone only. Regression means every label is an integer. | | Same as Vision Classification except no unknown and each label is an integer value reflecting some size or distance. At "Add a Learning block" only add the Regression block. We will do the distance to a computer mouse from above — try to train 1m, 2m and 3m. Then on classification the model should estimate the distance. |
| <a name="a54-anomaly" href="README.md#a54-anomaly">`a54-anomaly`</a> Vision Anomaly Detection | Have it work on your cell phone only. Anomaly detection is a measure of how different something is from the trained set. | | Train visually on what you expect. You can do 0unknown and 1pen like the first vision classification example — just change classification to Anomaly Detection in the learning block. On classification the model should detect the pen and rate its anomaly. Note: For FOMO-AD, replace the learning Object Detection block with Visual Anomaly Detection - FOMO-AD. You don't use bounding boxes — just images of the object. In Dashboard, far right-hand side, remove bounding boxes and select "one label per data item". You can switch back and forth between FOMO and FOMO-AD. |
| <a name="a55-fomo-gray-oled" href="README.md#a55-fomo-gray-oled">`a55-fomo-gray-oled`</a> EdgeImpulse Vision FOMO with Grayscale OLED | Use the Vision grayscale OLED from above and the new code: [seeed-camera-96x96-to-waveshare-grayscale-oled.ino](https://github.com/hpssjellis/maker100-eco/blob/main/seeed-sketches/seeed-camera-96x96-to-waveshare-grayscale-oled.ino). Note: like using the EdgeImpulse FOMO library, this code needs Arduino IDE ESP32 board version 2.0.17 (version 3.x has a breaking change). Better code to try: [a21b-SLOW-edgeimpulse-fomo-96x96-gray.ino](https://github.com/hpssjellis/maker100-xiaoML-kit/blob/main/seeed-sketches/a21b-SLOW-edgeimpulse-fomo-96x96-gray.ino). Get used to this — it is called DEPRECATION and is very stressful for anyone in coding. | [![video](https://img.youtube.com/vi/weNVGGaQO50/hqdefault.jpg)](https://www.youtube.com/watch?v=weNVGGaQO50&list=PL57Dnr1H_egt9XmHjfcyRR4YCo3eGrZwQ&index=2&pp=iAQB) Use the code given, then just change the default FOMO include file name to the deployed EdgeImpulse include file name. | Like the original classification model, just now with bounding boxes — label each object to detect. |

---

<br><br>

# Section 7 — WebAI / EdgeAI

For the full curriculum WebAI reference see [maker100-curriculum WebAI](https://github.com/hpssjellis/maker100-curriculum/blob/main/README.md#webai-edgeai).

Note: As microcontrollers get stronger, faster, and use less power, what is now WebAI/EdgeAI will eventually be TinyML, so it is best that students see what is coming and learn some WebAI. Getting them working is just a pass — changing them to do something unique creates the higher grade.

| Topic | Example Code | Video | Instructions and Prompt |
| :--- | :--- | :--- | :--- |
| <a name="a56-handpose" href="README.md#a56-handpose">`a56-handpose`</a> HandPose | Make a video of this webpage working: [handpose](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/handpose/index.html) | Your first [Maker100-Curriculum WebAI](https://github.com/hpssjellis/maker100-curriculum?tab=readme-ov-file#webai-edgeai) assignment — working presently on your cell phone or desktop/laptop. Eventually TinyML will be powerful enough to run this on the device. Note: Several Raspberry Pis and the Arduino UnoQ can already run this code from a web browser on the Linux tiny device. | |
| <a name="a57-webai-assignments" href="README.md#a57-webai-assignments">`a57-webai-assignments`</a> All WebAI Assignments | Prove you can get most of these working. Links are on the [Maker100-curriculum-webAI](https://github.com/hpssjellis/maker100-curriculum/blob/main/README.md#webai-edgeai) page. | Copy the examples and get the webpages working. | One of the few assignments that may need its own folder, but the video gets copied into the main folder. Slightly change each program. ~10 programs, one grade. We have already done the HandPose. |

**Quick links for WebAI examples (cell phone or school computer):**

| # | Demo | Link |
| :--- | :--- | :--- |
| WebAI-01 | HandPose | [handpose](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/handpose/index.html) |
| WebAI-02 | FaceMesh | [facemesh](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/facemesh/index.html) |
| WebAI-03 | BlazeFace | [blazeface](https://rocksetta.com/tensorflowjs/tfjs-models/blazeface/index.html) |
| WebAI-04 | BodyPix | [bodypix](https://rocksetta.com/tensorflowjs/tfjs-models/bodypix/index.html) |
| WebAI-05 | PoseNet | [posenet](https://rocksetta.com/tensorflowjs/tfjs-models/posenet/index.html) |
| WebAI-06 | Vector Search | [vector_search.html](https://hpssjellis.github.io/webAi-updates-early-2026/vector_search.html) |
| WebAI-07 | Live Scene | [live_scene.html](https://hpssjellis.github.io/webAi-updates-early-2026/live_scene.html) |
| WebAI-08 | Web YOLO | [web_yolo.html](https://hpssjellis.github.io/webAi-updates-early-2026/web_yolo.html) |
| WebAI-09 | Vision | [vision.html](https://hpssjellis.github.io/webAi-updates-early-2026/vision.html) |
| WebAI-10 | Console Simple | [console_simple.html](https://hpssjellis.github.io/webAi-updates-early-2026/console_simple.html) |

**Desktop-only WebAI examples (good desktop computer required, some need admin access):**

| # | Demo | Link |
| :--- | :--- | :--- |
| WebAI-D01 | Gemma4 (1GB download) | [my-examples-of-gemma4/index.html](https://hpssjellis.github.io/my-examples-of-gemma4/index.html) — better to download locally |
| WebAI-D02 | EdgeImpulse FOMO WASM on web | [multi-language-edgeimpulse-tutorial-vision-cell-phone](https://hpssjellis.github.io/multi-language-edgeimpulse-tutorial-vision-cell-phone/) |
| WebAI-D03 | BodyPix Segmentation | [bodypix](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/bodypix/index.html) |
| WebAI-D04 | PoseNet | [posenet](https://hpssjellis.github.io/beginner-tensorflowjs-examples-in-javascript/tfjs-models/posenet/index.html) |
| WebAI-D05 | Browser RAG | [deep-rag00.html](https://hpssjellis.github.io/my-examples-of-transformersJS/public/deep-rag/deep-rag00.html) |
| WebAI-D06 | Chrome Built-in AI | [webllm00.html](https://hpssjellis.github.io/my-examples-of-web-llm/public/webllm00.html) |
| WebAI-D07 | DeepSeekR1 1.5B | [deepseek-r1-webgpu-00.html](https://hpssjellis.github.io/my-examples-of-transformersJS/public/deepseek-r1-webgpu/deepseek-r1-webgpu-00.html) |
| WebAI-D08 | Janus-Pro Text to Image | [janus-pro-to-image-00.html](https://hpssjellis.github.io/my-examples-of-transformersJS/public/janus-pro/janus-pro-to-image-00.html) |
| WebAI-D09 | GeminiNano (4GB, 20GB disk) | [webllm00.html](https://hpssjellis.github.io/my-examples-of-web-llm/public/webllm00.html) |
| WebAI-D10 | Local LLM | [local_llm.html](https://hpssjellis.github.io/webAi-updates-early-2026/local_llm.html) |
| WebAI-D11 | Local Llama | [local-llama.html](https://hpssjellis.github.io/webAi-updates-early-2026/local-llama.html) |
| WebAI-D12 | Text | [text.html](https://hpssjellis.github.io/webAi-updates-early-2026/text.html) |
| WebAI-D13 | Translate | [translate.html](https://hpssjellis.github.io/webAi-updates-early-2026/translate.html) |
| WebAI-D14 | Speak to Text | [speak-to-text.html](https://hpssjellis.github.io/webAi-updates-early-2026/speak-to-text.html) |
| WebAI-D15 | Speak to Translate | [speak-to-translate.html](https://hpssjellis.github.io/webAi-updates-early-2026/speak-to-translate.html) |
| WebAI-D16 | WebAI updates early 2026 overview | [webAi-updates-early-2026](https://hpssjellis.github.io/webAi-updates-early-2026/) |

---

<br><br>

# Final Course Projects

Student must complete an individual final project to pass the in-person course; your teacher might have different requirements.

| # | Topic | Example Code | Video | Instructions |
| :--- | :--- | :--- | :--- | :--- |
| <a name="FP1" href="README.md#FP1">`FP1`</a> | One sensor with one actuator — needed to pass the course! | | | [See Appendix I - Final Project 1](#appendix-i) |
| <a name="FP2" href="README.md#FP2">`FP2`</a> | Complex sensor, ML, complex actuator and/or IoT communication — needed to get an "A" in the course | | | [See Appendix J - Final Project 2](#appendix-j) |
| <a name="FP3" href="README.md#FP3">`FP3`</a> | Group final project — proof of concept for a viable product or something fun and creative. Each person in the group brings a skill. Groups often organized by the teacher. Not required, but typically brings a final grade up a few percentage points. | | | [See Appendix K - Final Project 3](#appendix-k) |

---

<br><br>

# Tutorials If Needed

## Tutorial ml16

Arduino IDE: load board XIAO ESP32S3, PSRAM → OPI PSRAM, plugin XIAO ML Kit to USBA, Tools → Port, upload, reset board, type T or L in serial monitor.

For PlatformIO: install VS Code, PlatformIO extension, new project, board XIAO ESP32S3, load code into main.cpp, fix platformio.ini file, upload, serial monitor, T (tap) or L (longpress).

Code to load on PlatformIO and the Arduino IDE: [esp-all-menu-A0-image-train-infer.txt](https://github.com/hpssjellis/my-examples-of-tensorflowjs-for-tinytorch/blob/main/esp-on-device-train-one-program/esp-all-menu-A0-image-train-infer.txt)

**Prompt:** Help me load this code https://github.com/hpssjellis/my-examples-of-tensorflowjs-for-tinytorch/blob/main/esp-on-device-train-one-program/esp-all-menu-A0-image-train-infer.txt onto both the Arduino IDE and PlatformIO to compare them.

---

#### Jeremy Ellis — [LinkedIn](https://ca.linkedin.com/in/jeremy-ellis-4237a9bb)
#### High School Coding (35 Years), Robotics, Web Design, Animation and 3D Printing Teacher, BC Canada
#### Use this in-person course at your own risk!

---

<br><br>

# Appendices

## Appendix A: Teacher Extras — Why Not Use the XIAO Expansion Board and Round Display?

The Seeedstudio [$16.40 USD Expansion board](https://wiki.seeedstudio.com/Seeeduino-XIAO-Expansion-Board/) and [$18.00 USD Round Display](https://wiki.seeedstudio.com/get_start_round_display/) are amazing inexpensive add-ons to the XIAO ESP32S3-Sense and are very well explained on the Getting Started sites listed above.

I have both for my classrooms and may use them as the year goes on, but I have testing to do to find out if the colour round display is as fast as my greyscale OLED, and I do not like students using I2C and SPI connectors that come with the expansion board because students naturally begin to feel they can only use sensors and actuators that come with the correct connectors.

For their final projects, students stay away from new or unusual sensors/actuators because those sensors do not come with the correct connectors. A possible solution is to have [grove-4-pin-female-jumper-wires](https://ca.robotshop.com/products/grove-4-pin-female-jumper-wire) — I would prefer male pins but it is electrically safer to have female pins. If you are starting a course and know you will stick with the [Grove sensor/actuator system](https://wiki.seeedstudio.com/Grove_System/) and have a few extra connectors on bare wires for new devices, the expansion board might be a great way to teach.

If you choose to use the expansion board, this ebook [here](https://mjrovai.github.io/XIAO_Big_Power_Small_Board-ebook/) covers working with it very well.

---

## Appendix B: Teacher Tips — Teaching Guidelines and Best Practices

1. Students work on term assignments in partners and make very short videos teaching what they did for each assignment. Note: Students often learn much better working individually. Partnered groups typically drift to one person coding and the other connecting wires — neither learns Robotics well. Be clear about this concern. Final projects are individual, except the optional third final.
2. I expect all students to try to improve and change each assignment. "Until you change computer code do not expect to understand it."
3. MAKE EACH STUDENT DRAW THEIR OWN CIRCUIT DIAGRAM FOR EACH ASSIGNMENT. For easy assignments I make it hard for students to know how to connect the wires. I only give students clear diagrams for the difficult connections. Let students think — these are not fully made recipes!
4. For 2026 I will be using Wokwi for diagrams. Students can look at the diagram but must still make their own drawing that they understand (all connections labelled, perhaps including wire colour).
5. I expect all students to draw circuit diagrams before connecting wires and have someone check the diagram, then connect the wires and have someone check again before students connect power.
6. I teach one assignment per class but expect several students to work ahead and solve missing parts of the process in small groups; some students will fall behind. This allows us to have fewer sensors and actuators since the class rarely uses them all at the same time. I can often get away with 4 sensors for a 30-person class.
7. All assignments should be completed individually so that each student does the entire pipeline; students may work in partners but take turns at the computer.
8. Students should wipe the code after making their video so the next student needs to program it from scratch.
9. This GitHub of very fast instructions allows more dedicated students to work ahead and helps students who missed a class. THE VIDEOS ARE NOT EXPECTED TO BE AN ONLINE COURSE. THIS IS AN IN-PERSON COURSE! Educators can add important information and problem-solve many issues very difficult to solve at home in a fast-paced changing technological landscape.
10. The faster students finish the course, the more time they have for final projects.
11. To pass the course everyone must complete at least one final project using a sensor connected to an actuator of their choice.
12. Students plan 2 individual main projects and possibly one group project. Each main project must include at least one sensor with one actuator.
13. Many students will only complete one main project and that is fine. "Robotics projects are very difficult to finish."
14. Many final projects will need structures built to support them. Any safe material is fine — we typically 3D print the structures, although cardboard and/or wood is often used.
15. Final projects typically do not involve high voltage, water, or drones for the obvious safety reasons.
16. I tell students that if every term assignment is complete, the individual final project is their full mark if that helps their grade.
17. Teachers may decide to make several of the advanced assignments optional or even set for bonus marks.
18. Use an LLM for help — what I do with the free versions: [Claude.ai](https://claude.ai/new) for all help, [Gemini](https://gemini.google.com/app) for all research, [ChatGPT](https://chatgpt.com/) for advanced critique, [CoPilot](https://www.copilot.com/) for creative solutions and understanding code.

---

## Appendix C: Why Maker100-xiaoML-kit?

The Arduino PortentaH7 with LoRa Vision Shield is an incredible TinyML device that can do amazing things and has been a joy to teach, but I am part of an international group trying to bring TinyML to students in developing countries called [tinyML4D](https://tinyml.seas.harvard.edu/team) and the Arduino PortentaH7 is just too expensive for student explorations. Also when you fry one of these boards it is very upsetting.

---

## Appendix D: Price Comparison — How Much Cheaper Is the XIAOML Kit Version?

The [Arduino PortentaH7](https://store-usa.arduino.cc/products/portenta-h7) costs $113.90 USD. The [LoRa Vision Shield](https://store-usa.arduino.cc/products/arduino-portenta-vision-shield-lora%C2%AE) costs $69 USD.

The [XiaoEsp32s3-sense](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html) costs $13.99.

The [XIAO ML Kit](https://www.seeedstudio.com/The-XIAOML-Kit.html) is $22 USD without cables and micro SD card, and $38.90 USD with everything (ESP32S3 Sense with camera, microphone, SD Card module, IMU OLED module, cables, SD card reader and micro SD card — you can start learning immediately).

Very hard to compare a class set of 15 × $38.90 USD = $583.50 USD with a class set of PortentaH7s (15 × $182.90) = $2,743.50 USD.

---

## Appendix E: Useful Links

1. Simplified course layout and organisation: [course-order.md](course-order.md)
2. The original Maker100 Course: [https://github.com/hpssjellis/maker100](https://github.com/hpssjellis/maker100)
3. Excellent reference for the XIAO ESP32S3 section of this course: [XIAO_Big_Power_Small_Board-ebook](https://mjrovai.github.io/XIAO_Big_Power_Small_Board-ebook/)
4. SeeedStudio link to the XIAO ESP32S3-Sense store: [https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html](https://www.seeedstudio.com/XIAO-ESP32S3-Sense-p-5639.html) — Note: It needs headers soldered to do many assignments.
5. The original XiaoEsp32s3 and RAK2270 research: [https://github.com/hpssjellis/mcu-stable-edu-launch](https://github.com/hpssjellis/mcu-stable-edu-launch)
6. TinyMLjs: [https://github.com/hpssjellis/tinyMLjs](https://github.com/hpssjellis/tinyMLjs)
7. RocksettaTinyML Library: [https://github.com/hpssjellis/RocksettaTinyML](https://github.com/hpssjellis/RocksettaTinyML)

---

## Appendix F: EdgeImpulse Vision Model — Instructions and ChatGPT Prompt

**More Instructions:**

Connect your cell phone to EdgeImpulse, take 30 images of pens on various backgrounds, then take 50 images of various backgrounds without pens, create your impulse (96×96), generate features, train and then switch to classification on your cell phone.

> ⚠️ **EdgeImpulse is made for an older board version of the Expressif ESP32 board.**
> **IF THE CODE DOES NOT WORK, REMOVE THE ESP32 BOARD THEN RE-INSTALL BOARD 2.0.17.**
> **DO NOT UPDATE TO 2.0.17 — IT WILL TIMEOUT. Works better after a full ESP32 board remove.**

**ChatGPT Prompt:**

> Give me the steps to make a vision classification model on edgeimpulse.com with only an unknown label for the background and pens for the object. We will only be using our cell phone to collect the images, so it will need to be connected to the EdgeImpulse site. The cell phone will allow image labelling before I take the images. After the images are taken, explain how to set up the impulse machine learning model.

---

## Appendix G: Camera SD Card Instructions — More Details

Anytime you use the XIAO ESP32S3 Sense Camera you may run into pin issues. This pin setup works:

```cpp
// NOTE: Must have compile setting PSRAM: OPI PSRAM

// Frame sizes available:
// FRAMESIZE_96X96, FRAMESIZE_QQVGA (160x120), FRAMESIZE_QCIF (176x144),
// FRAMESIZE_HQVGA (240x176), FRAMESIZE_240X240, FRAMESIZE_QVGA (320x240),
// FRAMESIZE_CIF (400x296), FRAMESIZE_HVGA (480x320), FRAMESIZE_VGA (640x480),
// FRAMESIZE_SVGA (800x600), FRAMESIZE_XGA (1024x768), FRAMESIZE_HD (1280x720),
// FRAMESIZE_SXGA (1280x1024), FRAMESIZE_UXGA (1600x1200)
// 3MP: FRAMESIZE_FHD (1920x1080), FRAMESIZE_P_HD (720x1280), FRAMESIZE_QXGA (2048x1536)
// 5MP: FRAMESIZE_QHD (2560x1440), FRAMESIZE_WQXGA (2560x1600), FRAMESIZE_QSXGA (2560x1920)

// Pixel formats: PIXFORMAT_RGB565, PIXFORMAT_YUV422, PIXFORMAT_YUV420,
// PIXFORMAT_GRAYSCALE, PIXFORMAT_JPEG, PIXFORMAT_RGB888, PIXFORMAT_RAW,
// PIXFORMAT_RGB444, PIXFORMAT_RGB555

// XIAO ESP32S3 camera pin definitions:
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM     10
#define SIOD_GPIO_NUM     40
#define SIOC_GPIO_NUM     39
#define Y9_GPIO_NUM       48
#define Y8_GPIO_NUM       11
#define Y7_GPIO_NUM       12
#define Y6_GPIO_NUM       14
#define Y5_GPIO_NUM       16
#define Y4_GPIO_NUM       18
#define Y3_GPIO_NUM       17
#define Y2_GPIO_NUM       15
#define VSYNC_GPIO_NUM    38
#define HREF_GPIO_NUM     47
#define PCLK_GPIO_NUM     13
```

---

## Appendix H: XIAO ESP32S3-Sense Pinout Diagram

### Safe Pins When the XIAOML Kit Is Fully Connected and All Items Running

| Pin Label | GPIO | Internal Usage / Hardware Conflict | Status |
| :--- | :--- | :--- | :--- |
| **D0 / A0** | GPIO 1 | None | ✅ SAFE |
| **D1 / A1** | GPIO 2 | None | ✅ SAFE |
| **D2 / A2** | GPIO 3 | Strapping Pin (Keep HIGH/Float at boot) | ✅ SAFE |
| **D3 / A3** | GPIO 4 | None | ✅ SAFE |
| **D4 / A4** | GPIO 5 | **I2C SDA** (IMU & OLED) | ⚠️ SHARED |
| **D5 / A5** | GPIO 6 | **I2C SCL** (IMU & OLED) | ⚠️ SHARED |
| **D6** | GPIO 43 | None (UART0 TX by default) | ✅ SAFE |
| **D7** | GPIO 44 | None (UART0 RX by default) | ✅ SAFE |
| **D8 / A8** | GPIO 7 | **SPI SCK** (SD Card) | ⚠️ SHARED |
| **D9 / A9** | GPIO 8 | **SPI MISO** (SD Card) | ⚠️ SHARED |
| **D10 / A10** | GPIO 9 | **SPI MOSI / CS** (SD Card & User LED) | ⚠️ SHARED |
| **D11** | GPIO 41 | **PDM Mic Data** (Extra Camera Pin) | ⚠️ SHARED |
| **D12** | GPIO 42 | **PDM Mic Clock** (Extra Camera Pin) | ⚠️ SHARED |

<img width="1485" height="1255" alt="XIAO ESP32S3 pinout" src="https://github.com/user-attachments/assets/dd1f4474-8a7d-4989-9bc9-74fa03fd6a21" />

View the old [maker100](https://github.com/hpssjellis/maker100#latest-portenta-pinout) course for the Portenta Pinout Diagram.

View the old [XIAO SAMD21 pinout](https://github.com/hpssjellis/maker100#xiao-pinout) diagram (has a few slight differences from the XIAO ESP32S3 board).
