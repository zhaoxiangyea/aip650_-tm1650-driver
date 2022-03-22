#ifdef __cplusplus ///<use C compiler
extern "C" {
#endif

#include "main.h"
#include "AIP650.h"

Key_Value_Save_t Key_Value_History = 
{
    .Key_value_ptr = NULL,
    .write_index = 0,
    .read_index  = 0,
    .left_lenth  = 0
};

uint8_t Key_Value_Arr[KEY_VALUE_BUF_MAX] = {0};
/** Private variables --------------------------------------------------------*/

/** Private function prototypes ----------------------------------------------*/
static void Key_value_circle_init(void);
static int CQ_Putdata(uint8_t data);
static void SDA_Output(void);
static void SDA_Input(void);
//static void SCL_Input(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_Wait_Ack(void);
static void I2C_Ack(void);
static void I2C_Send_Byte(uint8_t data);

static uint8_t I2C_Read_Byte();


void delay_us(uint32_t nus)
{
    uint32_t Delay = nus;
    do
    {
        __NOP();
    }
    while (Delay --);
}



 /**
	******************************************************************
	* @brief   模拟I2C 数据脚配置为输出模式
	* @param   [in]None
	* @retval  None
	* @author  aron566
	* @version V1.0
	* @date    2020-5-18
	******************************************************************
	*/
static void SDA_Output(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

//	HAL_GPIO_WritePin(AIP_SDA_GPIO_Port, AIP_SDA_Pin, GPIO_PIN_SET);
	GPIO_InitStruct.Pin = AIP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(AIP_SDA_GPIO_Port, &GPIO_InitStruct);

//	HAL_GPIO_WritePin(AIP_SCL_GPIO_Port, AIP_SCL_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : AIP_SCL_Pin */
	GPIO_InitStruct.Pin = AIP_SCL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(AIP_SCL_GPIO_Port, &GPIO_InitStruct);
}
 
 /**
	******************************************************************
	* @brief   模拟I2C 数据脚配置为输入模式
	* @param   [in]None
	* @retval  None
	* @author  aron566
	* @version V1.0
	* @date    2020-5-18
	******************************************************************
	*/
static void SDA_Input(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*Configure GPIO pin : AIP_SDA_Pin */
	GPIO_InitStruct.Pin = AIP_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(AIP_SDA_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(AIP_SCL_GPIO_Port, AIP_SCL_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : AIP_SCL_Pin */
	GPIO_InitStruct.Pin = AIP_SCL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(AIP_SCL_GPIO_Port, &GPIO_InitStruct);
}
 

 


/**
  ******************************************************************
  * @brief   模拟I2C发出起始信号
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Start(void)
{
	SDA_Output();

	SDA_Dout_HIGH();
	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SDA_Dout_LOW();
	delay_us(TIME_UINT);
}
 
/**
  ******************************************************************
  * @brief   模拟I2C发出停止信号
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Stop(void)
{
	SDA_Output();
	SCL_Dout_LOW();
	delay_us(5);
	SDA_Dout_LOW();
	delay_us(TIME_UINT);

	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SDA_Dout_HIGH();
	delay_us(TIME_UINT);
}
 
/**
  ******************************************************************
  * @brief   模拟I2C等待应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Wait_Ack(void)
{
	uint8_t i = 1;
	SDA_Input();

	SCL_Dout_LOW();
	delay_us(TIME_UINT);
	SCL_Dout_HIGH();

	while(SDA_Data_IN() && i <= 10) {
		i++;
	}

	SDA_Dout_HIGH();
	delay_us(1);
	SCL_Dout_LOW();//时钟输出0
	SDA_Output();
	delay_us(1);

}
 
/**
  ******************************************************************
  * @brief   模拟I2C应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Ack(void)
{

	SCL_Dout_LOW();
	delay_us(5);

	SDA_Input();
	SCL_Dout_HIGH();
//	delay_us(TIME_UINT);

	while(SDA_Data_IN());
	SDA_Output();

	delay_us(TIME_UINT);
	SCL_Dout_LOW();
	delay_us(TIME_UINT);

//	SDA_Output();
//	delay_us(2);
//	SCL_Dout_LOW();//时钟输出0
//	delay_us(TIME_UINT);
}
 
/**
  ******************************************************************
  * @brief   模拟I2C不应答
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
//static void I2C_NAck(void)
//{
//	SCL_Dout_LOW();
//	delay_us(TIME_UINT);
//	SDA_Output();
//	SDA_Dout_HIGH();
//	delay_us(TIME_UINT);
//	SCL_Dout_HIGH();
//	delay_us(TIME_UINT);
//	SCL_Dout_LOW();
//}

/**
  ******************************************************************
  * @brief   模拟I2C发送一个字节
  * @param   [in]txd 发送的字节
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void I2C_Send_Byte(uint8_t data)
{
	//拉低时钟开始数据传输
	SDA_Output();
	for(uint8_t t = 0; t < 8; t++) {
		SCL_Dout_LOW();
		delay_us(5);
		SDA_Write(data & 0x80);
		delay_us(TIME_UINT);
		SCL_Dout_HIGH();
		data <<= 1;
		delay_us(TIME_UINT);
	}
	I2C_Ack();
} 	    

/**
  ******************************************************************
  * @brief   模拟I2C读取一个字节 
  * @param   [in]ack ack=1时，发送ACK，ack=0，发送nACK 
  * @retval  读取到的字节
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static uint8_t I2C_Read_Byte()
{
	uint8_t receive = 0;
	//SDA设置为输入
	SDA_Input();

	for(uint8_t i = 0;  i< 8; i++ ) {
		SCL_Dout_HIGH();
		delay_us(TIME_UINT);
		SCL_Dout_HIGH();
		receive<<=1;
		receive |= SDA_Data_IN();
		SCL_Dout_LOW();
		delay_us(TIME_UINT);
	}

	SDA_Output();

	SDA_Dout_HIGH();
	SCL_Dout_HIGH();
	delay_us(TIME_UINT);
	SCL_Dout_LOW();
	delay_us(TIME_UINT);
  
	return receive;
}

/**
  ******************************************************************
  * @brief   加入数据到环形缓冲区
  * @param   [in]data 一个字节数据
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static int CQ_Putdata(uint8_t data)
{
    if(Key_Value_History.left_lenth < KEY_VALUE_BUF_MAX)
    {
        Key_Value_History.Key_value_ptr[Key_Value_History.write_index] = data;//存入缓存
        Key_Value_History.write_index = (Key_Value_History.write_index + 1) % KEY_VALUE_BUF_MAX;//偏移下次存入地址
        Key_Value_History.left_lenth++;//未读数据++
        return 0;
    }
    return -1;
}
/**
  ******************************************************************
  * @brief   按键键值环形缓冲区初始化
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
static void Key_value_circle_init(void)
{
    Key_Value_History.Key_value_ptr = Key_Value_Arr;
    Key_Value_History.read_index  = 0;
    Key_Value_History.write_index = 0;
}
/** Public application code --------------------------------------------------*/
/*******************************************************************************
*
*       Public code
*
********************************************************************************
*/
/**
  ******************************************************************
  * @brief   初始化AIP650 默认关断所有指示灯
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
//void AIP_650_Init_Opt(void)
//{
//    I2C_Init();//i2c初始化
//    Key_value_circle_init();//!< 键值缓冲区初始化
//    I2C_Start();
//    I2C_Send_Byte(0x48);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(0x51);
//    I2C_Wait_Ack();
//    I2C_Stop();
//
////    I2C_Start();
////    I2C_Send_Byte(0x48);
////    while(I2C_Wait_Ack());
////    I2C_Send_Byte(0x01);
////    while(I2C_Wait_Ack());
////    I2C_Stop();
////
////    I2C_Start();
////    I2C_Send_Byte(0x68);
////    while(I2C_Wait_Ack());
////    I2C_Send_Byte(0x00);
////    while(I2C_Wait_Ack());
////    I2C_Stop();
//
//    I2C_Start();
//    I2C_Send_Byte(0x6A);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(0x00);
//    I2C_Wait_Ack();
//    I2C_Stop();
//
//    I2C_Start();
//    I2C_Send_Byte(0x6C);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(0x00);
//    I2C_Wait_Ack();
//    I2C_Stop();
//
//    I2C_Start();
//    I2C_Send_Byte(0x6E);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(0x00);
//    I2C_Wait_Ack();
//    I2C_Stop();
//}

/**
  ******************************************************************
  * @brief   读取AIP650按键键值，并加入到环形缓冲区
  * @param   [in]None
  * @retval  按键键值
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
uint8_t Read_Aip650_Key_Value(void) {
    static uint8_t ret = 0;
    uint8_t Current_key_act = 0;
    I2C_Start();
    I2C_Send_Byte(0x4F);
    I2C_Wait_Ack();
    Current_key_act = I2C_Read_Byte();
    I2C_Stop();

    switch(Current_key_act)
    {
      case 0x45://S1
      case 0x4D://S2
      case 0x55://S3
      case 0x5D://S4
      case 0x65://S5
      case 0x6D://S6
      case 0x75://S7
      case 0xFF://S8
      case 0x47://S9
      case 0x4F://S10
      case 0x57://S11
      case 0x5F://S12
        ret = Current_key_act;
        break;
      default :
        if(ret)
        {
            //按键松开，才判定一个按键产生
            CQ_Putdata(ret);
            ret = 0;
        }
        return 0;
    }
    return ret;
}

/**
  ******************************************************************
  * @brief   从环形缓冲区取出数据
  * @param   [in]None
  * @retval  一个字节数据
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
uint8_t CQ_Getdata(void) {
    uint8_t ret_data = 0;
    if(Key_Value_History.left_lenth > 0)
    {
        ret_data = Key_Value_History.Key_value_ptr[Key_Value_History.read_index];//!< 读取数据
        Key_Value_History.read_index = (Key_Value_History.read_index+1 >= KEY_VALUE_BUF_MAX ? 0 : Key_Value_History.read_index+1);//!< 地址偏移
        Key_Value_History.left_lenth--;//!< 未读数据--
        return ret_data;
    }    
    return 0;
}

/**
  ******************************************************************
  * @brief   设置LED值
  * @param   [in]command 0-7bit 控制HL1-HL8 8-15bit 控制HL9-HL10
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
//void Set_LED_ON_OFF(uint32_t command)
//{
//    I2C_Start();
//    I2C_Send_Byte(0x68);
//    I2C_Wait_Ack();
//    I2C_Send_Byte(command&0xFF);    //!< 0-7 控制HL1-HL8
//    I2C_Wait_Ack();
//    I2C_Stop();
//
//    I2C_Start();
//    I2C_Send_Byte(0x6C);
//    I2C_Wait_Ack();
////    I2C_Send_Byte((command>>8)&0x03);//!< 8-15 控制HL9-HL10
//    I2C_Wait_Ack();
//    I2C_Stop();
//}


//void writeCMD(uint16_t cmd) {
//	I2C_Start();
////	I2C_Send_Byte(cmd >> 8);
////	I2C_Send_Byte(cmd & 0xff);
//    I2C_Wait_Ack();
//}

//void display(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4) {
//	writeCMD(0x4801);// 开显示，8级显示(0x4801);睡眠使能。时钟停振(0x4804)
//	writeCMD(0x6800 | data1);//com0 显示
//	writeCMD(0x6A00 | data3);//com1显示
//	writeCMD(0x6800 | data2);//com2显示
//	writeCMD(0x6800 | data4);//com3显示
//}


//void displayDemo() {
//	display(0x00,0x00,0x00,0x3F);
//	co_delay_100us(500);
//	display(0x00,0x00,0x3F,0x06);
//	co_delay_100us(500);
//	display(0x00,0x3F,0x06,0x5B);
//	co_delay_100us(500);
//	display(0x3F,0x06,0x5B,0x4F);
//	co_delay_100us(500);
//}


 
/**
  ******************************************************************
  * @brief   模拟I2C初始化
  * @param   [in]None
  * @retval  None
  * @author  aron566
  * @version V1.0
  * @date    2020-5-18
  ******************************************************************
  */
void AIP650Init(void) {
	Key_value_circle_init();//!< 键值缓冲区初始化
}


void sendFullCmd(uint8_t adress, uint8_t data) {
	I2C_Start();
	I2C_Send_Byte(adress);
	I2C_Send_Byte(data);
	I2C_Stop();

}

//without   decimal point
//  0     1    2    3   4    5    6    7    8    9    a    b    c     d   e    f     
//{0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

//with   decimal point
//  0     1    2    3   4    5    6    7    8    9    a    b    c     d   e    f   
//{0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0xf7,0xfc,0xb9,0xde,0xf9,0xf1};

#define TIME 0

#define POINT 0x80

void copyCMD(void) {
	sendFullCmd(0x48, 0x51);
	sendFullCmd(0x68, 0x7c + POINT);
	sendFullCmd(0x6A, 0x7f + POINT);
	sendFullCmd(0x6C, 0x4f + POINT);
	sendFullCmd(0x6E, 0x3f + POINT);

}

void screenAction(uint8_t *arr) {
	if (arr[1] != 0x79) {
		sendFullCmd(0x48, 0x51);
		sendFullCmd(0x68, arr[1]);
		sendFullCmd(0x6A, arr[2]);
		sendFullCmd(0x6C, arr[3]);
	}
}

#ifdef __cplusplus ///<end extern c
}
#endif

