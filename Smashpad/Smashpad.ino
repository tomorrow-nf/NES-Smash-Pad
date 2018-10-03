#include "Nintendo.h"
/* This code uses the Nicohood Library
 * Use this code at your own risk
 * Code written by Simple Controllers and this code is open source.
 * Meaning its free to share, improve on, or anything you like!
 * Just remember to mention you used my code!
 * Version 2.0 I just suck at github
 */
CGamecubeConsole GamecubeConsole(26);      //Defines a "Gamecube Console" sending data to the console on pin 8
Gamecube_Data_t d = defaultGamecubeData;   //Structure for data to be sent to console
CGamecubeController GamecubeController1(25);

const int A = 8;
const int B = 9;
const int X = 10;
const int Z = 11;

// Output a digital signal on L too for other games
const int L = 12;
const int LLIGHT = 255;

const int START = 13;

const int LEFT = 4;
const int RIGHT = 3;
const int UP = 2;
const int DOWN = 5;

const int M1 = 6;
const int M2 = 7;

// Analog modifiers
const int M1y = 28; // Wavedash. No X-axis mod.
const int M1x = 0;
const int M2y = 54; // Shield drop on down. X tilt.
const int M2x = 43;
const int M3y = 52; // Both at once, for people with 3 feet
const int M3x = 43;

void setup()
{
  //This is establishing the pin assignments up there to input pins
  pinMode(A, INPUT_PULLUP);
  pinMode(B, INPUT_PULLUP);
  pinMode(X, INPUT_PULLUP);
  pinMode(Z, INPUT_PULLUP);
  pinMode(START, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  
  pinMode(M1, INPUT_PULLUP);
  pinMode(M2, INPUT_PULLUP);

  //This is needed to run the code.
  GamecubeController1.read();
}

void loop()
{
  //This resets and establishes all the values after the controller sends them to the console and helps with initial "zeroing"
  int pinA = 0;
  int pinB = 0;
  int pinX = 0;
  int pinZ = 0;
  int pinSTART = 0;
  
  int pinL = 0;
  int pinLLIGHT = 0;

  int pinLEFT = 0;
  int pinRIGHT = 0;
  int pinUP = 0;
  int pinDOWN = 0;

  int pinM1 = 0;
  int pinM2 = 0;

  int pinxAxisC = 128;
  int pinyAxisC = 128;
  
  int pinxAxis = 128;
  int xmod = 0;
  int pinyAxis = 128;

  //This reads control stick as neutral when both left/right or up/down is pressed at the same time.  Also sets parameters for the diffrent analog tilt modifiers IE: M1+M2 = M3
  if (digitalRead(LEFT) == HIGH && digitalRead(RIGHT) == LOW){
    pinxAxis = 128+86;
    if (digitalRead(M1) == LOW && digitalRead(M2) == HIGH)pinxAxis = M1x + 128;
    if (digitalRead(M1) == HIGH && digitalRead(M2) == LOW)pinxAxis = M2x + 128;
    if (digitalRead(M1) == LOW && digitalRead(M2) == LOW)pinxAxis = M3x + 128;
  }
  if (digitalRead(LEFT) == LOW && digitalRead(RIGHT) == HIGH){
    pinxAxis = 128-86;
    if (digitalRead(M1) == LOW && digitalRead(M2) == HIGH)pinxAxis = 128 - M1x;
    if (digitalRead(M1) == HIGH && digitalRead(M2) == LOW)pinxAxis = 128 - M2x;
    if (digitalRead(M1) == LOW && digitalRead(M2) == LOW)pinxAxis = 128 - M3x;
  }
    
  if (digitalRead(DOWN) == HIGH && digitalRead(UP) == LOW){
    pinyAxis = 128+86;
    if (digitalRead(M1) == LOW && digitalRead(M2) == HIGH)pinyAxis = 128 + M1y;
    if (digitalRead(M1) == HIGH && digitalRead(M2) == LOW)pinyAxis = 128 + M2y;
    if (digitalRead(M1) == LOW && digitalRead(M2) == LOW)pinyAxis = 128 + M3y;
  }
  if (digitalRead(DOWN) == LOW && digitalRead(UP) == HIGH){
    pinyAxis = 128-86;
    if (digitalRead(M1) == LOW && digitalRead(M2) == HIGH)pinyAxis = 128 - M1y;
    if (digitalRead(M1) == HIGH && digitalRead(M2) == LOW)pinyAxis = 128 - M2y;
    if (digitalRead(M1) == LOW && digitalRead(M2) == LOW)pinyAxis = 128 - M3y;
  }

  if (digitalRead(A) == LOW)pinA = 1;
  if (digitalRead(B) == LOW)pinB = 1;
  if (digitalRead(X) == LOW)pinX = 1;
  if (digitalRead(Z) == LOW)pinZ = 1;
  if (digitalRead(START) == LOW)pinSTART = 1;
  // Apply a max analog input on top of a digital L input for games other than Melee
  if (digitalRead(L) == LOW)pinLLIGHT = LLIGHT;
  if (digitalRead(L) == LOW)pinL = 1;

  // Reports data
  d.report.dup = 0;
  d.report.dright = 0;
  d.report.ddown = 0;
  d.report.dleft = 0;
  d.report.a = pinA;
  d.report.b = pinB;
  d.report.x = pinX;
  d.report.z = pinZ;
  d.report.start = pinSTART;
  d.report.l = pinL;
  d.report.left = pinLLIGHT;
  d.report.xAxis = pinxAxis;
  d.report.yAxis = pinyAxis;
  
  //sends the complied data to console when console polls for the input
  GamecubeConsole.write(d);
}
