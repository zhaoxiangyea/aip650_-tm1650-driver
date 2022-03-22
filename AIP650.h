#ifndef _AIP650_H
#define _AIP650_H

#define NULL ((void *)0)

/** Private defines ----------------------------------------------------------*/
/**  @name CPU频率 */
#define CPU_FREQUENCY_MHZ 72

#define TIME_UINT 1


//按键缓存大小
#define KEY_VALUE_BUF_MAX 		5U

//键值环形缓冲区
typedef struct Key_Value_Save
{
    uint8_t *Key_value_ptr;
    uint8_t write_index;
    uint8_t read_index;
    uint8_t left_lenth;
}Key_Value_Save_t;

// Exported macros-----------------------------------------------------------

#define SDA_Dout_LOW()          HAL_GPIO_WritePin(AIP_SDA_GPIO_Port, AIP_SDA_Pin, GPIO_PIN_RESET) 
#define SDA_Dout_HIGH()         HAL_GPIO_WritePin(AIP_SDA_GPIO_Port, AIP_SDA_Pin, GPIO_PIN_SET)
#define SDA_Data_IN()           HAL_GPIO_ReadPin(AIP_SDA_GPIO_Port,  AIP_SDA_Pin)
#define SCL_Dout_LOW()          HAL_GPIO_WritePin(AIP_SCL_GPIO_Port, AIP_SCL_Pin, GPIO_PIN_RESET) 
#define SCL_Dout_HIGH()         HAL_GPIO_WritePin(AIP_SCL_GPIO_Port, AIP_SCL_Pin, GPIO_PIN_SET)
#define SCL_Data_IN()           HAL_GPIO_ReadPin(AIP_SCL_GPIO_Port,  AIP_SCL_Pin)
#define SDA_Write(XX)           HAL_GPIO_WritePin(AIP_SDA_GPIO_Port, AIP_SDA_Pin, (XX?GPIO_PIN_SET:GPIO_PIN_RESET))

// Exported variables -------------------------------------------------------
extern Key_Value_Save_t Key_Value_History;
extern uint8_t Key_Value_Arr[];

// Exported variables -------------------------------------------------------

//void AIP_650_Init_Opt(void);
uint8_t Read_Aip650_Key_Value(void);
uint8_t CQ_Getdata(void);
void Set_LED_ON_OFF(uint32_t command);



void AIP650Init(void);

void copyCMD(void);

void sendFullCmd(uint8_t adress, uint8_t data);

void screenAction(uint8_t *arr);

#endif //_AIP650_H
