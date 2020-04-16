/*******************************************************************************
* File Name: EyeBallHorizontal.h
* Version 3.30
*
* Description:
*  Contains the prototypes and constants for the functions available to the
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_EyeBallHorizontal_H)
#define CY_PWM_EyeBallHorizontal_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EyeBallHorizontal_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define EyeBallHorizontal_Resolution                     (16u)
#define EyeBallHorizontal_UsingFixedFunction             (0u)
#define EyeBallHorizontal_DeadBandMode                   (0u)
#define EyeBallHorizontal_KillModeMinTime                (0u)
#define EyeBallHorizontal_KillMode                       (0u)
#define EyeBallHorizontal_PWMMode                        (1u)
#define EyeBallHorizontal_PWMModeIsCenterAligned         (0u)
#define EyeBallHorizontal_DeadBandUsed                   (0u)
#define EyeBallHorizontal_DeadBand2_4                    (0u)

#if !defined(EyeBallHorizontal_PWMUDB_genblk8_stsreg__REMOVED)
    #define EyeBallHorizontal_UseStatus                  (1u)
#else
    #define EyeBallHorizontal_UseStatus                  (0u)
#endif /* !defined(EyeBallHorizontal_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define EyeBallHorizontal_UseControl                 (1u)
#else
    #define EyeBallHorizontal_UseControl                 (0u)
#endif /* !defined(EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define EyeBallHorizontal_UseOneCompareMode              (0u)
#define EyeBallHorizontal_MinimumKillTime                (1u)
#define EyeBallHorizontal_EnableMode                     (0u)

#define EyeBallHorizontal_CompareMode1SW                 (0u)
#define EyeBallHorizontal_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define EyeBallHorizontal__B_PWM__DISABLED 0
#define EyeBallHorizontal__B_PWM__ASYNCHRONOUS 1
#define EyeBallHorizontal__B_PWM__SINGLECYCLE 2
#define EyeBallHorizontal__B_PWM__LATCHED 3
#define EyeBallHorizontal__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define EyeBallHorizontal__B_PWM__DBMDISABLED 0
#define EyeBallHorizontal__B_PWM__DBM_2_4_CLOCKS 1
#define EyeBallHorizontal__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define EyeBallHorizontal__B_PWM__ONE_OUTPUT 0
#define EyeBallHorizontal__B_PWM__TWO_OUTPUTS 1
#define EyeBallHorizontal__B_PWM__DUAL_EDGE 2
#define EyeBallHorizontal__B_PWM__CENTER_ALIGN 3
#define EyeBallHorizontal__B_PWM__DITHER 5
#define EyeBallHorizontal__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define EyeBallHorizontal__B_PWM__LESS_THAN 1
#define EyeBallHorizontal__B_PWM__LESS_THAN_OR_EQUAL 2
#define EyeBallHorizontal__B_PWM__GREATER_THAN 3
#define EyeBallHorizontal__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define EyeBallHorizontal__B_PWM__EQUAL 0
#define EyeBallHorizontal__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!EyeBallHorizontal_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!EyeBallHorizontal_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!EyeBallHorizontal_PWMModeIsCenterAligned) */
        #if (EyeBallHorizontal_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (EyeBallHorizontal_UseStatus) */

        /* Backup for Deadband parameters */
        #if(EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_256_CLOCKS || \
            EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(EyeBallHorizontal_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (EyeBallHorizontal_KillModeMinTime) */

        /* Backup control register */
        #if(EyeBallHorizontal_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (EyeBallHorizontal_UseControl) */

    #endif /* (!EyeBallHorizontal_UsingFixedFunction) */

}EyeBallHorizontal_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    EyeBallHorizontal_Start(void) ;
void    EyeBallHorizontal_Stop(void) ;

#if (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction)
    void  EyeBallHorizontal_SetInterruptMode(uint8 interruptMode) ;
    uint8 EyeBallHorizontal_ReadStatusRegister(void) ;
#endif /* (EyeBallHorizontal_UseStatus || EyeBallHorizontal_UsingFixedFunction) */

#define EyeBallHorizontal_GetInterruptSource() EyeBallHorizontal_ReadStatusRegister()

#if (EyeBallHorizontal_UseControl)
    uint8 EyeBallHorizontal_ReadControlRegister(void) ;
    void  EyeBallHorizontal_WriteControlRegister(uint8 control)
          ;
#endif /* (EyeBallHorizontal_UseControl) */

