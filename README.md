# M031BSP_I2C_Master_Slave
 M031BSP_I2C_Master_Slave

update @ 2019/07/12

##In Slave side , seperate state machine with I2C_ReadMultiBytes and I2C_ReadMultiBytesOneReg case

when use I2C_ReadMultiBytes , ack will be 0xA8 > 0xB8 > 0xB8 > ... > 0xC0

when use I2C_ReadMultiBytesOneReg , ack will be 0x60 > 0x80 > 0xA0 > 0xA8 > 0xB8 > 0xB8 > ... > 0xC0

when using RX without send TX data , will be no data transfer

- In terminal (ex : teraterm) , when press (master side)

- digit 1 (TX) : Master write customize data

- digit 2 (RX): Master request to read data from slave , with I2C_ReadMultiBytesOneReg

- digit 7 (RX): Master request to read data from slave , with I2C_ReadMultiBytes

- digit 3 (TX): write customize data , with customise register , also include DataCnt increase 10 per press , and reset to 0 after 100

- digit 4 (TX): write customize data , with customise register , multi data

- digit 5 (TX): write customize data , with customise register , multi data

- digit 6 (TX+RX): write customize data and request to read data , I2C_WriteMultiBytes + I2C_ReadMultiBytes

- digit 9 (TX+RX): Master write then read , I2C_WriteMultiBytesOneReg + I2C_ReadMultiBytesOneReg


update @ 2019/07/09

##In Master side , add UART RX IRQ , by using terminal command to test Master I2C command send to Slave

- Add I2Cx_Master_example , 

- In terminal (ex : teraterm) , when press 

- digit 1 : Master write customize data , 2 : Master request to read data from slave , 9 : Master write then read

- digit 3 : write customize data , with customise register , also include DataCnt increase 10 per press , and reset to 0 after 100

- digit 4 , 5  : write customize data , with customise register , multi data

- digit 6 : write customize data and request to read data

update @ 2019/07/05

##In KeilC , use 2 project to separate Master and Slave (#define BUILD_MASTER_I2C , BUILD_SLAVE_I2C)

##Use 2 PCs M031 EVM with I2C SCL/SDA pull high external , both EVM use I2C0 => PC1 : SCL , PC0 : SDA

##check define MASTER_I2C_USE_IRQ , MASTER_I2C_USE_POLLING , for different master I2C TX/RX flow

##Master behavior 

- send TX data to Slave then following with RX to read from Slave by using below parameter

- address : 0x15 

- set register : 0x66 

- data length : 10 

- customize data array 

##Slave behavior

- only interrupt available , 

- within the I2Cx_SlaveTRx , Insert I2Cx_Slave_StateMachine for customise the TX/RX data

- RX data will be save in g_u8FromMasterData array 

- RX length will be save in g_u8FromMasterLen

- RX flow stop at the "SLAVE_TRANSMIT_REPEAT_START_OR_STOP" inside the case "_state_RECEIVE_RX_" 

- Make sure to copy RX length if need to use later or it will be cleared at the "res == SLAVE_RECEIVE_ADDRESS_ACK" , check u8Temp

- TX data will be save in g_u8ToMasterData array 

- TX length will be save in g_u8ToMasterLen

- TX flow stop at the "SLAVE_TRANSMIT_DATA_NACK" inside the case "_state_TRANSMIT_TX_" 

- For Slave example , after receive data from Master , swap the order and output to Master , check I2C_LEFT_Master_Right_Slave_up_RX_down_TX_with_swap.jpg
