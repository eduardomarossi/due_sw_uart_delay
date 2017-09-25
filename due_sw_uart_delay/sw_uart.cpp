#include "sw_uart.h"

due_sw_uart *sw_uart_1;

void sw_uart_setup(due_sw_uart *duart, int rx, int tx, int baudrate, int stopbits, int databits, int paritybit) {
	duart->pin_tx = tx;
	duart->pin_rx = rx;
	duart->baudrate = baudrate;
	duart->stopbits = stopbits;
	duart->paritybit = paritybit;
  duart->databits = databits;
  pinMode(tx, OUTPUT);
  digitalWrite(tx, HIGH);
  pinMode(rx, INPUT);
  double setup_T = 1.0 / duart->baudrate * 1.0E9; // in nanoseconds
  Serial.println(setup_T);
  duart->ndelay_250 = setup_T / 1000;
}

void _sw_uart_rx_interrupt1(void) {
    detachInterrupt(sw_uart_1->pin_rx);
}

int sw_uart_receive_byte(due_sw_uart *duart, char* data) {
  // wait start bit
  while(digitalRead(duart->pin_rx) == HIGH);

  // confirm start bit
  _sw_uart_wait_half(duart);
  // HIGH = invalid
  if(digitalRead(duart->pin_rx) == HIGH) {
    return SW_UART_ERROR_FRAMING;
  }

  // start getting data 
  char aux = 0x00;
  for(int i = 0; i < duart->databits; i++) {
    // wait T (period)
    _sw_uart_wait_half(duart);
    _sw_uart_wait_half(duart);

    aux |= digitalRead(duart->pin_rx) << i;
  }

  // parity
  // to be implemented

  // stop bit
  _sw_uart_wait_half(duart);
  _sw_uart_wait_half(duart);
  if(digitalRead(duart->pin_rx) == LOW) {
    return SW_UART_ERROR_FRAMING;
  }

  *data = aux;
  return SW_UART_SUCCESS;
}

void sw_uart_write_byte(due_sw_uart *duart, char data) {
  digitalWrite(duart->pin_tx, HIGH);
  _sw_uart_wait_T(duart);
  _sw_uart_wait_T(duart);
  _sw_uart_wait_T(duart);

  // send start bit
  digitalWrite(duart->pin_tx, LOW);
  _sw_uart_wait_T(duart);
  
  // start sending data
  for(int i = 0; i < duart->databits; i++) {
    digitalWrite(duart->pin_tx, (data >> i) & 0x01);
    _sw_uart_wait_T(duart);
  }

  // send parity
  // tobe implemented

  // send stop bit
  digitalWrite(duart->pin_tx, HIGH);
  _sw_uart_wait_T(duart);

}

void _delay_250n(void) {
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
 //--
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  //--
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  //--
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  asm("NOP");
  //--
}

void _sw_uart_wait_half(due_sw_uart *duart) {
  for(uint32_t i = 0; i < duart->ndelay_250; i++) {
    _delay_250n();
  }
}

void _sw_uart_wait_T(due_sw_uart *duart) {
  for(uint32_t i = 0; i < duart->ndelay_250 * 2; i++) {
    _delay_250n();
  }
}

void sw_uart_enable_interrupt1(due_sw_uart *duart) {
	sw_uart_1 = duart;
	attachInterrupt(duart->pin_rx, _sw_uart_rx_interrupt1, FALLING);
}
