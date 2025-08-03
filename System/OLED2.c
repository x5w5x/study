#include"stm32f10x.h"
#include"OLED_Font.h"
#include"Delay.h"
/*��������*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))


uint8_t OLED_GRAM[8][128];//��������







/*���ų�ʼ��*/
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C��ʼ
  * @param  ��
  * @retval ��
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2Cֹͣ
  * @param  ��
  * @retval ��
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C����һ���ֽ�
  * @param  Byte Ҫ���͵�һ���ֽ�
  * @retval ��
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(!!(Byte & (0x80 >> i)));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//�����һ��ʱ�ӣ�������Ӧ���ź�
	OLED_W_SCL(0);
}



void OLED_WriteCommand(uint8_t cmd)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);
	OLED_I2C_SendByte(0x00);
	OLED_I2C_SendByte(cmd);
	OLED_I2C_Stop();
}

void OLED_WriteData(uint8_t data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);
	OLED_I2C_SendByte(0x40);
	OLED_I2C_SendByte(data);
	OLED_I2C_Stop();
}

void OLED_SetCursor(uint8_t x, uint8_t y)
{
    OLED_WriteCommand(0x00|(x&0x0F));		//�����е�ַ
    OLED_WriteCommand(0x10|((x&0xF0)>>4));		//�����е�ַ
    OLED_WriteCommand(0xB0+y);		//����ҳ��ַ
}

void OLED_Clear(void)
{
    uint8_t i,j;
    for(i=0;i<8;i++)
    {
        OLED_SetCursor(0,i);
        for(j=0;j<128;j++)
        {
            OLED_WriteData(0x00);
        }
    }
}

void OLED_On(void)
{
    uint8_t i,j;
    for(i=0;i<8;i++)
    {
        OLED_SetCursor(0,i);
        for(j=0;j<128;j++)
        {
            OLED_WriteData(0xFF);
			
        }
    }
}
void OLED_Init(void)
{
	OLED_I2C_Init();
    Delay_ms(100);
	OLED_WriteCommand(0xAE);	//�ر���ʾ
	
	OLED_WriteCommand(0xD5);	//������ʾʱ�ӷ�Ƶ��/����Ƶ��
	// OLED_WriteCommand(0x80);//Ĭ��ˢ��Ƶ��

	OLED_WriteCommand(0xE0);//�Զ���ˢ��Ƶ��
	
	OLED_WriteCommand(0xA8);	//���ö�·������
	OLED_WriteCommand(0x3F);

	
	OLED_WriteCommand(0xD3);	//������ʾƫ��
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//������ʾ��ʼ��
	
	OLED_WriteCommand(0xA1);	//�������ҷ���0xA1���� 0xA0���ҷ���
	
	OLED_WriteCommand(0xC8);	//�������·���0xC8���� 0xC0���·���

	OLED_WriteCommand(0xDA);	//����COM����Ӳ������
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//���öԱȶȿ���
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//����Ԥ�������
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//����VCOMHȡ��ѡ�񼶱�
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//����������ʾ��/�ر�

	OLED_WriteCommand(0xA6);	//��������/��ת��ʾ

	OLED_WriteCommand(0x8D);	//���ó���
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//������ʾ

	OLED_Clear();
		
	Delay_ms(100);

}


void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t size)
{
	if(size==6)
	{
    OLED_SetCursor(x,y);
	for(int8_t i=0;i<6;i++)
	{
		OLED_WriteData(OLED_F6x8[chr-' '][i]);
	}
	}

	else if(size==8)
	{
    OLED_SetCursor(x,y);
	for(int8_t i=0;i<8;i++)
	{
		OLED_WriteData(OLED_F8x16[chr-32][i]);
	}
	OLED_SetCursor(x,y+1);
	for(int8_t i=0;i<8;i++)
	{
		OLED_WriteData(OLED_F8x16[chr-32][i+8]);
	}

	}
}


