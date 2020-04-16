/*******************************************************************************
* File Name: EyelidGroup.c
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

#include "EyelidGroup.h"

/* Error message for removed <resource> through optimization */
#ifdef EyelidGroup_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* EyelidGroup_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 EyelidGroup_initVar = 0u;


/*******************************************************************************
* Function Name: EyelidGroup_Start
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
*  EyelidGroup_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void EyelidGroup_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(EyelidGroup_initVar == 0u)
    {
        EyelidGroup_Init();
        EyelidGroup_initVar = 1u;
    }
    EyelidGroup_Enable();

}


/*******************************************************************************
* Function Name: EyelidGroup_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  EyelidGroup_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void EyelidGroup_Init(void) 
{
    #if (EyelidGroup_UsingFixedFunction || EyelidGroup_UseControl)
        uint8 ctrl;
    #endif /* (EyelidGroup_UsingFixedFunction || EyelidGroup_UseControl) */

    #if(!EyelidGroup_UsingFixedFunction)
        #if(EyelidGroup_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 EyelidGroup_interruptState;
        #endif /* (EyelidGroup_UseStatus) */
    #endif /* (!EyelidGroup_UsingFixedFunction) */

    #if (EyelidGroup_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        EyelidGroup_CONTROL |= EyelidGroup_CFG0_MODE;
        #if (EyelidGroup_DeadBand2_4)
            EyelidGroup_CONTROL |= EyelidGroup_CFG0_DB;
        #endif /* (EyelidGroup_DeadBand2_4) */

        ctrl = EyelidGroup_CONTROL3 & ((uint8 )(~EyelidGroup_CTRL_CMPMODE1_MASK));
        EyelidGroup_CONTROL3 = ctrl | EyelidGroup_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        EyelidGroup_RT1 &= ((uint8)(~EyelidGroup_RT1_MASK));
        EyelidGroup_RT1 |= EyelidGroup_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        EyelidGroup_RT1 &= ((uint8)(~EyelidGroup_SYNCDSI_MASK));
        EyelidGroup_RT1 |= EyelidGroup_SYNCDSI_EN;

    #elif (EyelidGroup_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = EyelidGroup_CONTROL & ((uint8)(~EyelidGroup_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~EyelidGroup_CTRL_CMPMODE1_MASK));
        EyelidGroup_CONTROL = ctrl | EyelidGroup_DEFAULT_COMPARE2_MODE |
                                   EyelidGroup_DEFAULT_COMPARE1_MODE;
    #endif /* (EyelidGroup_UsingFixedFunction) */

    #if (!EyelidGroup_UsingFixedFunction)
        #if (EyelidGroup_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            EyelidGroup_AUX_CONTROLDP0 |= (EyelidGroup_AUX_CTRL_FIFO0_CLR);
        #else /* (EyelidGroup_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            EyelidGroup_AUX_CONTROLDP0 |= (EyelidGroup_AUX_CTRL_FIFO0_CLR);
            EyelidGroup_AUX_CONTROLDP1 |= (EyelidGroup_AUX_CTRL_FIFO0_CLR);
        #endif /* (EyelidGroup_Resolution == 8) */

        EyelidGroup_WriteCounter(EyelidGroup_INIT_PERIOD_VALUE);
    #endif /* (!EyelidGroup_UsingFixedFunction) */

    EyelidGroup_WritePeriod(EyelidGroup_INIT_PERIOD_VALUE);

        #if (EyelidGroup_UseOneCompareMode)
            EyelidGroup_WriteCompare(EyelidGroup_INIT_COMPARE_VALUE1);
        #else
            EyelidGroup_WriteCompare1(EyelidGroup_INIT_COMPARE_VALUE1);
            EyelidGroup_WriteCompare2(EyelidGroup_INIT_COMPARE_VALUE2);
        #endif /* (EyelidGroup_UseOneCompareMode) */

        #if (EyelidGroup_KillModeMinTime)
            EyelidGroup_WriteKillTime(EyelidGroup_MinimumKillTime);
        #endif /* (EyelidGroup_KillModeMinTime) */

        #if (EyelidGroup_DeadBandUsed)
            EyelidGroup_WriteDeadTime(EyelidGroup_INIT_DEAD_TIME);
        #endif /* (EyelidGroup_DeadBandUsed) */

    #if (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction)
        EyelidGroup_SetInterruptMode(EyelidGroup_INIT_INTERRUPTS_MODE);
    #endif /* (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction) */

    #if (EyelidGroup_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        EyelidGroup_GLOBAL_ENABLE |= EyelidGroup_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        EyelidGroup_CONTROL2 |= EyelidGroup_CTRL2_IRQ_SEL;
    #else
        #if(EyelidGroup_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            EyelidGroup_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            EyelidGroup_STATUS_AUX_CTRL |= EyelidGroup_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(EyelidGroup_interruptState);

            /* Clear the FIFO to enable the EyelidGroup_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            EyelidGroup_ClearFIFO();
        #endif /* (EyelidGroup_UseStatus) */
    #endif /* (EyelidGroup_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyelidGroup_Enable
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
void EyelidGroup_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (EyelidGroup_UsingFixedFunction)
        EyelidGroup_GLOBAL_ENABLE |= EyelidGroup_BLOCK_EN_MASK;
        EyelidGroup_GLOBAL_STBY_ENABLE |= EyelidGroup_BLOCK_STBY_EN_MASK;
    #endif /* (EyelidGroup_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (EyelidGroup_UseControl || EyelidGroup_UsingFixedFunction)
        EyelidGroup_CONTROL |= EyelidGroup_CTRL_ENABLE;
    #endif /* (EyelidGroup_UseControl || EyelidGroup_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyelidGroup_Stop
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
void EyelidGroup_Stop(void) 
{
    #if (EyelidGroup_UseControl || EyelidGroup_UsingFixedFunction)
        EyelidGroup_CONTROL &= ((uint8)(~EyelidGroup_CTRL_ENABLE));
    #endif /* (EyelidGroup_UseControl || EyelidGroup_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (EyelidGroup_UsingFixedFunction)
        EyelidGroup_GLOBAL_ENABLE &= ((uint8)(~EyelidGroup_BLOCK_EN_MASK));
        EyelidGroup_GLOBAL_STBY_ENABLE &= ((uint8)(~EyelidGroup_BLOCK_STBY_EN_MASK));
    #endif /* (EyelidGroup_UsingFixedFunction) */
}

