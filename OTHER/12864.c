#include "lcd12864.h"  
bool bShowPicFlag=false;          //��ͼʱͼ����ʾ����  
  
/* 
u8 LCD12864_table[]={"123456789"}; 
*/  
  
void LCD12864_drawFillRect(u8 x,u8 y, u8 width,u8 hight,u8 flag)//�������λ�õ���������  
{//������ʼ����x(0-127),y(0-63),��(1-128)��(1-64),flag��3��ֵ,0�������,1��ɫ,2��0  
    u8 i=0;  
    u8 j=0;  
    if(0==width||0==hight)   //���ο�Ȼ�߶�Ϊ0ʱ����  
    {  
        return ;  
    }  
    if( (x+width>128 ||(y+hight)>64)  )  
    {  
        led2=0;  
        return;  
    }  
    for(j=0;j
    {         
        for(i=0;i
        {  
            LCD12864_drawDot(x+i, y+j,flag);          
        }  
    }             
}  
  
  
void LCD12864_drawRectangle(u8 x,u8 y, u8 width,u8 hight,u8 flag)//������  
{   //������ʼ����x(0-127),y(0-63),���(1-128)�͸߶�(1-64) flag��3��ֵ,0����д1,1��ɫ,2��0  
    if(0==width||0==hight)   //���ο�Ȼ�߶�Ϊ0ʱ����  
    {  
        return ;  
    }  
    width--;hight--;  
    LCD12864_drawXYLine(x, y,x+width, y, flag);  
    LCD12864_drawXYLine(x+width, y,x+width, y+hight, flag);  
LCD12864_drawXYLine
LCD12864_drawXYLine(x, y,x, y+hight, flag);  
    LCD12864_drawXYLine(x, y+hight,x+width, y+hight, flag);   
}  
  
bool LCD12864_drawXYLine(u8 x1,u8 y1,  u8 x2, u8 y2,  u8 flag)//��ˮƽ��ֱֱ��  
{   //��ʼ��������յ�����,x(0-127),y(0-63),  flag��3��ֵ,0����д1,1��ɫ,2��0  
    u8 n=0;  
    if(flag>2|| x1>127||x2>127||y1>63||y2>63)  
    {  
        return false;  
    }  
  
    if(x1==x2)  
    {  
        for(n=0;n
        {  
            LCD12864_drawDot( x1,y1+(y2>=y1?n:-n) ,flag);      
        }  
    }  
  
    if(y1==y2)  
    {  
        for(n=0;n
        {  
             LCD12864_drawDot(x1+(x2>=x1?n:-n),y1,flag)  ;  
        }  
    }  
    return true;      
}  
  
void LCD12864_drawCircle(u8 x0,u8 y0,u8 r,u8 flag)  
{  
    s8 a,b;  
    s8 di;  
    if(r>31 ||r==0) return;    //�������ˣ���Һ����ʾ�����Բ�뾶Ϊ31  
    a=0;  
    b=r;  
    di=3-2*r;       //�ж��¸���λ�õı�־  
    while(a<=b)  
    {  
        LCD12864_drawDot(x0-b,y0-a,flag);  //3             
        LCD12864_drawDot(x0+b,y0-a,flag);  //0             
        LCD12864_drawDot(x0-a,y0+b,flag);  //1         
        LCD12864_drawDot(x0-b,y0-a,flag);  //7             
        LCD12864_drawDot(x0-a,y0-b,flag);  //2               
        LCD12864_drawDot(x0+b,y0+a,flag);  //4                 
        LCD12864_drawDot(x0+a,y0-b,flag);  //5  
        LCD12864_drawDot(x0+a,y0+b,flag);  //6   
        LCD12864_drawDot(x0-b,y0+a,flag);               
        a++;  
        //ʹ��Bresenham�㷨��Բ       
        if(di<0)  
        di +=4*a+6;  
        else  
        {  
            di +=10+4*(a-b);     
            b--;  
        }   
        LCD12864_drawDot(x0+a,y0+b,flag);  
    }  
}  
  
  
void LCD12864_drawVerticalSquare(u8 x,u8 y,u8 r,u8 flag)    //��վ����������  
{  
    u8 a,b;  
    float c=0;  
    a = 0;  
    b = r;  
    c = 3 - 2*r;  
    while(a < b)  
    {  
        LCD12864_drawDot(x+a,y+b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
        LCD12864_drawDot(x+a,y-b,flag);  
        LCD12864_drawDot(x-a,y-b,flag);  
          
        LCD12864_drawDot(x+b,y+a,flag);  
        LCD12864_drawDot(x-b,y+a,flag);  
        LCD12864_drawDot(x+b,y-a,flag);  
        LCD12864_drawDot(x-b,y-a,flag);  
          
        if(c < 0)  
        {  
            c = c+4*a + 6;   
        }  
        else  
        {  
            c= c + 4*(a - b) + 10;  
            b-=1;  
        }  
        a = a + 1;  //���ƴ����  
          
    }  
    if(a == b)  
    {  
        LCD12864_drawDot(x+a,y+b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
        LCD12864_drawDot(x+a,y-b,flag);  
        LCD12864_drawDot(x-a,y+b,flag);  
          
        LCD12864_drawDot(x+b,y+a,flag);  
        LCD12864_drawDot(x-b,y+a,flag);  
        LCD12864_drawDot(x+b,y-a,flag);  
        LCD12864_drawDot(x-b,y-a,flag);         
    }  
}  
  
  
void LCD12864_drawAnyLine(u8 StartX, u8 StartY,u8 EndX, u8 EndY, u8 flag)  //������ֱ��  
{  
    u8 t, distance ;      /*������Ļ��С�ı��������(���Ϊint��)*/  
    s16 x = 0 , y = 0 ;  
    s8 incx, incy, dx, dy ;  
    if((StartX==EndX) ||(StartY==EndY))  
    {  
        LCD12864_drawXYLine(StartX,StartY,EndX,EndY,flag);  
        return;  
    }  
  
    dx = EndX - StartX ;  
    dy = EndY - StartY ;          
    incx = dx > 0 ?1:-1;  
    incy = dy > 0 ?1:-1;  
  
    dx = abs( dx );  
    dy = abs( dy );  
    if( dx > dy )  
    {  
        distance = dx ;  
    }  
    else  
    {  
distance = dy ;
distance = dy ;  
    }  
    LCD12864_drawDot( StartX, StartY, flag ) ;        //���ײ���  
    for( t = 0 ; t <= distance+1 ; t++ )  
    {  
        LCD12864_drawDot( StartX, StartY, flag ) ;  
        x += dx ;  
        y += dy ;  
        if( x > distance )  
        {  
            x -= distance ;  
            StartX += incx ;  
        }  
        if( y > distance )  
        {  
            y -= distance ;  
            StartY += incy ;  
        }  
    }  
}  
  
void LCD12864_drawDot(u8 x, u8 y,u8 flag)   //����,0���,1��ɫ,2��0  
{  //x(0-127),y(0-63),flag��3��ֵ,0����д1,1��ɫ,2��0  
    u8 x_word=0;         //ˮƽ(0-127)�������е��ĸ���,һ��16λ  
    u8 x_mode=0;         //ȡ��  
    u8 y_part=0;  
    u8 y_bit=0;  
    u8 tempH=0;  
    u8 tempL=0;  
    x_word=x>>4;      //����һ����(0-7)          ,x_word=x/16   
    x_mode=x&0x0f;      //�ڸ��ֵ���һλ         ,x_mode= x%16   
    y_part=y>>5;        //���ĸ���0��1           ,y_part=y/32   
    y_bit= y&0x1f;      //��ֱ����,y_bit��Χ(0-31),y_bit=y%32   
    bShowPicFlag?LCD12864_writeCmd(0x36):LCD12864_writeCmd(0x34);  
    LCD12864_writeCmd(0x80+y_bit);  //��ֱ����  
    LCD12864_writeCmd(0x80+8*y_part+x_word);           //ˮƽλַ  
    
    LCD12864_readByte();  
    tempH=LCD12864_readByte();  //�Ƚ�����16λ���ݱ���  
    tempL= LCD12864_readByte();  
      
    LCD12864_writeCmd(0x80+y_bit);                     //�����ַ,��ΪAC����������  
    LCD12864_writeCmd(0x80+8*y_part+x_word);           //ˮƽλַ  
    if(0==flag)                                     //������,��1,  
    {  
        if(x_mode<8)  //���x_modeС��8,˵����Ӧλ�ڸ��ֵ���߸�8λ��  
        {  
            LCD12864_writeByte( tempH | bit(7- x_mode) );  
            //LCD12864_writeByte(tempL);  
        }  
        else  
        {  
            //LCD12864_writeByte(tempH);  
            LCD12864_readByte();     //��AC�߰벽  
            LCD12864_writeByte(tempL|bit(15-x_mode));  
        }     
    }  
    else if(1==flag)            //����,�õ���ԭ����״̬�෴  
    {  
        if(x_mode<8)  //���x_modeС��8,˵����Ӧλ�ڸ��ֵ���߸�8λ��  
        {  
            if(tempH & bit(7- x_mode))       //ԭ����1  
            {  
                LCD12864_writeByte( tempH&~bit(7- x_mode) );    //д0  
            }  
            else                             //ԭ����0  
            {  
                LCD12864_writeByte( tempH | bit(7- x_mode) );   //д1  
            }  
              
        }  
        else  
        {  
            LCD12864_readByte();     //��AC�߰���  
            if(tempL& bit(15-x_mode))     //ԭ����1��д0  
            {  
                  
                LCD12864_writeByte(tempL&~bit(15-x_mode));   //д0  
            }  
            else  
            {  
                LCD12864_writeByte(tempL|bit(15-x_mode));    //д0  
            }  
              
        }  
    }  
    else if(2==flag)              //��0  
    {  
        if(x_mode<8)  //���x_modeС��8,˵����Ӧλ�ڸ��ֵ���߸�8λ��  
        {  
            LCD12864_writeByte( tempH&~bit(7- x_mode) );  
        }  
        else  
        {  
            LCD12864_readByte();     //��AC�߰���  
            LCD12864_writeByte(tempL&~bit(15-x_mode));  
}
    }     
    }    
}  
  
void LCD12864_showGDRAM(bool bShowImage)    //GDRAMͼ����ʾ����  
{  
    if(bShowImage)       //������ʾ  
    {  
        LCD12864_writeCmd(0x36);  
        LCD12864_writeCmd(0x30);          
    }  
    else                 //�ر���ʾ  
    {  
        LCD12864_writeCmd(0x34);  
        LCD12864_writeCmd(0x30);          
    }  
}  
  
  
//���GDRAM  
u8 LCD12864_drawGDRAM(u8 x,u8 y,u8 width,u8 height,u8* pImageCode,u8 imageWidth,u8 imageHight,bool bReverse)  
{//ǰ4����:��ʼ��x(0-7)λַ,y(0-63)����,Ҫ��ʾ�Ŀ��(1-128)�͸߶�(1-64)[����ʾ��ͼ�����Ͻǿ�ʼ�Ĳ�������]  
 //��4����:ͼ������ַ,ͼ����Ŀ��(1-128)�͸߶�(1-64), ����(true����,false������)  
    u8 i=0;  
    u8 j=0;  
    if( height > imageHight )       //�����ʾ�߶�,��Ȳ���ⲻ������  
    {                              //��ʾ�ĸ߶Ȳ��ܳ���ͼƬ����߶�  
        return 0x01;               //Ҳ����˵����ʾͼ��Ĳ�������(��ͼ�����Ͻǿ�ʼ�Ĳ�������)  
    }  
    width>>=3;                       //���ؿ��ת��Ϊ�ֽڸ���,����width������8��������  
    imageWidth>>=3;                  //���ؿ��ת��Ϊ�ֽڸ���,����width������8��������  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //��дGDRAMʱ,������ͼ��ʾ,�ɷ�ֹ������ʾʱ����          
    }  
    else  
    {  
        LCD12864_writeCmd(0x34);    //��дGDRAMʱ,�رջ�ͼ��ʾ  
    }  
  
    for(j=0;j
    {  
        if(y+j>31)                           //��ַ�任  
        {  
            LCD12864_writeCmd(0x80+y+j-32); //��ֱ����  
            LCD12864_writeCmd(0x88+x);      //ˮƽλַ  
        }  
        else  
        {  
            LCD12864_writeCmd(0x80+y+j);      
            LCD12864_writeCmd(0x80+x);  
        }  
        for(i=0;i
        {  
            LCD12864_writeByte(bReverse?~pImageCode[imageWidth*j+i]:pImageCode[imageWidth*j+i]);      
        }     
    }  
    LCD12864_writeCmd(0x30);  
    return 0x02;  
}  
  
  
void LCD12864_clearGDRAM()          //Һ���������Ļ�ͼGDRAM��0  
{      
    u8 j=0;  
    u8 i=0;  
    LCD12864_writeCmd(0x34);        //��չָ��  
    for(j=0;j<64;j++)            //��ֱ�����ַ�ֶ�����,��j=64ʱ������GDram  
    {                               //����ֻҪ���������GDRAM�Ϳ�����  
        LCD12864_writeCmd(0x80+j);  //y������  
        LCD12864_writeCmd(0x80);    //x������  
        for(i=0;i<32;i++)           //ˮƽ����λַ�Զ�����  
        {  
            LCD12864_writeByte(0x00);  
        }  
    }  
    LCD12864_writeCmd(0x30);  //�ص�����ָ��  
}       
  
  
/*--------------------------------CGRAM start----------------------------------------------*/  
void LCD12864_clearCGRAM(u8 CGRAM_groupNum)//���û��Զ��������CGRAM��0      
{   //����һ��CGRAM��4���û��ռ������(0~3) ,���������û��Զ���ͼ����ֵı���  
    u8 i,addr=0;      
    bShowPicFlag?LCD12864_writeCmd(0x36):LCD12864_writeCmd(0x34);//��չָ��,��ͼ���ر���                                
    LCD12864_writeCmd(0x02);        //SR����0,�������þ���ַ  
    LCD12864_writeCmd(0x30);        //�ָ�Ϊ8λ����,����ָ�  
    addr=(CGRAM_groupNum<<4)|0x40;    //��CGRAM�ռ��ת��Ϊ��Ӧ�洢��ַ  
    LCD12864_writeCmd(addr);        //��λ����λַ(�û��ռ�λַ��Χ0x40-0x7F��128�ֽ�)  
    for(i=0;i<16;i++)                //���û��Զ������д���16*16λԪ��ռ�  
    {  
        LCD12864_writeByte(0);      //����д2���ֽڹ�16λ  
        LCD12864_writeByte(0);  
    }      
}  
  
void LCD12864_writeScrollCGRAM(u8 CGRAM_groupNum, u8* pUserCode)//���û��Զ������д��CGRAM      
{   //����һ��CGRAM��4���û��ռ������(0~3) ,���������û��Զ���ͼ����ֵı���  
    u8 i,addr=0;  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //������ͼ��ʾ,���������Ŷ���   
		}  
    else  
    {  
        LCD12864_writeCmd(0x34);    //Ĭ�Ϲرջ�ͼ��ʾ  
    }                 
    LCD12864_writeCmd(0x02);        //SR����0,�������þ���ַ  
    LCD12864_writeCmd(0x30);        //�ָ�Ϊ8λ����,����ָ�  
    addr=(CGRAM_groupNum<<4)|0x40;    //��CGRAM�ռ��ת��Ϊ��Ӧ�洢��ַ  
    LCD12864_writeCmd(addr);        //��λ����λַ(�û��ռ�λַ��Χ0x40-0x7F��128�ֽ�)  
    for(i=0;i<16;i++)                //���û��Զ������д���16*16λԪ��ռ�  
    {  
        LCD12864_writeByte(pUserCode[i*2]);      //����д2���ֽڹ�16λ  
        LCD12864_writeByte(pUserCode[i*2+1]);  
    }      
}  
  
void LCD12864_writeCGRAM(u8 CGRAM_groupNum, u8* pUserCode)//���û��Զ������д��CGRAM    
{   //����һ��CGRAM��4���û��ռ������(0~3) ,���������û��Զ���ͼ����ֵı���  
    u8 i,addr=0;  
    if(bShowPicFlag)                  
    {  
        LCD12864_writeCmd(0x36);    //������ͼ��ʾ,���������Ŷ���          
    }  
    else  
    {  
        LCD12864_writeCmd(0x34);    //Ĭ�Ϲرջ�ͼ��ʾ  
    }                 
    LCD12864_writeCmd(0x02);        //SR����0,�������þ���ַ  
    LCD12864_writeCmd(0x30);        //�ָ�Ϊ8λ����,����ָ�  
    addr=(CGRAM_groupNum<<4)|0x40;    //��CGRAM�ռ��ת��Ϊ��Ӧ�洢��ַ  
    LCD12864_writeCmd(addr);        //��λ����λַ(�û��ռ�λַ��Χ0x40-0x7F��128�ֽ�)  
    for(i=0;i<16;i++)                //���û��Զ������д���16*16λԪ��ռ�  
    {  
        LCD12864_writeByte(pUserCode[i*2]);      //����д2���ֽڹ�16λ  
        LCD12864_writeByte(pUserCode[i*2+1]);  
    }      
}  
  
void LCD12864_showScrollCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum)//����CGRAM  
{   //row(0-3), cols(0-15)  
    //�������������û��ռ����(0~3��4��ռ����),�ú����2����������Ӧ��[�����û��ռ����]  
    LCD12864_setScrollPos(row,cols);  
    LCD12864_writeByte(0x00);//4���û��ռ�ı���ĸ��ֽڶ��̶�Ϊ0,�Ҳ�����Ϊ��E��ASCII�����ֿ�  
    LCD12864_writeByte(CGRAM_groupNum*2);   //��Ӧ����00h,02h,04h,06h  
    LCD12864_showCGRAM(row,cols,CGRAM_groupNum);  
}  
  
void LCD12864_showCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum)//��λҺ�����,����ʾ�Զ�������  
{   //row(0-3), cols(0-15)  
    //�������������û��ռ����(0~3��4��ռ����),�ú����2����������Ӧ��[�����û��ռ����]  
    LCD12864_setPos(row,cols);  
    LCD12864_writeByte(0x00);//4���û��ռ�ı���ĸ��ֽڶ��̶�Ϊ0,�Ҳ�����Ϊ��E��ASCII�����ֿ�  
    LCD12864_writeByte(CGRAM_groupNum*2);   //��Ӧ����00h,02h,04h,06h  
}  
/*--------------------------------CGRAM end----------------------------------------------*/  
  
/*--------------------------------DDRAM start----------------------------------------------*/  
void LCD12864_earseSomeDDRam(u8 row,u8 cols,u8 dataSize) //����N���ֽ�DDRam  
{   //row(0-3),cols(0-15),�����ʼ��ַ�Ǻ��ֵĵ��ֽ�,���һͬ�������ֵĸ��ֽ�  
    LCD12864_setPos(row, cols);                //��λ                              
    if(cols%2!=0)                              //����������п�ʼ  
    {  
        LCD12864_readByte();                   //�ն�һ��,��λַָ���ƶ�����  
        if(LCD12864_readByte()>127)             //����λ�Ƿ��Ǻ�����  
        {  
            LCD12864_setPos(row, cols);        //�Ǻ�����Ļ�Ҫ����,��ȻҪ����  
            LCD12864_writeByte(' ');           //��ʵ��д�ո�,�������˾͵��ڲ�����  
        }                                      //����д2��0�Ļ�������  
    }     
    while(dataSize--)                          //����  
    {  
        if(cols)                               //cols>0  
        {  
            if(0==cols%16)                     //���һ������  
            {  
                row++;                         //׼��������Ƶ���һ��  
                cols=0;                        //��������������  
                LCD12864_setPos(row, cols);    //�����¹��  
            }                 
        }  
        LCD12864_writeByte(' ');               //��ʵ��д�ո�,��Ϊɶ��д0��  
cols++; //��Ϊ0����CGRAM������,д2��0����
 cols++;                                //��Ϊ0����CGRAM������,д2��0�������  
    }  
      
}  
  
  
/***************************************************************************************** 
pBuf������������ַ���,dataSize=strlen(pBuf); 
pBuf�����һ���ַ�����,dataSize=sizeof(pBuf); 
strlen()��ȻҲ�������������ַ����鳤��,������'\0'ʱ�ͻ᷵��,�����ټ������������ַ� 
��VC��strlen()ֻ�ܼ����ַ�������,���ܼ����ַ�����,���������� 
sizeof("���5"),sizeof("���56"),����Һ�����λ����һ����,�ʲ�Ҫ��sizeof�����ַ��� 
*****************************************************************************************/  
void LCD12864_writeData(u8 row,u8 cols,u8* pBuf,u8 dataSize)//д����  
{   //֧��ȫ�ǰ���ַ�����Ӣ��ϵ��ַ���,Ҳ��д���ַ������Ӵ�,(������0~3,������0~15)  
    u8 flag=0;                                  //Һ�����ֽ�ram���ݼ���־,0�����  
    LCD12864_setPos(row, cols);                 //���ù��      
    if(cols%2!=0)                               //�кŲ�Ϊż��(������Һ����Ҫż����)  
    {   //Ҫ��λַ����һ���ֽ�,ִ����������������,Ч���Ǵﵽ��  
        LCD12864_readByte();//��ACֵû��,�һ��ɳ������AC����ָ��,����һ����־λû����)  
        flag=1;                                 //��ʱ��Ҫ���Һ����λ�ֽ�ram     
    }                                           //��Ϊ��λ�ֽ����ڿ����Ǻ�����  
  
    while(dataSize--)                           //ѭ������Ŀ���ֽ���  
    {                                             
        if(0==cols%2)                           //ż����ʱ,����ram���ֽ�  
        {  
            if(*pBuf>127)                        //���д��ram�ĸ��ֽ��Ǻ�����  
            {  
                flag=0;                         //��һ�β�Ҫ�����ֽ�,��Ϊ�϶��Ǻ�����  
            }  
            else                                //������ֽ��ǰ���ַ�  
            {  
                flag=1;                         //���ڵ��ֽ�ramд�뺺�־�������,�ʼ��  
            }                 
        }  
  
        if(cols%2!=0)                           //����Һ�����ֽ�  
        {  
            if(flag)                            //���Ҫ�����ֽ�  
            {  
                if(*pBuf>127)                    //������ֽ��Ǻ�����  
                {  
                    LCD12864_writeByte(0x20);   //����һ���ո�  
                    cols++;                     //�ֽڼ�����++  
                    flag=0;                     //�����־  
                }                     
            }     
        }        
          
        if(cols)                                //��β���  
        {  
            if(0==cols%16)                      //���һ������  
            {  
                row++;                          //׼��������Ƶ���һ��  
                cols=0;                         //��������������  
                LCD12864_setPos(row, cols);     //������λַ  
            }                 
        }   
  
        LCD12864_writeByte(*pBuf++);            //���ڿ���д������  
cols++;
 cols++;                                 //�к��ۼ�  
    }  
}  
  
  
//����ģʽ��д���ݺ���  
void LCD12864_writeScrollData(u8 row,u8 cols,u8* pBuf,u8 dataSize)//д����,��ģʽ  
{   //֧��ȫ�ǰ���ַ�����Ӣ��ϵ��ַ���,Ҳ��д���ַ������Ӵ�,(������0~3,������0~15)  
    u8 flag=0;                                  //Һ�����ֽ�ram���ݼ���־,0�����  
    LCD12864_writeData(row,cols,pBuf,dataSize);  
    LCD12864_setScrollPos(row, cols);                   //���ù��      
    if(cols%2!=0)                               //�кŲ�Ϊż��(������Һ����Ҫż����)  
    {   //Ҫ��λַ����һ���ֽ�,ִ����������������,Ч���Ǵﵽ��  
        LCD12864_readByte();//��ACֵû��,�һ��ɳ������AC����ָ��,����һ����־λû����)  
        flag=1;                                 //��ʱ��Ҫ���Һ����λ�ֽ�ram     
    }                                           //��Ϊ��λ�ֽ����ڿ����Ǻ�����  
  
    while(dataSize--)                           //ѭ������Ŀ���ֽ���  
    {                                             
        if(0==cols%2)                           //ż����ʱ,����ram���ֽ�  
        {  
            if(*pBuf>127)                        //���д��ram�ĸ��ֽ��Ǻ�����  
            {  
                flag=0;                         //��һ�β�Ҫ�����ֽ�,��Ϊ�϶��Ǻ�����  
            }  
            else                                //������ֽ��ǰ���ַ�  
            {  
                flag=1;                         //���ڵ��ֽ�ramд�뺺�־�������,�ʼ��  
            }                 
        }  
  
        if(cols%2!=0)                           //����Һ�����ֽ�  
        {  
            if(flag)                            //���Ҫ�����ֽ�  
            {  
                if(*pBuf>127)                    //������ֽ��Ǻ�����  
                {  
                    LCD12864_writeByte(0x20);   //����һ���ո�  
                    cols++;                     //�ֽڼ�����++  
                    flag=0;                     //�����־  
                }                     
            }     
        }        
          
        if(cols)                                //��β���  
        {  
            if(0==cols%16)                      //���һ������  
            {  
                row++;                          //׼��������Ƶ���һ��  
                cols=0;                         //��������������  
                LCD12864_setScrollPos(row, cols);       //������λַ  
            }                 
        }   
  
        LCD12864_writeByte(*pBuf++);            //���ڿ���д������  
        cols++;                                 //�к��ۼ�  
    }  
}  
  
void  LCD12864_startScroll(u8 scrollNum,u16 delay_ms)  //����  
{   //scrollNum����ֵΪ64  
    u8 i;  
LCD12864_writeCmd(0x34);
 LCD12864_writeCmd(0x34);      
    LCD12864_writeCmd(0x03);  
    for(i=0x40;i<0x40+scrollNum;i++)   
    {    
        LCD12864_writeCmd(i); //���þ���ַ  
        delayms(delay_ms);         //ʵ��ʹ��ʱ�����ö�ʱ������  
    }  
    LCD12864_writeCmd(0x40);  //����һ��  
    LCD12864_writeCmd(0x30);  
}  
  
void LCD12864_setScrollPos(u8 row, u8 cols)     //���ù��λ�� ,��ģʽ  
{                                               //row������0~3  
    u8 newPos=0;                                //cols������0~15  
    switch(row)  
    {  
        case 0:  
        {  
            row=0xa8;     
        }  
        break;  
        case 1:  
        {  
            row=0xb8;  
        }  
        break;  
        case 2:  
        {  
            row=0xa0;  
        }  
        break;  
        case 3:  
        {  
            row=0xb0;  
        }  
        break;  
        default:        //�����Ҫ��������귶Χ,��������Ӵ���  
        break;            
    }  
    newPos=row+cols/2;  //Һ��дָ������ֻ��8��,�ҵĺ�������������16����,֧�ְ��ȫ�ǻ��  
    LCD12864_writeCmd(newPos);  
}  
  
  
void LCD12864_setPos(u8 row, u8 cols)           //���ù��λ��  
{                                               //row������0~3  
    u8 newPos=0;                                //cols������0~15  
    switch(row)  
    {  
        case 0:  
        {  
            row=0x80;     
        }  
        break;  
        case 1:  
        {  
            row=0x90;  
        }  
        break;  
        case 2:  
        {  
            row=0x88;  
        }  
        break;  
        case 3:  
        {  
            row=0x98;  
        }  
        break;  
        case 4:  
        {  
            row=0xa0;  
        }  
        break;  
        case 5:  
        {  
            row=0xb0;  
        }  
        break;  
        case 6:  
        {  
            row=0xa8;  
        }  
        break;  
        case 7:  
        {  
            row=0xb8;  
        }  
        break;  
  
        default:        //�����Ҫ��������귶Χ,��������Ӵ���  
        break;            
    }  
    newPos=row+cols/2;  //Һ��дָ������ֻ��8��,�ҵĺ�������������16����,֧�ְ��ȫ�ǻ��  
    LCD12864_writeCmd(newPos);  
}  
/* 
void LCD12864_setPos(u8 row, u8 cols)           //���ù��λ�� 
{                                               //row������0~3 
    u8 newPos=0;                                //cols������0~15 
    switch(row) 
    { 
        case 0: 
        { 
            row=0x80;    
        } 
        break; 
        case 1: 
        { 
            row=0x90; 
        } 
        break; 
        case 2: 
        { 
            row=0x88; 
        } 
        break; 
        case 3: 
        { 
            row=0x98; 
        } 
        break; 
default: //�����Ҫ��������귶
  default:        //�����Ҫ��������귶Χ,��������Ӵ��� 
        break;           
    } 
    newPos=row+cols/2;  //Һ��дָ������ֻ��8��,�ҵĺ�������������16����,֧�ְ��ȫ�ǻ�� 
    LCD12864_writeCmd(newPos); 
} 
    */  
  
  
  
void LCD12864_init()                  //��ʼ��  
{  
    delayms(40);                      //rst�ɵ͵��ߺ󱣳�40ms����,���ǵ�rst��VCC  
    LCD_PSB= 1;                       //ѡ�񲢿ڷ�ʽ  
  
    LCD12864_writeCmd( B(110000) );   //0x30,���û���ָ�  
    delayXus(15);                     //Ҫ����ʱ100us����,(8+6x)*1.085=106us  
  
    LCD12864_writeCmd( B(110000) );   //0x30,Ҫ��д2�θ�ָ��  
    delayXus(5);                      //Ҫ����ʱ37us����,(8+6x)*1.085=41us  
  
    LCD12864_writeCmd( B(1100) );     //0x0f,������ʾ,�α�,�α귴��  
    delayXus(15);                     //Ҫ����ʱ100us����  
  
    LCD12864_writeCmd( B(0001) );     //0x01,����ָ��,����Ļд���ո�  
    delayms(10);                      //Ҫ����ʱ10ms����  
  
    LCD12864_writeCmd( B(110) );      //0x06,����ģʽ����,�α��Զ�ָ����һλ��,  
                                                  
    delayms(5);                       //�ֲ���û˵����Ҫ��ʱ,��,���Ǽ��ϰ�  
}  
  
  
void LCD12864_writeCmd(u8 cmd)        //дָ��  
{  
    while(LCD12864_isBusy());  
    LCD_EN=0;                         //ʹ�� ����  
    LCD_RW=0;                         //д  
    LCD_RS=0;_nop_();                 //����  
          
    LCD_EN=1;                         //ʹ��  
    LCD_dataBus=cmd;                  //��ָ��  
    _nop_();_nop_();                  //�ȶ�  
  
    LCD_EN=0;_nop_();                 //ȡ��  
}  
  
void LCD12864_writeByte(u8 dat)       //дһ���ֽ�  
{  
    while(LCD12864_isBusy());  
    LCD_EN=0;                //ʹ��������  
    LCD_RW=0;                //д  
    LCD_RS=1;_nop_();        //����  
      
    LCD_EN=1;  
    LCD_dataBus=dat;  
    _nop_();_nop_();         //��ʱ����1.5us  
  
    LCD_EN=0;_nop_();        //�½���ȡ������  
}  
  
u8 LCD12864_readByte()       //�������ݴ���Data Register  
{                            //�õ�ʱ��Ҫ�ղ���һ��  
    u8 temp=0;  
    while(LCD12864_isBusy());//æ���  
    LCD_dataBus=0xff;        //�����߶�����ʱ��������Ϊ����ģʽ  
    LCD_EN=0;                //ʹ��������  
    LCD_RW=1;                //��  
    LCD_RS=1;_nop_();        //����                      
    LCD_EN=1;_nop_();        //ʹ��  
    temp=LCD_dataBus;        //ȡ������  
      
    _nop_();  
    LCD_EN=0;                //ʹ�ָܻ�  
    return temp;  
}  
  
bool LCD12864_isBusy()       //���Һ���Ƿ�æ  
{  
    if(LCD12864_readIR() & 0x80) //���BFλ  
    {  
        return TRUE;         //æ  
    }  
    return FALSE;            //��æ  
}  
  
u8 LCD12864_readIR()         //��ָ���ݴ���Instruction Register  
{  
    u8 temp=0;  
    LCD_EN=0;                //ʹ��׼��  
    LCD_RW=1;                //��  
    LCD_RS=0;_nop_();        //������  
    LCD_dataBus=0xff;        //׼������  
    LCD_EN=1;_nop_();        //ʹ��  
    temp=LCD_dataBus;        //��ȡ����  
  
    _nop_();  
    LCD_EN=0;                //ʹ������  
    return temp;                
}  

//���Ը��´���