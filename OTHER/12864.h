#define LCD_dataBus  P0    //����  
sbit LCD_EN = P3^4;        //ʹ�ܿ���  
sbit LCD_RS = P3^5;        //����_����ѡ���  
sbit LCD_RW = P3^6;        //��д����  
sbit LCD_PSB= P3^7;        //����ѡ��,H����,L����  
  
  
extern bool bShowPicFlag;  //��ͼʱͼ����ʾ����(������GDRAM)  
  
/*************************�������ܺ���*********************************************/  
extern void LCD12864_init();                    //��ʼ��,�����ö�����  
extern void LCD12864_setPos(u8 row, u8 cols);   //���ù��λ��  
extern void LCD12864_writeByte(u8 dat);         //дһ���ֽ�  
extern void LCD12864_writeCmd(u8 cmd);          //дָ��  
extern   u8 LCD12864_readByte();                //��һ���ֽ�ram  
extern   u8 LCD12864_readIR();                  //���ݴ���  
extern bool LCD12864_isBusy();                  //��æ  
  
/*************************���û����ֿ���ʾ����**************************************/   
//����֧��ȫ�ǰ���ַ�����Ӣ��ϵ��ַ���,���ַ������Ӵ�,��ʼ�к�row(0-3)��������cols(0-15),д����ĻΪֹ  
//�к�4-7���ǹ�����  
extern void LCD12864_writeData(u8 row, u8 cols,u8* pBuf,u8 dataSize);//дһ������  
extern void LCD12864_earseSomeDDRam(u8 row,u8 cols,u8 dataSize);    //����N�ֽ�DDRam  
  
/*************************�û��Զ���ͼ������****************************************/  
extern void LCD12864_writeCGRAM(u8 userRamNum,u8* pCGRAM_userCode); //д�Զ���ͼ������  
extern void LCD12864_showCGRAM(u8 row,u8 cols,u8 num) ; //��ʾ�Զ���ͼ������,row(0-3),cols(0-15)  
extern void LCD12864_clearCGRAM(u8 CGRAM_groupNum) ;    //CGRAM����(��ʼ��Ҳ����0)  
  
/*************************ͼ����ʾ���ܺ���**********************************************/  
extern void LCD12864_showGDRAM(bool bShowImage);     //GDRAM��ͼ��ʾ����  
extern void LCD12864_clearGDRAM();                   //Һ��������������GDRAM������0  
//ǰ4����:��ʼ��x(0-7)λַ,y(0-63)����,Ҫ��ʾ�Ŀ��(1-128)�͸߶�(1-64)[����ʾ��ͼ�����Ͻǿ�ʼ�Ĳ�������]  
//��4����:ͼ������ַ,ͼ����Ŀ��(1-128)�͸߶�(1-64), ����(true����,false������)  
//��ͼ���GDRAM ,ע:��ʾ���������ͼ�����ȱ�����8�ı���  
extern u8 LCD12864_drawGDRAM(u8 x,u8 y,u8 width,u8 height,u8 *pImageCode,u8 imageWidth,u8 imageHight,bool bReverse);  
extern void LCD12864_drawDot(u8 x,u8 y,u8 flag);        //���,x(0-127),y(0-63),flag(0����,1����,2��0)  
extern bool LCD12864_drawXYLine(u8 x1, u8 y1,u8 x2, u8 y2,u8 flag);       //��ˮƽ��ֱֱ��  
extern void LCD12864_drawAnyLine(u8 x1, u8 y1,u8 x2, u8 y2,u8 flag) ;     //������ֱ��  
extern void LCD12864_drawRectangle(u8 x,u8 y ,u8 width,u8 height,u8 flag);//������  
extern void LCD12864_drawFillRect(u8 x,u8 y, u8 width,u8 hight,u8 flag);  //������,�ɶԾ��������׻���0  
extern void LCD12864_drawVerticalSquare(u8 x,u8 y,u8 r,u8 flag) ;         //��վ����������  
extern void LCD12864_drawCircle(u8 x0,u8 y0,u8 r,u8 flag);                //��Բ  
  
//��㷨ȫ����ͼ�е�����,��㷨���׾�����������,������η�ΧСһЩ,��Ȼ�Ƚ���  
//��㷨Ч�����,��Ϊ���ֵľ������Ƚ�С,�ٶȺܿ�  
//������ͼ����������Ч�ʸ�,flash�ռ��ԣ�Ľ����û�ͼ��  
  
/***************************ȫ������*******************************************/  
//��Ҫ����ʱ,��LCD12864_writeScrollData()����,������LCD12864_writeData()һ��  
extern void LCD12864_writeScrollData(u8 row,u8 cols,u8* pBuf,u8 dataSize);//д���� (����ģʽ)  
extern void LCD12864_setScrollPos(u8 row, u8 cols);     //���ù���ģʽ������  
extern void LCD12864_showScrollCGRAM(u8 row,u8 cols,u8 CGRAM_groupNum);//����CGRAM������ʾǰִ��  
extern void LCD12864_startScroll(u8 scrollNum,u16 delay_ms);  //������ʼ  