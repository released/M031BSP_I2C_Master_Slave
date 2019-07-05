/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    A project template for M031 MCU.
 *
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"



#if defined (BUILD_MASTER_I2C)	//PA12 : SCL , PA13 : SDA
void I2Cx_Master_Init(void);
void I2Cx_Master_example (void);

#elif defined (BUILD_SLAVE_I2C)	//PC1 : SCL , PC0 : SDA
void I2Cx_Slave_Init(void);
void I2Cx_Slave_example (void);
#endif


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HIRC clock (Internal RC 48MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Wait for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Select HCLK clock source as HIRC and HCLK source divider as 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Enable UART0 clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Switch UART0 clock source to HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Set PB multi-function pins for UART0 RXD=PB.12 and TXD=PB.13 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk)) |
                    (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Enable IP clock */
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HIRC, 0);


#if defined (BUILD_MASTER_I2C)	
	//I2C 0 : PC1 : SCL , PC0 : SDA
    CLK_EnableModuleClock(I2C0_MODULE);

    /* Set I2C0 multi-function pins */
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk)) |
                    (SYS_GPC_MFPL_PC0MFP_I2C0_SDA | SYS_GPC_MFPL_PC1MFP_I2C0_SCL);

	//I2C 1 : PA12 : SCL , PA13 : SDA
//    CLK_EnableModuleClock(I2C1_MODULE);

//    /* Set I2C0 multi-function pins */
//    SYS->GPA_MFPH = (SYS->GPA_MFPH & ~(SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk)) |
//                    (SYS_GPA_MFPH_PA13MFP_I2C1_SDA | SYS_GPA_MFPH_PA12MFP_I2C1_SCL);


#elif defined (BUILD_SLAVE_I2C)	//PC1 : SCL , PC0 : SDA
    CLK_EnableModuleClock(I2C0_MODULE);

    /* Set I2C0 multi-function pins */
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~(SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC0MFP_Msk)) |
                    (SYS_GPC_MFPL_PC0MFP_I2C0_SDA | SYS_GPC_MFPL_PC1MFP_I2C0_SCL);
#endif

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Lock protected registers */
    SYS_LockReg();
}

/*
 * This is a template project for M031 series MCU. Users could based on this project to create their
 * own application without worry about the IAR/Keil project settings.
 *
 * This template application uses external crystal as HCLK source and configures UART0 to print out
 * "Hello World", users may need to do extra system configuration based on their system design.
 */

int main()
{
    SYS_Init();

    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);

	printf("\r\nCLK_GetCPUFreq : %8d\r\n",CLK_GetCPUFreq());
	printf("CLK_GetHXTFreq : %8d\r\n",CLK_GetHXTFreq());
	printf("CLK_GetLXTFreq : %8d\r\n",CLK_GetLXTFreq());	
	printf("CLK_GetPCLK0Freq : %8d\r\n",CLK_GetPCLK0Freq());
	printf("CLK_GetPCLK1Freq : %8d\r\n",CLK_GetPCLK1Freq());	
	

#if defined (BUILD_MASTER_I2C)
	//I2C 0 : PC1 : SCL , PC0 : SDA
	//I2C 1 : PA12 : SCL , PA13 : SDA
	I2Cx_Master_Init();
#elif defined (BUILD_SLAVE_I2C)	//PC1 : SCL , PC0 : SDA
	I2Cx_Slave_Init();

#endif

    /* Got no where to go, just loop forever */
    while(1)
    {
#if defined (BUILD_MASTER_I2C)
		//I2C 0 : PC1 : SCL , PC0 : SDA
		//I2C 1 : PA12 : SCL , PA13 : SDA
		I2Cx_Master_example();
#elif defined (BUILD_SLAVE_I2C)	//PC1 : SCL , PC0 : SDA
		I2Cx_Slave_example();
#endif

        TIMER_Delay(TIMER0, 1000000);

    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
