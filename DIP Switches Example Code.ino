/*
 * Author: Seytonic,Draguve
 *         https://twitter.com/seytonic
 *         https://twitter.com/draguve
 *         https://www.youtube.com/seytonic
 * GIT:
 *         https://github.com/Seytonic/Duckduino-microSD
 */
#include <SPI.h>
#include <SD.h>
#include <string.h>
#include "Keyboard.h"

File myFile;
boolean first = true;
String DEFAULT_FILE_NAME = "script.txt";
unsigned long thisLineStartPos=0;
unsigned long lastLineStartPos;
void setup() {
    String dip = ""; // Name of the file that will be opened

    // Sets the given pins as switches for the dip switches
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);
    pinMode(8, INPUT_PULLUP);
    pinMode(9, INPUT_PULLUP);

    // Switches are checked, dip string is contructed
    if (digitalRead(6) == LOW){dip += "1";} else {dip += "0";}
    if (digitalRead(7) == LOW){dip += "1";} else {dip += "0";}
    if (digitalRead(8) == LOW){dip += "1";} else {dip += "0";}
    if (digitalRead(9) == LOW){dip += "1";} else {dip += "0";}

    dip += ".txt";

  //Keyboard.begin();
  if (!SD.begin(4)) {
    Keyboard.print("Problem");
    return;
  }

  myFile = SD.open(dip);
  if (myFile) {
    Keyboard.begin();
    String line = "";
    while (myFile.available()) {
      char m = myFile.read();
      if (m == '\n'){
        Line(line);
        line = "";
        lastLineStartPos = thisLineStartPos;
        thisLineStartPos = myFile.position();
        }
        else if((int) m != 13)
        {
          line += m;
        }
        if(line.length()==7){
          if(line.equals("STRING ")){
              unsigned long strPos = myFile.position();
              printString(strPos);
              line = "";
              lastLineStartPos = thisLineStartPos;
              thisLineStartPos = myFile.position();
            }
        }
    }
    Line(line);
    myFile.close();
  } else {
  }
  Keyboard.end();
}

void Line(String l)
{
  int space_1 = l.indexOf(" ");
  if (space_1 == -1)
  {
    Press(l);
  }
  else if (l.substring(0,space_1) == "DELAY")
  {
    int delaytime = l.substring(space_1 + 1).toInt();
    delay(delaytime);
  }
  else if (l.substring(0,space_1) == "DEFAULT_DELAY"||l.substring(0,space_1) == "DEFAULTDELAY")
  {
    delay(100);
  }
  else if(l.substring(0,space_1) == "REM"){}
  else if(l.substring(0,space_1) == "CPY"){
    File cpyFile = SD.open(l.substring(space_1+1));
    if (cpyFile) {
      while (cpyFile.available()) {
        Keyboard.write(cpyFile.read());
      }
      cpyFile.close();
  }
  }
  else if(l.substring(0,space_1) == "REPLAY" || l.substring(0,space_1) == "REPEAT"){
      unsigned long toGoTo = myFile.position();
      myFile.seek(lastLineStartPos);
      String nline="";
      bool isString = false;
      int noOfTimes = l.substring(space_1+1).toInt();
      bool foundLine=false;
      while(!foundLine){
        char m = myFile.read();
        if (m == '\n'){
            foundLine=true;
        }
        else if((int) m != 13)
        {
          nline += m;
        }
        if(nline.length()==7){
          if(nline.equals("STRING ")){
            isString=true;
            foundLine=true;
          }
        }
      }
      if(isString){
        unsigned long stringPos = myFile.position();
        for(int i=0;i<noOfTimes;i++){
          printString(stringPos);
          myFile.seek(stringPos);
        }
      }else{
        for(int i=0;i<noOfTimes;i++){
          Line(nline);
        }
      }
      myFile.seek(toGoTo);
  }
  else if(l.substring(0,space_1) == "WAIT_PULLUP" || l.substring(0,space_1) == "PULLUP"){
    int pin = l.substring(space_1+1).toInt();
    if(pin>1 && pin<=10 && pin!=4 && pin!=6 && pin!=7 && pin!=8 && pin!=9){
      pinMode(pin,INPUT_PULLUP);
      bool allowed = false;
      while(!allowed){
        if(digitalRead(pin) == LOW){
          allowed=true;
        }
      }
    }
  }
  else if(l.substring(0,space_1) == "HIGH"){
    int pin = l.substring(space_1+1).toInt();
    if(pin>1 && pin<=10 && pin!=4 && pin!=6 && pin!=7 && pin!=8 && pin!=9){
      pinMode(pin,OUTPUT);
      digitalWrite(pin,HIGH);
    }
  }
  else if(l.substring(0,space_1) == "LOW"){
    int pin = l.substring(space_1+1).toInt();
    if(pin>1 && pin<=10 && pin!=4 && pin!=6 && pin!=7 && pin!=8 && pin!=9){
      pinMode(pin,OUTPUT);
      digitalWrite(pin,LOW);
    }
  }
  else{
      String remain = l;

      while(remain.length() > 0)
      {
        int latest_space = remain.indexOf(" ");
        if (latest_space == -1)
        {
          Press(remain);
          remain = "";
        }
        else
        {
          Press(remain.substring(0, latest_space));
          remain = remain.substring(latest_space + 1);
        }
        delay(5);
      }
  }
  Keyboard.releaseAll();
}

