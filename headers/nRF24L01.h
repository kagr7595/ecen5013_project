/***************************************************************************
*
*  	Filename: nRF24L01.h
*	Description: Header file for nRF24L01.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _NRF24L01_H
#define _NRF24L01_H

#ifdef FRDM
#include "spi.h"
#elif BBB
#include "spi_bbb.h"
#endif

#include <stdint.h>
#include <stdio.h>

/* Defines and Structures section
 ***************************************************************************/
// defines the errors present
typedef enum nRF_Errors_t {
	NRF_NO_ERROR = 0x01,
	NRF_UNKNOWN_CMD = 0x02,
	NRF_INVALID_LENGTH = 0x03,
	NRF_INVALID_ADDRESS = 0x04,
} nRF_Errors;

// Command names
#define R_REGISTER(r_addr) (~(0x7<<5) & r_addr)
#define W_REGISTER(w_addr) ((~(0x7<<5) & w_addr) | 0x20)
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2

// NOP command
#define NOP 0xFF

// Addresses and address lengths
#define CONFIG 0x00
#define CONFIG_LENGTH 1
	#define CONFIG_RX_DR_MASK 0x40
	#define CONFIG_TX_DS_MASK 0x20
	#define CONFIG_MAX_RT_MASK 0x10
	#define CONFIG_EN_CRC_MASK 0x08
	#define CONFIG_CRC0_MASK 0x04
	#define CONFIG_PWR_UP_MASK 0x02
	#define CONFIG_PRIM_RX_MASK 0x01

#define EN_AA 0x01
#define EN_AA_LENGTH 1
#define EN_RXADDR 0x02
#define EN_RXADDR_LENGTH 1
#define SETUP_AW 0x03
#define SETUP_AW_LENGTH 1
#define SETUP_RETR 0x04
#define SETUP_RETR_LENGTH 1
#define RF_CH 0x05
#define RF_CH_LENGTH 1
#define RF_SETUP 0x06
#define RF_SETUP_LENGTH 1
	#define RF0 3
	#define RF6 2
	#define RF12 1
	#define RF18 0
#define RF_SETUP_POWER_MASK 0x06
#define RF_SETUP_POWER_SHIFT 1
#define RF_SETUP_POWER_WIDTH 2
#define RF_SETUP_POWER_SET(x) (((uint8_t)(((uint8_t)(x))<<RF_SETUP_POWER_SHIFT))&RF_SETUP_POWER_MASK)

#define STATUS 0x07
#define STATUS_LENGTH 1
	#define STATUS_RX_DR_MASK 0x40
	#define STATUS_TX_DS_MASK 0x20
	#define STATUS_MAX_RT_MASK 0x10
	#define STATUS_RX_P_NO_MASK 0x0E
	#define STATUS_TX_FULL_MASK 0x01

#define OBSERVE_TX 0x08
#define OBSERVE_TX_LENGTH 1
#define RPD 0x09
#define RPD_LENGTH 1
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P0_LENGTH 5
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P1_LENGTH 5
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P2_LENGTH 1
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P3_LENGTH 1
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P4_LENGTH 1
#define RX_ADDR_P5 0x0F
#define RX_ADDR_P5_LENGTH 1
#define TX_ADDR 0x10
#define TX_ADDR_LENGTH 5
#define RX_PW_P0 0x11
#define RX_PW_P0_LENGTH 1
#define RX_PW_P1 0x12
#define RX_PW_P1_LENGTH 1
#define RX_PW_P2 0x13
#define RX_PW_P2_LENGTH 1
#define RX_PW_P3 0x14
#define RX_PW_P3_LENGTH 1
#define RX_PW_P4 0x15
#define RX_PW_P4_LENGTH 1
#define RX_PW_P5 0x16
#define RX_PW_P5_LENGTH 1
#define FIFO_STATUS 0x17
#define FIFO_STATUS_LENGTH 1
#define DYNPD 0x1C
#define DYNPD_LENGTH 1
#define FEATURE 0x1D
#define FEATURE_LENGTH 1

/* Function prototype Section
 * Add prototypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/

// Reads the desired register from the nRF24L01 device. The number of returned bytes
// is provided by the user but is command dependent.
// Since the status is returned as the first byte for all commands, this will be placed in
// the first spot in the array.
uint8_t nrf_read_reg(uint8_t addr, uint8_t length, uint8_t *data);

// Writes the desired register to the nRF24L01 device. The number of expected bytes
// is provided by the user but is command dependent.
uint8_t nrf_write_reg(uint8_t addr, uint8_t length, uint8_t *data);

// Reads the config register
// Returns the register data
uint8_t nrf_config_read(void);

// Writes the config register
// Returns an error code
uint8_t nrf_config_write(uint8_t data);

// Reads the transmit data address
// Returns error
uint8_t nrf_tx_addr_read(uint8_t *data);

// Writes the transmit data address
// Returns error
uint8_t nrf_tx_addr_write(uint8_t *data);

// Reads the RF setup register
// Returns the RF setup data
uint8_t nrf_rf_setup_read(void);

// Write power to the RF setup register
// Returns an error code
uint8_t nrf_rf_setup_power(uint8_t pwr_lvl);

// Reads the status register from the nRF24L01 device.
// Returns the status data
uint8_t nrf_status(void);

// Reads the FIFO status register from the nRF24L01 device.
// Returns the FIFO status data.
uint8_t nrf_fifo_status(void);

#endif
