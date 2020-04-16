/*******************************************************************************
* File Name: EyeBallHorizontal.c
* Version 3.30
*
* Description:
*  The PWM User Module consist of an 8 or 16-bit counter with two 8 or 16-bit
*  comparitors. Each instance of this user module is capable of generating
*  two PWM outputs with the same period. The pulse width is selectable between
*  1 and 255/65535. The period is selectable between 2 and 255/65536 clocks.
*  The compare value output may be configured to be active when the present
*  counter is less than or less than/equal to the compare value.
*  A terminal count output is also provided. It generates a pulse one clock
*  width wide when the counter is equal to zero.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "EyeBallHorizontal.h"

/* Error message for removed <resource> through optimization */
#ifdef EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 EyeBallHorizontal_initVar = 0u;


/*******************************************************************************
* Function Name: EyeBallHorizontal_Start
********************************************************************************
*
* Summary:
*  The start function initializes the pwm with the default values, the
*  enables the counter to begin counting.  It does not enable interrupts,
*  the EnableInt command should be called if interrupt generation is required.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  EyeBallHorizontal_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void EyeBallHorizontal_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(EyeBallHorizontal_initVar == 0u)
    {
        EyeBallHorizontal_Init();
        EyeBallHorizontal_initVar = 1u;
    }
    EyeBallHorizontal_Enable();

}


/*******************************************************************************
* Function Name: EyeBallHorizontal_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  EyeBallHorizontal_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EyeBallHorizontal_Init(void) 
{
    #if (EyeBallHorizontal_UsingFixedFunction || EyeBallHorizontal_UseControl)
        uint8 ctrl;
    #endif /* (EyeBallHorizontal_UsingFixedFunction || EyeBallHorizontal_UseControl) */

    #if(!EyeBallHorizontal_UsingFixedFunction)
        #if(EyeBallHorizontal_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 EyeBallHorizontal_interruptState;
        #endif /* (EyeBallHorizontal_UseStatus) */
    #endif /* (!EyeBallHorizontal_UsingFixedFunction) */

    #if (EyeBallHorizontal_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        EyeBallHorizontal_CONTROL |= EyeBallHorizontal_CFG0_MODE;
        #if (EyeBallHorizontal_DeadBand2_4)
            EyeBallHorizontal_CONTROL |= EyeBallHorizontal_CFG0_DB;
        #endif /* (EyeBallHorizontal_DeadBand2_4) */

        ctrl = EyeBallHorizontal_CONTROL3 & ((uint8 )(~EyeBallHorizontal_CTRL_CMPMODE1_MASK));
        EyeBallHorizontal_CONTROL3 = ctrl | EyeBallHorizontal_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        EyeBallHorizontal_RT1 &= ((uint8)(~EyeBallHorizontal_RT1_MASK));
        EyeBallHorizontal_RT1 |= EyeBallHorizontal_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        EyeBallHorizontal_RT1 &= ((uint8)(~EyeBallHorizontal_SYNCDSI_MASK));
        EyeBallHorizontal_RT1 |= EyeBallHorizontal_SYNCDSI_EN;

    #elif (EyeBallHorizontal_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = EyeBallHorizontal_CONTROL & ((uint8)(~EyeBallHorizontal_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~EyeBallHorizontal_CTRL_CMPMODE1_MASK));
        EyeBallHorizontal_CONTROL = ctrl | EyeBallHorizontal_DEFAULT_COMPARE2_MODE |
                                   EyeBallHorizontal_DEFAULT_COMPARE1_MODE;
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */

    #if (!EyeBallHorizontal_UsingFixedFunction)
        #if (EyeBallHorizontal_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            EyeBallHorizontal_AUX_CONTROLDP0 |= (EyeBallHorizontal_AUX_CTRL_FIFO0_CLR);
        #else /* (EyeBallHorizontal_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            EyeBallHorizontal_AUX_CONTROLDP0 |= (EyeBallHorizontal_AUX_CTRL_FIFO0_CLR);
            EyeBallHorizontal_AUX_CONTROLDP1 |= (EyeBallHorizontal_AUX_CTRL_FIFO0_CLR);
        #endif /* (EyeBallHorizontal_Resolution == 8) */

        EyeBallHorizontal_WriteCounter(EyeBallHorizontal_INIT_PERIOD_VALUE);
    #endif /* (!EyeBallHorizontal_UsingFixedFunction) */

    EyeBallHorizontal_WritePeriod(EyeBallHorizontal_INIT_PERIOD_VALUE);

        #if (EyeBallHorizontal_UseOneCompareMode)
            EyeBallHorizontal_WriteCompare(EyeBallHorizontal_INIT_COMPARE_VALUE1);
        #else
            EyeBallHorizontal_WriteCompare1(EyeBallHorizontal_INIT_COMPARE_VALUE1);
            EyeBallHorizontal_WriteCompare2(EyeBallHorizontal_INIT_COMPARE_VALUE2);
        #endif /* (EyeBallHorizontal_UseOneCompareMode) */

        #if (EyeBallHorizontal_KillModeMinTime)
            EyeBallHorizontal_WriteKillTime(EyeBallHorizontal_MinimumKillTime);
        #endif /* (EyeBallHorizontal_KillModeMinTime) */

        #if (EyeBallHorizontal_DeadBandUsed)
            EyeBallHorizontal_WriteDeadTime(EyeBallHorizontal_INIT_DEAD_TIME);
        #endif /* (EyeBallHorizontal_DeadBandUsed) */

    #if (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction)
        EyeBallHorizontal_SetInterruptMode(EyeBallHorizontal_INIT_INTERRUPTS_MODE);
    #endif /* (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction) */

    #if (EyeBallHorizontal_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        EyeBallHorizontal_GLOBAL_ENABLE |= EyeBallHorizontal_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        EyeBallHorizontal_CONTROL2 |= EyeBallHorizontal_CTRL2_IRQ_SEL;
    #else
        #if(EyeBallHorizontal_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            EyeBallHorizontal_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            EyeBallHorizontal_STATUS_AUX_CTRL |= EyeBallHorizontal_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(EyeBallHorizontal_interruptState);

            /* Clear the FIFO to enable the EyeBallHorizontal_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            EyeBallHorizontal_ClearFIFO();
        #endif /* (EyeBallHorizontal_UseStatus) */
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeBallHorizontal_Enable
********************************************************************************
*
* Summary:
*  Enables the PWM block operation
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  This works only if software enable mode is chosen
*
*******************************************************************************/
void EyeBallHorizontal_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (EyeBallHorizontal_UsingFixedFunction)
        EyeBallHorizontal_GLOBAL_ENABLE |= EyeBallHorizontal_BLOCK_EN_MASK;
        EyeBallHorizontal_GLOBAL_STBY_ENABLE |= EyeBallHorizontal_BLOCK_STBY_EN_MASK;
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (EyeBallHorizontal_UseControl || EyeBallHorizontal_UsingFixedFunction)
        EyeBallHorizontal_CONTROL |= EyeBallHorizontal_CTRL_ENABLE;
    #endif /* (EyeBallHorizontal_UseControl || EyeBallHorizontal_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeBallHorizontal_Stop
