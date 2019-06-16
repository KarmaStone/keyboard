#include "bsp_iic.h"

/* ����I2C�������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����4�д��뼴������ı�SCL��SDA������ */

#define RCC_I2C_PORT 	RCC_APB2Periph_GPIOC		/* GPIO�˿�ʱ�� */

#define PORT_I2C_SCL	GPIOC			/* GPIO�˿� */
#define PIN_I2C_SCL		GPIO_PIN_9		/* GPIO���� */

#define PORT_I2C_SDA	GPIOC			/* GPIO�˿� */
#define PIN_I2C_SDA		GPIO_PIN_8		/* GPIO���� */

#define I2C_SCL_PIN		GPIO_PIN_9			/* ���ӵ�SCLʱ���ߵ�GPIO */
#define I2C_SDA_PIN		GPIO_PIN_8			/* ���ӵ�SDA�����ߵ�GPIO */



/*
*********************************************************************************************************
*	�� �� ��: bsp_InitI2C
*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/

GPIO_InitTypeDef GPIO_Initure;

void bsp_InitI2C(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();           //����GPIOBʱ��
	
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;       //�������
    GPIO_Initure.Pull=GPIO_PULLUP;               //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;     //����
	
    GPIO_Initure.Pin=PIN_I2C_SCL;  
    HAL_GPIO_Init(PORT_I2C_SCL,&GPIO_Initure);
	
	GPIO_Initure.Pin=PIN_I2C_SDA;  
    HAL_GPIO_Init(PORT_I2C_SDA,&GPIO_Initure);
	
    HAL_GPIO_WritePin(PORT_I2C_SCL,PIN_I2C_SCL,GPIO_PIN_SET);
    HAL_GPIO_WritePin(PORT_I2C_SDA,PIN_I2C_SDA,GPIO_PIN_SET);
	
}


#define SCL_PIN		PIN_I2C_SCL	
#define SDA_PIN		PIN_I2C_SDA
#define I2C_GPIO	PORT_I2C_SCL

#define SCL_H()				I2C_GPIO->BSRR = SCL_PIN; 	/*PB6 = 1  */
#define SCL_L()				I2C_GPIO->BRR  = SCL_PIN;  /*PB6 = 0  */

#define SDA_H()				I2C_GPIO->BSRR = SDA_PIN; 	/*PB7 = 1  */
#define SDA_L()				I2C_GPIO->BRR  = SDA_PIN;  /*PB7 = 0  */

#define I2CERR_OK       0       /* No error */
#define I2CERR_NAK      1       /* No ACK from slave */
#define I2CERR_LOST     2       /* Arbitration lost */
#define I2CERR_BUS      3       /* Bus is stuck (not used yet) */
#define I2CERR_TIMEOUT  4       /* Timeout on bus */

#define I2C_CLK_Streching		
#define Streching_Delay		0x3FF
uint16_t I2C_CLK_Streching_Cnt = Streching_Delay ;

unsigned char i2c_error = 0; 	/* Last error */

