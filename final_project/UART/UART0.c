#include "UART0.h"
#include "TM4C123GH6PM.h"
#include "frame.h"


void UART0_Init(void)
{
	// Enable the clock to the UART0 module by setting the 
	// R0 bit (Bit 0) in the RCGCUART register
	SYSCTL->RCGCUART |= 0x01;
	
	// Enable the clock to Port A by setting the
	// R0 bit (Bit 0) in the RCGCGPIO register
	SYSCTL->RCGCGPIO |= 0x01;
	
	// Disable the UART0 module before configuration by clearing
	// the UARTEN bit (Bit 0) in the CTL register
	UART0->CTL &= ~0x0001;
	
	// Configure the UART0 module to use the system clock (50 MHz)
	// divided by 16 by clearing the HSE bit (Bit 5) in the CTL register
	UART0->CTL &= ~0x0020;
	
	// Set the baud rate by writing to the DIVINT field (Bits 15 to 0)
	// and the DIVFRAC field (Bits 5 to 0) in the IBRD and FBRD registers, respectively.
	// The integer part of the calculated constant will be written to the IBRD register,
	// while the fractional part will be written to the FBRD register.
	// BRD = (System Clock Frequency) / (16 * Baud Rate)
	// BRDI = (50,000,000) / (16 * 9600) = 27.12673611 (IBRD = 27)
	// BRDF = ((0.520833 * 64) + 0.5) = 8.611 (FBRD = 8)
	UART0->IBRD = 325;
	UART0->FBRD = 33;
	
	// Configure the data word length of the UART packet to be 8 bits by 
	// writing a value of 0x3 to the WLEN field (Bits 6 to 5) in the LCRH register
	UART0->LCRH |= 0x60;
	
	// Enable the Transmit FIFO and the Receive FIFO by setting the FEN bit (Bit 4) in the LCRH register
	UART0->LCRH |= 0x10;
	
	// Select one stop bit to be transmitted at the end of a UART frame by
	// clearing the STP2 bit (Bit 3) in the LCRH register
	UART0->LCRH &= ~0x08;
	
	// Disable the parity bit by clearing the PEN bit (Bit 1) in the LCRH register
	UART0->LCRH &= ~0x02;
	
	// Enable the UART0 module after configuration by setting
	// the UARTEN bit (Bit 0) in the CTL register
	UART0->CTL |= 0x01;
	
	// Configure the PA1 (U0TX) and PA0 (U0RX) pins to use the alternate function
	// by setting Bits 1 to 0 in the AFSEL register
	GPIOA->AFSEL |= 0x03;
	
	// Clear the PMC1 (Bits 7 to 4) and PMC0 (Bits 3 to 0) fields in the PCTL register before configuration
	GPIOA->PCTL &= ~0x000000FF;
	
	// Configure the PA1 pin to operate as a U0TX pin by writing 0x1 to the
	// PMC1 field (Bits 7 to 4) in the PCTL register
	// The 0x1 value is derived from Table 23-5 in the TM4C123G Microcontroller Datasheet
	GPIOA->PCTL |= 0x00000010;
	
	// Configure the PA0 pin to operate as a U0RX pin by writing 0x1 to the
	// PMC0 field (Bits 3 to 0) in the PCTL register
	// The 0x1 value is derived from Table 23-5 in the TM4C123G Microcontroller Datasheet
	GPIOA->PCTL |= 0x00000001;
	
	// Enable the digital functionality for the PA1 and PA0 pins
	// by setting Bits 1 to 0 in the DEN register
	GPIOA->DEN |= 0x03;
}

uint8_t UART0_InChar(void) {
    while ((UART0->FR & 0x10) != 0);
    return (uint8_t)(UART0->DR & 0xFF);
}

void UART0_OutChar(uint8_t data) {
    while ((UART0->FR & 0x20) != 0);
    UART0->DR = data;
}