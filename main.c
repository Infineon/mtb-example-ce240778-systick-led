/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Toggle LED with SysTick Timer Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
 * (c) 2024-2026, Infineon Technologies AG, or an affiliate of Infineon
 * Technologies AG. All rights reserved.
 * This software, associated documentation and materials ("Software") is
 * owned by Infineon Technologies AG or one of its affiliates ("Infineon")
 * and is protected by and subject to worldwide patent protection, worldwide
 * copyright laws, and international treaty provisions. Therefore, you may use
 * this Software only as provided in the license agreement accompanying the
 * software package from which you obtained this Software. If no license
 * agreement applies, then any use, reproduction, modification, translation, or
 * compilation of this Software is prohibited without the express written
 * permission of Infineon.
 *
 * Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
 * THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
 * SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
 * Infineon reserves the right to make changes to the Software without notice.
 * You are responsible for properly designing, programming, and testing the
 * functionality and safety of your intended application of the Software, as
 * well as complying with any legal requirements related to its use. Infineon
 * does not guarantee that the Software will be free from intrusion, data theft
 * or loss, or other breaches ("Security Breaches"), and Infineon shall have
 * no liability arising out of any Security Breaches. Unless otherwise
 * explicitly approved by Infineon, the Software may not be used in any
 * application where a failure of the Product or any consequences of the use
 * thereof can reasonably be expected to result in personal injury.
*******************************************************************************/

#include "cy_pdl.h"
#include "cybsp.h"

/*******************************************************************************
* Macros
********************************************************************************/
#define SYSTICK_RELOAD_VAL   (10000000UL)
#define SYSTICK_PERIOD_TIMES (10u)

/*******************************************************************************
* Function Prototypes
********************************************************************************/
static void toggle_led_on_systick_handler(void);

/*******************************************************************************
* Global Variables
********************************************************************************/
uint32_t counterTick = 0;

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This main achieve the systick timer interrupt function. Toggle user led when generate
* the systick interrupt up to 10 times.
*
* Return: int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    /*Initialize the User LED*/
    Cy_GPIO_Pin_Init(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, &CYBSP_USER_LED_config);

    /*Initialize the systick*/
    Cy_SysTick_Init(CY_SYSTICK_CLOCK_SOURCE_CLK_CPU, SYSTICK_RELOAD_VAL);

    /*Set Systick interrupt callback*/
    Cy_SysTick_SetCallback(0, toggle_led_on_systick_handler);

    /*Enable Systick and the Systick interrupt*/
    Cy_SysTick_Enable();


    for (;;)
    {
        /*toggle user led*/
        if(counterTick > SYSTICK_PERIOD_TIMES)
        {
            counterTick = 0;
            Cy_GPIO_Inv(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
        }
    }
}

/*******************************************************************************
* Function Name: toggle_led_on_systick_handler
********************************************************************************
*
*  Summary:
*  Systick interrupt handler
*
*  Parameters:
*  None
*
*  Return:
*  None
*
**********************************************************************************/
void toggle_led_on_systick_handler(void)
{
    counterTick++;
}

/* [] END OF FILE */
