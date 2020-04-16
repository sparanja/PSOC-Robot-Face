/*******************************************************************************
* File Name: Lip.c
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

#include "Lip.h"

/* Error message for removed <resource> through optimization */
#ifdef Lip_PWMUDB_genblk1_ctrlreg__REMOVED
    #error PWM_v3_30 detected with a constant 0 for the enable or \
         constant 1 for reset. This will prevent the component from operating.
#endif /* Lip_PWMUDB_genblk1_ctrlreg__REMOVED */

uint8 Lip_initVar = 0u;


/*******************************************************************************
* Function Name: Lip_Start
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
*  Lip_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Lip_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(Lip_initVar == 0u)
    {
        Lip_Init();
        Lip_initVar = 1u;
    }
    Lip_Enable();

}


/*******************************************************************************
* Function Name: Lip_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the
*  customizer of the component placed onto schematic. Usually called in
*  Lip_Start().
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Lip_Init(void) 
{
    #if (Lip_UsingFixedFunction || Lip_UseControl)
        uint8 ctrl;
    #endif /* (Lip_UsingFixedFunction || Lip_UseControl) */

    #if(!Lip_UsingFixedFunction)
        #if(Lip_UseStatus)
            /* Interrupt State Backup for Critical Region*/
            uint8 Lip_interruptState;
        #endif /* (Lip_UseStatus) */
    #endif /* (!Lip_UsingFixedFunction) */

    #if (Lip_UsingFixedFunction)
        /* You are allowed to write the compare value (FF only) */
        Lip_CONTROL |= Lip_CFG0_MODE;
        #if (Lip_DeadBand2_4)
            Lip_CONTROL |= Lip_CFG0_DB;
        #endif /* (Lip_DeadBand2_4) */

        ctrl = Lip_CONTROL3 & ((uint8 )(~Lip_CTRL_CMPMODE1_MASK));
        Lip_CONTROL3 = ctrl | Lip_DEFAULT_COMPARE1_MODE;

         /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
        Lip_RT1 &= ((uint8)(~Lip_RT1_MASK));
        Lip_RT1 |= Lip_SYNC;

        /*Enable DSI Sync all all inputs of the PWM*/
        Lip_RT1 &= ((uint8)(~Lip_SYNCDSI_MASK));
        Lip_RT1 |= Lip_SYNCDSI_EN;

    #elif (Lip_UseControl)
        /* Set the default compare mode defined in the parameter */
        ctrl = Lip_CONTROL & ((uint8)(~Lip_CTRL_CMPMODE2_MASK)) &
                ((uint8)(~Lip_CTRL_CMPMODE1_MASK));
        Lip_CONTROL = ctrl | Lip_DEFAULT_COMPARE2_MODE |
                                   Lip_DEFAULT_COMPARE1_MODE;
    #endif /* (Lip_UsingFixedFunction) */

    #if (!Lip_UsingFixedFunction)
        #if (Lip_Resolution == 8)
            /* Set FIFO 0 to 1 byte register for period*/
            Lip_AUX_CONTROLDP0 |= (Lip_AUX_CTRL_FIFO0_CLR);
        #else /* (Lip_Resolution == 16)*/
            /* Set FIFO 0 to 1 byte register for period */
            Lip_AUX_CONTROLDP0 |= (Lip_AUX_CTRL_FIFO0_CLR);
            Lip_AUX_CONTROLDP1 |= (Lip_AUX_CTRL_FIFO0_CLR);
        #endif /* (Lip_Resolution == 8) */

        Lip_WriteCounter(Lip_INIT_PERIOD_VALUE);
    #endif /* (!Lip_UsingFixedFunction) */

    Lip_WritePeriod(Lip_INIT_PERIOD_VALUE);

        #if (Lip_UseOneCompareMode)
            Lip_WriteCompare(Lip_INIT_COMPARE_VALUE1);
        #else
            Lip_WriteCompare1(Lip_INIT_COMPARE_VALUE1);
            Lip_WriteCompare2(Lip_INIT_COMPARE_VALUE2);
        #endif /* (Lip_UseOneCompareMode) */

        #if (Lip_KillModeMinTime)
            Lip_WriteKillTime(Lip_MinimumKillTime);
        #endif /* (Lip_KillModeMinTime) */

        #if (Lip_DeadBandUsed)
            Lip_WriteDeadTime(Lip_INIT_DEAD_TIME);
        #endif /* (Lip_DeadBandUsed) */

    #if (Lip_UseStatus || Lip_UsingFixedFunction)
        Lip_SetInterruptMode(Lip_INIT_INTERRUPTS_MODE);
    #endif /* (Lip_UseStatus || Lip_UsingFixedFunction) */

    #if (Lip_UsingFixedFunction)
        /* Globally Enable the Fixed Function Block chosen */
        Lip_GLOBAL_ENABLE |= Lip_BLOCK_EN_MASK;
        /* Set the Interrupt source to come from the status register */
        Lip_CONTROL2 |= Lip_CTRL2_IRQ_SEL;
    #else
        #if(Lip_UseStatus)

            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            Lip_interruptState = CyEnterCriticalSection();
            /* Use the interrupt output of the status register for IRQ output */
            Lip_STATUS_AUX_CTRL |= Lip_STATUS_ACTL_INT_EN_MASK;

             /* Exit Critical Region*/
            CyExitCriticalSection(Lip_interruptState);

            /* Clear the FIFO to enable the Lip_STATUS_FIFOFULL
                   bit to be set on FIFO full. */
            Lip_ClearFIFO();
        #endif /* (Lip_UseStatus) */
    #endif /* (Lip_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lip_Enable
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
void Lip_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (Lip_UsingFixedFunction)
        Lip_GLOBAL_ENABLE |= Lip_BLOCK_EN_MASK;
        Lip_GLOBAL_STBY_ENABLE |= Lip_BLOCK_STBY_EN_MASK;
    #endif /* (Lip_UsingFixedFunction) */

    /* Enable the PWM from the control register  */
    #if (Lip_UseControl || Lip_UsingFixedFunction)
        Lip_CONTROL |= Lip_CTRL_ENABLE;
    #endif /* (Lip_UseControl || Lip_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lip_Stop
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
void Lip_Stop(void) 
{
    #if (Lip_UseControl || Lip_UsingFixedFunction)
        Lip_CONTROL &= ((uint8)(~Lip_CTRL_ENABLE));
    #endif /* (Lip_UseControl || Lip_UsingFixedFunction) */

    /* Globally disable the Fixed Function Block chosen */
    #if (Lip_UsingFixedFunction)
        Lip_GLOBAL_ENABLE &= ((uint8)(~Lip_BLOCK_EN_MASK));
        Lip_GLOBAL_STBY_ENABLE &= ((uint8)(~Lip_BLOCK_STBY_EN_MASK));
    #endif /* (Lip_UsingFixedFunction) */
}

