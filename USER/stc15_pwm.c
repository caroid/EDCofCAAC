/************************************************************
* ��֯���ƣ� (C), 1988-1999, Tech. Co., Ltd.
* �ļ�����: STC15_PWM.C
* ����:  ������
* �汾:  1.1
* ����:  2017/4/27
* ����:  Ӳ��pwm�Ŀ⺯��
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 2017/4/27 1.1 �޸���һ���������case��������
* �ܳ��� 2017/5/6  1.2 ������һЩ�������ú���
***********************************************************/
#include    "stc15_pwm.h"
#include "../USER/GPIO.h"
//PWM��Ϣ�洢
static struct
{
    u32  PWM_period;
    float PWM_2_duty;
    float PWM_3_duty;
    float PWM_4_duty;
    float PWM_5_duty;
    float PWM_6_duty;
    float PWM_7_duty;
} PWM_info;
static bit PWM_state=0;	//PWM״̬�Ĵ�
//========================================================================
//u8    PWM_Inilize(PWM_InitTypeDef *PWM)
// ����:PWM��ʼ������
// ����:u8 PWM_N:PWM·�����(2~7) PWM: �ṹ����,��ο�pwm.h��Ķ���.
// ����: �ɹ�����0, ���󷵻�1
//========================================================================
static void PWM_Inilize(u8 PWM_N,PWM_InitTypeDef *PWMx)
{
    P_SW2|=0X80;
    if(ENABLE==PWMx->PWM_GOTO_ADC)            //ENABLE=����������ʱ ����ADC
    {
        PWMCFG|=(1<<7); //������˼���ǲ���ı�����λ��ֵ
    }
    else
    {
        PWMCFG&=(~(1<<7)); //��ʵҲ�������ϱߵİ취����������д����˼��ֱ��
    }
    if(PWM_HIGHT==PWMx->PWM_V_INIT)              //PWM_HIGHT=��ʼ�ߵ�ƽ     PWM_LOW=��ʼ�͵�ƽ
    {
        PWMCFG|=(1<<PWM_N);
    }
    else
    {
        PWMCFG&=(~(1<<PWM_N));
    }
    if(ENABLE==PWMx->PWM_0ISR_EN)             //ENABLE=ʹ��PWM�����������ж�  DISABLE=�ر�PWM�����������ж� �� CBIF��Ȼ�ᱻӲ����λ
    {
        PWMCR|=(1<<6);
    }
    else
    {
        PWMCR&=(~(1<<6));
    }
    if(ENABLE==PWMx->PWM_OUT_EN)              //ENABLE=PWMͨ��x�Ķ˿�ΪPWM��������� ��PWM���η���������
    {
        PWMCR|=(1<<PWM_N);
    }
    else
    {
        PWMCR&=(~(1<<PWM_N));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_EN)          //ENABLE=ʹ��PWM���ⲿ�쳣��⹦��
    {
        PWMFDCR=(1<<5);
    }
    else
    {
        PWMFDCR&=(~(1<<5));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_OUT)         //ENABLE=�����쳣ʱ��PWM��Ӧ������ڻ��� ��������ģʽ
    {
        PWMFDCR=(1<<4);
    }
    else
    {
        PWMFDCR&=(~(1<<4));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_ISR_EN)      //ENABLE=ʹ���쳣����ж� DISABLE=�ر��쳣����ж� ��FDIF��Ȼ�ᱻӲ����λ
    {
        PWMFDCR=(1<<3);
    }
    else
    {
        PWMFDCR&=(~(1<<3));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_CMP0_EN)     //ENABLE=�쳣���ԴΪ�Ƚ�������� ���ȽϽ��Ϊ��ʱ ����PWM�쳣
    {
        PWMFDCR=(1<<2);
    }
    else
    {
        PWMFDCR&=(~(1<<2));
    }
    if(ENABLE==PWMx->PWM_UNUSUAL_P24_EN)      //ENABLE=�쳣���ԴΪP24/PWMFLT ��P24=1 ����PWM�쳣
    {
        PWMFDCR=(1<<1);
    }
    else
    {
        PWMFDCR&=(~(1<<1));
    }
    //  PWMCKS=0;
    if(PWM_Clock_NT==PWMx->PWM_CLOCK)               //PWM_Clock_NT=PWM��ʱ��Դ��ϵͳʱ�Ӿ���Ƶ���ʱ��  PWM_Clock_Timer2_OF=PWM��ʱ��Դ��TMER2���������
    {
        PWMCKS&=(~(1<<4));
    }
    else
    {
        PWMCKS|=(1<<4);
    }
    // PWMCKS=0x00;
    PWMCKS|=PWMx->PWM_CLOCK_DIV;           //��PWM_CLOCK=PWM_Clock_NTʱ PWM��ʱ��Դ��ϵͳʱ��/(PS[3:0]+1)
    switch(PWM_N)
    {
    case PWM_2:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM2CR&=(~(1<<3));
        }
        else
        {
            PWM2CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM2CR|=(1<<2);
        }
        else
        {
            PWM2CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM2CR|=(1<<1);
        }
        else
        {
            PWM2CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM2CR|=(1<<0);
        }
        else
        {
            PWM2CR&=(~(1<<0));
        }
    }
    break;
    case PWM_3:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM3CR&=(~(1<<3));
        }
        else
        {
            PWM3CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM3CR|=(1<<2);
        }
        else
        {
            PWM3CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM3CR|=(1<<1);
        }
        else
        {
            PWM3CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM3CR|=(1<<0);
        }
        else
        {
            PWM3CR&=(~(1<<0));
        }
    }
    break;
    case PWM_4:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM4CR&=(~(1<<3));
        }
        else
        {
            PWM4CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM4CR|=(1<<2);
        }
        else
        {
            PWM4CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM4CR|=(1<<1);
        }
        else
        {
            PWM4CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM4CR|=(1<<0);
        }
        else
        {
            PWM4CR&=(~(1<<0));
        }
    }
    break;
    case PWM_5:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM5CR&=(~(1<<3));
        }
        else
        {
            PWM5CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM5CR|=(1<<2);
        }
        else
        {
            PWM5CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM5CR|=(1<<1);
        }
        else
        {
            PWM5CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM5CR|=(1<<0);
        }
        else
        {
            PWM5CR&=(~(1<<0));
        }
    }
    break;
    case PWM_6:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM6CR&=(~(1<<3));
        }
        else
        {
            PWM6CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM6CR|=(1<<2);
        }
        else
        {
            PWM6CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM6CR|=(1<<1);
        }
        else
        {
            PWM6CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM6CR|=(1<<0);
        }
        else
        {
            PWM6CR&=(~(1<<0));
        }
    }
    break;
    case PWM_7:
    {
        if(PWM_SELECT_N==PWMx->PWM_SELECTx_IO)          //PWM_SELECT_N=PWM��һѡ��IO�� PWM_SELECT_N_2=PWM�ڶ�ѡ��IO��
        {
            PWM7CR&=(~(1<<3));
        }
        else
        {
            PWM7CR|=(1<<3);
        }
        if(ENABLE==PWMx->PWM_ISRx_EN)             //ENABLE=ʹ��PWMx�ж� ʹ�ܵ�һ��ת��ڶ���ת�ж�
        {
            PWM7CR|=(1<<2);
        }
        else
        {
            PWM7CR&=(~(1<<2));
        }
        if(ENABLE==PWMx->PWM_T1x_EN)              //ENABLE=ʹ�ܵ�һ��ת�ж�
        {
            PWM7CR|=(1<<1);
        }
        else
        {
            PWM7CR&=(~(1<<1));
        }
        if(ENABLE==PWMx->PWM_T2x_EN)              //ENABLE=ʹ�ܵڶ���ת�ж�
        {
            PWM7CR|=(1<<0);
        }
        else
        {
            PWM7CR&=(~(1<<0));
        }
    }
    break;
    default:
