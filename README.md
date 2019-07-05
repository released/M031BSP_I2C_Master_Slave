# M031BSP_I2C_Master_Slave
 M031BSP_I2C_Master_Slave

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

- RX flow stop at the "res == SLAVE_TRANSMIT_REPEAT_START_OR_STOP" inside the case "_state_RECEIVE_RX_" 

- Make sure to copy RX length if need to use later or it will be cleared at the "res == SLAVE_RECEIVE_ADDRESS_ACK" , check u8Temp

- TX data will be save in g_u8ToMasterData array 

- TX length will be save in g_u8ToMasterLen

- TX flow stop at the "res == SLAVE_TRANSMIT_DATA_NACK" inside the case "_state_TRANSMIT_TX_" 
