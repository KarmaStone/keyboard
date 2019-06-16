#ifndef __BSP_IIC_H
#define __BSP_IIC_H

#include "bsp_sys.h"

#define I2C_WR	0		/* Ğ´¿ØÖÆbit */
#define I2C_RD	1		/* ¶Á¿ØÖÆbit */

void i2c_init(void);
unsigned char I2C_CheckBusy (uint16_t slaveaddr);

unsigned char I2C_Comm_MasterSend (uint16_t slaveaddr, uint8_t offset, uint8_t* pBuffer, uint8_t length);
unsigned char I2C_Comm_MasterReceive (uint16_t slaveaddr, uint8_t offset, uint8_t* pBuffer, uint8_t length);

#endif

