#ifndef SW_UART_HEADER
#define SW_UART_HEADER

#include <Arduino.h>

struct due_sw_uart {
	int pin_rx;
	int pin_tx;
	int baudrate;
	int stopbits;
	int paritybit;
	int enable_interrupt;
  int databits;
  uint32_t ndelay_250;
};

typedef struct due_sw_uart due_sw_uart;

#define SW_UART_SUCCESS 0
#define SW_UART_ERROR_FRAMING 1
#define SW_UART_ERROR_PARITY  2


void sw_uart_setup(due_sw_uart *duart, int rx, int tx, int baudrate, int stopbits, int databits, int paritybit);

void _sw_uart_rx_interrupt1(void);

int sw_uart_receive_byte(due_sw_uart *duart, char* data);
void sw_uart_write_byte(due_sw_uart *duart, char data);

void _sw_uart_wait_half(due_sw_uart *duart);
void _sw_uart_wait_T(due_sw_uart *duart);
void sw_uart_enable_interrupt1(due_sw_uart *duart);


#endif