********************************************************************************
*
* Summary:
*  The stop function halts the PWM, but does not change any modes or disable
*  interrupts.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If the Enable mode is set to Hardware only then this function
*  has no effect on the operation of the PWM
*
*******************************************************************************/
void EyeBallHorizontal_Stop(void) 
{
    #if (EyeBallHorizontal_UseControl || EyeBallHorizontal_UsingFixedFunction)
        EyeBallHorizontal_CONTROL &= ((uint8)(~EyeBallHorizontal_CTRL_ENABLE));
    #endif /* (EyeBallHorizontal_UseControl || EyeBallHorizontal_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (EyeBallHorizontal_UsingFixedFunction)
        EyeBallHorizontal_GLOBAL_ENABLE &= ((uint8)(~EyeBallHorizontal_BLOCK_EN_MASK));
        EyeBallHorizontal_GLOBAL_STBY_ENABLE &= ((uint8)(~EyeBallHorizontal_BLOCK_STBY_EN_MASK));
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */
}

#if (EyeBallHorizontal_UseOneCompareMode)
    #if (EyeBallHorizontal_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyeBallHorizontal_SetCompareMode
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm output when in Dither mode,
        *  Center Align Mode or One Output Mode.
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeBallHorizontal_SetCompareMode(uint8 comparemode) 
        {
            #if(EyeBallHorizontal_UsingFixedFunction)

                #if(0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeBallHorizontal_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT) */

                EyeBallHorizontal_CONTROL3 &= ((uint8)(~EyeBallHorizontal_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                EyeBallHorizontal_CONTROL3 |= comparemodemasked;

            #elif (EyeBallHorizontal_UseControl)

                #if(0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)) &
                                                EyeBallHorizontal_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & EyeBallHorizontal_CTRL_CMPMODE1_MASK;
                #endif /* (0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT) */

                #if(0 != EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)) &
                                               EyeBallHorizontal_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & EyeBallHorizontal_CTRL_CMPMODE2_MASK;
                #endif /* (0 != EyeBallHorizontal_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                EyeBallHorizontal_CONTROL &= ((uint8)(~(EyeBallHorizontal_CTRL_CMPMODE1_MASK |
                                            EyeBallHorizontal_CTRL_CMPMODE2_MASK)));
                EyeBallHorizontal_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (EyeBallHorizontal_UsingFixedFunction) */
        }
    #endif /* EyeBallHorizontal_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (EyeBallHorizontal_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyeBallHorizontal_SetCompareMode1
        ********************************************************************************
        *
        * Summary:
        *  This function writes the Compare Mode for the pwm or pwm1 output
        *
        * Parameters:
        *  comparemode:  The new compare mode for the PWM output. Use the compare types
        *                defined in the H file as input arguments.
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeBallHorizontal_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)) &
                                           EyeBallHorizontal_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & EyeBallHorizontal_CTRL_CMPMODE1_MASK;
            #endif /* (0 != EyeBallHorizontal_CTRL_CMPMODE1_SHIFT) */

            #if (EyeBallHorizontal_UseControl)
                EyeBallHorizontal_CONTROL &= ((uint8)(~EyeBallHorizontal_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                EyeBallHorizontal_CONTROL |= comparemodemasked;
            #endif /* (EyeBallHorizontal_UseControl) */
        }
    #endif /* EyeBallHorizontal_CompareMode1SW */

#if (EyeBallHorizontal_CompareMode2SW)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_SetCompareMode2
    ********************************************************************************
    *
    * Summary:
    *  This function writes the Compare Mode for the pwm or pwm2 output
    *
    * Parameters:
    *  comparemode:  The new compare mode for the PWM output. Use the compare types
    *                defined in the H file as input arguments.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)) &
                                                 EyeBallHorizontal_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & EyeBallHorizontal_CTRL_CMPMODE2_MASK;
        #endif /* (0 != EyeBallHorizontal_CTRL_CMPMODE2_SHIFT) */

        #if (EyeBallHorizontal_UseControl)
            EyeBallHorizontal_CONTROL &= ((uint8)(~EyeBallHorizontal_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            EyeBallHorizontal_CONTROL |= comparemodemasked;
        #endif /* (EyeBallHorizontal_UseControl) */
    }
    #endif /*EyeBallHorizontal_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!EyeBallHorizontal_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteCounter
    ********************************************************************************
    *
    * Summary:
    *  Writes a new counter value directly to the counter register. This will be
    *  implemented for that currently running period and only that period. This API
    *  is valid only for UDB implementation and not available for fixed function
    *  PWM implementation.
    *
    * Parameters:
    *  counter:  The period new period counter value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  The PWM Period will be reloaded when a counter value will be a zero
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(EyeBallHorizontal_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadCounter
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current value of the counter.  It doesn't matter
    *  if the counter is enabled or running.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  The current value of the counter.
    *
    *******************************************************************************/
    uint16 EyeBallHorizontal_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(EyeBallHorizontal_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(EyeBallHorizontal_CAPTURE_LSB_PTR));
    }

    #if (EyeBallHorizontal_UseStatus)


        /*******************************************************************************
        * Function Name: EyeBallHorizontal_ClearFIFO
        ********************************************************************************
        *
        * Summary:
        *  This function clears all capture data from the capture FIFO
        *
        * Parameters:
        *  None
        *
        * Return:
        *  None
        *
        *******************************************************************************/
        void EyeBallHorizontal_ClearFIFO(void) 
        {
            while(0u != (EyeBallHorizontal_ReadStatusRegister() & EyeBallHorizontal_STATUS_FIFONEMPTY))
            {
                (void)EyeBallHorizontal_ReadCapture();
            }
        }

    #endif /* EyeBallHorizontal_UseStatus */

#endif /* !EyeBallHorizontal_UsingFixedFunction */


/*******************************************************************************
* Function Name: EyeBallHorizontal_WritePeriod
********************************************************************************
*
* Summary:
*  This function is used to change the period of the counter.  The new period
*  will be loaded the next time terminal count is detected.
*
* Parameters:
*  period:  Period value. May be between 1 and (2^Resolution)-1.  A value of 0
*           will result in the counter remaining at zero.
*
* Return:
*  None
*
*******************************************************************************/
void EyeBallHorizontal_WritePeriod(uint16 period) 
{
    #if(EyeBallHorizontal_UsingFixedFunction)
        CY_SET_REG16(EyeBallHorizontal_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(EyeBallHorizontal_PERIOD_LSB_PTR, period);
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */
}

#if (EyeBallHorizontal_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteCompare
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value when the PWM is in Dither
    *  mode. The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  compared to the compare value based on the compare mode defined in
    *  Dither Mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    * Side Effects:
    *  This function is only available if the PWM mode parameter is set to
    *  Dither Mode, Center Aligned Mode or One Output Mode
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteCompare(uint16 compare) \
                                       
    {
        #if(EyeBallHorizontal_UsingFixedFunction)
            CY_SET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR, compare);
        #endif /* (EyeBallHorizontal_UsingFixedFunction) */

        #if (EyeBallHorizontal_PWMMode == EyeBallHorizontal__B_PWM__DITHER)
            #if(EyeBallHorizontal_UsingFixedFunction)
                CY_SET_REG16(EyeBallHorizontal_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(EyeBallHorizontal_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (EyeBallHorizontal_UsingFixedFunction) */
        #endif /* (EyeBallHorizontal_PWMMode == EyeBallHorizontal__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteCompare1
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare1 value.  The compare output will
    *  reflect the new value on the next UDB clock.  The compare output will be
    *  driven high when the present counter value is less than or less than or
    *  equal to the compare register, depending on the mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteCompare1(uint16 compare) \
                                        
    {
        #if(EyeBallHorizontal_UsingFixedFunction)
            CY_SET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR, compare);
        #endif /* (EyeBallHorizontal_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteCompare2
    ********************************************************************************
    *
    * Summary:
    *  This funtion is used to change the compare value, for compare1 output.
    *  The compare output will reflect the new value on the next UDB clock.
    *  The compare output will be driven high when the present counter value is
    *  less than or less than or equal to the compare register, depending on the
    *  mode.
    *
    * Parameters:
    *  compare:  New compare value.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteCompare2(uint16 compare) \
                                        
    {
        #if(EyeBallHorizontal_UsingFixedFunction)
            CY_SET_REG16(EyeBallHorizontal_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(EyeBallHorizontal_COMPARE2_LSB_PTR, compare);
        #endif /* (EyeBallHorizontal_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (EyeBallHorizontal_DeadBandUsed)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function writes the dead-band counts to the corresponding register
    *
    * Parameters:
    *  deadtime:  Number of counts for dead time
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!EyeBallHorizontal_DeadBand2_4)
            CY_SET_REG8(EyeBallHorizontal_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            EyeBallHorizontal_DEADBAND_COUNT &= ((uint8)(~EyeBallHorizontal_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(EyeBallHorizontal_DEADBAND_COUNT_SHIFT)
                EyeBallHorizontal_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << EyeBallHorizontal_DEADBAND_COUNT_SHIFT)) &
                                                    EyeBallHorizontal_DEADBAND_COUNT_MASK;
            #else
                EyeBallHorizontal_DEADBAND_COUNT |= deadtime & EyeBallHorizontal_DEADBAND_COUNT_MASK;
            #endif /* (EyeBallHorizontal_DEADBAND_COUNT_SHIFT) */

        #endif /* (!EyeBallHorizontal_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadDeadTime
    ********************************************************************************
    *
    * Summary:
    *  This function reads the dead-band counts from the corresponding register
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Dead Band Counts
    *
    *******************************************************************************/
    uint8 EyeBallHorizontal_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!EyeBallHorizontal_DeadBand2_4)
            return (CY_GET_REG8(EyeBallHorizontal_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(EyeBallHorizontal_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(EyeBallHorizontal_DEADBAND_COUNT & EyeBallHorizontal_DEADBAND_COUNT_MASK)) >>
                                                                           EyeBallHorizontal_DEADBAND_COUNT_SHIFT));
            #else
                return (EyeBallHorizontal_DEADBAND_COUNT & EyeBallHorizontal_DEADBAND_COUNT_MASK);
            #endif /* (EyeBallHorizontal_DEADBAND_COUNT_SHIFT) */
        #endif /* (!EyeBallHorizontal_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_SetInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  This function configures the interrupts mask control of theinterrupt
    *  source status register.
    *
    * Parameters:
    *  uint8 interruptMode: Bit field containing the interrupt sources enabled
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(EyeBallHorizontal_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadStatusRegister
    ********************************************************************************
    *
    * Summary:
    *  This function returns the current state of the status register.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current status register value. The status register bits are:
    *  [7:6] : Unused(0)
    *  [5]   : Kill event output
    *  [4]   : FIFO not empty
    *  [3]   : FIFO full
    *  [2]   : Terminal count
    *  [1]   : Compare output 2
    *  [0]   : Compare output 1
    *
    *******************************************************************************/
    uint8 EyeBallHorizontal_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(EyeBallHorizontal_STATUS_PTR));
    }

#endif /* (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction) */


#if (EyeBallHorizontal_UseControl)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the control register. This API is available
    *  only if the control register is not removed.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8 : Current control register value
    *
    *******************************************************************************/
    uint8 EyeBallHorizontal_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(EyeBallHorizontal_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteControlRegister
    ********************************************************************************
    *
    * Summary:
    *  Sets the bit field of the control register. This API is available only if
    *  the control register is not removed.
    *
    * Parameters:
    *  uint8 control: Control register bit field, The status register bits are:
    *  [7]   : PWM Enable
    *  [6]   : Reset
    *  [5:3] : Compare Mode2
    *  [2:0] : Compare Mode2
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(EyeBallHorizontal_CONTROL_PTR, control);
    }

#endif /* (EyeBallHorizontal_UseControl) */


#if (!EyeBallHorizontal_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadCapture
    ********************************************************************************
    *
    * Summary:
    *  Reads the capture value from the capture FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: The current capture value
    *
    *******************************************************************************/
    uint16 EyeBallHorizontal_ReadCapture(void) 
    {
        return (CY_GET_REG16(EyeBallHorizontal_CAPTURE_LSB_PTR));
    }

#endif /* (!EyeBallHorizontal_UsingFixedFunction) */


#if (EyeBallHorizontal_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadCompare
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare output when the PWM Mode parameter is
    *  set to Dither mode, Center Aligned mode, or One Output mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value
    *
    *******************************************************************************/
    uint16 EyeBallHorizontal_ReadCompare(void) 
    {
        #if(EyeBallHorizontal_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR));
        #endif /* (EyeBallHorizontal_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadCompare1
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare1 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 EyeBallHorizontal_ReadCompare1(void) 
    {
        return (CY_GET_REG16(EyeBallHorizontal_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadCompare2
    ********************************************************************************
    *
    * Summary:
    *  Reads the compare value for the compare2 output.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8/uint16: Current compare value.
    *
    *******************************************************************************/
    uint16 EyeBallHorizontal_ReadCompare2(void) 
    {
        return (CY_GET_REG16(EyeBallHorizontal_COMPARE2_LSB_PTR));
    }

#endif /* (EyeBallHorizontal_UseOneCompareMode) */


/*******************************************************************************
* Function Name: EyeBallHorizontal_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the period value used by the PWM hardware.
*
* Parameters:
*  None
*
* Return:
*  uint8/16: Period value
*
*******************************************************************************/
uint16 EyeBallHorizontal_ReadPeriod(void) 
{
    #if(EyeBallHorizontal_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(EyeBallHorizontal_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(EyeBallHorizontal_PERIOD_LSB_PTR));
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */
}

#if ( EyeBallHorizontal_KillModeMinTime)


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_WriteKillTime
    ********************************************************************************
    *
    * Summary:
    *  Writes the kill time value used by the hardware when the Kill Mode
    *  is set to Minimum Time.
    *
    * Parameters:
    *  uint8: Minimum Time kill counts
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void EyeBallHorizontal_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(EyeBallHorizontal_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: EyeBallHorizontal_ReadKillTime
    ********************************************************************************
    *
    * Summary:
    *  Reads the kill time value used by the hardware when the Kill Mode is set
    *  to Minimum Time.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  uint8: The current Minimum Time kill counts
    *
    *******************************************************************************/
    uint8 EyeBallHorizontal_ReadKillTime(void) 
    {
        return (CY_GET_REG8(EyeBallHorizontal_KILLMODEMINTIME_PTR));
    }

#endif /* ( EyeBallHorizontal_KillModeMinTime) */

/* [] END OF FILE */
