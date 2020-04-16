/*******************************************************************************
* File Name: Neck_PM.c
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

#include "Neck.h"

static Neck_backupStruct Neck_backup;


/*******************************************************************************
* Function Name: Neck_SaveConfig
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
*  Neck_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Neck_SaveConfig(void) 
{

    #if(!Neck_UsingFixedFunction)
        #if(!Neck_PWMModeIsCenterAligned)
            Neck_backup.PWMPeriod = Neck_ReadPeriod();
        #endif /* (!Neck_PWMModeIsCenterAligned) */
        Neck_backup.PWMUdb = Neck_ReadCounter();
        #if (Neck_UseStatus)
            Neck_backup.InterruptMaskValue = Neck_STATUS_MASK;
        #endif /* (Neck_UseStatus) */

        #if(Neck_DeadBandMode == Neck__B_PWM__DBM_256_CLOCKS || \
            Neck_DeadBandMode == Neck__B_PWM__DBM_2_4_CLOCKS)
            Neck_backup.PWMdeadBandValue = Neck_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Neck_KillModeMinTime)
             Neck_backup.PWMKillCounterPeriod = Neck_ReadKillTime();
        #endif /* (Neck_KillModeMinTime) */

        #if(Neck_UseControl)
            Neck_backup.PWMControlRegister = Neck_ReadControlRegister();
        #endif /* (Neck_UseControl) */
    #endif  /* (!Neck_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Neck_RestoreConfig
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
*  Neck_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Neck_RestoreConfig(void) 
{
        #if(!Neck_UsingFixedFunction)
            #if(!Neck_PWMModeIsCenterAligned)
                Neck_WritePeriod(Neck_backup.PWMPeriod);
            #endif /* (!Neck_PWMModeIsCenterAligned) */

            Neck_WriteCounter(Neck_backup.PWMUdb);

            #if (Neck_UseStatus)
                Neck_STATUS_MASK = Neck_backup.InterruptMaskValue;
            #endif /* (Neck_UseStatus) */

            #if(Neck_DeadBandMode == Neck__B_PWM__DBM_256_CLOCKS || \
                Neck_DeadBandMode == Neck__B_PWM__DBM_2_4_CLOCKS)
                Neck_WriteDeadTime(Neck_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Neck_KillModeMinTime)
                Neck_WriteKillTime(Neck_backup.PWMKillCounterPeriod);
            #endif /* (Neck_KillModeMinTime) */

            #if(Neck_UseControl)
                Neck_WriteControlRegister(Neck_backup.PWMControlRegister);
            #endif /* (Neck_UseControl) */
        #endif  /* (!Neck_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Neck_Sleep
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
*  Neck_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Neck_Sleep(void) 
{
    #if(Neck_UseControl)
        if(Neck_CTRL_ENABLE == (Neck_CONTROL & Neck_CTRL_ENABLE))
        {
            /*Component is enabled */
            Neck_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Neck_backup.PWMEnableState = 0u;
        }
    #endif /* (Neck_UseControl) */

    /* Stop component */
    Neck_Stop();

    /* Save registers configuration */
    Neck_SaveConfig();
}


/*******************************************************************************
* Function Name: Neck_Wakeup
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
*  Neck_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Neck_Wakeup(void) 
{
     /* Restore registers values */
    Neck_RestoreConfig();

    if(Neck_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Neck_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
