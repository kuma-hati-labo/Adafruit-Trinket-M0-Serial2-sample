#include <Arduino.h>   // required before wiring_private.h
#include "wiring_private.h" // pinPeripheral() function

#define PIN_SERIAL2_RX       (2ul) // PA09
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_1)
#define PIN_SERIAL2_TX       (0ul) // PA08
#define PAD_SERIAL2_TX       (UART_TX_PAD_0)

Uart Serial2( &sercom2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX ) ;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  Serial.begin(115200);  

  Serial2.begin(115200);
  pinPeripheral(0, PIO_SERCOM_ALT);
  pinPeripheral(2, PIO_SERCOM_ALT);
}
     
// the loop function runs over and over again forever
void loop() {
  if (Serial.available()) {
    // get the new byte:
    unsigned char inChar = (char)Serial.read();
    Serial2.write(inChar);
  }
  while (Serial2.available()) {
    unsigned char inChar = Serial2.read();
    Serial.write(inChar);
  }
}

void SERCOM2_Handler() {
  Serial2.IrqHandler();
}