#if (EyeBallHorizontal_UseOneCompareMode)
   #if (EyeBallHorizontal_CompareMode1SW)
       void    EyeBallHorizontal_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (EyeBallHorizontal_CompareMode1SW) */
#else
    #if (EyeBallHorizontal_CompareMode1SW)
        void    EyeBallHorizontal_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (EyeBallHorizontal_CompareMode1SW) */
    #if (EyeBallHorizontal_CompareMode2SW)
        void    EyeBallHorizontal_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (EyeBallHorizontal_CompareMode2SW) */
#endif /* (EyeBallHorizontal_UseOneCompareMode) */

#if (!EyeBallHorizontal_UsingFixedFunction)
    uint16   EyeBallHorizontal_ReadCounter(void) ;
    uint16 EyeBallHorizontal_ReadCapture(void) ;

    #if (EyeBallHorizontal_UseStatus)
            void EyeBallHorizontal_ClearFIFO(void) ;
    #endif /* (EyeBallHorizontal_UseStatus) */

    void    EyeBallHorizontal_WriteCounter(uint16 counter)
            ;
#endif /* (!EyeBallHorizontal_UsingFixedFunction) */

void    EyeBallHorizontal_WritePeriod(uint16 period)
        ;
uint16 EyeBallHorizontal_ReadPeriod(void) ;

#if (EyeBallHorizontal_UseOneCompareMode)
    void    EyeBallHorizontal_WriteCompare(uint16 compare)
            ;
    uint16 EyeBallHorizontal_ReadCompare(void) ;
#else
    void    EyeBallHorizontal_WriteCompare1(uint16 compare)
            ;
    uint16 EyeBallHorizontal_ReadCompare1(void) ;
    void    EyeBallHorizontal_WriteCompare2(uint16 compare)
            ;
    uint16 EyeBallHorizontal_ReadCompare2(void) ;
#endif /* (EyeBallHorizontal_UseOneCompareMode) */


#if (EyeBallHorizontal_DeadBandUsed)
    void    EyeBallHorizontal_WriteDeadTime(uint8 deadtime) ;
    uint8   EyeBallHorizontal_ReadDeadTime(void) ;
#endif /* (EyeBallHorizontal_DeadBandUsed) */

#if ( EyeBallHorizontal_KillModeMinTime)
    void EyeBallHorizontal_WriteKillTime(uint8 killtime) ;
    uint8 EyeBallHorizontal_ReadKillTime(void) ;
#endif /* ( EyeBallHorizontal_KillModeMinTime) */

void EyeBallHorizontal_Init(void) ;
void EyeBallHorizontal_Enable(void) ;
void EyeBallHorizontal_Sleep(void) ;
void EyeBallHorizontal_Wakeup(void) ;
void EyeBallHorizontal_SaveConfig(void) ;
void EyeBallHorizontal_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define EyeBallHorizontal_INIT_PERIOD_VALUE          (60000u)
#define EyeBallHorizontal_INIT_COMPARE_VALUE1        (0u)
#define EyeBallHorizontal_INIT_COMPARE_VALUE2        (0u)
#define EyeBallHorizontal_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    EyeBallHorizontal_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define EyeBallHorizontal_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)
#define EyeBallHorizontal_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)
#define EyeBallHorizontal_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (EyeBallHorizontal_UsingFixedFunction)
   #define EyeBallHorizontal_PERIOD_LSB              (*(reg16 *) EyeBallHorizontal_PWMHW__PER0)
   #define EyeBallHorizontal_PERIOD_LSB_PTR          ( (reg16 *) EyeBallHorizontal_PWMHW__PER0)
   #define EyeBallHorizontal_COMPARE1_LSB            (*(reg16 *) EyeBallHorizontal_PWMHW__CNT_CMP0)
   #define EyeBallHorizontal_COMPARE1_LSB_PTR        ( (reg16 *) EyeBallHorizontal_PWMHW__CNT_CMP0)
   #define EyeBallHorizontal_COMPARE2_LSB            (0x00u)
   #define EyeBallHorizontal_COMPARE2_LSB_PTR        (0x00u)
   #define EyeBallHorizontal_COUNTER_LSB             (*(reg16 *) EyeBallHorizontal_PWMHW__CNT_CMP0)
   #define EyeBallHorizontal_COUNTER_LSB_PTR         ( (reg16 *) EyeBallHorizontal_PWMHW__CNT_CMP0)
   #define EyeBallHorizontal_CAPTURE_LSB             (*(reg16 *) EyeBallHorizontal_PWMHW__CAP0)
   #define EyeBallHorizontal_CAPTURE_LSB_PTR         ( (reg16 *) EyeBallHorizontal_PWMHW__CAP0)
   #define EyeBallHorizontal_RT1                     (*(reg8 *)  EyeBallHorizontal_PWMHW__RT1)
   #define EyeBallHorizontal_RT1_PTR                 ( (reg8 *)  EyeBallHorizontal_PWMHW__RT1)

