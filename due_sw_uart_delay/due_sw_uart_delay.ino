#include "sw_uart.h"

due_sw_uart uart;

void setup() {
    Serial.begin(115200);
  
  // put your setup code here, to run once:
  sw_uart_setup(&uart, 5, 6, 38400, 1, 8, 0);
Serial.println(uart.ndelay_250);
}

void loop() {
  // put your main code here, to run repeatedly:
  //char data;
  //sw_uart_receive_byte(&uart, data);
  sw_uart_write_byte(&uart, 'A');
  Serial.println("DATA SENT");
  delay(1000);
  
}