#if (Lip_UseOneCompareMode)
    #if (Lip_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Lip_SetCompareMode
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
        void Lip_SetCompareMode(uint8 comparemode) 
        {
            #if(Lip_UsingFixedFunction)

                #if(0 != Lip_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lip_CTRL_CMPMODE1_SHIFT));
                #else
                    uint8 comparemodemasked = comparemode;
                #endif /* (0 != Lip_CTRL_CMPMODE1_SHIFT) */

                Lip_CONTROL3 &= ((uint8)(~Lip_CTRL_CMPMODE1_MASK)); /*Clear Existing Data */
                Lip_CONTROL3 |= comparemodemasked;

            #elif (Lip_UseControl)

                #if(0 != Lip_CTRL_CMPMODE1_SHIFT)
                    uint8 comparemode1masked = ((uint8)((uint8)comparemode << Lip_CTRL_CMPMODE1_SHIFT)) &
                                                Lip_CTRL_CMPMODE1_MASK;
                #else
                    uint8 comparemode1masked = comparemode & Lip_CTRL_CMPMODE1_MASK;
                #endif /* (0 != Lip_CTRL_CMPMODE1_SHIFT) */

                #if(0 != Lip_CTRL_CMPMODE2_SHIFT)
                    uint8 comparemode2masked = ((uint8)((uint8)comparemode << Lip_CTRL_CMPMODE2_SHIFT)) &
                                               Lip_CTRL_CMPMODE2_MASK;
                #else
                    uint8 comparemode2masked = comparemode & Lip_CTRL_CMPMODE2_MASK;
                #endif /* (0 != Lip_CTRL_CMPMODE2_SHIFT) */

                /*Clear existing mode */
                Lip_CONTROL &= ((uint8)(~(Lip_CTRL_CMPMODE1_MASK |
                                            Lip_CTRL_CMPMODE2_MASK)));
                Lip_CONTROL |= (comparemode1masked | comparemode2masked);

            #else
                uint8 temp = comparemode;
            #endif /* (Lip_UsingFixedFunction) */
        }
    #endif /* Lip_CompareMode1SW */

