/***************************************************************************
*
*  	Filename: nRF24L01.c
*	Description: nRF24L01 Interface Application Layer code
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _NRF24L01_C
#define _NRF24L01_C

#include "nRF24L01.h"

// Reads the desired register from the nRF24L01 device. The number of returned bytes
// is provided by the user but is command dependent.
// Since the status is returned as the first byte for all commands, this will be placed in
// the first spot in the array.
uint8_t nrf_read_reg(uint8_t addr, uint8_t length, uint8_t *data){
	if(length > 6) {return NRF_INVALID_LENGTH;}
	else if(addr > 0x1D) {return NRF_INVALID_ADDRESS;}
	uint8_t cmd = R_REGISTER(addr);
#ifdef FRDM
	CS_NRF_LOW();
#endif
	*data = SPI_tx_rx(cmd);
	uint8_t i;
	for(i = 1; i <= length; i++){
		*(data+i) = SPI_tx_rx(0xFF);
	}
#ifdef FRDM
	CS_NRF_HIGH();
#endif
	return NRF_NO_ERROR;
}

// Writes the desired register to the nRF24L01 device. The number of expected bytes
// is provided by the user but is command dependent.
uint8_t nrf_write_reg(uint8_t addr, uint8_t length, uint8_t *data){
	if(length > 5) {return NRF_INVALID_LENGTH;}
	else if(addr > 0x1D) {return NRF_INVALID_ADDRESS;}
	uint8_t cmd = W_REGISTER(addr);
#ifdef FRDM
	CS_NRF_LOW();
#endif
	uint8_t read = SPI_tx_rx(cmd);
	uint8_t i;
	for(i = 0; i < length; i++){
		read = SPI_tx_rx(*(data+i));
	}
#ifdef FRDM
	CS_NRF_HIGH();
#endif
	return NRF_NO_ERROR;
}

// Reads the config register
// Returns the register data
uint8_t nrf_config_read(){
	uint8_t data[2];
	nrf_read_reg(CONFIG, CONFIG_LENGTH+1, data);
	return *(data+1);
}

// Writes the config register
// Returns an error code
uint8_t nrf_config_write(uint8_t data){
	uint8_t* config_in = &data;
	uint8_t error = nrf_write_reg(CONFIG, CONFIG_LENGTH, config_in);
	return error;
}

// Reads the transmit data address
// Returns an error
uint8_t nrf_tx_addr_read(uint8_t *data){
	uint8_t error = nrf_read_reg(TX_ADDR, TX_ADDR_LENGTH+1, data);
	return error;
}

// Writes the transmit data address
// Returns error
uint8_t nrf_tx_addr_write(uint8_t *data){
	uint8_t error = nrf_write_reg(TX_ADDR, TX_ADDR_LENGTH, data);
	return error;
}

// Reads the RF setup register
// Returns the RF setup data
uint8_t nrf_rf_setup_read(){
	uint8_t data[2];
	nrf_read_reg(RF_SETUP, RF_SETUP_LENGTH+1, data);
	return *(data+1);
}

// Write to the RF setup register
// Returns an error code
uint8_t nrf_rf_setup_power(uint8_t pwr_lvl){
	uint8_t data = RF_SETUP_POWER_SET(pwr_lvl);
	uint8_t* setup_in = &data;
	uint8_t error = nrf_write_reg(RF_SETUP, RF_SETUP_LENGTH, setup_in);
	return error;
}

// Reads the status register from the nRF24L01 device.
// Returns the status data.
uint8_t nrf_status(){
#ifdef FRDM
	CS_NRF_LOW();
#endif
	uint8_t data = SPI_tx_rx(NOP);
#ifdef FRDM
	CS_NRF_HIGH();
#endif
	return data;
}

// Reads the FIFO status register from the nRF24L01 device.
// Returns the FIFO status data.
uint8_t nrf_fifo_status(){
	uint8_t data[2];
	nrf_read_reg(FIFO_STATUS, FIFO_STATUS_LENGTH+1, data);
	return *(data+1);
}

#endif
