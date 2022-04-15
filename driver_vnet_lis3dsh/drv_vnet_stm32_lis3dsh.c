#include "drv_vnet_stm32_lis3dsh.h"
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;


void LIS3DSH_Init(motion *MotionData) // Init 
{
	MotionData->biasX = 0;
	MotionData->biasY = 0;
	MotionData->biasZ = 0;
	MotionData->motionDectect = 0;
}
void LIS3DSH_Write(uint8_t reg, uint8_t value, uint8_t size) // ghi data vao thanh ghi reg
{
	HAL_I2C_Mem_Write(&hi2c1, LIS3DSH_I2C_ADDR, reg, 1, &value, size, 100); 
}
int LIS3DSH_Read(uint8_t reg, uint8_t size) // doc 1 byte data tu thanh ghi reg
{
	int readval;
	uint8_t pdata[2];
	HAL_I2C_Mem_Read(&hi2c1, LIS3DSH_I2C_ADDR, SET_READ_SINGLE_CMD(reg), 1, pdata, size, 100);
	readval = pdata[0];
	return readval;
}
void Config_Reg(uint8_t reg, uint8_t value) // Config thanh ghi LIS3DSH
{
//	LIS3DSH_Write(CTRL_REG4, 0x4F, 1);
//	LIS3DSH_Write(CTRL_REG6, 0x10, 1);
//	LIS3DSH_Write(CTRL_REG1,0x01,1);
//  LIS3DSH_Write(CTRL_REG3,0x48,1);
//  LIS3DSH_Write(CTRL_REG5,0x80,1);
//  LIS3DSH_Write(THRS1_1,0x55,1);
//  LIS3DSH_Write(ST1_1,0x05,1);
//  LIS3DSH_Write(ST1_2,0x11,1);
//  LIS3DSH_Write(MASK1_B,0xFC,1);
//  LIS3DSH_Write(MASK1_A,0xFC,1);
//  LIS3DSH_Write(SETT1,0x01,1);
	LIS3DSH_Write(reg, value, 1);
}
uint8_t Motion_Det(motion *MotionData) // Phat hien chuyen dong, gia tri tra = 0 khi khong chuyen dong va = 1 khi co chuyen dong
{
	int buff_L[3];
	int buff_H[3];
	
	
	buff_L[0] = LIS3DSH_Read(ADD_REG_OUT_X_L,2); 	//Doc byte low tu thanh ghi truc X
	buff_L[1] = LIS3DSH_Read(ADD_REG_OUT_Y_L,2);	//Doc byte low tu thanh ghi truc Y
	buff_L[2] = LIS3DSH_Read(ADD_REG_OUT_Z_L,2);	//Doc byte low tu thanh ghi truc Z
	buff_H[0] = LIS3DSH_Read(ADD_REG_OUT_X_H,2);	//Doc byte high tu thanh ghi truc X
	buff_H[1] = LIS3DSH_Read(ADD_REG_OUT_Y_H,2);	//Doc byte high tu thanh ghi truc Y
	buff_H[2] = LIS3DSH_Read(ADD_REG_OUT_Z_H,2);	//Doc byte high tu thanh ghi truc Z
	
	MotionData->accelX = INT16_C(buff_H[0]<<8|buff_L[0]);	//Tinh gia tri cua sensor truc X
	MotionData->accelY = INT16_C(buff_H[1]<<8|buff_L[1]);	//Tinh gia tri cua sensor truc Y
	MotionData->accelZ = INT16_C(buff_H[2]<<8|buff_L[2]);	//Tinh gia tri cua sensor truc Z
	
	MotionData->biasX = __fabs(MotionData->accelX - MotionData->prevX);	//Tinh Do sai lech gia tri giua 2 lan lay mau lien tiep cua truc X
	MotionData->biasY = __fabs(MotionData->accelY - MotionData->prevY);	//Tinh Do sai lech gia tri giua 2 lan lay mau lien tiep cua truc Y
	MotionData->biasZ = __fabs(MotionData->accelZ - MotionData->prevZ);	//Tinh Do sai lech gia tri giua 2 lan lay mau lien tiep cua truc Z
	
	//Ham so sanh Do lech gia tri giua 2 lan lay mau tra ve gia tri 0 hoac 1 
	if(((MotionData->biasX >= sensities)||(MotionData->biasY >= sensities)||(MotionData->biasZ >= sensities))&&((MotionData->prevX != 0)&&(MotionData->prevY != 0)&&(MotionData->prevZ != 0)))  
	{
		MotionData->motionDectect = 1;
	}
	else if((MotionData->biasX < sensities)&&(MotionData->biasY < sensities)&&(MotionData->biasZ < sensities))
	{
		MotionData->motionDectect = 0;
	}
	
	MotionData->prevX = MotionData->accelX;	//Gan prevX = gia tri lay mau truoc do
	MotionData->prevY = MotionData->accelY;	//Gan prevY = gia tri lay mau truoc do
	MotionData->prevZ = MotionData->accelZ;	//Gan prevZ = gia tri lay mau truoc do
	

	return MotionData->motionDectect;

}


