/**
 * @file bsp_MPU9255.h
 * @author Qiaoyy@xlnav.com
 * @version v1.0
 * @date 2018-01-22
 * @brief  采用 STMCUBE HAL库I2C方法读取 MPU9255 加速度计、陀螺、磁力计和温度计的数据
 * Copyright (c) 2018 XiLang Co. Ltd.
 * All rights reserved.
 */
 
 /* Includes ------------------------------------------------------------------*/
#include "Global.h"
#include "i2c.h"
#include "dvc_MPU9255.h"

/* Private typedef -----------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t g_ucBuffer[16];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  
 * @param
 * @return 
*/
void MPU9255_ReadAddressReg(uint16_t DevAddress, uint16_t RegAddr, uint8_t Num, uint8_t *pBuffer)
{
	HAL_I2C_Mem_Read(&hi2c1, DevAddress, RegAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Num, 100);
}

/**
 * @brief  
 * @param
 * @return 
*/
void MPU9255_WriteAddressReg(uint16_t DevAddress, uint16_t RegAddr, uint8_t Val) 
{
	HAL_I2C_Mem_Write(&hi2c1, DevAddress, RegAddr, I2C_MEMADD_SIZE_8BIT, &Val, 1, 100); 
} 

/**
  * @brief  Initializes MPU9255
  * @param  None
  * @retval None
  */ 
void MPU9255_ReadReg(uint8_t RegAddr, uint8_t Num, uint8_t *pBuffer) 
{
	MPU9255_ReadAddressReg(MPU9255_ADDRESS, (uint16_t)RegAddr, Num, pBuffer);
}

/**
  * @brief  Initializes MPU9255
  * @param  None
  * @retval None
  */ 
void MPU9255_WriteReg(uint8_t RegAddr, uint8_t Val) 
{
	MPU9255_WriteAddressReg( MPU9255_ADDRESS, (uint16_t)RegAddr, Val); 
} 

/**
  * @brief  Initializes MPU9255
  * @param  None
  * @retval None
  */ 
void MPU9255_Init(void)
{
    uint8_t i2c_dev = 0;
    MPU9255_WriteReg(PWR_MGMT_1, PWR_RUN_MODE);
    HAL_Delay(50);
	// Read WHO_AM_I 
    MPU9255_ReadReg(WHO_AM_I, 1, &i2c_dev); // 0x73
	HAL_Delay(10);
	if (i2c_dev == WHO_AM_I_MPU9255)
	{
		// Clock Source
		MPU9255_WriteReg(PWR_MGMT_1, PWR_CLOCK_SOURCE_AUTO);
		HAL_Delay(10);
		MPU9255_WriteReg(SMPLRT_DIV, SAMPLE_RATE_125HZ);
		HAL_Delay(10);
		MPU9255_WriteReg(CONFIG, DLPF_CFG5);
		HAL_Delay(10);
		MPU9255_WriteReg(GYRO_CONFIG, GYRO_250DPS);
		HAL_Delay(10);
		MPU9255_WriteReg(ACCEL_CONFIG, ACCEL_16G);
		HAL_Delay(10);
		MPU9255_WriteReg(ACCEL_CONFIG2, A_DLPF_CFG4_20Hz); 
		HAL_Delay(10);
	
		MPU9255_WriteReg(0x37,0x02);//turn on Bypass Mode 
        HAL_Delay(50); 
        MPU9255_ReadAddressReg(MAG_ADDRESS, 0x00, 1, &i2c_dev); // 0x48
		if (i2c_dev == 0x48)
		{
			MPU9255_WriteAddressReg(MAG_ADDRESS,0x0A,0x01); 
		}
	}
	else
	{
		
	}
}

/**
  * @brief Get accelerometer datas
  * @param  None
  * @retval None
  */
void MPU9255_ReadAcce(int16_t accel[3])
{ 
	MPU9255_ReadReg(ACCEL_XOUT_H, 6, g_ucBuffer);	
	accel[0]=	(g_ucBuffer[0]<<8)|g_ucBuffer[1];
	accel[1]=	(g_ucBuffer[2]<<8)|g_ucBuffer[3];				   
	accel[2]=	(g_ucBuffer[4]<<8)|g_ucBuffer[5];			       
}

/**
  * @brief Get gyroscopes datas
  * @param  None
  * @retval None
  */
