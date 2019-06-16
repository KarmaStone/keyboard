#include "bsp_XFM10412.h"
#include "bsp_timer.h"


#define XFM10412_DEVADDR  (0x8E)    // Slave address(8bit)

void usage()
{
    printf("=============================");
    printf("Arduino demo for xfm10412");
    printf("[1] Get version");
    printf("[2] Get wakeup angle");
    printf("[3] Enter wakeup mode");
    printf("[4] Exit wakeup mode");
    printf("Please select: ");
}

void i2cWrite(u8 addr, u8 reg, u8 len, u8 *data)
{

	I2C_Comm_MasterSend(addr,reg,data,len);
	HAL_Delay(1);        // delay 1ms at least
}

void i2cRead(u8 addr, u8 reg, u8 len, u8 *data)
{
	
	I2C_Comm_MasterReceive(addr,reg,data,len);
    HAL_Delay(1);        // delay 1ms at least
}

unsigned long cmd = 0;
unsigned long debugVelue = 0;

void getVersion()
{
    cmd = 0x00000F00;
    
    // 1. Write command to XFM10412
    i2cWrite(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
    
    // 2. Wait for command complete
    while (0x00020001 != cmd)
        i2cRead(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);

    // 3. Read firmware version
    i2cRead(XFM10412_DEVADDR, 0x01, 4, (u8 *)&cmd);
//    Serial.println("Firmware version: " + String(cmd&0xFF, DEC) + "." + String((cmd>>8)&0xFF, DEC));
	printf("Firmware version: %d . %d\r\n",(u8)cmd&0xFF,(u8)(cmd>>8)&0xFF);
    
    // 4. Read build version, optional
    i2cRead(XFM10412_DEVADDR, 0x02, 4, (u8 *)&cmd);
//    Serial.println("Build bersion : " + String(cmd&0xFF, DEC) + "." + String((cmd>>8)&0xFF, DEC) + "." + String((cmd>>16)&0xFF, DEC) + "." + String((cmd>>24)&0xFF, DEC));
	printf("Build bersion: %d . %d . %d . %d\r\n",(u8)cmd&0xFF,(u8)(cmd>>8)&0xFF , (u8)(cmd>>16)&0xFF ,(u8)(cmd>>24)&0xFF);
}

void getDegree()
{
    cmd = 0x00001000;
    
    // 1. Write command to XFM10412
    i2cWrite(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
    
    // 2. Wait for command complete
    while (0x00010001 != cmd)
        i2cRead(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
 
    // 3. Read wakeup degree
    i2cRead(XFM10412_DEVADDR, 0x01, 4, (u8 *)&cmd);
    printf("Wakeup degree: %d\r\n" ,(u32)cmd&0xFFFF);
	debugVelue = (u32)cmd&0xFFFF ;
	
	if(debugVelue <= 45)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_RESET);	//默认初始化后灯灭
	}
	if(debugVelue > 45 && debugVelue<=90)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_RESET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);	//默认初始化后灯灭
	}
	if(debugVelue > 90 && debugVelue<=135)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);	//默认初始化后灯灭
	}
	if(debugVelue > 135 && debugVelue<=180)
	{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);	//默认初始化后灯灭
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);	//默认初始化后灯灭
	}
	
}

void enterWakeup()
{
    cmd = 0x00001100;
    
    // 1. Write command to XFM10412
    i2cWrite(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
    
    // 2. Wait for command complete
    while (0x00000001 != cmd)
        i2cRead(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
    printf("Enter wakeup mode\r\n");
}

void exitWakeup()
{
    cmd = 0x00001200;
    
    // 1. Write command to XFM10412
    i2cWrite(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd);
    
    // 2. Wait for command complete
    while (0x00000001 != cmd)
        i2cRead(XFM10412_DEVADDR, 0x00, 4, (u8 *)&cmd); 
    printf("Exit wakeup mode\r\n");
}



//void setup()
//{
//    Wire.begin();		// join i2c bus (address optional for master)
//    Serial.begin(115200);	// start serial for output
//    usage();
//}

//void loop()
//{
//    char c;
//    
//    if (Serial.available() <= 0 || (c = Serial.read()) == -1)
//        return;
//    
//    Serial.println(c);
//    
//    switch (c - '0') {
//    case 1:   // get version
//        getVersion();
//        break;
//    case 2:   // get angle
//        getDegree();
//        break;
//    case 3:   // enter wakeup
//        enterWakeup();
//        break;
//    case 4:   // exit wakeup
//        exitWakeup();
//        break;
//    default:
//        Serial.println("Unsupported command");
//        break;
//    }
//   
//    delay(1);
//    usage();
//}

