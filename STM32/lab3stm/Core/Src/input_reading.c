/*
 * input_reading.c
 *
 *  Created on: Nov 2, 2022
 *      Author: xanlo
 */


#include "main.h"
//we aim to work with more than one buttons
#define N0_OF_BUTTONS 				       3
//timer interrupt duration is 10ms, so to pass 1 second,
//we need to jump to the interrupt service routine 100 time
#define DURATION_FOR_AUTO_INCREASING	   100
#define BUTTON_IS_PRESSED                  GPIO_PIN_RESET
#define BUTTON_IS_RELEASED                 GPIO_PIN_SET
//the buffer that the final result is stored after
//debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];
//we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];
//we define a flag for a button pressed more than 1 second.

static GPIO_TypeDef *buttonPort[N0_OF_BUTTONS] = {
		MODE_GPIO_Port,
		ADD_GPIO_Port,
		CONFIRM_GPIO_Port,
		RESET_GPIO_Port
};

static uint16_t buttonPin[N0_OF_BUTTONS] = {
		MODE_Pin,
		ADD_Pin,
		CONFIRM_Pin,
		RESET_Pin
};

static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
//we define counter for automatically increasing the value
//after the button is pressed more than 1 second.
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

void button_reading(void){
	for (int i = 0; i < N0_OF_BUTTONS; i++) {
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(buttonPort[i], buttonPin[i]);

		if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
			//valid input, can read now
			buttonBuffer[i] = debounceButtonBuffer1[i];
//			if (buttonBuffer[i] == BUTTON_IS_PRESSED) {
//				if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING){
//					counterForButtonPress1s[i]++;
//				} else {
//					flagForButtonPress1s[i] = 1;
//				}
//			} else {
//				counterForButtonPress1s[i] = 0;
//				flagForButtonPress1s[i] = 0;
//			}
		}
	}
}

unsigned char is_button_pressed(uint8_t index){
	if(index >= N0_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index){
	if(index >= N0_OF_BUTTONS) return 0xff;
	return (flagForButtonPress1s[index] == 1);
}
