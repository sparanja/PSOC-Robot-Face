/*******************************************************************************
* File Name: LeftEyebrow_PM.c
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

#include "LeftEyebrow.h"

static LeftEyebrow_backupStruct LeftEyebrow_backup;


/*******************************************************************************
* Function Name: LeftEyebrow_SaveConfig
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
*  LeftEyebrow_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void LeftEyebrow_SaveConfig(void) 
{

    #if(!LeftEyebrow_UsingFixedFunction)
        #if(!LeftEyebrow_PWMModeIsCenterAligned)
            LeftEyebrow_backup.PWMPeriod = LeftEyebrow_ReadPeriod();
        #endif /* (!LeftEyebrow_PWMModeIsCenterAligned) */
        LeftEyebrow_backup.PWMUdb = LeftEyebrow_ReadCounter();
        #if (LeftEyebrow_UseStatus)
            LeftEyebrow_backup.InterruptMaskValue = LeftEyebrow_STATUS_MASK;
        #endif /* (LeftEyebrow_UseStatus) */

        #if(LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_256_CLOCKS || \
            LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_2_4_CLOCKS)
            LeftEyebrow_backup.PWMdeadBandValue = LeftEyebrow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(LeftEyebrow_KillModeMinTime)
             LeftEyebrow_backup.PWMKillCounterPeriod = LeftEyebrow_ReadKillTime();
        #endif /* (LeftEyebrow_KillModeMinTime) */

        #if(LeftEyebrow_UseControl)
            LeftEyebrow_backup.PWMControlRegister = LeftEyebrow_ReadControlRegister();
        #endif /* (LeftEyebrow_UseControl) */
    #endif  /* (!LeftEyebrow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: LeftEyebrow_RestoreConfig
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
*  LeftEyebrow_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void LeftEyebrow_RestoreConfig(void) 
{
        #if(!LeftEyebrow_UsingFixedFunction)
            #if(!LeftEyebrow_PWMModeIsCenterAligned)
                LeftEyebrow_WritePeriod(LeftEyebrow_backup.PWMPeriod);
            #endif /* (!LeftEyebrow_PWMModeIsCenterAligned) */

            LeftEyebrow_WriteCounter(LeftEyebrow_backup.PWMUdb);

            #if (LeftEyebrow_UseStatus)
                LeftEyebrow_STATUS_MASK = LeftEyebrow_backup.InterruptMaskValue;
            #endif /* (LeftEyebrow_UseStatus) */

            #if(LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_256_CLOCKS || \
                LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_2_4_CLOCKS)
                LeftEyebrow_WriteDeadTime(LeftEyebrow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(LeftEyebrow_KillModeMinTime)
                LeftEyebrow_WriteKillTime(LeftEyebrow_backup.PWMKillCounterPeriod);
            #endif /* (LeftEyebrow_KillModeMinTime) */

            #if(LeftEyebrow_UseControl)
                LeftEyebrow_WriteControlRegister(LeftEyebrow_backup.PWMControlRegister);
            #endif /* (LeftEyebrow_UseControl) */
        #endif  /* (!LeftEyebrow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: LeftEyebrow_Sleep
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
*  LeftEyebrow_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void LeftEyebrow_Sleep(void) 
{
    #if(LeftEyebrow_UseControl)
        if(LeftEyebrow_CTRL_ENABLE == (LeftEyebrow_CONTROL & LeftEyebrow_CTRL_ENABLE))
        {
            /*Component is enabled */
            LeftEyebrow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            LeftEyebrow_backup.PWMEnableState = 0u;
        }
    #endif /* (LeftEyebrow_UseControl) */

    /* Stop component */
    LeftEyebrow_Stop();

    /* Save registers configuration */
    LeftEyebrow_SaveConfig();
}


/*******************************************************************************
* Function Name: LeftEyebrow_Wakeup
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
*  LeftEyebrow_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void LeftEyebrow_Wakeup(void) 
{
     /* Restore registers values */
    LeftEyebrow_RestoreConfig();

    if(LeftEyebrow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        LeftEyebrow_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