void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *str, uint8_t size)
{
	while(*str != '\0')
	{
		OLED_ShowChar(x+=(size==6?6:8), y, *(str++), size);
	}
}



void OLED_ShowImage(uint8_t x, uint8_t y, uint8_t width, uint8_t height,const uint8_t *Image)
{
   for(uint8_t j=0;j<height;j++)
    {
        OLED_SetCursor(x,y+j);
        for(uint8_t i=0;i<width;i++)
        {
            OLED_WriteData(Image[i+j*width]);
        }
    }
}

// void OLED_ShowChinese(uint8_t x, uint8_t y, uint8_t *str)
// {
//     char SingleChinese[4]={0};
// 	uint8_t pChinese=0;
// 	while(*str != '\0')
// 	{
// 		pChinese=*str++;
// 		SingleChinese[0]=pChinese;
// 		SingleChinese[1]=*(str++);
// 		SingleChinese[2]=*(str++);
// 		SingleChinese[3]=*(str++);
// 		OLED_SetCursor(x,y);
// 		for(int8_t i=0;i<16;i++)
// 		{
// 			OLED_WriteData(OLED_F16x16[SingleChinese[0]-0x80][i]);
// 		}
// 	}
// }


void OLED_UpdateGRAM(void)
{
    uint8_t i,j;
    for(i=0;i<8;i++)
    {
        OLED_SetCursor(0,i);
        for(j=0;j<128;j++)
        {
            OLED_WriteData(OLED_GRAM[i][j]);
        }
    }
}


void OLED_GRAM_Fill(void)
{
    for(uint8_t i=0;i<8;i++)
{
	for(uint8_t  j=0;j<128;j++)
	{
		OLED_GRAM[i][j]=0xFF;
	}
}
}


void OLED_GRAM_Clear(void)
{
    for(uint8_t i=0;i<8;i++)
{
	for(uint8_t j=0;j<128;j++)
	{
		OLED_GRAM[i][j]=0x00;
	}
}
}
//����
void OLED_DrawPoint(uint8_t x, uint8_t y)
{
	OLED_GRAM[y/8][x]=OLED_GRAM[y/8][x]|(0x01<<(y%8));

}
//���
void OLED_ClearPoint(uint8_t x, uint8_t y)
{
	OLED_GRAM[y/8][x]=OLED_GRAM[y/8][x]&(~(0x01<<(y%8)));
}




void FourPoint(uint8_t x,uint8_t y)
{
	for(uint8_t i=y;i<64;i+=2)
	{
	    for(uint8_t j=x;j<128;j+=2)
		{
			OLED_GRAM[i/8][j]|=(0x01<<(i%8));
		}
	}
}



void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t dot)
{
    uint8_t lx=x2>x1?x2-x1:x1-x2;
    uint8_t ly=y2>y1?y2-y1:y1-y2;
	uint8_t dm,i;
	float dx,dy,x,y;
	dm=lx>ly?lx:ly;

	dx=(float)(x2-x1)/dm;
	dy=(float)(y2-y1)/dm;
	x=(float)x1+0.5;
	y=(float)y1+0.5;
	for(i=0;i<dm;i++)
	{
	if(!(i%dot))
		OLED_DrawPoint((uint8_t)x,(uint8_t)y);
		x+=dx;
		y+=dy;
	}
}


void OLED_ClearLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t dot)
{
    uint8_t lx=x2>x1?x2-x1:x1-x2;
    uint8_t ly=y2>y1?y2-y1:y1-y2;
	uint8_t dm,i;
	float dx,dy,x,y;
	dm=lx>ly?lx:ly;

	dx=(float)(x2-x1)/dm;
	dy=(float)(y2-y1)/dm;
	x=(float)x1+0.5;
	y=(float)y1+0.5;
	for(i=0;i<dm;i++)
	{
	if(!(i%dot))
		OLED_ClearPoint((uint8_t)x,(uint8_t)y);
		x+=dx;
		y+=dy;
	}
}

