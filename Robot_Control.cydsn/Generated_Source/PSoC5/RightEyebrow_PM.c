/*******************************************************************************
* File Name: RightEyebrow_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RightEyebrow.h"

static RightEyebrow_backupStruct RightEyebrow_backup;


/*******************************************************************************
* Function Name: RightEyebrow_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RightEyebrow_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void RightEyebrow_SaveConfig(void) 
{

    #if(!RightEyebrow_UsingFixedFunction)
        #if(!RightEyebrow_PWMModeIsCenterAligned)
            RightEyebrow_backup.PWMPeriod = RightEyebrow_ReadPeriod();
        #endif /* (!RightEyebrow_PWMModeIsCenterAligned) */
        RightEyebrow_backup.PWMUdb = RightEyebrow_ReadCounter();
        #if (RightEyebrow_UseStatus)
            RightEyebrow_backup.InterruptMaskValue = RightEyebrow_STATUS_MASK;
        #endif /* (RightEyebrow_UseStatus) */

        #if(RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_256_CLOCKS || \
            RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_2_4_CLOCKS)
            RightEyebrow_backup.PWMdeadBandValue = RightEyebrow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(RightEyebrow_KillModeMinTime)
             RightEyebrow_backup.PWMKillCounterPeriod = RightEyebrow_ReadKillTime();
        #endif /* (RightEyebrow_KillModeMinTime) */

        #if(RightEyebrow_UseControl)
            RightEyebrow_backup.PWMControlRegister = RightEyebrow_ReadControlRegister();
        #endif /* (RightEyebrow_UseControl) */
    #endif  /* (!RightEyebrow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: RightEyebrow_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RightEyebrow_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void RightEyebrow_RestoreConfig(void) 
{
        #if(!RightEyebrow_UsingFixedFunction)
            #if(!RightEyebrow_PWMModeIsCenterAligned)
                RightEyebrow_WritePeriod(RightEyebrow_backup.PWMPeriod);
            #endif /* (!RightEyebrow_PWMModeIsCenterAligned) */

            RightEyebrow_WriteCounter(RightEyebrow_backup.PWMUdb);

            #if (RightEyebrow_UseStatus)
                RightEyebrow_STATUS_MASK = RightEyebrow_backup.InterruptMaskValue;
            #endif /* (RightEyebrow_UseStatus) */

            #if(RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_256_CLOCKS || \
                RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_2_4_CLOCKS)
                RightEyebrow_WriteDeadTime(RightEyebrow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(RightEyebrow_KillModeMinTime)
                RightEyebrow_WriteKillTime(RightEyebrow_backup.PWMKillCounterPeriod);
            #endif /* (RightEyebrow_KillModeMinTime) */

            #if(RightEyebrow_UseControl)
                RightEyebrow_WriteControlRegister(RightEyebrow_backup.PWMControlRegister);
            #endif /* (RightEyebrow_UseControl) */
        #endif  /* (!RightEyebrow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: RightEyebrow_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RightEyebrow_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void RightEyebrow_Sleep(void) 
{
    #if(RightEyebrow_UseControl)
        if(RightEyebrow_CTRL_ENABLE == (RightEyebrow_CONTROL & RightEyebrow_CTRL_ENABLE))
        {
            /*Component is enabled */
            RightEyebrow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            RightEyebrow_backup.PWMEnableState = 0u;
        }
    #endif /* (RightEyebrow_UseControl) */

    /* Stop component */
    RightEyebrow_Stop();

    /* Save registers configuration */
    RightEyebrow_SaveConfig();
}


/*******************************************************************************
* Function Name: RightEyebrow_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  RightEyebrow_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void RightEyebrow_Wakeup(void) 
{
     /* Restore registers values */
    RightEyebrow_RestoreConfig();

    if(RightEyebrow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        RightEyebrow_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
