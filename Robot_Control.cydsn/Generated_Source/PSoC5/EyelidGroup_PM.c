/*******************************************************************************
* File Name: EyelidGroup_PM.c
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

#include "EyelidGroup.h"

static EyelidGroup_backupStruct EyelidGroup_backup;


/*******************************************************************************
* Function Name: EyelidGroup_SaveConfig
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
*  EyelidGroup_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void EyelidGroup_SaveConfig(void) 
{

    #if(!EyelidGroup_UsingFixedFunction)
        #if(!EyelidGroup_PWMModeIsCenterAligned)
            EyelidGroup_backup.PWMPeriod = EyelidGroup_ReadPeriod();
        #endif /* (!EyelidGroup_PWMModeIsCenterAligned) */
        EyelidGroup_backup.PWMUdb = EyelidGroup_ReadCounter();
        #if (EyelidGroup_UseStatus)
            EyelidGroup_backup.InterruptMaskValue = EyelidGroup_STATUS_MASK;
        #endif /* (EyelidGroup_UseStatus) */

        #if(EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_256_CLOCKS || \
            EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_2_4_CLOCKS)
            EyelidGroup_backup.PWMdeadBandValue = EyelidGroup_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(EyelidGroup_KillModeMinTime)
             EyelidGroup_backup.PWMKillCounterPeriod = EyelidGroup_ReadKillTime();
        #endif /* (EyelidGroup_KillModeMinTime) */

        #if(EyelidGroup_UseControl)
            EyelidGroup_backup.PWMControlRegister = EyelidGroup_ReadControlRegister();
        #endif /* (EyelidGroup_UseControl) */
    #endif  /* (!EyelidGroup_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: EyelidGroup_RestoreConfig
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
*  EyelidGroup_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void EyelidGroup_RestoreConfig(void) 
{
        #if(!EyelidGroup_UsingFixedFunction)
            #if(!EyelidGroup_PWMModeIsCenterAligned)
                EyelidGroup_WritePeriod(EyelidGroup_backup.PWMPeriod);
            #endif /* (!EyelidGroup_PWMModeIsCenterAligned) */

            EyelidGroup_WriteCounter(EyelidGroup_backup.PWMUdb);

            #if (EyelidGroup_UseStatus)
                EyelidGroup_STATUS_MASK = EyelidGroup_backup.InterruptMaskValue;
            #endif /* (EyelidGroup_UseStatus) */

            #if(EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_256_CLOCKS || \
                EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_2_4_CLOCKS)
                EyelidGroup_WriteDeadTime(EyelidGroup_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(EyelidGroup_KillModeMinTime)
                EyelidGroup_WriteKillTime(EyelidGroup_backup.PWMKillCounterPeriod);
            #endif /* (EyelidGroup_KillModeMinTime) */

            #if(EyelidGroup_UseControl)
                EyelidGroup_WriteControlRegister(EyelidGroup_backup.PWMControlRegister);
            #endif /* (EyelidGroup_UseControl) */
        #endif  /* (!EyelidGroup_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: EyelidGroup_Sleep
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
*  EyelidGroup_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void EyelidGroup_Sleep(void) 
{
    #if(EyelidGroup_UseControl)
        if(EyelidGroup_CTRL_ENABLE == (EyelidGroup_CONTROL & EyelidGroup_CTRL_ENABLE))
        {
            /*Component is enabled */
            EyelidGroup_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            EyelidGroup_backup.PWMEnableState = 0u;
        }
    #endif /* (EyelidGroup_UseControl) */

    /* Stop component */
    EyelidGroup_Stop();

    /* Save registers configuration */
    EyelidGroup_SaveConfig();
}


/*******************************************************************************
* Function Name: EyelidGroup_Wakeup
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
*  EyelidGroup_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void EyelidGroup_Wakeup(void) 
{
     /* Restore registers values */
    EyelidGroup_RestoreConfig();

    if(EyelidGroup_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        EyelidGroup_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
