/***************************************************************************
*
*  	Filename: spi.c
*	Description: SPI Application Layer code
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _SPI_C
#define _SPI_C

#include "spi.h"

// SPI Receive byte of data
uint8_t SPI_rx_byte() {
	while((SPI0_S & SPI_S_SPRF_MASK) == 0) {;}
	uint8_t receive = SPI0_D;
	return receive;
}

// SPI send byte of data
void SPI_tx_byte(uint8_t send) {
    while((SPI0_S & SPI_S_SPTEF_MASK) == 0) {;}
    SPI0_D = send;
}

void SPI_init() {
	// SPI0 clock gate
	SIM_SCGC4 |= SIM_SCGC4_SPI0(1);

	// Enable clock at Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC(1);

	// Set pin 8 to be an output GPIO pin. This will be used as the CS for the Nordic chip
	PTC_BASE_PTR->PDDR |= 1<<8;
	CS_NRF_HIGH();

	// Set the 4 pins as SPI connections
	PORTC_PCR8 = PORT_PCR_MUX(1); //CS
	PORTC_PCR5 = PORT_PCR_MUX(2); //SCK
	PORTC_PCR6 = PORT_PCR_MUX(2); //MOSI
	PORTC_PCR7 = PORT_PCR_MUX(2); //MISO

	// Control register 1
	SPI0_C1 = SPI_C1_SPIE(1)   //interrupt enable
			|  SPI_C1_MSTR(1)   //master/slave -> master mode
			|  SPI_C1_SSOE(1);   //slave select output enable

	// Control register 2
	SPI0_C2 = 0;

	// SPI baud rate register
	SPI0_BR |= SPI_BR_SPPR(3) //divide by 4
			|  SPI_BR_SPR(3); //divide by 16

	SPI0_C1 |= SPI_C1_SPE(1);    //SPI enable
}

#endif
