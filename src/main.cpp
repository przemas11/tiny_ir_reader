#include <Arduino.h>
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>

#include "ir_remote_definitions.h"
#include <IRremote.hpp>
#define IR_PIN 3 // IR sensor pin

// #include <SendOnlySoftwareSerial.h>
// SendOnlySoftwareSerial mySerial(4); // Tx pin

void printOLED(char const *str1, char const *str2 = "");

void setup()
{
  // put your setup code here, to run once:
  oled.begin();
  oled.setFont(FONT8X16);
  oled.clear();
  oled.on();
  oled.switchRenderFrame();

  // mySerial.begin(9600);
  // mySerial.println("SETUP Complete - Attiny85 Serial Example");

  IrReceiver.begin(IR_PIN, false);
  printOLED("READY");
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode())
  {
    // mySerial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    char code[11] = "0x\0";
    char buf[9];
    ltoa(IrReceiver.decodedIRData.decodedRawData, buf, 16);
    strcat(code, buf);

    char protocol[11];

    switch (IrReceiver.decodedIRData.protocol)
    {
    case NEC:
      strcpy(protocol, "NEC");
      break;
    case SONY:
      strcpy(protocol, "SONY");
      break;
    case RC5:
      strcpy(protocol, "RC5");
      break;
    case RC6:
      strcpy(protocol, "RC6");
      break;
    case DISH:
      strcpy(protocol, "DISH");
      break;
    case SHARP:
      strcpy(protocol, "SHARP");
      break;
    case JVC:
      strcpy(protocol, "JVC");
      break;
    case SAMSUNG:
      strcpy(protocol, "SAMSUNG");
      break;
    case LG:
      strcpy(protocol, "LG");
      break;
    case WHYNTER:
      strcpy(protocol, "WHYNTER");
      break;
    case PANASONIC:
      strcpy(protocol, "PANASONIC");
      break;
    case DENON:
      strcpy(protocol, "DENON");
      break;
    default:
      strcpy(protocol, "UNKNOWN");
      break;
    }

    printOLED(protocol, code);
    IrReceiver.resume(); // Enable receiving of the next value
  }
}

void printOLED(char const *str1, char const *str2 = "")
{
  oled.clear();
  oled.setCursor(0, 0);
  oled.print(str1);

  oled.setCursor(0, 2);
  oled.print(str2);

  oled.switchFrame();
}