/******************************************************************************
 *
 * Endocer: rotary encoder with central pin connected to gnd
 * Button
 * Board: Blue Pill STM32F103C8T6
 *
 * ***************************************************************************/

#include "Arduino.h"
#include "AiEsp32RotaryEncoder.h"

#define ENCODER_PIN_A   PA0
#define ENCODER_PIN_B   PA1
#define BUTTON_PIN      PA2
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
  encoder.setup(readEncoderISR);
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