#else /* UseOneCompareMode */

    #if (Lip_CompareMode1SW)


        /*******************************************************************************
        * Function Name: Lip_SetCompareMode1
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
        void Lip_SetCompareMode1(uint8 comparemode) 
        {
            #if(0 != Lip_CTRL_CMPMODE1_SHIFT)
                uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lip_CTRL_CMPMODE1_SHIFT)) &
                                           Lip_CTRL_CMPMODE1_MASK;
            #else
                uint8 comparemodemasked = comparemode & Lip_CTRL_CMPMODE1_MASK;
            #endif /* (0 != Lip_CTRL_CMPMODE1_SHIFT) */

            #if (Lip_UseControl)
                Lip_CONTROL &= ((uint8)(~Lip_CTRL_CMPMODE1_MASK)); /*Clear existing mode */
                Lip_CONTROL |= comparemodemasked;
            #endif /* (Lip_UseControl) */
        }
    #endif /* Lip_CompareMode1SW */

#if (Lip_CompareMode2SW)


    /*******************************************************************************
    * Function Name: Lip_SetCompareMode2
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
    void Lip_SetCompareMode2(uint8 comparemode) 
    {

        #if(0 != Lip_CTRL_CMPMODE2_SHIFT)
            uint8 comparemodemasked = ((uint8)((uint8)comparemode << Lip_CTRL_CMPMODE2_SHIFT)) &
                                                 Lip_CTRL_CMPMODE2_MASK;
        #else
            uint8 comparemodemasked = comparemode & Lip_CTRL_CMPMODE2_MASK;
        #endif /* (0 != Lip_CTRL_CMPMODE2_SHIFT) */

        #if (Lip_UseControl)
            Lip_CONTROL &= ((uint8)(~Lip_CTRL_CMPMODE2_MASK)); /*Clear existing mode */
            Lip_CONTROL |= comparemodemasked;
        #endif /* (Lip_UseControl) */
    }
    #endif /*Lip_CompareMode2SW */

#endif /* UseOneCompareMode */


#if (!Lip_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lip_WriteCounter
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
    void Lip_WriteCounter(uint16 counter) \
                                       
    {
        CY_SET_REG16(Lip_COUNTER_LSB_PTR, counter);
    }


    /*******************************************************************************
    * Function Name: Lip_ReadCounter
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
    uint16 Lip_ReadCounter(void) 
    {
        /* Force capture by reading Accumulator */
        /* Must first do a software capture to be able to read the counter */
        /* It is up to the user code to make sure there isn't already captured data in the FIFO */
          (void)CY_GET_REG8(Lip_COUNTERCAP_LSB_PTR_8BIT);

        /* Read the data from the FIFO */
        return (CY_GET_REG16(Lip_CAPTURE_LSB_PTR));
    }

    #if (Lip_UseStatus)


        /*******************************************************************************
        * Function Name: Lip_ClearFIFO
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
        void Lip_ClearFIFO(void) 
        {
            while(0u != (Lip_ReadStatusRegister() & Lip_STATUS_FIFONEMPTY))
            {
                (void)Lip_ReadCapture();
            }
        }

    #endif /* Lip_UseStatus */

