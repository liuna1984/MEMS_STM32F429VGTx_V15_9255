#ifndef BSP_MPU9255_H_20180122
#define BSP_MPU9255_H_20180122
/**
 * @file bsp_MPU9255.h
 * @author Qiaoyy@xlnav.com
 * @date 2018-01-22
 * @brief 采用 STMCUBE HAL库I2C方法读取 MPU9255 加速度计、陀螺、磁力计和温度计的数据
 * All right reserved by XiLang Co.
 */
 
/* Includes ------------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

// define MPU9250 register address
#define ADDRESS_AD0_LOW     0xD0 //address pin low (GND), default for InvenSense evaluation board
#define ADDRESS_AD0_HIGH    0xD1 //address pin high (VCC)
#define MPU9255_ADDRESS     ADDRESS_AD0_LOW

#define	PWR_MGMT_1		0x6B	//Power Management. Typical values:0x00(run mode)
#define PWR_RUN_MODE 	0x00
#define PWR_CLOCK_SOURCE_AUTO 0x01

#define	PWR_MGMT_2		0x6C	//Power Management. Typical values:0x00(run mode)
#define ENALBE_ACC_AND_GYR 	0x00

#define	WHO_AM_I		0x75	//identity of the device
#define	WHO_AM_I_MPU9255 0x73	//identity of the device

#define	SMPLRT_DIV		0x19	//Sample Rate Divider. Typical values:0x07(125Hz) 1KHz internal sample rate
#define SAMPLE_RATE_125HZ		0x07
#define DIV_7			0x06
#define DIV_6			0x05
#define DIV_5			0x04
#define DIV_4			0x03
#define DIV_3			0x02
#define DIV_2			0x01
#define DIV_1			0x00

#define	CONFIG			0x1A	//Low Pass Filter.Typical values:0x06(5Hz)
#define FIFO_MODE_ENABLE
#define EXT_SYNC_SET_TEMP
#define EXT_SYNC_SET_GYRO_XOUT
#define EXT_SYNC_SET_GYRO_YOUT
#define EXT_SYNC_SET_GYRO_ZOUT
#define EXT_SYNC_SET_ACCEL_XOUT
#define EXT_SYNC_SET_ACCEL_YOUT
#define EXT_SYNC_SET_ACCEL_ZOUT
#define DLPF_CFG0 		0x00
#define DLPF_CFG1		0x01
#define DLPF_CFG2		0x02
#define DLPF_CFG3		0x03
#define DLPF_CFG4		0x04
#define DLPF_CFG5		0x05
#define DLPF_CFG6		0x06
#define DLPF_CFG7		0x07

#define	GYRO_CONFIG		0x1B	//Gyro Full Scale Select. 
#define	GYRO_250DPS     0x00
#define	GYRO_500DPS     0x08
#define	GYRO_1000DPS    0x10
#define	GYRO_2000DPS    0x18

#define	ACCEL_CONFIG	0x1C	//Accel Full Scale Select. 
#define ACCEL_2G      	0x00
#define ACCEL_4G      	0x08
#define ACCEL_8G		0x10
#define ACCEL_16G       0x18

#define	ACCEL_CONFIG2	0x1D	//Accel Full Scale Select. 
#define ACCEL_FCHOICE_DISABLE	0x08 // Bandwidth 1.13K
#define A_DLPF_CFG0_460Hz		0x00
#define A_DLPF_CFG1_184Hz		0x01
#define A_DLPF_CFG2_92Hz		0x02
#define A_DLPF_CFG3_41Hz		0x03
#define A_DLPF_CFG4_20Hz		0x04
#define A_DLPF_CFG5_10Hz		0x05
#define A_DLPF_CFG6_5Hz			0x06
#define A_DLPF_CFG7_460Hz		0x07

//#define INT_PIN_CFG     0x37      // INT Pin / Bypass Enable Configuration
//#define INT_ENABLE      0x38      // Interrupt Enable

#define I2C_MST_CTRL    0x4D      // I2C Master Control

#define USER_CTRL       0x6A      // User Control
#define I2C_MST_EN 		0x20

/// 寄存器地址
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40

#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42

#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48

#define MAG_ADDRESS    0x18   //compass device address

#define MAG_XOUT_L		0x03
#define MAG_XOUT_H		0x04
#define MAG_YOUT_L		0x05
#define MAG_YOUT_H		0x06
#define MAG_ZOUT_L		0x07
#define MAG_ZOUT_H		0x08

#define	ASAX			0x10	//MAG X -axis sensitivity adjustment value(Fuse ROM)
#define	ASAY			0x11	//MAG Y -axis sensitivity adjustment value(Fuse ROM)
#define	ASAZ			0x12	//MAG Y -axis sensitivity adjustment value(Fuse ROM)

/* Exported functions --------------------------------------------------------*/
void MPU9250_Init(void);
void MPU9250_ReadMagn(int16_t magn[3]);
void MPU9250_ReadGyro(int16_t gyro[3]);
void MPU9250_ReadAcce(int16_t accel[3]);
void MPU9250_ReadTemp(int16_t* tempreture);
void MPU9250_ReadImu(int16_t gyro[3], int16_t accel[3], int16_t* tempreture);
#endif
/************************ (C) COPYRIGHT XiLang CO. Ltd. *******END OF FILE*****/
