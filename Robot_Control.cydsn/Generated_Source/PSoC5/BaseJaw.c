/*******************************************************************************
* File Name: BaseJaw.c
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

#include "BaseJaw.h"

/* Error message for removed <resource> through optimization */
#ifdef BaseJaw_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* BaseJaw_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 BaseJaw_initVar = 0u;


/*******************************************************************************
* Function Name: BaseJaw_Start
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
*  BaseJaw_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void BaseJaw_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(BaseJaw_initVar == 0u)
    {
        BaseJaw_Init();
        BaseJaw_initVar = 1u;
    }
    BaseJaw_Enable();

}


/*******************************************************************************
* Function Name: BaseJaw_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  BaseJaw_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void BaseJaw_Init(void) 
{
    #if (BaseJaw_UsingFixedFunction || BaseJaw_UseControl)
        uint8 ctrl;
    #endif /* (BaseJaw_UsingFixedFunction || BaseJaw_UseControl) */

    #if(!BaseJaw_UsingFixedFunction)
        #if(BaseJaw_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 BaseJaw_interruptState;
        #endif /* (BaseJaw_UseStatus) */
    #endif /* (!BaseJaw_UsingFixedFunction) */

    #if (BaseJaw_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        BaseJaw_CONTROL |= BaseJaw_CFG0_MODE;
        #if (BaseJaw_DeadBand2_4)
            BaseJaw_CONTROL |= BaseJaw_CFG0_DB;
        #endif /* (BaseJaw_DeadBand2_4) */

        ctrl = BaseJaw_CONTROL3 & ((uint8 )(~BaseJaw_CTRL_CMPMODE1_MASK));
        BaseJaw_CONTROL3 = ctrl | BaseJaw_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        BaseJaw_RT1 &= ((uint8)(~BaseJaw_RT1_MASK));
        BaseJaw_RT1 |= BaseJaw_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        BaseJaw_RT1 &= ((uint8)(~BaseJaw_SYNCDSI_MASK));
        BaseJaw_RT1 |= BaseJaw_SYNCDSI_EN;

    #elif (BaseJaw_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = BaseJaw_CONTROL & ((uint8)(~BaseJaw_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~BaseJaw_CTRL_CMPMODE1_MASK));
        BaseJaw_CONTROL = ctrl | BaseJaw_DEFAULT_COMPARE2_MODE |
                                   BaseJaw_DEFAULT_COMPARE1_MODE;
    #endif /* (BaseJaw_UsingFixedFunction) */

    #if (!BaseJaw_UsingFixedFunction)
        #if (BaseJaw_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            BaseJaw_AUX_CONTROLDP0 |= (BaseJaw_AUX_CTRL_FIFO0_CLR);
        #else /* (BaseJaw_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            BaseJaw_AUX_CONTROLDP0 |= (BaseJaw_AUX_CTRL_FIFO0_CLR);
            BaseJaw_AUX_CONTROLDP1 |= (BaseJaw_AUX_CTRL_FIFO0_CLR);
        #endif /* (BaseJaw_Resolution == 8) */

        BaseJaw_WriteCounter(BaseJaw_INIT_PERIOD_VALUE);
    #endif /* (!BaseJaw_UsingFixedFunction) */

    BaseJaw_WritePeriod(BaseJaw_INIT_PERIOD_VALUE);

        #if (BaseJaw_UseOneCompareMode)
            BaseJaw_WriteCompare(BaseJaw_INIT_COMPARE_VALUE1);
        #else
            BaseJaw_WriteCompare1(BaseJaw_INIT_COMPARE_VALUE1);
            BaseJaw_WriteCompare2(BaseJaw_INIT_COMPARE_VALUE2);
        #endif /* (BaseJaw_UseOneCompareMode) */

        #if (BaseJaw_KillModeMinTime)
            BaseJaw_WriteKillTime(BaseJaw_MinimumKillTime);
        #endif /* (BaseJaw_KillModeMinTime) */

        #if (BaseJaw_DeadBandUsed)
            BaseJaw_WriteDeadTime(BaseJaw_INIT_DEAD_TIME);
        #endif /* (BaseJaw_DeadBandUsed) */

    #if (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction)
        BaseJaw_SetInterruptMode(BaseJaw_INIT_INTERRUPTS_MODE);
    #endif /* (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction) */

    #if (BaseJaw_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        BaseJaw_GLOBAL_ENABLE |= BaseJaw_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        BaseJaw_CONTROL2 |= BaseJaw_CTRL2_IRQ_SEL;
    #else
        #if(BaseJaw_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            BaseJaw_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            BaseJaw_STATUS_AUX_CTRL |= BaseJaw_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(BaseJaw_interruptState);

            /* Clear the FIFO to enable the BaseJaw_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            BaseJaw_ClearFIFO();
        #endif /* (BaseJaw_UseStatus) */
    #endif /* (BaseJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseJaw_Enable
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
void BaseJaw_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (BaseJaw_UsingFixedFunction)
        BaseJaw_GLOBAL_ENABLE |= BaseJaw_BLOCK_EN_MASK;
        BaseJaw_GLOBAL_STBY_ENABLE |= BaseJaw_BLOCK_STBY_EN_MASK;
    #endif /* (BaseJaw_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (BaseJaw_UseControl || BaseJaw_UsingFixedFunction)
        BaseJaw_CONTROL |= BaseJaw_CTRL_ENABLE;
    #endif /* (BaseJaw_UseControl || BaseJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseJaw_Stop
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
void BaseJaw_Stop(void) 
{
    #if (BaseJaw_UseControl || BaseJaw_UsingFixedFunction)
        BaseJaw_CONTROL &= ((uint8)(~BaseJaw_CTRL_ENABLE));
    #endif /* (BaseJaw_UseControl || BaseJaw_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (BaseJaw_UsingFixedFunction)
        BaseJaw_GLOBAL_ENABLE &= ((uint8)(~BaseJaw_BLOCK_EN_MASK));
        BaseJaw_GLOBAL_STBY_ENABLE &= ((uint8)(~BaseJaw_BLOCK_STBY_EN_MASK));
    #endif /* (BaseJaw_UsingFixedFunction) */
}