//      return 1;
        break;
    }
    if(ENABLE==PWMx->PWM_EN)                  //ENABLE=PWMʹ�� ������PWM�������úú�������� ������رպ��ڴ򿪣���PWM���������´�0����
    {
        PWMCR|=(1<<7);
    }
    else
    {
        PWMCR&=(~(1<<7));
    }
}
/*************************************************
* ��������: void    PWM_config(u8 PWM_N)
* ����: ������Ҫʹ�õ�pwmͨ��
* ����: u8 PWM_N��N�ķ�Χ��2~7
* ����ֵ: ��
* ����˵��: �����Զ���ʼ����Ӧ��io����
*************************************************/
void    PWM_config(u8 PWM_N)
{
    GPIO_InitTypeDef    GPIO_InitStructure;     //�ṹ����
    PWM_InitTypeDef  PWM_InitStructure;
    switch(PWM_N)
    {
    case PWM_2:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_7 ;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;
        GPIO_Inilize(GPIO_P3,&GPIO_InitStructure);  //��ʼ��
        P37=1;
    };
    break;
    case PWM_3:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_1 ;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //��ʼ��
        P21=1;
    };
    break;
    case PWM_4:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_2 ;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //��ʼ��
        P22=1;
    };
    break;
    case PWM_5:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_3 ;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P2,&GPIO_InitStructure);  //��ʼ��
        P23=1;
    };
    break;
    case PWM_6:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_6;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);  //��ʼ��
        P16=1;
    };
    break;
    case PWM_7:
    {
        GPIO_InitStructure.Pin  = GPIO_Pin_7 ;    //ָ��Ҫ��ʼ����IO, GPIO_Pin_0 ~ GPIO_Pin_7, �����
        GPIO_InitStructure.Mode = GPIO_PullUp;       //ָ��IO������������ʽ,GPIO_PullUp,GPIO_HighZ,GPIO_OUT_OD,GPIO_OUT_PP
        GPIO_Inilize(GPIO_P1,&GPIO_InitStructure);  //��ʼ��
        P17=1;
    };
    break;
    }
    PWM_UNLOCK;
    PWM_InitStructure.PWM_GOTO_ADC=DISABLE;
    PWM_InitStructure.      PWM_V_INIT= PWM_LOW;
    PWM_InitStructure.      PWM_0ISR_EN=  DISABLE;
    PWM_InitStructure.      PWM_OUT_EN=ENABLE;
    PWM_InitStructure.     PWM_UNUSUAL_EN= DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_OUT=  DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_ISR_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_CMP0_EN=DISABLE;
    PWM_InitStructure.     PWM_UNUSUAL_P24_EN=DISABLE;
    PWM_InitStructure.       PWM_CLOCK=PWM_Clock_NT;
    PWM_InitStructure.       PWM_CLOCK_DIV=0x00;
    PWM_InitStructure.       PWM_SELECTx_IO=PWM_SELECT_N;
    PWM_InitStructure.     PWM_ISRx_EN=  DISABLE;
    PWM_InitStructure.       PWM_T1x_EN=   DISABLE;
    PWM_InitStructure.       PWM_T2x_EN=    DISABLE;
    PWM_InitStructure.       PWM_EN=  DISABLE;
    PWM_Inilize(PWM_N,&PWM_InitStructure) ;
    PWM_LOCK;
    
  
}
//void PCA_PWM_config(void)//PCA����pwm
//{
////      PCA_InitStructure.PCA_Clock    = PCA_Clock_12T;     //PCA_Clock_1T, PCA_Clock_2T, PCA_Clock_4T, PCA_Clock_6T, PCA_Clock_8T, PCA_Clock_12T, PCA_Clock_Timer0_OF, PCA_Clock_ECI
////    PCA_InitStructure.PCA_IoUse    = PCA_P24_P25_P26_P27;   //PCA_P12_P11_P10_P37, PCA_P34_P35_P36_P37, PCA_P24_P25_P26_P27
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //ENABLE, DISABLE
////    PCA_InitStructure.PCA_Polity   = PolityLow;         //????? Polityduty,PolityLow
////    PCA_Init(PCA_Counter,&PCA_InitStructure);
////    PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;      //PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_dutyPulseOutput
////    PCA_InitStructure.PCA_PWM_Wide = 0;      //PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
////    PCA_InitStructure.PCA_Value    = 100;         //??PWM,?8??PWM???
////    PCA_Init(PCA0,&PCA_InitStructure);
////    PCA_InitStructure.PCA_Mode     = PCA_Mode_HighPulseOutput;      //PCA_Mode_PWM, PCA_Mode_Capture, PCA_Mode_SoftTimer, PCA_Mode_dutyPulseOutput
////    PCA_InitStructure.PCA_PWM_Wide = 0;      //PCA_PWM_8bit, PCA_PWM_7bit, PCA_PWM_6bit
////    PCA_InitStructure.PCA_Interrupt_Mode = ENABLE;     //PCA_Rise_Active, PCA_Fall_Active, ENABLE, DISABLE
////    PCA_InitStructure.PCA_Value    = 100;         //??PWM,?8??PWM???
////    PCA_Init(PCA1,&PCA_InitStructure);
//}

