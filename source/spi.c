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

//volatile CircBuf_t * rx_buf;

// UART Receive data to be stored into another pointer for processing
void SPI_rx_data(uint8_t *read, uint8_t length) {

}

// UART send data to uart
void SPI_tx_data(uint8_t *send, uint8_t length) {
    uint8_t i;
    for (i = 0; i < length; i++) {
    	//checks the TX empty flag
    	while(!(SPI0_S & SPI_S_SPTEF_MASK)) {;}
    	SPI0_D = *(send + i);
    }
}

extern void SPI0_IRQHandler() {

}

void SPI_init() {
	__disable_irq();

	// SPI0 clock gate
	SIM_SCGC4 |= SIM_SCGC4_I2C0(1);

	// Enable clock at Port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC(1)

	// Set the 4 pins as SPI connections
	PORTC_PCR4 |= PORT_PCR_MUX(2); //PCSO
	PORTC_PCR5 |= PORT_PCR_MUX(2); //SCK
	PORTC_PCR6 |= PORT_PCR_MUX(2); //MOSI
	PORTC_PCR7 |= PORT_PCR_MUX(2); //MISO

	// Control register 1
	SPI0_C1 |= SPI_C1_SPIE(1)   //interrupt enable
			|  SPI_C1_SPE(1)    //SPI enable
			|  SPI_C1_SPTIE(0)  //TX IE
			|  SPI_C1_MSTR(1)   //master/slave -> master mode
			|  SPI_C1_CPOL(0)   //clock polarity -> not inverted
			|  SPI_C1_CPHA(0)   //clock phase -> first edge of clock occurs at middle of first cycle TX
			|  SPI_C1_SSOE(1)   //slave select output enable
			|  SPI_C1_LSBFE(0); //MSBit first

	// Control register 2
	SPI0_C2 |= SPI_C2_SPMIE(0)  //SPI match IE
			|  SPI_C2_TXDMAE(0) //transmit DMA enable
			|  SPI_C2_MODFEN(1) //master mode-fault function enable -> slave select output
			|  SPI_C2_RXDMAE(0) //receive DMA enable
			|  SPI_C2_SPC0(0);  //SPI pin control 0 -> SPI uses separate pins for data in and out

	// SPI baud rate register
	SPI0_BR |= SPI_BR_SPPR(3) //divide by 4
			|  SPI_BR_SPR(3); //divide by 16

    // Clear pending interrupt
    NVIC_ClearPendingIRQ(SPI0_IRQn);

    // Enable Interrupt for SPI0, interrupt 12 in vector table
    NVIC_EnableIRQ(SPI0_IRQn);

	__enable_irq();
}

#endif
