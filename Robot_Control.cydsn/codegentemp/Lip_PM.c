/*******************************************************************************
* File Name: Lip_PM.c
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

#include "Lip.h"

static Lip_backupStruct Lip_backup;


/*******************************************************************************
* Function Name: Lip_SaveConfig
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
*  Lip_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Lip_SaveConfig(void) 
{

    #if(!Lip_UsingFixedFunction)
        #if(!Lip_PWMModeIsCenterAligned)
            Lip_backup.PWMPeriod = Lip_ReadPeriod();
        #endif /* (!Lip_PWMModeIsCenterAligned) */
        Lip_backup.PWMUdb = Lip_ReadCounter();
        #if (Lip_UseStatus)
            Lip_backup.InterruptMaskValue = Lip_STATUS_MASK;
        #endif /* (Lip_UseStatus) */

        #if(Lip_DeadBandMode == Lip__B_PWM__DBM_256_CLOCKS || \
            Lip_DeadBandMode == Lip__B_PWM__DBM_2_4_CLOCKS)
            Lip_backup.PWMdeadBandValue = Lip_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Lip_KillModeMinTime)
             Lip_backup.PWMKillCounterPeriod = Lip_ReadKillTime();
        #endif /* (Lip_KillModeMinTime) */

        #if(Lip_UseControl)
            Lip_backup.PWMControlRegister = Lip_ReadControlRegister();
        #endif /* (Lip_UseControl) */
    #endif  /* (!Lip_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Lip_RestoreConfig
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
*  Lip_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Lip_RestoreConfig(void) 
{
        #if(!Lip_UsingFixedFunction)
            #if(!Lip_PWMModeIsCenterAligned)
                Lip_WritePeriod(Lip_backup.PWMPeriod);
            #endif /* (!Lip_PWMModeIsCenterAligned) */

            Lip_WriteCounter(Lip_backup.PWMUdb);

            #if (Lip_UseStatus)
                Lip_STATUS_MASK = Lip_backup.InterruptMaskValue;
            #endif /* (Lip_UseStatus) */

            #if(Lip_DeadBandMode == Lip__B_PWM__DBM_256_CLOCKS || \
                Lip_DeadBandMode == Lip__B_PWM__DBM_2_4_CLOCKS)
                Lip_WriteDeadTime(Lip_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Lip_KillModeMinTime)
                Lip_WriteKillTime(Lip_backup.PWMKillCounterPeriod);
            #endif /* (Lip_KillModeMinTime) */

            #if(Lip_UseControl)
                Lip_WriteControlRegister(Lip_backup.PWMControlRegister);
            #endif /* (Lip_UseControl) */
        #endif  /* (!Lip_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Lip_Sleep
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
*  Lip_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Lip_Sleep(void) 
{
    #if(Lip_UseControl)
        if(Lip_CTRL_ENABLE == (Lip_CONTROL & Lip_CTRL_ENABLE))
        {
            /*Component is enabled */
            Lip_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Lip_backup.PWMEnableState = 0u;
        }
    #endif /* (Lip_UseControl) */

    /* Stop component */
    Lip_Stop();

    /* Save registers configuration */
    Lip_SaveConfig();
}


/*******************************************************************************
* Function Name: Lip_Wakeup
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
*  Lip_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Lip_Wakeup(void) 
{
     /* Restore registers values */
    Lip_RestoreConfig();

    if(Lip_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Lip_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