#endif /* !Lip_UsingFixedFunction */


/*******************************************************************************
* Function Name: Lip_WritePeriod
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
void Lip_WritePeriod(uint16 period) 
{
    #if(Lip_UsingFixedFunction)
        CY_SET_REG16(Lip_PERIOD_LSB_PTR, (uint16)period);
    #else
        CY_SET_REG16(Lip_PERIOD_LSB_PTR, period);
    #endif /* (Lip_UsingFixedFunction) */
}

#if (Lip_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Lip_WriteCompare
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
    void Lip_WriteCompare(uint16 compare) \
                                       
    {
        #if(Lip_UsingFixedFunction)
            CY_SET_REG16(Lip_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Lip_COMPARE1_LSB_PTR, compare);
        #endif /* (Lip_UsingFixedFunction) */

        #if (Lip_PWMMode == Lip__B_PWM__DITHER)
            #if(Lip_UsingFixedFunction)
                CY_SET_REG16(Lip_COMPARE2_LSB_PTR, (uint16)(compare + 1u));
            #else
                CY_SET_REG16(Lip_COMPARE2_LSB_PTR, (compare + 1u));
            #endif /* (Lip_UsingFixedFunction) */
        #endif /* (Lip_PWMMode == Lip__B_PWM__DITHER) */
    }


#else


    /*******************************************************************************
    * Function Name: Lip_WriteCompare1
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
    void Lip_WriteCompare1(uint16 compare) \
                                        
    {
        #if(Lip_UsingFixedFunction)
            CY_SET_REG16(Lip_COMPARE1_LSB_PTR, (uint16)compare);
        #else
            CY_SET_REG16(Lip_COMPARE1_LSB_PTR, compare);
        #endif /* (Lip_UsingFixedFunction) */
    }


    /*******************************************************************************
    * Function Name: Lip_WriteCompare2
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
    void Lip_WriteCompare2(uint16 compare) \
                                        
    {
        #if(Lip_UsingFixedFunction)
            CY_SET_REG16(Lip_COMPARE2_LSB_PTR, compare);
        #else
            CY_SET_REG16(Lip_COMPARE2_LSB_PTR, compare);
        #endif /* (Lip_UsingFixedFunction) */
    }
#endif /* UseOneCompareMode */

#if (Lip_DeadBandUsed)


    /*******************************************************************************
    * Function Name: Lip_WriteDeadTime
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
    void Lip_WriteDeadTime(uint8 deadtime) 
    {
        /* If using the Dead Band 1-255 mode then just write the register */
        #if(!Lip_DeadBand2_4)
            CY_SET_REG8(Lip_DEADBAND_COUNT_PTR, deadtime);
        #else
            /* Otherwise the data has to be masked and offset */
            /* Clear existing data */
            Lip_DEADBAND_COUNT &= ((uint8)(~Lip_DEADBAND_COUNT_MASK));

            /* Set new dead time */
            #if(Lip_DEADBAND_COUNT_SHIFT)
                Lip_DEADBAND_COUNT |= ((uint8)((uint8)deadtime << Lip_DEADBAND_COUNT_SHIFT)) &
                                                    Lip_DEADBAND_COUNT_MASK;
            #else
                Lip_DEADBAND_COUNT |= deadtime & Lip_DEADBAND_COUNT_MASK;
            #endif /* (Lip_DEADBAND_COUNT_SHIFT) */

        #endif /* (!Lip_DeadBand2_4) */
    }


    /*******************************************************************************
    * Function Name: Lip_ReadDeadTime
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
    uint8 Lip_ReadDeadTime(void) 
    {
        /* If using the Dead Band 1-255 mode then just read the register */
        #if(!Lip_DeadBand2_4)
            return (CY_GET_REG8(Lip_DEADBAND_COUNT_PTR));
        #else

            /* Otherwise the data has to be masked and offset */
            #if(Lip_DEADBAND_COUNT_SHIFT)
                return ((uint8)(((uint8)(Lip_DEADBAND_COUNT & Lip_DEADBAND_COUNT_MASK)) >>
                                                                           Lip_DEADBAND_COUNT_SHIFT));
            #else
                return (Lip_DEADBAND_COUNT & Lip_DEADBAND_COUNT_MASK);
            #endif /* (Lip_DEADBAND_COUNT_SHIFT) */
        #endif /* (!Lip_DeadBand2_4) */
    }