/////////////////////////////////////////
//����PWM����
u8 PWM_SET_PERIOD(u16 period)
{
    if(0x8000>period)
    {
        PWMCL=(u8)(period);
        PWMCH=(u8)(period>>8);
        return 0;
    }
    else
    {
        return 1;
    }
}
/////////////////////////////////////////
//����PWM��һ�κ͵ڶ��η�ת����
//����⺯���Ĵ���ȫ�������õ�pwm2
static u8 PWM_SET_T12_PERIOD(u8 PWM_N,u16 period1,u32 period2)
{
    switch(PWM_N)
    {
    case PWM_2:
        PWM2T1L=(u8)(period1);
        PWM2T1H=(u8)(period1>>8);
        PWM2T2L=(u8)(period2);
        PWM2T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_3:
        PWM3T1L=(u8)(period1);
        PWM3T1H=(u8)(period1>>8);
        PWM3T2L=(u8)(period2);
        PWM3T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_4:
        PWM4T1L=(u8)(period1);
        PWM4T1H=(u8)(period1>>8);
        PWM4T2L=(u8)(period2);
        PWM4T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_5:
        PWM5T1L=(u8)(period1);
        PWM5T1H=(u8)(period1>>8);
        PWM5T2L=(u8)(period2);
        PWM5T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_6:
        PWM6T1L=(u8)(period1);
        PWM6T1H=(u8)(period1>>8);
        PWM6T2L=(u8)(period2);
        PWM6T2H=(u8)(period2>>8);
        return 0;
        break;
    case PWM_7:
        PWM7T1L=(u8)(period1);
        PWM7T1H=(u8)(period1>>8);
        PWM7T2L=(u8)(period2);
        PWM7T2H=(u8)(period2>>8);
        return 0;
        break;
    default:
        return 1;
        break;
    }
}
/*************************************************
* ��������: u32 getPWM_period(void )
* ����: ���������õ�pwmƵ����Ϣ
* ����: ��
* ���: ��
* ����ֵ: pwmƵ��
* ����˵��: ��û������pwm��Ƶ�ʾ͵��ô˺�����᷵��0��
*************************************************/
u32 getPWM_period(void )
{
    return PWM_info.PWM_period;
}
/*************************************************
* ��������: float getPWM_n_duty(u8 PWM_N)
* ����: ����PWM_N��ռ�ձ���Ϣ
* ����: u8 PWM_N
* ���: ��
* ����ֵ: PWM_N��ռ�ձ���Ϣ,float��ʽ
* ����˵��: ��û������pwm��ռ�ձȾ͵��ô˺�����᷵��0��
*************************************************/
float getPWM_N_duty(u8 PWM_N)
{
    switch(PWM_N)
    {
    case PWM_2:
        return PWM_info.PWM_2_duty;
        break;
    case PWM_3:
        return PWM_info.PWM_3_duty;
        break;
    case PWM_4:
        return PWM_info.PWM_4_duty;
        break;
    case PWM_5:
        return PWM_info.PWM_5_duty;
        break;
    case PWM_6:
        return PWM_info.PWM_6_duty;
        break;
    case PWM_7:
        return PWM_info.PWM_7_duty;
        break;
    }
}