void MPU9255_ReadGyro(int16_t gyro[3])
{
	MPU9255_ReadReg(GYRO_XOUT_H, 6, g_ucBuffer);	
	gyro[0] = (g_ucBuffer[0]<<8)|g_ucBuffer[1];
	gyro[1] = (g_ucBuffer[2]<<8)|g_ucBuffer[3];
	gyro[2] = (g_ucBuffer[4]<<8)|g_ucBuffer[5];	
}

/**
  * @brief Get compass datas
  * @param  None
  * @retval None
  */
void MPU9255_ReadMagn(int16_t magn[3])
{ 
    char xa,ya,za;
    int16_t InBuffer[3] = {0};
	double outx1;
	double outx2;
	double outy1;
	double outy2;
	double outz1;
	double outz2;
	
    MPU9255_ReadAddressReg(MAG_ADDRESS, MAG_XOUT_L, 6, g_ucBuffer);

    InBuffer[0] = (g_ucBuffer[1]<<8)|g_ucBuffer[0];
    InBuffer[1] = (g_ucBuffer[3]<<8)|g_ucBuffer[2];
    InBuffer[2] = (g_ucBuffer[5]<<8)|g_ucBuffer[4];	
       
    MPU9255_WriteAddressReg(MAG_ADDRESS,0x0A,0x01); 
    
    MPU9255_ReadAddressReg(MAG_ADDRESS,ASAX, 1, (unsigned char*)&xa);
	MPU9255_ReadAddressReg(MAG_ADDRESS,ASAY, 1, (unsigned char*)&ya);
	MPU9255_ReadAddressReg(MAG_ADDRESS,ASAZ, 1, (unsigned char*)&za);
	
    outx1 = (double)InBuffer[0];
    outx2 = ((double)((xa-128)/256.0)+1)*100.0;
    outy1 = (double)InBuffer[1];
    outy2 = ((double)((ya-128)/256.0)+1)*100.0;
    outz1 = (double)InBuffer[2];
    outz2 = ((double)((za-128)/256.0)+1)*100.0;
   
    magn[0]=(int) (outx1 * outx2);
	magn[1]=(int) (outy1 * outy2);
	magn[2]=(int) (outz1 * outz2);
}

/**
 * @brief  
 * @param
 * @return 
*/
void MPU9255_ReadTempreture(int16_t* tempreture)
{ 
	uint16_t InBuffer = 0x00;
    MPU9255_ReadReg(TEMP_OUT_H, 2, g_ucBuffer);
    InBuffer = (g_ucBuffer[0]<<8)|g_ucBuffer[1];
    *tempreture = (int16_t)((((double)(InBuffer-0)/333.87)+21.0)* 100) ;
}

/**
 * @brief  
 * @param
 * @return 
*/
void MPU9255_ReadImu(int16_t gyro[3], int16_t accel[3], int16_t* tempreture)
{
	int16_t InBuffer = 0x00;
	MPU9255_ReadReg(ACCEL_XOUT_H, 14, g_ucBuffer);	
	accel[0]= (g_ucBuffer[0]<<8)|g_ucBuffer[1];
	accel[1]= (g_ucBuffer[2]<<8)|g_ucBuffer[3];				   
	accel[2]= (g_ucBuffer[4]<<8)|g_ucBuffer[5];
	InBuffer = (g_ucBuffer[6]<<8)|g_ucBuffer[7];
	gyro[0] = (g_ucBuffer[8]<<8)|g_ucBuffer[9];
	gyro[1] = (g_ucBuffer[10]<<8)|g_ucBuffer[11];
	gyro[2] = (g_ucBuffer[12]<<8)|g_ucBuffer[13];	
	
    *tempreture = (int16_t)((((double)(InBuffer-0)/333.87)+21.0)* 100) ;
}
float acc_f[3],gyro_f[3],magn_f[3],temp_f;
//void ICM20948_Imu_datadeal(int16_t accel[3], int16_t gyro[3],int16_t magn[3],int16_t* temp)
void MPU9255_Imu_datadeal(int16_t gyro[3],int16_t accel[3],int16_t* temp)
{
	int i;
	for(i=0;i<3;i++)
	{
		acc_f[i]=(float)((double)accel[i]/2048*9.8);
	}
	for(i=0;i<3;i++)
	{
		gyro_f[i]=(float)((double)gyro[i]/131);
	}
//		for(i=0;i<3;i++)
//	{
//		magn_f[i]=(float)((double)magn[i]/100);
//	}
	temp_f=(float)*temp/100;
}
/************************ (C) COPYRIGHT XiLang CO. Ltd. *******END OF FILE*****/
