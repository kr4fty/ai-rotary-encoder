/*
 * We use interrupts of the PinChangeInterrupt type, since almost any of the
 * ATmega pins can be used, compared to the external type, which are limited
 *
 */


#include <Arduino.h>
#include <EnableInterrupt.h>    // to attach our ISR routine
#include "AiEsp32RotaryEncoder.h"

#define ENCODER_PIN_A    10
#define ENCODER_PIN_B     9
#define BUTTON_PIN       11
#define ENCODER_VCC_PIN               -1 // Using onboard VCC
#define ENCODER_STEPS                  4
#define ENCODER_CENTRAL_PIN_TO_VCC false // middle pin connected to GND

AiEsp32RotaryEncoder encoder = AiEsp32RotaryEncoder(ENCODER_PIN_A,
                                                    ENCODER_PIN_B,
                                                    BUTTON_PIN,
                                                    ENCODER_VCC_PIN,
                                                    ENCODER_STEPS,
                                                    ENCODER_CENTRAL_PIN_TO_VCC);

void readEncoderISR()
{
	encoder.readEncoder_ISR();
}

long int  encoderCounter=0;


void setup() {
  Serial.begin(9600);

  encoder.begin();
  //encoder.setup(readEncoderISR);
  enableInterrupt(ENCODER_PIN_A, readEncoderISR, CHANGE); //instead of setup(readEncoderISR),
  enableInterrupt(ENCODER_PIN_B, readEncoderISR, CHANGE); //we attach it from here

  bool circleValues =false;
  encoder.setBoundaries(0, 300, circleValues); //minValue, maxValue, circleValues true|false (when max go to min and vice versa)
  //encoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
  encoder.setAcceleration(100); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
  encoder.setEncoderValue(encoderCounter);
}


void loop() {
  if (encoder.encoderChanged())
    Serial.println(encoderCounter = encoder.readEncoder());

  if (encoder.isEncoderButtonClicked())
    Serial.println("PRESSED");
}