/*************************************************
* ��������:void PWM_period(u16 Hz)
* ����: ����Ӳ��pwm��ͬһƵ�� ��������Ƶ������
* �����������õĺ���:
* 1.PWM_SET_PERIOD
* ���ñ������ĺ���:
* ����:
* 1.u16 Hz:Ҫ�����pwm��Ƶ�ʣ���Ϊ�������Ĳ���ֵ������Ӳ�����ޣ�����ı�����6��pwm��Ƶ��
* ���: ��
* ����ֵ: ��
* ����: �˺���ֻ������pwm�ļ�������ʼֵ���Ӷ����pwm��ͬƵ�ʵ������
        �������ڵ�Ƭ��Ӳ�����ޣ������Ե�����ÿ·pwm��Ƶ�ʽ����޸ģ�
        ֻ��һ��ȫ�ġ�
*************************************************/
void PWM_period(u16 Hz)
{
    PWM_info.PWM_period= (u16)(MAIN_Fosc/Hz);
    PWM_UNLOCK;
    PWM_SET_PERIOD(PWM_info.PWM_period);
    PWM_LOCK;
}
/*************************************************
* ��������: void PWM_duty(u8 PWM_N,float duty)
* ����: �޸�ĳһ·pwm��ռ�ձ� ��������ռ�ձ�����
* �����������õĺ���:
* ���ñ������ĺ���:
* ����:
* 1.u8 PWM_N �� ��һ·pwm
* 2.float duty��ռ�ձȣ�ʹ��С������0.8����80%��ռ�ձ�
* ���: ��
* ����ֵ: ��
* ����˵��:
*************************************************/
void PWM_duty(u8 PWM_N,float duty)
{
    u32 period2;
    if(duty>0.999f)
    {
        duty=0.999f;
#ifdef PID_DEBUG
        PrintString1("duty is over the maximum\n");
#endif
    }
    if(duty<0.001f)
    {
        duty=0.001f;
#ifdef PID_DEBUG
        PrintString1("duty is over the miximum\n");
#endif
    }
    switch(PWM_N)
    {
    case PWM_2:
        PWM_info.PWM_2_duty=duty;
        period2=(u32)(PWM_info.PWM_2_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_3:
        PWM_info.PWM_3_duty=duty;
        period2=(u32)(PWM_info.PWM_3_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_4:
        PWM_info.PWM_4_duty=duty;
        period2=(u32)(PWM_info.PWM_4_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_5:
        PWM_info.PWM_5_duty=duty;
        period2=(u32)(PWM_info.PWM_5_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_6:
        PWM_info.PWM_6_duty=duty;
        period2=(u32)(PWM_info.PWM_6_duty*PWM_info.PWM_period ) ;
        break;
    case PWM_7:
        PWM_info.PWM_7_duty=duty;
        period2=(u32)(PWM_info.PWM_6_duty*PWM_info.PWM_period ) ;
        break;
    }
    PWM_UNLOCK;
    PWM_SET_T12_PERIOD(PWM_N,0,period2);
    PWM_LOCK;
}
void OPEN_PWM(void)
{
	PWM_UNLOCK;	
	PWM_ALL_EN;
	PWM_state=ON;
  PWM_LOCK;
}
void CLOSE_PWM(void)
{
	PWM_UNLOCK;	
	PWM_ALL_NO;
	PWM_state=OFF;
    PWM_LOCK;
	
}
bit getPWM_state(void)
{
	
return PWM_state;	
}

