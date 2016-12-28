# Duckduino-microSD
Interpreter that runs on an arduino, decodes and executes ducky script on a microSD card.

## Benefits Over Alternatives
Once the arduino has been programmed, you need only deal with ducky scripts on a microSD card. No reprogramming the arduino to change scripts!

## Setup

[![video link](http://img.youtube.com/vi/ksvo1WDYQ7s/mqdefault.jpg)](https://www.youtube.com/watch?v=ksvo1WDYQ7s)

The instructions are for an arduino pro micro, it should work on any arduino using an atmega32u4 chip such as the leonardo.
Simply upload Duckduino-microSD to your arduino, format your microSD to FAT32 and save your script on the microSD card titled script.txt
Lastly, connect a microsd breakout board using the pins below
```
Arduino ||| microSD module

VCC  --->   VCC

D15  --->   SCK

D14  --->   MISO

D16  --->   MOSI

GND  --->   GND

D4   --->   CS
```

## Keep in mind...
~~Long lines of strings may crash the arduino due to taking up too much RAM, if you have a line "STRING ..." over 300 characters then split it into separate lines of strings, this won't affect how your script runs, it just reduces how much of your script is held in memory at any one time.~~
**Should Now Run With Strings Larger than 300**

I have seen some ducky scripts that put hyphens (-) in between keys to be pressed simultaneously eg."CTRL-ALT DELETE". Note that when using duckduino-microSD you must not use hyphens and instead just use spaces eg."CTRL ALT DELETE"

~~The following duckyscript features are not yet implemented: DEFAULT_DELAY, REPLAY~~.
REPLAY,DEFAULT_DELAY And MENU Now Work

This project uses arduino's inbuilt <a href="https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h">keyboard.h</a> library, any keys not implemented in that will not work with this. eg: PRINTSCREEN.

**Script Commands Also Added**
```
HIGH x ||| Puts Pin x To High Logic Level
LOW x ||| Puts Pin x to Low Logic Level
CPY filename.extension  ||| Writes The Contents of the file to the host
PULLUP x / WAIT_PULLUP x ||| Executes The Rest Of the Code After Pin x is connected to Ground

```

This has only been tested on the following <a href="https://www.amazon.co.uk/Micro-Adapter-Reader-Module-Arduino/dp/B00NNDBIRK">microSD module</a>,Also Works With This  <a href="http://www.amazon.in/Reader-Writer-Module-Socket-Arduino/dp/B008B52QQC">SD Card Reader</a> ,I'm sure others will work, though no guarantees.