#else
   #if (EyeBallHorizontal_Resolution == 8u) /* 8bit - PWM */

       #if(EyeBallHorizontal_PWMModeIsCenterAligned)
           #define EyeBallHorizontal_PERIOD_LSB      (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define EyeBallHorizontal_PERIOD_LSB      (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (EyeBallHorizontal_PWMModeIsCenterAligned) */

       #define EyeBallHorizontal_COMPARE1_LSB        (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeBallHorizontal_COMPARE1_LSB_PTR    ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeBallHorizontal_COMPARE2_LSB        (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeBallHorizontal_COMPARE2_LSB_PTR    ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeBallHorizontal_COUNTERCAP_LSB      (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeBallHorizontal_COUNTERCAP_LSB_PTR  ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeBallHorizontal_COUNTER_LSB         (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeBallHorizontal_COUNTER_LSB_PTR     ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeBallHorizontal_CAPTURE_LSB         (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define EyeBallHorizontal_CAPTURE_LSB_PTR     ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(EyeBallHorizontal_PWMModeIsCenterAligned)
               #define EyeBallHorizontal_PERIOD_LSB      (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define EyeBallHorizontal_PERIOD_LSB      (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (EyeBallHorizontal_PWMModeIsCenterAligned) */

            #define EyeBallHorizontal_COMPARE1_LSB       (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeBallHorizontal_COMPARE1_LSB_PTR   ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeBallHorizontal_COMPARE2_LSB       (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeBallHorizontal_COMPARE2_LSB_PTR   ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeBallHorizontal_COUNTERCAP_LSB     (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeBallHorizontal_COUNTERCAP_LSB_PTR ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeBallHorizontal_COUNTER_LSB        (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeBallHorizontal_COUNTER_LSB_PTR    ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeBallHorizontal_CAPTURE_LSB        (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define EyeBallHorizontal_CAPTURE_LSB_PTR    ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(EyeBallHorizontal_PWMModeIsCenterAligned)
               #define EyeBallHorizontal_PERIOD_LSB      (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define EyeBallHorizontal_PERIOD_LSB      (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define EyeBallHorizontal_PERIOD_LSB_PTR  ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (EyeBallHorizontal_PWMModeIsCenterAligned) */

            #define EyeBallHorizontal_COMPARE1_LSB       (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeBallHorizontal_COMPARE1_LSB_PTR   ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeBallHorizontal_COMPARE2_LSB       (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeBallHorizontal_COMPARE2_LSB_PTR   ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeBallHorizontal_COUNTERCAP_LSB     (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeBallHorizontal_COUNTERCAP_LSB_PTR ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeBallHorizontal_COUNTER_LSB        (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeBallHorizontal_COUNTER_LSB_PTR    ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeBallHorizontal_CAPTURE_LSB        (*(reg16 *) EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define EyeBallHorizontal_CAPTURE_LSB_PTR    ((reg16 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define EyeBallHorizontal_AUX_CONTROLDP1          (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define EyeBallHorizontal_AUX_CONTROLDP1_PTR      ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (EyeBallHorizontal_Resolution == 8) */

   #define EyeBallHorizontal_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define EyeBallHorizontal_AUX_CONTROLDP0          (*(reg8 *)  EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define EyeBallHorizontal_AUX_CONTROLDP0_PTR      ((reg8 *)   EyeBallHorizontal_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (EyeBallHorizontal_UsingFixedFunction) */

#if(EyeBallHorizontal_KillModeMinTime )
    #define EyeBallHorizontal_KILLMODEMINTIME        (*(reg8 *)  EyeBallHorizontal_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define EyeBallHorizontal_KILLMODEMINTIME_PTR    ((reg8 *)   EyeBallHorizontal_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (EyeBallHorizontal_KillModeMinTime ) */