#if (BaseJaw_UseOneCompareMode)
    #if (BaseJaw_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BaseJaw_SetCompareMode
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
        void BaseJaw_SetCompareMode(uint8 comparemode) 
        {
            #if(BaseJaw_UsingFixedFunction)

                #if(0 != BaseJaw_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseJaw_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != BaseJaw_CTRL_CMPMODE1_SHIFT) */

                BaseJaw_CONTROL3 &= ((uint8)(~BaseJaw_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                BaseJaw_CONTROL3 |= comparemodemasked;

            #elif (BaseJaw_UseControl)

                #if(0 != BaseJaw_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << BaseJaw_CTRL_CMPMODE1_SHIFT)) &
                                                BaseJaw_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & BaseJaw_CTRL_CMPMODE1_MASK;
                #endif /* (0 != BaseJaw_CTRL_CMPMODE1_SHIFT) */

                #if(0 != BaseJaw_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << BaseJaw_CTRL_CMPMODE2_SHIFT)) &
                                               BaseJaw_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & BaseJaw_CTRL_CMPMODE2_MASK;
                #endif /* (0 != BaseJaw_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                BaseJaw_CONTROL &= ((uint8)(~(BaseJaw_CTRL_CMPMODE1_MASK |
                                            BaseJaw_CTRL_CMPMODE2_MASK)));
                BaseJaw_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (BaseJaw_UsingFixedFunction) */
        }
    #endif /* BaseJaw_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (BaseJaw_CompareMode1SW)


        /*******************************************************************************
        * Function Name: BaseJaw_SetCompareMode1
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
        void BaseJaw_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != BaseJaw_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseJaw_CTRL_CMPMODE1_SHIFT)) &
                                           BaseJaw_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & BaseJaw_CTRL_CMPMODE1_MASK;
            #endif /* (0 != BaseJaw_CTRL_CMPMODE1_SHIFT) */

            #if (BaseJaw_UseControl)
                BaseJaw_CONTROL &= ((uint8)(~BaseJaw_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                BaseJaw_CONTROL |= comparemodemasked;
            #endif /* (BaseJaw_UseControl) */
        }
    #endif /* BaseJaw_CompareMode1SW */

#if (BaseJaw_CompareMode2SW)


    /*******************************************************************************
    * Function Name: BaseJaw_SetCompareMode2
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
    void BaseJaw_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != BaseJaw_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << BaseJaw_CTRL_CMPMODE2_SHIFT)) &
                                                 BaseJaw_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & BaseJaw_CTRL_CMPMODE2_MASK;
        #endif /* (0 != BaseJaw_CTRL_CMPMODE2_SHIFT) */

        #if (BaseJaw_UseControl)
            BaseJaw_CONTROL &= ((uint8)(~BaseJaw_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            BaseJaw_CONTROL |= comparemodemasked;
        #endif /* (BaseJaw_UseControl) */
    }
    #endif /*BaseJaw_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!BaseJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseJaw_WriteCounter
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
    void BaseJaw_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(BaseJaw_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: BaseJaw_ReadCounter
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
    uint16 BaseJaw_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(BaseJaw_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(BaseJaw_CAPTURE_LSB_PTR));
    }

    #if (BaseJaw_UseStatus)


        /*******************************************************************************
        * Function Name: BaseJaw_ClearFIFO
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
        void BaseJaw_ClearFIFO(void) 
        {
            while(0u != (BaseJaw_ReadStatusRegister() & BaseJaw_STATUS_FIFONEMPTY))
            {
                (void)BaseJaw_ReadCapture();
            }
        }

    #endif /* BaseJaw_UseStatus */

#endif /* !BaseJaw_UsingFixedFunction */


/*******************************************************************************
* Function Name: BaseJaw_WritePeriod
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
void BaseJaw_WritePeriod(uint16 period) 
{
    #if(BaseJaw_UsingFixedFunction)
        CY_SET_REG16(BaseJaw_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(BaseJaw_PERIOD_LSB_PTR, period);
    #endif /* (BaseJaw_UsingFixedFunction) */
}

#if (BaseJaw_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BaseJaw_WriteCompare
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
    void BaseJaw_WriteCompare(uint16 compare) \
                                       
    {
        #if(BaseJaw_UsingFixedFunction)
            CY_SET_REG16(BaseJaw_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BaseJaw_COMPARE1_LSB_PTR, compare);
        #endif /* (BaseJaw_UsingFixedFunction) */

        #if (BaseJaw_PWMMode == BaseJaw__B_PWM__DITHER)
            #if(BaseJaw_UsingFixedFunction)
                CY_SET_REG16(BaseJaw_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(BaseJaw_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (BaseJaw_UsingFixedFunction) */
        #endif /* (BaseJaw_PWMMode == BaseJaw__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: BaseJaw_WriteCompare1
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
    void BaseJaw_WriteCompare1(uint16 compare) \
                                        
    {
        #if(BaseJaw_UsingFixedFunction)
            CY_SET_REG16(BaseJaw_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(BaseJaw_COMPARE1_LSB_PTR, compare);
        #endif /* (BaseJaw_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: BaseJaw_WriteCompare2
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
    void BaseJaw_WriteCompare2(uint16 compare) \
                                        
    {
        #if(BaseJaw_UsingFixedFunction)
            CY_SET_REG16(BaseJaw_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(BaseJaw_COMPARE2_LSB_PTR, compare);
        #endif /* (BaseJaw_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (BaseJaw_DeadBandUsed)


    /*******************************************************************************
    * Function Name: BaseJaw_WriteDeadTime
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
    void BaseJaw_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!BaseJaw_DeadBand2_4)
            CY_SET_REG8(BaseJaw_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            BaseJaw_DEADBAND_COUNT &= ((uint8)(~BaseJaw_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(BaseJaw_DEADBAND_COUNT_SHIFT)
                BaseJaw_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << BaseJaw_DEADBAND_COUNT_SHIFT)) &
                                                    BaseJaw_DEADBAND_COUNT_MASK;
            #else
                BaseJaw_DEADBAND_COUNT |= deadtime & BaseJaw_DEADBAND_COUNT_MASK;
            #endif /* (BaseJaw_DEADBAND_COUNT_SHIFT) */

        #endif /* (!BaseJaw_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: BaseJaw_ReadDeadTime
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
    uint8 BaseJaw_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!BaseJaw_DeadBand2_4)
            return (CY_GET_REG8(BaseJaw_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(BaseJaw_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(BaseJaw_DEADBAND_COUNT & BaseJaw_DEADBAND_COUNT_MASK)) >>
                                                                           BaseJaw_DEADBAND_COUNT_SHIFT));
            #else
                return (BaseJaw_DEADBAND_COUNT & BaseJaw_DEADBAND_COUNT_MASK);
            #endif /* (BaseJaw_DEADBAND_COUNT_SHIFT) */
        #endif /* (!BaseJaw_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseJaw_SetInterruptMode
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
    void BaseJaw_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(BaseJaw_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: BaseJaw_ReadStatusRegister
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
    uint8 BaseJaw_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(BaseJaw_STATUS_PTR));
    }

#endif /* (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction) */


#if (BaseJaw_UseControl)


    /*******************************************************************************
    * Function Name: BaseJaw_ReadControlRegister
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
    uint8 BaseJaw_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(BaseJaw_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: BaseJaw_WriteControlRegister
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
    void BaseJaw_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(BaseJaw_CONTROL_PTR, control);
    }

#endif /* (BaseJaw_UseControl) */


#if (!BaseJaw_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: BaseJaw_ReadCapture
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
    uint16 BaseJaw_ReadCapture(void) 
    {
        return (CY_GET_REG16(BaseJaw_CAPTURE_LSB_PTR));
    }

#endif /* (!BaseJaw_UsingFixedFunction) */


#if (BaseJaw_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: BaseJaw_ReadCompare
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
    uint16 BaseJaw_ReadCompare(void) 
    {
        #if(BaseJaw_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(BaseJaw_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(BaseJaw_COMPARE1_LSB_PTR));
        #endif /* (BaseJaw_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: BaseJaw_ReadCompare1
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
    uint16 BaseJaw_ReadCompare1(void) 
    {
        return (CY_GET_REG16(BaseJaw_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: BaseJaw_ReadCompare2
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
    uint16 BaseJaw_ReadCompare2(void) 
    {
        return (CY_GET_REG16(BaseJaw_COMPARE2_LSB_PTR));
    }

#endif /* (BaseJaw_UseOneCompareMode) */


/*******************************************************************************
* Function Name: BaseJaw_ReadPeriod
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
uint16 BaseJaw_ReadPeriod(void) 
{
    #if(BaseJaw_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(BaseJaw_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(BaseJaw_PERIOD_LSB_PTR));
    #endif /* (BaseJaw_UsingFixedFunction) */
}

#if ( BaseJaw_KillModeMinTime)


    /*******************************************************************************
    * Function Name: BaseJaw_WriteKillTime
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
    void BaseJaw_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(BaseJaw_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: BaseJaw_ReadKillTime
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
    uint8 BaseJaw_ReadKillTime(void) 
    {
        return (CY_GET_REG8(BaseJaw_KILLMODEMINTIME_PTR));
    }

#endif /* ( BaseJaw_KillModeMinTime) */

/* [] END OF FILE */
