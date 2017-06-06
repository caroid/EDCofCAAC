/************************************************************
* ��֯���ƣ����Ӵ���С��
* �ļ�����: MODE.C
* ����: �ܳ���
* �汾 beta 1.1
* ����: 5/26
* ����: ����ѡ��ģʽ��ִ��ģʽ������ļ�
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 17/5/28 1.0			������ģʽһ
* �ܳ���	 17/6/6  1.1    ������ģʽ��
***********************************************************/

#include "MODE.H"
#include "timer.h" //������ʱ��ͷ�ļ�
#include "../RTOS/OS.h"
#include "../USER/delay.h"
#include "../USER/USART1.h"
#include <math.h>
  static u8 mode=0; //Ĭ��ģʽ0�����������ð���ѡ��ģʽ
//������⣬4��������Ӧ4��ģʽ

void modeSelect(void)
{
	static bit BUTTON1_bit = 0;  //�������±�־λ
	static bit BUTTON2_bit = 0;  //ͬ��
	static bit BUTTON3_bit = 0;
	static bit BUTTON4_bit = 0;

	if (getButtonState(BUTTON1_GPIO_PIN))
	{
		if (!BUTTON1_bit)
		{
			mode=1;
			BUTTON1_bit = 1;
		
		}

	}
	else
	{
		BUTTON1_bit = 0;
	}

	if (getButtonState(BUTTON2_GPIO_PIN))
	{
		if (!BUTTON2_bit)
		{
			BUTTON2_bit = 1;

		  mode=2;

		}
	}
	else
	{
		BUTTON2_bit = 0;
	}
		if (getButtonState(BUTTON3_GPIO_PIN))
	{
		if (!BUTTON3_bit)
		{
			mode=3;
			BUTTON3_bit = 1;
		
		}

	}
	else
	{
		BUTTON3_bit = 0;
	}

	if (getButtonState(BUTTON4_GPIO_PIN))
	{
		if (!BUTTON4_bit)
		{
			BUTTON4_bit = 1;

		  mode=4;

		}
	}
	else
	{
		BUTTON4_bit = 0;
	}

	
}
//��ͬģʽ��Ӧ�ĳ���
void modeStart(void)
{  
	 switch(mode)
	 {
		 case 1://ģʽ1
		 {
			 	static bit step1=0;//ģʽһ����1��־λ
				static bit step2=0; //����2 ��־λ
				static bit step3=0;  //��������־λ

			 if(step1)//����һ�Ѿ����
			 {
				 
				  if(step2) //�������2�����
					{
						  if(step3) //����������Ѿ����
							{
								  //ģʽһ�Ѿ���� ����������ʼ��
								mode=0;//��ʼ��ģʽ
								step1=0;
								step2=0;
								step3=0;
								
							}
							else//���������û�����
							{
								stopMotor();
								step3=OK;
								PrintString1("step3 is ok\n");
								
							}
						
					}
					else //��������û�����
					{
					setTimeout(Timer1,5000); //���ö�ʱ����ʱ���� ,5��
		//////////////////////��ʱ��////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
					{
						
						  setMotorSpeed(LEFT_MOTOR,0.01f);
						  setMotorSpeed(RIGHT_MOTOR,0.99f);
							step2=OK;
						  PrintString1("step2 is ok\n");
					}
					else//���δ�ﵽ��ʱʱ���ʱ��δ����
					{ 
						
						if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		   
					
					}
			 }
			 else //�������һû�����
			 {
				 setPID_data(SET_ANGLE,100); //�趨�ȶ��Ƕ�
				 setTimeout(Timer1,5000); //���ö�ʱ����ʱ���� ,3��
				 startMotor();//�����ʼ����
				 if(abs(getPID_data(ERR))<2.0f)//�����С��2��ʱ����Ϊ�ﵽ�ȶ�,��ʱ���Ϳ�ʼ��ʱ
				{
		//////////////////////��ʱ��////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
					{
						 stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
						 step1=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
						 PrintString1("step1 is ok\n");
					}
					else//���δ�ﵽ��ʱʱ���ʱ��δ����
					{ 
						
						if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		 
				}
			 }
			 
			 
		 };
		 break;
		 case 2://ģʽ��
		 {
			static bit step1=0;
			static bit step2=0; 
			static bit step3=0;
			static bit step4=0;
			if(step1)
			{
        if(step2)
				{
					if(step3)
					{
						if(step4)
						{ 
							mode=0;
							
							step1=0;
							step2=0;
							step3=0;
							step4=0;
							
						}
						else
						{
							 setPID_data(SET_ANGLE,110); //�趨�ȶ��Ƕ�
							 setTimeout(Timer1,1000); //���ö�ʱ����ʱ���� ,1��
							 startMotor();//�����ʼ����
							 if(abs(getPID_data(ERR))<2.0f)//�����С��2��ʱ����Ϊ�ﵽ�ȶ�,��ʱ���Ϳ�ʼ��ʱ
							{
					//////////////////////��ʱ��////////////////////////////////////////
								if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
								{
									 stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
									 step4=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
									 PrintString1("step4 is ok\n");
								}
								else//���δ�ﵽ��ʱʱ���ʱ��δ����
								{ 
									
									if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
									{
										restartTimer(Timer1);
										
									}
								}
					////////////////////////////////////////////////////////////////		 
							 }
						}
						
					}
					else
					{
						  setPID_data(SET_ANGLE,70); //�趨�ȶ��Ƕ�
							 setTimeout(Timer1,1000); //���ö�ʱ����ʱ���� ,1��
							 startMotor();//�����ʼ����
							 if(getPID_data(ERR)<2.0f)//�����С��2��ʱ���ӽ��ȶ�,��ʱ���Ϳ�ʼ��ʱ
							{
					//////////////////////��ʱ��////////////////////////////////////////
								if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
								{
									 stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
									 step3=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
									 PrintString1("step3 is ok\n");
								}
								else//���δ�ﵽ��ʱʱ���ʱ��δ����
								{ 
									
									if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
									{
										restartTimer(Timer1);
										
									}
								}
					////////////////////////////////////////////////////////////////		 
							 }
						
					}
					
				}				
				else
				{
				 setPID_data(SET_ANGLE,110); //�趨�ȶ��Ƕ�
				 setTimeout(Timer1,1000); //���ö�ʱ����ʱ���� ,1��
				 startMotor();//�����ʼ����
				 if(getPID_data(ERR)<2.0f)//�����С��2��ʱ����Ϊ�ﵽ�ȶ�,��ʱ���Ϳ�ʼ��ʱ
				{
		//////////////////////��ʱ��////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
					{
						 stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
						 step2=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
						 PrintString1("step2 is ok\n");
					}
					else//���δ�ﵽ��ʱʱ���ʱ��δ����
					{ 
						
						if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		 
				 }
				}


			}
			else
			{
				 setPID_data(SET_ANGLE,70); //�趨�ȶ��Ƕ�
				 setTimeout(Timer1,3000); //���ö�ʱ����ʱ���� ,3��
				 startMotor();//�����ʼ����
				 if(<2.0f)//�����С��2��ʱ����Ϊ�ﵽ�ȶ�,��ʱ���Ϳ�ʼ��ʱ
				{
		//////////////////////��ʱ��////////////////////////////////////////
					if(isExpiredTimer(Timer1))   //����ﵽ��ʱʱ��
					{
						 stopTimer(Timer1);//�ﵽ��ʱʱ���رն�ʱ��
						 step1=OK; //����һ��� ���Ѿ��ﵽ�ȶ�״̬����������һ��
						 PrintString1("step1 is ok\n");
					}
					else//���δ�ﵽ��ʱʱ���ʱ��δ����
					{ 
						
						if(isStopped(Timer1)) //ֻ�е���ʱ����ֹͣ״̬ʱ��������ʱ����
						{
							restartTimer(Timer1);
							
						}
					}
		////////////////////////////////////////////////////////////////		 
				}
				
			}
	
		
		 };
		 break;
		 case 3: //ģʽ3
		 {
			 static unsigned int mode2_ERR_times = 0;
			 static bit mode2_step1 = 0;
			 static bit mode2_step2 = 0;
			 static unsigned int mode2_time = 0;
			 static unsigned float mode2_Sta_angle = 0;
			 
			 setTimeout(Timer1,10);
			 if(mode2_step1)
			 {
				 
			 }
			 else
			 {
				 setPID_data(SET_ANGLE,70);
				 startMotor();
				 if(getPID_data(ERR) < 2.0f)
				 {
					 if(isExpiredTimer(Timer1))
					 {
						 mode2_ERR_times++;
						 mode2_Sta_angle += getPID_data(ERR);
						 if(mode2_ERR_times >= 50)
						 {
							 mode2_Sta_angle /= mode2_ERR_times;
							 mode2_ERR_times = 0;
							 if(abs(mode2_ERR_times) < 5)
							 {
								 mode2_step = 1;
							 }
						 }
					 }
					 else
					 {
						 restartTimer(Timer1);
					 }
				 }
			 }
			 
		 };
		 break;
		 case 4:  //ģʽ4
		 {
			 
			 
		 };
		 break;
    
		 default:
		break;		 
	 }
	
}