#if(EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_256_CLOCKS)
    #define EyeBallHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeBallHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeBallHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeBallHorizontal_DEADBAND_LSB_PTR       ((reg8 *)   EyeBallHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define EyeBallHorizontal_DEADBAND_LSB           (*(reg8 *)  EyeBallHorizontal_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (EyeBallHorizontal_UsingFixedFunction)
        #define EyeBallHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeBallHorizontal_PWMHW__CFG0)
        #define EyeBallHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallHorizontal_PWMHW__CFG0)
        #define EyeBallHorizontal_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeBallHorizontal_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define EyeBallHorizontal_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define EyeBallHorizontal_DEADBAND_COUNT         (*(reg8 *)  EyeBallHorizontal_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeBallHorizontal_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallHorizontal_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeBallHorizontal_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeBallHorizontal_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define EyeBallHorizontal_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (EyeBallHorizontal_UsingFixedFunction) */
#endif /* (EyeBallHorizontal_DeadBandMode == EyeBallHorizontal__B_PWM__DBM_256_CLOCKS) */



#if (EyeBallHorizontal_UsingFixedFunction)
    #define EyeBallHorizontal_STATUS                 (*(reg8 *) EyeBallHorizontal_PWMHW__SR0)
    #define EyeBallHorizontal_STATUS_PTR             ((reg8 *) EyeBallHorizontal_PWMHW__SR0)
    #define EyeBallHorizontal_STATUS_MASK            (*(reg8 *) EyeBallHorizontal_PWMHW__SR0)
    #define EyeBallHorizontal_STATUS_MASK_PTR        ((reg8 *) EyeBallHorizontal_PWMHW__SR0)
    #define EyeBallHorizontal_CONTROL                (*(reg8 *) EyeBallHorizontal_PWMHW__CFG0)
    #define EyeBallHorizontal_CONTROL_PTR            ((reg8 *) EyeBallHorizontal_PWMHW__CFG0)
    #define EyeBallHorizontal_CONTROL2               (*(reg8 *) EyeBallHorizontal_PWMHW__CFG1)
    #define EyeBallHorizontal_CONTROL3               (*(reg8 *) EyeBallHorizontal_PWMHW__CFG2)
    #define EyeBallHorizontal_GLOBAL_ENABLE          (*(reg8 *) EyeBallHorizontal_PWMHW__PM_ACT_CFG)
    #define EyeBallHorizontal_GLOBAL_ENABLE_PTR      ( (reg8 *) EyeBallHorizontal_PWMHW__PM_ACT_CFG)
    #define EyeBallHorizontal_GLOBAL_STBY_ENABLE     (*(reg8 *) EyeBallHorizontal_PWMHW__PM_STBY_CFG)
    #define EyeBallHorizontal_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) EyeBallHorizontal_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define EyeBallHorizontal_BLOCK_EN_MASK          (EyeBallHorizontal_PWMHW__PM_ACT_MSK)
    #define EyeBallHorizontal_BLOCK_STBY_EN_MASK     (EyeBallHorizontal_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define EyeBallHorizontal_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define EyeBallHorizontal_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define EyeBallHorizontal_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define EyeBallHorizontal_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define EyeBallHorizontal_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define EyeBallHorizontal_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define EyeBallHorizontal_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeBallHorizontal_CTRL_ENABLE_SHIFT)
    #define EyeBallHorizontal_CTRL_RESET             (uint8)((uint8)0x01u << EyeBallHorizontal_CTRL_RESET_SHIFT)
    #define EyeBallHorizontal_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)
    #define EyeBallHorizontal_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EyeBallHorizontal_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define EyeBallHorizontal_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << EyeBallHorizontal_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define EyeBallHorizontal_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define EyeBallHorizontal_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define EyeBallHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeBallHorizontal_STATUS_TC_INT_EN_MASK_SHIFT            (EyeBallHorizontal_STATUS_TC_SHIFT - 4u)
    #define EyeBallHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeBallHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeBallHorizontal_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define EyeBallHorizontal_STATUS_TC              (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_TC_SHIFT)
    #define EyeBallHorizontal_STATUS_CMP1            (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define EyeBallHorizontal_STATUS_TC_INT_EN_MASK              (uint8)((uint8)EyeBallHorizontal_STATUS_TC >> 4u)
    #define EyeBallHorizontal_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)EyeBallHorizontal_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define EyeBallHorizontal_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define EyeBallHorizontal_RT1_MASK              (uint8)((uint8)0x03u << EyeBallHorizontal_RT1_SHIFT)
    #define EyeBallHorizontal_SYNC                  (uint8)((uint8)0x03u << EyeBallHorizontal_RT1_SHIFT)
    #define EyeBallHorizontal_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define EyeBallHorizontal_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << EyeBallHorizontal_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define EyeBallHorizontal_SYNCDSI_EN            (uint8)((uint8)0x0Fu << EyeBallHorizontal_SYNCDSI_SHIFT)


