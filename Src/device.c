#include "main.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "usart.h"
#include "dvc_MPU9255.h"
extern float acc_f[3],gyro_f[3],magn_f[3],temp_f;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	int16_t accel[3]={0};
	int16_t gyro[3]={0};
	int16_t magn[3]={0};
	int16_t temp;
	if (htim->Instance == htim6.Instance)
	{
		///@todo 在这里补充输出函数
		HAL_GPIO_TogglePin(GPIOB, LED3_Pin|LED2_Pin|LED1_Pin);
		MPU9255_ReadImu(&gyro[0],&accel[0],&temp);
		//MPU9255_ReadMagn(&magn[0]);
		//ICM20948_Imu_datadeal(&accel[0],&gyro[0],&magn[0],&temp);
		MPU9255_Imu_datadeal(&gyro[0],&accel[0],&temp);
  	//printf("%d %d %d %d %d %d %d %d %d %d\n",accel[0],accel[1],accel[2],gyro[0],gyro[1],gyro[2],magn[0],magn[1],magn[2],temp);
	  printf("%f %f %f %f %f %f %f\n",gyro_f[0],gyro_f[1],gyro_f[2],acc_f[0],acc_f[1],acc_f[2],temp_f);
		//printf("%f %f %f %f %f %f %f %f %f %f\n",acc_f[0],acc_f[1],acc_f[2],gyro_f[0],gyro_f[1],gyro_f[2],magn_f[0],magn_f[1],magn_f[2],temp_f);	
    //printf("%f %f %f %f %f %f %f %f %f %f\n",g_hImu20948.acc_f[0],g_hImu20948.acc_f[1],g_hImu20948.acc_f[2],g_hImu20948.gyro_f[0],g_hImu20948.gyro_f[1],g_hImu20948.gyro_f[2],\
		g_hImu20948.magn_f[0],g_hImu20948.magn_f[1],g_hImu20948.magn_f[2],g_hImu20948.temp);		
   // MTiRead();
//		MTidatadeal();
//		HAL_SPI_Receive(&hspi1,(uint8_t*)&buffer[0],8,100);
	}
}
/**
  * 函数功能: 重定向c库函数printf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/**
  * 函数功能: 重定向c库函数getchar,scanf到DEBUG_USARTx
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明：无
  */
int fgetc(FILE * f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart3,&ch, 1, 0xffff);
  return ch;
}