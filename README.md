# Duckduino-microSD
Interpreter that runs on an arduino, decodes and executes ducky script on a microSD card.

## Benefits Over Alternatives
Once the arduino has been programmed, you need only deal with ducky scripts on a microSD card. No reprogramming the arduino to change scripts!

## Setup
The instructions are for an arduino pro micro, it should work on any arduino using an atmega32u4 chip such as the leonardo.
Simply upload Duckduino-microSD to your arduino, forma your microSD to FAT32 and save your script on the microSD card titled script.txt
Lastly, connect a microsd breakout board using the pins below

Arduino ||| microSD module

VCC  --->   VCC

D15  --->   SCK

D14  --->   MISO

D16  --->   MOSI

GND  --->   GND

D4   --->   CS

## Caveats
The following duckyscript features are not yet implemented: DEFAULT_DELAY, REPLAY. This project uses arduino's inbuilt <a href="https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h">keyboard.h</a> library, any keys not implemented in that will not work with this. eg: PRINTSCREEN.
This has only been tested on the following <a href="https://www.amazon.co.uk/Micro-Adapter-Reader-Module-Arduino/dp/B00NNDBIRK">microSD module</a>, I'm sure others will work, though no guarantees.