#endif /* DeadBandUsed */

#if (Lip_UseStatus || Lip_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lip_SetInterruptMode
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
    void Lip_SetInterruptMode(uint8 interruptMode) 
    {
        CY_SET_REG8(Lip_STATUS_MASK_PTR, interruptMode);
    }


    /*******************************************************************************
    * Function Name: Lip_ReadStatusRegister
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
    uint8 Lip_ReadStatusRegister(void) 
    {
        return (CY_GET_REG8(Lip_STATUS_PTR));
    }

#endif /* (Lip_UseStatus || Lip_UsingFixedFunction) */


#if (Lip_UseControl)


    /*******************************************************************************
    * Function Name: Lip_ReadControlRegister
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
    uint8 Lip_ReadControlRegister(void) 
    {
        uint8 result;

        result = CY_GET_REG8(Lip_CONTROL_PTR);
        return (result);
    }


    /*******************************************************************************
    * Function Name: Lip_WriteControlRegister
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
    void Lip_WriteControlRegister(uint8 control) 
    {
        CY_SET_REG8(Lip_CONTROL_PTR, control);
    }

#endif /* (Lip_UseControl) */


#if (!Lip_UsingFixedFunction)


    /*******************************************************************************
    * Function Name: Lip_ReadCapture
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
    uint16 Lip_ReadCapture(void) 
    {
        return (CY_GET_REG16(Lip_CAPTURE_LSB_PTR));
    }

#endif /* (!Lip_UsingFixedFunction) */


#if (Lip_UseOneCompareMode)


    /*******************************************************************************
    * Function Name: Lip_ReadCompare
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
    uint16 Lip_ReadCompare(void) 
    {
        #if(Lip_UsingFixedFunction)
            return ((uint16)CY_GET_REG16(Lip_COMPARE1_LSB_PTR));
        #else
            return (CY_GET_REG16(Lip_COMPARE1_LSB_PTR));
        #endif /* (Lip_UsingFixedFunction) */
    }

#else


    /*******************************************************************************
    * Function Name: Lip_ReadCompare1
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
    uint16 Lip_ReadCompare1(void) 
    {
        return (CY_GET_REG16(Lip_COMPARE1_LSB_PTR));
    }


    /*******************************************************************************
    * Function Name: Lip_ReadCompare2
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
    uint16 Lip_ReadCompare2(void) 
    {
        return (CY_GET_REG16(Lip_COMPARE2_LSB_PTR));
    }

#endif /* (Lip_UseOneCompareMode) */


/*******************************************************************************
* Function Name: Lip_ReadPeriod
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
uint16 Lip_ReadPeriod(void) 
{
    #if(Lip_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(Lip_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(Lip_PERIOD_LSB_PTR));
    #endif /* (Lip_UsingFixedFunction) */
}

#if ( Lip_KillModeMinTime)


    /*******************************************************************************
    * Function Name: Lip_WriteKillTime
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
    void Lip_WriteKillTime(uint8 killtime) 
    {
        CY_SET_REG8(Lip_KILLMODEMINTIME_PTR, killtime);
    }


    /*******************************************************************************
    * Function Name: Lip_ReadKillTime
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
    uint8 Lip_ReadKillTime(void) 
    {
        return (CY_GET_REG8(Lip_KILLMODEMINTIME_PTR));
    }

#endif /* ( Lip_KillModeMinTime) */

/* [] END OF FILE */
