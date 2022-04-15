#ifndef _DRV_VNET_STM32_LIS3DSH_
#define _DRV_VNET_STM32_LIS3DSH_

#include "stdint.h"
#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_i2c.h"
#include "stm32g0xx_hal_uart.h"
#include "math.h"
#include "string.h"
#include "stdio.h"

#define LIS3DSH_I2C_ADDR       		0x3C 					//Dia chi LIS3dSH (slave address)
#define LIS3DSH_WHO_AM_I_ADDR     	0x0F					//Dia chi thanh ghi Who_am_I
#define SET_READ_SINGLE_CMD(x)		(x|0x80)			
#define SET_WRITE_SINGLE_CMD(x)		(x&(~(0x80)))
#define ADD_REG_OUT_X_L 		0x28					//Dia chi thanh ghi byte low OUT_X
#define ADD_REG_OUT_X_H			0x29					//Dia chi thanh ghi byte high OUT_X
#define ADD_REG_OUT_Y_L			0x2A					//Dia chi thanh ghi byte low OUT_Y
#define ADD_REG_OUT_Y_H			0x2B					//Dia chi thanh ghi byte high OUT_Y
#define ADD_REG_OUT_Z_L			0x2C					//Dia chi thanh ghi byte low OUT_Z
#define ADD_REG_OUT_Z_H			0x2D					//Dia chi thanh ghi byte high OUT_Z
#define CTRL_REG1     			0x21
#define CTRL_REG3     			0x23
#define CTRL_REG4    			0x20
#define CTRL_REG5     			0x24
#define CTRL_REG6     			0x25
#define STATUS        			0x27
#define THRS1_1       			0x57
#define ST1_1         			0x40
#define ST1_2        			0x41
#define MASK1_B       			0x59
#define MASK1_A      			0x5A
#define SETT1         			0x5B

#define sensities 			500			


typedef struct
{
	 uint16_t biasX; 
	 uint16_t biasY;
	 uint16_t biasZ;
	 uint16_t prevX; 
	 uint16_t prevY;
	 uint16_t prevZ;
	 uint16_t accelX; 
	 uint16_t accelY;
	 uint16_t accelZ;
	 uint8_t motionDectect;
} motion;
void LIS3DSH_Init(motion *MotionData);
void Config_Reg(uint8_t reg, uint8_t value);
void LIS3DSH_Write(uint8_t reg, uint8_t value, uint8_t size);
int LIS3DSH_Read(uint8_t reg, uint8_t size);
uint8_t Motion_Det(motion *MotionData);

#endif
