/*******************************************************************************
* File Name: BaseJaw_PM.c
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

#include "BaseJaw.h"

static BaseJaw_backupStruct BaseJaw_backup;


/*******************************************************************************
* Function Name: BaseJaw_SaveConfig
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
*  BaseJaw_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void BaseJaw_SaveConfig(void) 
{

    #if(!BaseJaw_UsingFixedFunction)
        #if(!BaseJaw_PWMModeIsCenterAligned)
            BaseJaw_backup.PWMPeriod = BaseJaw_ReadPeriod();
        #endif /* (!BaseJaw_PWMModeIsCenterAligned) */
        BaseJaw_backup.PWMUdb = BaseJaw_ReadCounter();
        #if (BaseJaw_UseStatus)
            BaseJaw_backup.InterruptMaskValue = BaseJaw_STATUS_MASK;
        #endif /* (BaseJaw_UseStatus) */

        #if(BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_256_CLOCKS || \
            BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_2_4_CLOCKS)
            BaseJaw_backup.PWMdeadBandValue = BaseJaw_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(BaseJaw_KillModeMinTime)
             BaseJaw_backup.PWMKillCounterPeriod = BaseJaw_ReadKillTime();
        #endif /* (BaseJaw_KillModeMinTime) */

        #if(BaseJaw_UseControl)
            BaseJaw_backup.PWMControlRegister = BaseJaw_ReadControlRegister();
        #endif /* (BaseJaw_UseControl) */
    #endif  /* (!BaseJaw_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: BaseJaw_RestoreConfig
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
*  BaseJaw_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void BaseJaw_RestoreConfig(void) 
{
        #if(!BaseJaw_UsingFixedFunction)
            #if(!BaseJaw_PWMModeIsCenterAligned)
                BaseJaw_WritePeriod(BaseJaw_backup.PWMPeriod);
            #endif /* (!BaseJaw_PWMModeIsCenterAligned) */

            BaseJaw_WriteCounter(BaseJaw_backup.PWMUdb);

            #if (BaseJaw_UseStatus)
                BaseJaw_STATUS_MASK = BaseJaw_backup.InterruptMaskValue;
            #endif /* (BaseJaw_UseStatus) */

            #if(BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_256_CLOCKS || \
                BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_2_4_CLOCKS)
                BaseJaw_WriteDeadTime(BaseJaw_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(BaseJaw_KillModeMinTime)
                BaseJaw_WriteKillTime(BaseJaw_backup.PWMKillCounterPeriod);
            #endif /* (BaseJaw_KillModeMinTime) */

            #if(BaseJaw_UseControl)
                BaseJaw_WriteControlRegister(BaseJaw_backup.PWMControlRegister);
            #endif /* (BaseJaw_UseControl) */
        #endif  /* (!BaseJaw_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: BaseJaw_Sleep
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
*  BaseJaw_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void BaseJaw_Sleep(void) 
{
    #if(BaseJaw_UseControl)
        if(BaseJaw_CTRL_ENABLE == (BaseJaw_CONTROL & BaseJaw_CTRL_ENABLE))
        {
            /*Component is enabled */
            BaseJaw_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            BaseJaw_backup.PWMEnableState = 0u;
        }
    #endif /* (BaseJaw_UseControl) */

    /* Stop component */
    BaseJaw_Stop();

    /* Save registers configuration */
    BaseJaw_SaveConfig();
}


/*******************************************************************************
* Function Name: BaseJaw_Wakeup
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
*  BaseJaw_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void BaseJaw_Wakeup(void) 
{
     /* Restore registers values */
    BaseJaw_RestoreConfig();

    if(BaseJaw_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        BaseJaw_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