#if (EyelidGroup_UseOneCompareMode)
    #if (EyelidGroup_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyelidGroup_SetCompareMode
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
        void EyelidGroup_SetCompareMode(uint8 comparemode) 
        {
            #if(EyelidGroup_UsingFixedFunction)

                #if(0 != EyelidGroup_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyelidGroup_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != EyelidGroup_CTRL_CMPMODE1_SHIFT) */

                EyelidGroup_CONTROL3 &= ((uint8)(~EyelidGroup_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                EyelidGroup_CONTROL3 |= comparemodemasked;

            #elif (EyelidGroup_UseControl)

                #if(0 != EyelidGroup_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << EyelidGroup_CTRL_CMPMODE1_SHIFT)) &
                                                EyelidGroup_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & EyelidGroup_CTRL_CMPMODE1_MASK;
                #endif /* (0 != EyelidGroup_CTRL_CMPMODE1_SHIFT) */

                #if(0 != EyelidGroup_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << EyelidGroup_CTRL_CMPMODE2_SHIFT)) &
                                               EyelidGroup_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & EyelidGroup_CTRL_CMPMODE2_MASK;
                #endif /* (0 != EyelidGroup_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                EyelidGroup_CONTROL &= ((uint8)(~(EyelidGroup_CTRL_CMPMODE1_MASK |
                                            EyelidGroup_CTRL_CMPMODE2_MASK)));
                EyelidGroup_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (EyelidGroup_UsingFixedFunction) */
        }
    #endif /* EyelidGroup_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (EyelidGroup_CompareMode1SW)


        /*******************************************************************************
        * Function Name: EyelidGroup_SetCompareMode1
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
        void EyelidGroup_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != EyelidGroup_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyelidGroup_CTRL_CMPMODE1_SHIFT)) &
                                           EyelidGroup_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & EyelidGroup_CTRL_CMPMODE1_MASK;
            #endif /* (0 != EyelidGroup_CTRL_CMPMODE1_SHIFT) */

            #if (EyelidGroup_UseControl)
                EyelidGroup_CONTROL &= ((uint8)(~EyelidGroup_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                EyelidGroup_CONTROL |= comparemodemasked;
            #endif /* (EyelidGroup_UseControl) */
        }
    #endif /* EyelidGroup_CompareMode1SW */

#if (EyelidGroup_CompareMode2SW)


    /*******************************************************************************
    * Function Name: EyelidGroup_SetCompareMode2
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
    void EyelidGroup_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != EyelidGroup_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << EyelidGroup_CTRL_CMPMODE2_SHIFT)) &
                                                 EyelidGroup_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & EyelidGroup_CTRL_CMPMODE2_MASK;
        #endif /* (0 != EyelidGroup_CTRL_CMPMODE2_SHIFT) */

        #if (EyelidGroup_UseControl)
            EyelidGroup_CONTROL &= ((uint8)(~EyelidGroup_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            EyelidGroup_CONTROL |= comparemodemasked;
        #endif /* (EyelidGroup_UseControl) */
    }
    #endif /*EyelidGroup_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!EyelidGroup_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteCounter
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
    void EyelidGroup_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(EyelidGroup_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadCounter
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
    uint16 EyelidGroup_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(EyelidGroup_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(EyelidGroup_CAPTURE_LSB_PTR));
    }

    #if (EyelidGroup_UseStatus)


        /*******************************************************************************
        * Function Name: EyelidGroup_ClearFIFO
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
        void EyelidGroup_ClearFIFO(void) 
        {
            while(0u != (EyelidGroup_ReadStatusRegister() & EyelidGroup_STATUS_FIFONEMPTY))
            {
                (void)EyelidGroup_ReadCapture();
            }
        }

    #endif /* EyelidGroup_UseStatus */

#endif /* !EyelidGroup_UsingFixedFunction */


/*******************************************************************************
* Function Name: EyelidGroup_WritePeriod
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
void EyelidGroup_WritePeriod(uint16 period) 
{
    #if(EyelidGroup_UsingFixedFunction)
        CY_SET_REG16(EyelidGroup_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(EyelidGroup_PERIOD_LSB_PTR, period);
    #endif /* (EyelidGroup_UsingFixedFunction) */
}

#if (EyelidGroup_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteCompare
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
    void EyelidGroup_WriteCompare(uint16 compare) \
                                       
    {
        #if(EyelidGroup_UsingFixedFunction)
            CY_SET_REG16(EyelidGroup_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyelidGroup_COMPARE1_LSB_PTR, compare);
        #endif /* (EyelidGroup_UsingFixedFunction) */

        #if (EyelidGroup_PWMMode == EyelidGroup__B_PWM__DITHER)
            #if(EyelidGroup_UsingFixedFunction)
                CY_SET_REG16(EyelidGroup_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(EyelidGroup_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (EyelidGroup_UsingFixedFunction) */
        #endif /* (EyelidGroup_PWMMode == EyelidGroup__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteCompare1
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
    void EyelidGroup_WriteCompare1(uint16 compare) \
                                        
    {
        #if(EyelidGroup_UsingFixedFunction)
            CY_SET_REG16(EyelidGroup_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(EyelidGroup_COMPARE1_LSB_PTR, compare);
        #endif /* (EyelidGroup_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteCompare2
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
    void EyelidGroup_WriteCompare2(uint16 compare) \
                                        
    {
        #if(EyelidGroup_UsingFixedFunction)
            CY_SET_REG16(EyelidGroup_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(EyelidGroup_COMPARE2_LSB_PTR, compare);
        #endif /* (EyelidGroup_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (EyelidGroup_DeadBandUsed)


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteDeadTime
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
    void EyelidGroup_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!EyelidGroup_DeadBand2_4)
            CY_SET_REG8(EyelidGroup_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            EyelidGroup_DEADBAND_COUNT &= ((uint8)(~EyelidGroup_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(EyelidGroup_DEADBAND_COUNT_SHIFT)
                EyelidGroup_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << EyelidGroup_DEADBAND_COUNT_SHIFT)) &
                                                    EyelidGroup_DEADBAND_COUNT_MASK;
            #else
                EyelidGroup_DEADBAND_COUNT |= deadtime & EyelidGroup_DEADBAND_COUNT_MASK;
            #endif /* (EyelidGroup_DEADBAND_COUNT_SHIFT) */

        #endif /* (!EyelidGroup_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadDeadTime
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
    uint8 EyelidGroup_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!EyelidGroup_DeadBand2_4)
            return (CY_GET_REG8(EyelidGroup_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(EyelidGroup_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(EyelidGroup_DEADBAND_COUNT & EyelidGroup_DEADBAND_COUNT_MASK)) >>
                                                                           EyelidGroup_DEADBAND_COUNT_SHIFT));
            #else
                return (EyelidGroup_DEADBAND_COUNT & EyelidGroup_DEADBAND_COUNT_MASK);
            #endif /* (EyelidGroup_DEADBAND_COUNT_SHIFT) */
        #endif /* (!EyelidGroup_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyelidGroup_SetInterruptMode
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
    void EyelidGroup_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(EyelidGroup_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadStatusRegister
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
    uint8 EyelidGroup_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(EyelidGroup_STATUS_PTR));
    }

#endif /* (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction) */


#if (EyelidGroup_UseControl)


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadControlRegister
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
    uint8 EyelidGroup_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(EyelidGroup_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteControlRegister
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
    void EyelidGroup_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(EyelidGroup_CONTROL_PTR, control);
    }

#endif /* (EyelidGroup_UseControl) */


#if (!EyelidGroup_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadCapture
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
    uint16 EyelidGroup_ReadCapture(void) 
    {
        return (CY_GET_REG16(EyelidGroup_CAPTURE_LSB_PTR));
    }

#endif /* (!EyelidGroup_UsingFixedFunction) */


#if (EyelidGroup_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadCompare
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
    uint16 EyelidGroup_ReadCompare(void) 
    {
        #if(EyelidGroup_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(EyelidGroup_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(EyelidGroup_COMPARE1_LSB_PTR));
        #endif /* (EyelidGroup_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadCompare1
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
    uint16 EyelidGroup_ReadCompare1(void) 
    {
        return (CY_GET_REG16(EyelidGroup_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadCompare2
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
    uint16 EyelidGroup_ReadCompare2(void) 
    {
        return (CY_GET_REG16(EyelidGroup_COMPARE2_LSB_PTR));
    }

#endif /* (EyelidGroup_UseOneCompareMode) */


/*******************************************************************************
* Function Name: EyelidGroup_ReadPeriod
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
uint16 EyelidGroup_ReadPeriod(void) 
{
    #if(EyelidGroup_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(EyelidGroup_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(EyelidGroup_PERIOD_LSB_PTR));
    #endif /* (EyelidGroup_UsingFixedFunction) */
}

#if ( EyelidGroup_KillModeMinTime)


    /*******************************************************************************
    * Function Name: EyelidGroup_WriteKillTime
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
    void EyelidGroup_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(EyelidGroup_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: EyelidGroup_ReadKillTime
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
    uint8 EyelidGroup_ReadKillTime(void) 
    {
        return (CY_GET_REG8(EyelidGroup_KILLMODEMINTIME_PTR));
    }

#endif /* ( EyelidGroup_KillModeMinTime) */

/* [] END OF FILE */
