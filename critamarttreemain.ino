// mp1 addresses = 
/*  -- |pin on the circuit| |name of pin on hardware| |ID of the LED on arduino|
--  21  GPA0  0
--  22  GPA1  1
--  23  GPA2  2
--  24  GPA3  3
--  25  GPA4  4
--  26  GPA5  5
--  27  GPA6  6
--  28  GPA7  7
--  1   GPB0  8
--  2   GPB1  9
--  3   GPB2  10
--  4   GPB3  11
--  5   GPB4  12
--  6   GPB5  13
--  7   GPB6  14
--  8   GPB7  15
*/
//mp2 addresses = 
/* substract 16 for actual address
--  21  GPA0  16
--  22  GPA1  17
--  23  GPA2  18
--  24  GPA3  19
--  25  GPA4  20
--  26  GPA5  21
--  27  GPA6  22
--  28  GPA7  23
--  1   GPB0  24
--  2   GPB1  25
--  3   GPB2  26
--  4   GPB3  27
--  5   GPB4  28
--  6   GPB5  29
--  7   GPB6  30
--  8   GPB7  31
*/
short int ledStates [31];
long ledTimers [31];

#include <Adafruit_MCP23X17.h>
#include <Wire.h>

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
int funnyVariable = 0;
long lastTime = millis();
long lastTurnON = millis();
long lastTurnOFF = millis();
 short ledSelected = 16;
 int  ledPattern = 3000;
 long lastLEDPattern = millis();
 long offTimerCheck = millis();
 long ledSelect = millis();
void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");
mcp1.begin_I2C(0x20); //low low low
mcp2.begin_I2C(0x21); //high high high

    mcp1.pinMode(15, OUTPUT);
mcp2.pinMode(15, OUTPUT);
  mcp1.pinMode(14, OUTPUT);
mcp2.pinMode(14, OUTPUT);
  mcp1.pinMode(13, OUTPUT);
mcp2.pinMode(13, OUTPUT);
  mcp1.pinMode(12, OUTPUT);
mcp2.pinMode(12, OUTPUT);
  mcp1.pinMode(11, OUTPUT);
mcp2.pinMode(11, OUTPUT);
  mcp1.pinMode(10, OUTPUT);
mcp2.pinMode(10, OUTPUT);
  mcp1.pinMode(9, OUTPUT);
mcp2.pinMode(9, OUTPUT);
  mcp1.pinMode(8, OUTPUT);
mcp2.pinMode(8, OUTPUT);
  mcp1.pinMode(7, OUTPUT);
mcp2.pinMode(7, OUTPUT);
  mcp1.pinMode(6, OUTPUT);
mcp2.pinMode(6, OUTPUT);
  mcp1.pinMode(5, OUTPUT);
mcp2.pinMode(5, OUTPUT);
  mcp1.pinMode(4, OUTPUT);
mcp2.pinMode(4, OUTPUT);
  mcp1.pinMode(3, OUTPUT);
mcp2.pinMode(3, OUTPUT);
  mcp1.pinMode(2, OUTPUT);
mcp2.pinMode(2, OUTPUT);
  mcp1.pinMode(1, OUTPUT);
mcp2.pinMode(1, OUTPUT);
  mcp1.pinMode(0, OUTPUT);
mcp2.pinMode(0, OUTPUT);

  Serial.println("volas");
}

void loop() {
  if(millis() - ledSelect > 20) {
  ledSelected = random(0,30);
  }
  if(ledStates[ledSelected] > 0 && millis() - ledTimers[ledSelected] >= ledStates[ledSelected])  {
    turnOffLED(ledSelected);
  }
  if(ledStates[ledSelected] < 0 && millis() - offTimerCheck > 10)
  {
    offTimerCheck = millis();
    ledStates[ledSelected] = ledStates[ledSelected] + 10; 
  }
  if(ledStates[ledSelected] == 0) {
    turnLED2sec(ledSelected);
  }
}
void turnOffLED (int ledID) {
     short int actualLedID;
    if(ledID >= 16) {
      actualLedID = ledID - 16;
      mcp2.digitalWrite(actualLedID, LOW) ;
      ledTimers[ledID] = millis();
      ledStates[ledID] = -50;
    } else {
      mcp1.digitalWrite(ledID , LOW);
      ledTimers[ledID] = millis();
      ledStates[ledID] = -50;
     }

}
void turnLED2sec (int ledID) {
  short int actualLedID;
    if(ledID >= 16) {
      actualLedID = ledID - 16;
      mcp2.digitalWrite(actualLedID, HIGH) ;
      ledStates[ledID] = 1000;
      ledTimers[ledID] = millis();
    } else {
      mcp1.digitalWrite(ledID,HIGH);
      ledStates[ledID] = 1000;
      ledTimers[ledID] = millis();
     }

}