void OLED_DrawRect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	OLED_DrawLine(x1,y1,x2,y1,1);
	OLED_DrawLine(x2,y1,x2,y2,1);
	OLED_DrawLine(x2,y2,x1,y2,1);
	OLED_DrawLine(x1,y2,x1,y1,1);
	
}
//��ʵ�ľ���
void OLED_DrawBlock(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	
	uint8_t d=y2>y1?1:-1;
	for(uint8_t i=0;i<(y2>y1?y2-y1:y1-y2);i++)
	{
		OLED_DrawLine(x1,y1+i*d,x2,y1+i*d,1);
	}
}

uint8_t ADCdata[128]
= {
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    
    // P ����21-30�����ķ�ȥ����
    135, 140, 145, 150, 145, 140, 135, 130, 128, 128,
    
    // PR �Σ�31-40��
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    
    // QRS ��Ⱥ��41-60��������ȥ����
    120, 110, 100, 90, 80, 70, 60, 70, 90, 110,
    130, 150, 170, 190, 200, 190, 170, 150, 130, 110,
    
    // ST �Σ�61-80��
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    
    // T ����81-100�������Ҹ�����
    140, 145, 150, 155, 160, 155, 150, 145, 140, 135,
    130, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    
    // ��һ�����ڣ�101-128��
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
    128, 128, 128, 128, 128, 128, 128, 128
};
void OLED_ADCWaveLine(uint8_t step)
{
    uint8_t Pointx,Pointy,Range=63,PointXlast,PointYlast;
	float Scale=(float)Range/255;
	for(uint8_t i=0;i<128;i+=step)
	{
		PointXlast=Pointx;
		PointYlast=Pointy;
		Pointx=i;
		Pointy=ADCdata[i]*Scale;
		OLED_DrawLine(PointXlast,63-PointYlast,Pointx,63-Pointy,1);
		// Pointx=i;
		// Pointy=ADCdata[i]*Scale;
		// OLED_DrawPoint(Pointx,63-Pointy);
	}
}




void OLED_ADCWavePoint(uint8_t step)
{
    uint8_t Pointx,Pointy,Range=63;
	float Scale=(float)Range/255;
	for(uint8_t i=0;i<128;i+=step)
	{
		
		Pointx=i;
		Pointy=ADCdata[i]*Scale;
		OLED_DrawPoint(Pointx,63-Pointy);
	}
}

// uint8_t WaveData[128];
// void ButtonWave(void)
// {
   
// 	for(uint8_t i=127;i>0;i--)
// 	WaveData[i]=WaveData[i-1];
// 	if(Key_GetNum()==1)
// 	WaveData[0]=60;
// 	else
// 	WaveData[0]=10;
// 	OLED_GRAM_Clear();

// 	for(uint8_t i=0;i<127;i++)
	
// 		OLED_DrawLine(i,63-WaveData[i],i+1,63-WaveData[i+1],1);
		
	
// 	OLED_UpdateGRAM();Delay_ms(50);

// }

#include"math.h"
void OLED_DrawSin( uint8_t x0,uint8_t y0)
{

	float Si,Sx,Sy,Rad;
	for(Si=-180;Si<180;Si+=0.5)
	{
	    Rad=Si*3.14/180;
		Sx=Si/3.5;
		Sy=25*sin(Rad);
		OLED_DrawPoint((uint8_t)(x0+Sx),64-(uint8_t)(y0+Sy));
		// OLED_UpdateGRAM();

	
	}
}

void OLED_DrawCircle(uint8_t x0,uint8_t y0,uint8_t r)
{
	float Rx,Ry,angle,Rad;
	OLED_DrawPoint(x0,y0);
	for(angle=0;angle<359;angle+=1)
	{
		Rad=angle*3.14/180;
		Rx=r*cos(Rad);
		Ry=r*sin(Rad);
		OLED_DrawPoint((uint8_t)(x0+Rx),64-(uint8_t)y0+Ry);
	}
    
}