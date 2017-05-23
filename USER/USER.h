#ifndef _USER_H_
#define _USER_H_
#include "config.h"

//debugģʽ��ע�ʹ��д������˳���debug
#define DEBUG
#ifdef DEBUG
//#define MOTOR_DEBUG
//#define DISPLAY_DEBUG
//#define BUTTON_DEBUG
//#define PID_DEBUG
#endif
//��ʼ�������궨��
#define UART1_BANDRATE 115200ul
#define PWM_PERIOD 5000
#define ANGLE_PIN ADC_P10//adc io��
#define ANGLE_Speed ADC_90T//adcת���ٶ�

void loop(void);
void setup(void);
void setAngle(void);
void sendScopeData(void);    
void uiDraw(void);
void UART1_init(unsigned long BandRate);

#endif
