/*
 * software_timer.c
 *
 *  Created on: Nov 3, 2022
 *      Author: xanlo
 */


#include "software_timer.h"

int timer1_flag = 0;
int timer1_counter = 0;
int timer2_flag = 0;
int timer2_counter = 0;
int timer3_flag = 0;
int timer3_counter = 0;
int timer4_flag = 0;
int timer4_counter = 0;
int timer5_flag = 0;
int timer5_counter = 0;
int timer_vertical_flag = 0;
int timer_vertical_counter = 0;
int timer_horizontal_flag = 0;
int timer_horizontal_counter = 0;

int TIMER_CYCLE = 10;

void setTimer1(int duration) {
	timer1_counter = duration / TIMER_CYCLE;
	timer1_flag = 0;
}

void setTimer2(int duration) {
	timer2_counter = duration / TIMER_CYCLE;
	timer2_flag = 0;
}

void setTimer3(int duration) {
	timer3_counter = duration / TIMER_CYCLE;
	timer3_flag = 0;
}

void setTimer4(int duration) {
	timer4_counter = duration / TIMER_CYCLE;
	timer4_flag = 0;
}
void setTimer5(int duration) {
	timer5_counter = duration / TIMER_CYCLE;
	timer5_flag = 0;
}

void setTimerVertical(int duration) {
	timer_vertical_counter = duration / TIMER_CYCLE;
	timer_vertical_flag = 0;
}

void setTimerHorizontal(int duration) {
	timer_horizontal_counter = duration / TIMER_CYCLE;
	timer_horizontal_flag = 0;
}

void clearTimer1() {
	timer1_counter = 0;
	timer1_flag = 0;
}

void clearTimer2() {
	timer2_counter = 0;
	timer2_flag = 0;
}

void clearTimer3() {
	timer3_counter = 0;
	timer3_flag = 0;
}

void clearTimer4() {
	timer4_counter = 0;
	timer4_flag = 0;
}

void clearTimer5() {
	timer5_counter = 0;
	timer5_flag = 0;
}

void clearTimerVertical() {
	timer_vertical_counter = 0;
	timer_vertical_flag = 0;
}

void clearTimerHorizontal() {
	timer_horizontal_counter = 0;
	timer_horizontal_flag = 0;
}

void timerRun() {
	if (timer1_counter > 0) {
		timer1_counter--;
		if (timer1_counter <= 0) {
			timer1_flag = 1;
		}
	}

	if (timer2_counter > 0) {
		timer2_counter--;
		if (timer2_counter <= 0) {
			timer2_flag = 1;
		}
	}

	if (timer3_counter > 0) {
		timer3_counter--;
		if (timer3_counter <= 0) {
			timer3_flag = 1;
		}
	}

	if (timer4_counter > 0) {
		timer4_counter--;
		if (timer4_counter <= 0) {
			timer4_flag = 1;
		}
	}

	if (timer5_counter > 0) {
		timer5_counter--;
		if (timer5_counter <= 0) {
			timer5_flag = 1;
		}
	}

	if (timer_vertical_counter > 0) {
		timer_vertical_counter--;
		if (timer_vertical_counter <= 0) {
			timer_vertical_flag = 1;
		}
	}

	if (timer_horizontal_counter > 0) {
		timer_horizontal_counter--;
		if (timer_horizontal_counter <= 0) {
			timer_horizontal_flag = 1;
		}
	}

}
