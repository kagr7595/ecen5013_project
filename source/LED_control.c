/***************************************************************************
*
*  	Filename: LED_control.c
*	Description: High level functions to alter the color and brightness of the
*	LEDs
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _LED_CONTROL_C
#define _LED_CONTROL_C

#include "LED_control.h"

//global variables allow for the code to retain memory of what the LED was last set to
#if FRDM
uint8_t color = RGB;
uint8_t duty = 100;
#endif

void set_brightness(uint8_t new_duty){
#if FRDM
	// function runs directly if invoked by the FRDM board
	set_PWM_RGB(new_duty, color);
	duty = new_duty;
#else
	//if invoked by the BBB, it initiates a command packet transfer
    CI_Msg cmd;
    uint8_t data[1] = {new_duty};
    create_cmd(&cmd, SET_BRIGHTNESS, 1, data);
    send_cmd(&cmd);
#endif
}

void set_color(uint8_t new_color){
#if FRDM
	// function runs directly if invoked by the FRDM board
	set_PWM_RGB(duty, new_color);
	color = new_color;
#else
	//if invoked by the BBB, it initiates a command packet transfer
    CI_Msg cmd;
    uint8_t data[1] = {new_color};
    create_cmd(&cmd, SET_COLOR, 1, data);
    send_cmd(&cmd);
#endif
}

#endif
