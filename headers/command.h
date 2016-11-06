/***************************************************************************
*
*  	Filename: command.h
*	Description: Header file for command.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _command_H
#define _command_H

#include <stdint.h>
#include "uart.h"
#include "memory.h"

#define MAX_DATA_SIZE 10

// define the commands here
typedef enum Cmds_t {
	SET_COLOR = 1, // Sets the LED color
	SET_BRIGHTNESS = 2, // Sets the LED brightness
} Cmds;

// defines the errors present
typedef enum Cmd_Errors_t {
	NO_ERROR = 0x01,
	UNKNOWN_CMD = 0x02,
	INVALID_LENGTH = 0x03,
	INVALID_DATA = 0x04,
	INCORRECT_CHECKSUM = 0x05,
} Cmd_Errors;

// defines the messaging interface
typedef struct CI_Msg_t{
	Cmds command; // Command operation
	uint8_t length; // Size of message
	uint8_t data[MAX_DATA_SIZE]; // Generic data payload
	uint16_t checksum; // Error detection checksum
} CI_Msg;

// takes in the important parameters for a CI_Msg and constructs this at the pointer *cmd
uint8_t create_cmd(CI_Msg *cmd, Cmds command, uint8_t length, uint8_t *data);

// waits for a command packet to be received
// returns an error code
// a pointer to where the received command will be placed is passed in
uint8_t receive_cmd(CI_Msg *cmd);

// sends a command packet
uint8_t send_cmd(CI_Msg *cmd);

// creates a checksum for the send command
uint16_t create_checksum(CI_Msg *cmd);

// verifies the checksum upon a received command
uint8_t verify_checksum(CI_Msg *cmd);

#endif
