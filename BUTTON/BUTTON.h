#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "../USER/GPIO.h"
#define FIRST_MEUN_NUM 0
#define SECOND_MEUN_NUM 1
#define BUTTON1_GPIO_PIN GPIO_Pin_3
#define BUTTON2_GPIO_PIN GPIO_Pin_4
#define BUTTON3_GPIO_PIN GPIO_Pin_5
#define BUTTON4_GPIO_PIN GPIO_Pin_6
#define BUTTON1 P23
#define BUTTON2 P24
#define BUTTON3 P25
#define BUTTON4 P26
/*********��������ͽӿں���***********/
void  buttonScan(void );
unsigned char getMenuNum(menuNum);
void setMenu_MAXandMIN(char max,char min);
void Button_config();
bit getButtonState(u8 BUTTON_data); //��ȡ����״̬����,���°�������1��û���·���0
#endif