void printString(unsigned long strPos){
  myFile.seek(strPos);
  bool lineEnding=false;
  while(!lineEnding){
      char m = myFile.read();
      if(m!='\n'){
          Keyboard.write(m);
        }else{
          lineEnding=true;
        }
    }
   //myFile.seek(strPos);
}


void Press(String b)
{
  if(b.length() == 1)
  {
    char c = b[0];
    Keyboard.press(c);
  }
  else if (b.equals("ENTER"))
  {
    Keyboard.press(KEY_RETURN);
  }
  else if (b.equals("CTRL")||b.equals("CONTROL"))
  {
    Keyboard.press(KEY_LEFT_CTRL);
  }
    else if (b.equals("SHIFT"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
  }
    else if (b.equals("ALT"))
  {
    Keyboard.press(KEY_LEFT_ALT);
  }
    else if (b.equals("GUI") || b.equals("WINDOWS") || b.equals("COMMAND"))
  {
    Keyboard.press(KEY_LEFT_GUI);
  }
    else if (b.equals("UP") || b.equals("UPARROW"))
  {
    Keyboard.press(KEY_UP_ARROW);
  }
    else if (b.equals("DOWN") || b.equals("DOWNARROW"))
  {
    Keyboard.press(KEY_DOWN_ARROW);
  }
    else if (b.equals("LEFT") || b.equals("LEFTARROW"))
  {
    Keyboard.press(KEY_LEFT_ARROW);
  }
    else if (b.equals("RIGHT") || b.equals("RIGHTARROW"))
  {
    Keyboard.press(KEY_RIGHT_ARROW);
  }
    else if (b.equals("DELETE")|| b.equals("DEL"))
  {
    Keyboard.press(KEY_DELETE);
  }
    else if (b.equals("PAGEUP"))
  {
    Keyboard.press(KEY_PAGE_UP);
  }
    else if (b.equals("PAGEDOWN"))
  {
    Keyboard.press(KEY_PAGE_DOWN);
  }
    else if (b.equals("HOME"))
  {
    Keyboard.press(KEY_HOME);
  }
    else if (b.equals("ESC") || b.equals("ESCAPE"))
  {
    Keyboard.press(KEY_ESC);
  }
    else if (b.equals("INSERT"))
  {
    Keyboard.press(KEY_INSERT);
  }
    else if (b.equals("TAB"))
  {
    Keyboard.press(KEY_TAB);
  }
    else if (b.equals("END"))
  {
    Keyboard.press(KEY_END);
  }
    else if (b.equals("CAPSLOCK") || b.equals("CAPS"))
  {
    Keyboard.press(KEY_CAPS_LOCK);
  }
    else if (b.equals("F1"))
  {
    Keyboard.press(KEY_F1);
  }
    else if (b.equals("F2"))
  {
    Keyboard.press(KEY_F2);
  }
    else if (b.equals("F3"))
  {
    Keyboard.press(KEY_F3);
  }
    else if (b.equals("F4"))
  {
    Keyboard.press(KEY_F4);
  }
    else if (b.equals("F5"))
  {
    Keyboard.press(KEY_F5);
  }
    else if (b.equals("F6"))
  {
    Keyboard.press(KEY_F6);
  }
    else if (b.equals("F7"))
  {
    Keyboard.press(KEY_F7);
  }
    else if (b.equals("F8"))
  {
    Keyboard.press(KEY_F8);
  }
    else if (b.equals("F9"))
  {
    Keyboard.press(KEY_F9);
  }
    else if (b.equals("F10"))
  {
    Keyboard.press(KEY_F10);
  }
    else if (b.equals("F11"))
  {
    Keyboard.press(KEY_F11);
  }
    else if (b.equals("F12"))
  {
    Keyboard.press(KEY_F12);
  }
    else if (b.equals("SPACE"))
  {
    Keyboard.press(' ');
  }
    else if (b.equals("MENU") || b.equals("APP"))
  {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_F10);
  }
}

void loop() {
  // nothing happens after setup
}
