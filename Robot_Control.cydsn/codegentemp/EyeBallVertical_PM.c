/*******************************************************************************
* File Name: EyeBallVertical_PM.c
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

#include "EyeBallVertical.h"

static EyeBallVertical_backupStruct EyeBallVertical_backup;


/*******************************************************************************
* Function Name: EyeBallVertical_SaveConfig
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
*  EyeBallVertical_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EyeBallVertical_SaveConfig(void) 
{

    #if(!EyeBallVertical_UsingFixedFunction)
        #if(!EyeBallVertical_PWMModeIsCenterAligned)
            EyeBallVertical_backup.PWMPeriod = EyeBallVertical_ReadPeriod();
        #endif /* (!EyeBallVertical_PWMModeIsCenterAligned) */
        EyeBallVertical_backup.PWMUdb = EyeBallVertical_ReadCounter();
        #if (EyeBallVertical_UseStatus)
            EyeBallVertical_backup.InterruptMaskValue = EyeBallVertical_STATUS_MASK;
        #endif /* (EyeBallVertical_UseStatus) */

        #if(EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_256_CLOCKS || \
            EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_2_4_CLOCKS)
            EyeBallVertical_backup.PWMdeadBandValue = EyeBallVertical_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EyeBallVertical_KillModeMinTime)
             EyeBallVertical_backup.PWMKillCounterPeriod = EyeBallVertical_ReadKillTime();
        #endif /* (EyeBallVertical_KillModeMinTime) */

        #if(EyeBallVertical_UseControl)
            EyeBallVertical_backup.PWMControlRegister = EyeBallVertical_ReadControlRegister();
        #endif /* (EyeBallVertical_UseControl) */
    #endif  /* (!EyeBallVertical_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyeBallVertical_RestoreConfig
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
*  EyeBallVertical_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EyeBallVertical_RestoreConfig(void) 
{
        #if(!EyeBallVertical_UsingFixedFunction)
            #if(!EyeBallVertical_PWMModeIsCenterAligned)
                EyeBallVertical_WritePeriod(EyeBallVertical_backup.PWMPeriod);
            #endif /* (!EyeBallVertical_PWMModeIsCenterAligned) */

            EyeBallVertical_WriteCounter(EyeBallVertical_backup.PWMUdb);

            #if (EyeBallVertical_UseStatus)
                EyeBallVertical_STATUS_MASK = EyeBallVertical_backup.InterruptMaskValue;
            #endif /* (EyeBallVertical_UseStatus) */

            #if(EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_256_CLOCKS || \
                EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_2_4_CLOCKS)
                EyeBallVertical_WriteDeadTime(EyeBallVertical_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EyeBallVertical_KillModeMinTime)
                EyeBallVertical_WriteKillTime(EyeBallVertical_backup.PWMKillCounterPeriod);
            #endif /* (EyeBallVertical_KillModeMinTime) */

            #if(EyeBallVertical_UseControl)
                EyeBallVertical_WriteControlRegister(EyeBallVertical_backup.PWMControlRegister);
            #endif /* (EyeBallVertical_UseControl) */
        #endif  /* (!EyeBallVertical_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EyeBallVertical_Sleep
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
*  EyeBallVertical_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EyeBallVertical_Sleep(void) 
{
    #if(EyeBallVertical_UseControl)
        if(EyeBallVertical_CTRL_ENABLE == (EyeBallVertical_CONTROL & EyeBallVertical_CTRL_ENABLE))
        {
            /*Component is enabled */
            EyeBallVertical_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EyeBallVertical_backup.PWMEnableState = 0u;
        }
    #endif /* (EyeBallVertical_UseControl) */

    /* Stop component */
    EyeBallVertical_Stop();

    /* Save registers configuration */
    EyeBallVertical_SaveConfig();
}


/*******************************************************************************
* Function Name: EyeBallVertical_Wakeup
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
*  EyeBallVertical_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EyeBallVertical_Wakeup(void) 
{
     /* Restore registers values */
    EyeBallVertical_RestoreConfig();

    if(EyeBallVertical_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EyeBallVertical_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