/*
*********************************************************************************************************
*	�� �� ��: i2c_delay1
*	����˵��: ��ʱ
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_delay(void)
{
	uint16_t i = 0;
	while(i<600)
	{
		i++;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: I2C_SDA_IN1
*	����˵��: GPIO��ʼ��������GPIO��ʼ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void I2C_SCL_OUT(void)
{
	
	GPIO_Initure.Pin=PIN_I2C_SCL;  
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;                     
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;     
    HAL_GPIO_Init(PORT_I2C_SCL,&GPIO_Initure);
}
/*
*********************************************************************************************************
*	�� �� ��: I2C_SDA_IN1
*	����˵��: GPIO��ʼ��������GPIO��ʼ����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void I2C_SDA_OUT(void)
{
	
	GPIO_Initure.Pin=PIN_I2C_SDA;  
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_OD;                     
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;     
    HAL_GPIO_Init(PORT_I2C_SDA,&GPIO_Initure);
}
/*
*********************************************************************************************************
*	�� �� ��: SDA_IN1
*	����˵��: ���ݸߵ͵�ƽ���������ݣ�
*	��    �Σ���
*	�� �� ֵ: 0��1
*********************************************************************************************************
*/
unsigned char SDA_IN(void)
{
	 if (0x00 == HAL_GPIO_ReadPin(I2C_GPIO, SDA_PIN) )
	 {
	    return 0;
	 }
	 else
	 {
	 	return 1;
	 }
}
/*
*********************************************************************************************************
*	�� �� ��: SCL_IN1
*	����˵��: ʱ�Ӹߵ͵�ƽ������ʱ�ӣ�
*	��    �Σ���
*	�� �� ֵ: 0��1
*********************************************************************************************************
*/
unsigned char SCL_IN(void)
{
	if (0x00 == HAL_GPIO_ReadPin(I2C_GPIO, SCL_PIN) )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
/*
*********************************************************************************************************
*	�� �� ��: SDA_OUT1
*	����˵��: ���һ���ߵ͵�ƽ���������λ��
*	��    �Σ���
*	�� �� ֵ: �ߵ͵�ƽ
*********************************************************************************************************
*/
void SDA_OUT(unsigned char b)
{
	if (b == 0) 
	{
		SDA_L();
	}
	else 
	{
		SDA_H();
	}
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_init1
*	����˵��: I2C��ʼ��
*	��    �Σ���
*	�� �� ֵ: bin���ɹ������
*********************************************************************************************************
*/
void i2c_init(void)
{
	bsp_InitI2C();
	
	I2C_SCL_OUT() ;
	I2C_SDA_OUT();
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_start1
*	����˵��: i2c_start�ź�
*	��    �Σ���
*	�� �� ֵ: bin���ɹ������
*********************************************************************************************************
*/
unsigned char i2c_start(void)
{
	unsigned char bin;
	SCL_H(); 			/* EHO: 15-07-2003 in case of repeated start, first scl high */
	i2c_delay();

	I2C_CLK_Streching_Cnt = Streching_Delay;
	while (I2C_CLK_Streching_Cnt --)
	{
		bin = SCL_IN();
		if (bin == 1)
		{
			break ;
		}
	}
	i2c_delay();
	
	SDA_L(); 			/* Pull SDA down...	*/
	i2c_delay();
	
	SCL_L(); 			/* ...and then SCL -> start condition. */
	i2c_delay();
	
	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_stop
*	����˵��: i2c_stop�ź�
*	��    �Σ���
*	�� �� ֵ: bin���ɹ������
*********************************************************************************************************
*/
unsigned char i2c_stop(void)
{
	unsigned char bin;
	SDA_L(); 	/* Pull SDA down if it was not down */
	i2c_delay();
	
	SCL_H(); 	/* Let SCL go up */
	i2c_delay();
	
	I2C_CLK_Streching_Cnt = Streching_Delay;
	while (I2C_CLK_Streching_Cnt --)
	{
		bin = SCL_IN();
		if (bin == 1)
		{
			break ;
		}
	}
	i2c_delay();
	
	SDA_H(); 	/* ...and then SDA up -> stop condition. */
	SCL_H();
	i2c_delay();
	
	return (0);
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_bit_out1
*	����˵��: I2C���
*	��    �Σ���
*	�� �� ֵ: bin���ɹ������
*********************************************************************************************************
*/
unsigned char i2c_bit_out(unsigned char bout)
{
	unsigned char bin;

	SDA_OUT(bout); 	/* Put data out on SDA */
	i2c_delay();
	
	SCL_H(); 		/* Let SCL go up */
	i2c_delay();

	I2C_CLK_Streching_Cnt = Streching_Delay;
	while (I2C_CLK_Streching_Cnt --)
	{
		bin = SCL_IN();
		if (bin == 1)
		{
			break ;
		}
	}
	i2c_delay();

	SCL_L(); 		/* Pull SCL back down */
	i2c_delay();
	
	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_bit_in_ACK1
*	����˵��: ACK�ź�
*	��    �Σ���
*	�� �� ֵ: bin���ɹ������
*********************************************************************************************************
*/
unsigned char i2c_bit_in_ACK(void)
{
	unsigned char bin;

	SDA_H();
	i2c_delay();
	
	SCL_H(); 		/* Let SCL go up */
	i2c_delay();
	
	I2C_CLK_Streching_Cnt = Streching_Delay;
	while (I2C_CLK_Streching_Cnt --)
	{
		bin = SCL_IN();
		if(bin == 1)
		{
			break ;
		}
	}
	
	I2C_CLK_Streching_Cnt = Streching_Delay ;	
	while (I2C_CLK_Streching_Cnt--)
	{
		bin = SDA_IN(); 	/* Read in data */
		if(bin == 0)
		{ 
			break;
		}		
	}
	i2c_delay();
	
	SCL_L(); 		/* Pull SCL back up */
	i2c_delay();
	
	return bin; 		/* Return the sampled bit */
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_bit_in
*	����˵��: һ��bit��ʱ��
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
unsigned char i2c_bit_in(void)
{
	unsigned char bin;
	
	SDA_H();
	i2c_delay();	
	
	SCL_H(); 		/* Let SCL go up */
	i2c_delay();
	
	I2C_CLK_Streching_Cnt = Streching_Delay;
	while(I2C_CLK_Streching_Cnt --)
	{
		bin = SCL_IN();
		if(bin == 1)
		{
			break ;
		}
	}
	i2c_delay();
	
	bin = SDA_IN();	
	i2c_delay();
	
	SCL_L(); 		/* Pull SCL back up */
	i2c_delay();
	
	return bin; 		/* Return the sampled bit */
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_byte_out1
*	����˵��: ���һ���ֽ�
*	��    �Σ����ݵ�һ���ֽ�
*	�� �� ֵ: 1�����ͳɹ���0�����ʹ���
*********************************************************************************************************
*/
unsigned char i2c_byte_out(unsigned char dat)
{
	unsigned char  bit_count;
	
	bit_count = 8;
	
	while(bit_count)
	{
		if (dat & 0x80)
		{
			if (i2c_bit_out(1))	return 1;
		}
		else
		{
			if (i2c_bit_out(0))	return 1;
		}
		
		dat <<= 1;
		bit_count--;
	}
	
	if (i2c_bit_in_ACK())
	{
		return 1;
	}
	
	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_byte_in
*	����˵��: һ���ֽڵ�ʱ��
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
unsigned char i2c_byte_in(unsigned char ack)
{
	unsigned char bit_count, byte_in;
	bit_count = 8;
	byte_in = 0;

	while(bit_count)
	{
		byte_in <<= 1;
		if (i2c_bit_in())
		{
			byte_in |= 0x01;
		}
		bit_count--;
	}
	i2c_bit_out(ack);
	
	SDA_H();
	i2c_delay();

	return byte_in;
}
/*
*********************************************************************************************************
*	�� �� ��: I2C_Comm_MasterSend
*	����˵��: ����ָ���
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
unsigned char I2C_Comm_MasterSend (uint16_t slaveaddr, uint8_t offset, uint8_t* pBuffer, uint8_t length)
{
	unsigned char byte_out;
	 
	if (i2c_start()) return 1;
	i2c_error = 0;
	i2c_delay();

	byte_out = (unsigned char)(slaveaddr);
	if (i2c_byte_out(byte_out))	//send device address
	{
		if (i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
	}
	i2c_delay();
	
	if (i2c_byte_out(offset))	//send device address
	{
		if (i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
	}
	i2c_delay();
	
	while(length)
	{	
		byte_out = *pBuffer;
		pBuffer++;		
		if (i2c_byte_out(byte_out))
		{
			if(i2c_error == I2CERR_NAK)
			{
				i2c_stop();
				return 1;				
			}
			return i2c_error;
		}		
		length--;		
	}
	i2c_stop();
	
	return 0;
}
/*
*********************************************************************************************************
*	�� �� ��: I2C_Comm_MasterReceive
*	����˵��: �������ͼĴ���ֵ
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
unsigned char I2C_Comm_MasterReceive (uint16_t slaveaddr, uint8_t offset, uint8_t* pBuffer, uint8_t length)
{
	unsigned char byte_out;
	unsigned char byte_in ;

	if (i2c_start()) return 1;
	i2c_error = 0;

	byte_out = (unsigned char)(slaveaddr);
	if (i2c_byte_out(byte_out))	//send device address
	{
		if (i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
	}	
	i2c_delay();
	
	if (i2c_byte_out(offset))	//send device address
	{
		if(i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
	}
	i2c_delay();
	
	if (i2c_start()) return 1;
	i2c_error = 0;
	i2c_delay();

	byte_out = (unsigned char)(slaveaddr) |0x01;
	if (i2c_byte_out(byte_out))	//send read device address
	{
		if (i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
	}
	i2c_delay();
	 	
	while(length)
	{
		if(--length)
		{
			byte_in = i2c_byte_in(0);
		}
		else
		{
			byte_in = i2c_byte_in(1); /* No ACK during last byte */
		}
		*pBuffer	= byte_in;
		pBuffer++;
	}
	i2c_stop();
	
	return 0 ;	
}
/*
*********************************************************************************************************
*	�� �� ��: I2C_CheckBusy
*	����˵��: �ж�æ�ź�
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
unsigned char I2C_CheckBusy (uint16_t slaveaddr)
{
	unsigned char byte_out;
	 
	if (i2c_start()) return 1;
	i2c_error = 0;
	i2c_delay();

	byte_out = (unsigned char)(slaveaddr);
	if (i2c_byte_out(byte_out))
	{
		if (i2c_error == I2CERR_NAK )
		{
			i2c_stop();			
			return 1;
		}
		else
		{
			i2c_stop();			
			return 1;
		}
	}
	else
	{
		i2c_stop();				
		return 0;
	}
}


