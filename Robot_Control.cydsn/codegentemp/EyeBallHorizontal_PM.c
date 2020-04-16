/*******************************************************************************
* File Name: EyeBallHorizontal_PM.c
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

#include "EyeBallHorizontal.h"

static EyeBallHorizontal_backupStruct EyeBallHorizontal_backup;


/*******************************************************************************
* Function Name: EyeBallHorizontal_SaveConfig
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
*  EyeBallHorizontal_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EyeBallHorizontal_SaveConfig(void) 
{

    #if(!EyeBallHorizontal_UsingFixedFunction)
        #if(!EyeBallHorizontal_PWMModeIsCenterAligned)
            EyeBallHorizontal_backup.PWMPeriod = EyeBallHorizontal_ReadPeriod();
        #endif /* (!EyeBallHorizontal_PWMModeIsCenterAligned) */
        EyeBallHorizontal_backup.PWMUdb = EyeBallHorizontal_ReadCounter();
        #if (EyeBallHorizontal_UseStatus)
            EyeBallHorizontal_backup.InterruptMaskValue = EyeBallHorizontal_STATUS_MASK;
        #endif /* (EyeBallHorizontal_UseStatus) */

        #if(EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_256_CLOCKS || \
            EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_2_4_CLOCKS)
            EyeBallHorizontal_backup.PWMdeadBandValue = EyeBallHorizontal_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EyeBallHorizontal_KillModeMinTime)
             EyeBallHorizontal_backup.PWMKillCounterPeriod = EyeBallHorizontal_ReadKillTime();
        #endif /* (EyeBallHorizontal_KillModeMinTime) */

        #if(EyeBallHorizontal_UseControl)
            EyeBallHorizontal_backup.PWMControlRegister = EyeBallHorizontal_ReadControlRegister();
        #endif /* (EyeBallHorizontal_UseControl) */
    #endif  /* (!EyeBallHorizontal_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeBallHorizontal_RestoreConfig
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
*  EyeBallHorizontal_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EyeBallHorizontal_RestoreConfig(void) 
{
        #if(!EyeBallHorizontal_UsingFixedFunction)
            #if(!EyeBallHorizontal_PWMModeIsCenterAligned)
                EyeBallHorizontal_WritePeriod(EyeBallHorizontal_backup.PWMPeriod);
            #endif /* (!EyeBallHorizontal_PWMModeIsCenterAligned) */

            EyeBallHorizontal_WriteCounter(EyeBallHorizontal_backup.PWMUdb);

            #if (EyeBallHorizontal_UseStatus)
                EyeBallHorizontal_STATUS_MASK = EyeBallHorizontal_backup.InterruptMaskValue;
            #endif /* (EyeBallHorizontal_UseStatus) */

            #if(EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_256_CLOCKS || \
                EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_2_4_CLOCKS)
                EyeBallHorizontal_WriteDeadTime(EyeBallHorizontal_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EyeBallHorizontal_KillModeMinTime)
                EyeBallHorizontal_WriteKillTime(EyeBallHorizontal_backup.PWMKillCounterPeriod);
            #endif /* (EyeBallHorizontal_KillModeMinTime) */

            #if(EyeBallHorizontal_UseControl)
                EyeBallHorizontal_WriteControlRegister(EyeBallHorizontal_backup.PWMControlRegister);
            #endif /* (EyeBallHorizontal_UseControl) */
        #endif  /* (!EyeBallHorizontal_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EyeBallHorizontal_Sleep
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
*  EyeBallHorizontal_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EyeBallHorizontal_Sleep(void) 
{
    #if(EyeBallHorizontal_UseControl)
        if(EyeBallHorizontal_CTRL_ENABLE == (EyeBallHorizontal_CONTROL & EyeBallHorizontal_CTRL_ENABLE))
        {
            /*Component is enabled */
            EyeBallHorizontal_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EyeBallHorizontal_backup.PWMEnableState = 0u;
        }
    #endif /* (EyeBallHorizontal_UseControl) */

    /* Stop component */
    EyeBallHorizontal_Stop();

    /* Save registers configuration */
    EyeBallHorizontal_SaveConfig();
}


/*******************************************************************************
* Function Name: EyeBallHorizontal_Wakeup
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
*  EyeBallHorizontal_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EyeBallHorizontal_Wakeup(void) 
{
     /* Restore registers values */
    EyeBallHorizontal_RestoreConfig();

    if(EyeBallHorizontal_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EyeBallHorizontal_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