#else
    #define EyeBallHorizontal_STATUS                (*(reg8 *)   EyeBallHorizontal_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeBallHorizontal_STATUS_PTR            ((reg8 *)    EyeBallHorizontal_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeBallHorizontal_STATUS_MASK           (*(reg8 *)   EyeBallHorizontal_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeBallHorizontal_STATUS_MASK_PTR       ((reg8 *)    EyeBallHorizontal_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeBallHorizontal_STATUS_AUX_CTRL       (*(reg8 *)   EyeBallHorizontal_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define EyeBallHorizontal_CONTROL               (*(reg8 *)   EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define EyeBallHorizontal_CONTROL_PTR           ((reg8 *)    EyeBallHorizontal_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define EyeBallHorizontal_CTRL_ENABLE_SHIFT      (0x07u)
    #define EyeBallHorizontal_CTRL_RESET_SHIFT       (0x06u)
    #define EyeBallHorizontal_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define EyeBallHorizontal_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define EyeBallHorizontal_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define EyeBallHorizontal_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeBallHorizontal_CTRL_ENABLE_SHIFT)
    #define EyeBallHorizontal_CTRL_RESET             (uint8)((uint8)0x01u << EyeBallHorizontal_CTRL_RESET_SHIFT)
    #define EyeBallHorizontal_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeBallHorizontal_CTRL_CMPMODE2_SHIFT)
    #define EyeBallHorizontal_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeBallHorizontal_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define EyeBallHorizontal_STATUS_KILL_SHIFT          (0x05u)
    #define EyeBallHorizontal_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define EyeBallHorizontal_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define EyeBallHorizontal_STATUS_TC_SHIFT            (0x02u)
    #define EyeBallHorizontal_STATUS_CMP2_SHIFT          (0x01u)
    #define EyeBallHorizontal_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define EyeBallHorizontal_STATUS_KILL_INT_EN_MASK_SHIFT          (EyeBallHorizontal_STATUS_KILL_SHIFT)
    #define EyeBallHorizontal_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (EyeBallHorizontal_STATUS_FIFONEMPTY_SHIFT)
    #define EyeBallHorizontal_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (EyeBallHorizontal_STATUS_FIFOFULL_SHIFT)
    #define EyeBallHorizontal_STATUS_TC_INT_EN_MASK_SHIFT            (EyeBallHorizontal_STATUS_TC_SHIFT)
    #define EyeBallHorizontal_STATUS_CMP2_INT_EN_MASK_SHIFT          (EyeBallHorizontal_STATUS_CMP2_SHIFT)
    #define EyeBallHorizontal_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeBallHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define EyeBallHorizontal_STATUS_KILL            (uint8)((uint8)0x00u << EyeBallHorizontal_STATUS_KILL_SHIFT )
    #define EyeBallHorizontal_STATUS_FIFOFULL        (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_FIFOFULL_SHIFT)
    #define EyeBallHorizontal_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_FIFONEMPTY_SHIFT)
    #define EyeBallHorizontal_STATUS_TC              (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_TC_SHIFT)
    #define EyeBallHorizontal_STATUS_CMP2            (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_CMP2_SHIFT)
    #define EyeBallHorizontal_STATUS_CMP1            (uint8)((uint8)0x01u << EyeBallHorizontal_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define EyeBallHorizontal_STATUS_KILL_INT_EN_MASK            (EyeBallHorizontal_STATUS_KILL)
    #define EyeBallHorizontal_STATUS_FIFOFULL_INT_EN_MASK        (EyeBallHorizontal_STATUS_FIFOFULL)
    #define EyeBallHorizontal_STATUS_FIFONEMPTY_INT_EN_MASK      (EyeBallHorizontal_STATUS_FIFONEMPTY)
    #define EyeBallHorizontal_STATUS_TC_INT_EN_MASK              (EyeBallHorizontal_STATUS_TC)
    #define EyeBallHorizontal_STATUS_CMP2_INT_EN_MASK            (EyeBallHorizontal_STATUS_CMP2)
    #define EyeBallHorizontal_STATUS_CMP1_INT_EN_MASK            (EyeBallHorizontal_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define EyeBallHorizontal_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define EyeBallHorizontal_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define EyeBallHorizontal_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define EyeBallHorizontal_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define EyeBallHorizontal_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* EyeBallHorizontal_UsingFixedFunction */

#endif  /* CY_PWM_EyeBallHorizontal_H */


/* [] END OF FILE */
