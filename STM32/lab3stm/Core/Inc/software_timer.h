/*
 * software_timer.h
 *
 *  Created on: Nov 3, 2022
 *      Author: xanlo
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int TIMER_CYCLE;
extern int timer_vertical_flag;
extern int timer_horizontal_flag;

void setTimer1(int duration);
void setTimer2(int duration);
void setTimer3(int duration);
void setTimerVertical(int duration);
void setTimerHorizontal(int duration);
void clearTimer1();
void clearTimerVertical();
void clearTimerHorizontal();
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
