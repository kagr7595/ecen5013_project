/***************************************************************************
*
*  	Filename: command.c
*	Description: Defines the command structure and enums for various commands
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _command_C
#define _command_C

#include "command.h"

// sends data using either UART or SPI depending on the compilation flag "SPI"
void send_data(uint8_t *send, uint8_t length){
#ifndef SPI

	#ifdef FRDM
		uart_tx_data(send, length);
	#else
		uint8_t i = 0;
		for(i = 0; i < legth; i++){
			printf("%d",*(send+1));
		}
	#endif

#else

	#ifdef FRDM

	#else

	#endif

#endif
}

// receives data using either UART or SPI depending on the compilation flag "SPI"
void receive_data(uint8_t *read, uint8_t length){
#ifndef SPI

	#ifdef FRDM
		uart_rx_data(read, length);
	#else

	#endif

#else

	#ifdef FRDM

	#else

	#endif

#endif
}

// takes in the important parameters for a CI_Msg and constructs this at the pointer *cmd
uint8_t create_cmd(CI_Msg *cmd, Cmds command, uint8_t length, uint8_t *data){
	cmd->command = command;
	cmd->length = length;
	my_memmove(data, cmd->data , length);
	cmd->checksum = create_checksum(cmd);
}

// waits for a command packet to be received
// returns an error code
// a pointer to where the received command will be placed is passed in
uint8_t receive_cmd(CI_Msg *cmd) {
	uint8_t read[MAX_DATA_SIZE];
	receive_data(read, 1);
	cmd->command = (Cmds)(*read);
	if((cmd->command < 1) || (cmd->command > 2)) {
		return UNKNOWN_CMD;
	}
	receive_data(read, 1);
	cmd->length = (*read);
	if(cmd->length < 0) {
		return INVALID_LENGTH;
	}
	if(cmd->length > 0) {
		receive_data(read, cmd->length);
		my_memmove(read, cmd->data , cmd->length);
	}
	receive_data(read, 2);
	cmd->checksum = (((uint16_t)(*read)) << 8) | ((uint16_t)(*(read+1)));
	if(verify_checksum(cmd)){
		return INCORRECT_CHECKSUM;
	}
	return NO_ERROR;
}

// sends a command packet
uint8_t send_cmd(CI_Msg *cmd) {
	uint8_t length = 4+cmd->length;
	uint8_t send[length];
	*send = cmd->command;
	*(send+1) = cmd->length;
	uint8_t i = 0;
	while(i < cmd->length) {
		*(send+2+i) = *((cmd->data)+i);
		i++;
	}
	*(send+2+cmd->length) = (uint8_t)((cmd->checksum) >> 8);
	*(send+3+cmd->length) = (uint8_t)(cmd->checksum);
	send_data(send, length);
	return 0;
}

// creates a adding checksum for the send command
uint16_t create_checksum(CI_Msg *cmd) {
	uint16_t sum = (uint16_t)(cmd->command) + cmd->length;
	uint8_t i = 0;
	while(i < cmd->length) {
		sum += (*((cmd->data)+i));
		i++;
	}
	return sum;
}

// verifies the checksum upon a received command
uint8_t verify_checksum(CI_Msg *cmd) {
	uint16_t sum = (uint16_t)(cmd->command) + cmd->length;
	uint8_t i = 0;
	while(i < cmd->length) {
		sum += (*((cmd->data)+i));
		i++;
	}
	if(cmd->checksum != sum) {
		return 1;
	}
	return 0;
}

// runs the received command
uint8_t run_cmd(CI_Msg *cmd) {
	if(cmd->command == SET_COLOR){
		if(cmd->length != 1){return INVALID_LENGTH;}
		if((*(cmd->data) < OFF) || ((*(cmd->data)) > RGB)){return INVALID_DATA;}
		set_color(*(cmd->data));
	}
	else if(cmd->command == SET_BRIGHTNESS){
		if(cmd->length != 1){return INVALID_LENGTH;}
		if((*(cmd->data) < 0) || ((*(cmd->data)) > 100)){return INVALID_DATA;}
		set_brightness(*(cmd->data));
	}
	else {return UNKNOWN_CMD;}
	return NO_ERROR;
}

#endif
