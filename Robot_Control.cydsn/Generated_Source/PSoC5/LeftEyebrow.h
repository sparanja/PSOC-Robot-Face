/*******************************************************************************
* File Name: LeftEyebrow.h
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

#if !defined(CY_PWM_LeftEyebrow_H)
#define CY_PWM_LeftEyebrow_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 LeftEyebrow_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define LeftEyebrow_Resolution                     (16u)
#define LeftEyebrow_UsingFixedFunction             (0u)
#define LeftEyebrow_DeadBandMode                   (0u)
#define LeftEyebrow_KillModeMinTime                (0u)
#define LeftEyebrow_KillMode                       (0u)
#define LeftEyebrow_PWMMode                        (1u)
#define LeftEyebrow_PWMModeIsCenterAligned         (0u)
#define LeftEyebrow_DeadBandUsed                   (0u)
#define LeftEyebrow_DeadBand2_4                    (0u)

#if !defined(LeftEyebrow_PWMUDB_genblk8_stsreg__REMOVED)
    #define LeftEyebrow_UseStatus                  (1u)
#else
    #define LeftEyebrow_UseStatus                  (0u)
#endif /* !defined(LeftEyebrow_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(LeftEyebrow_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define LeftEyebrow_UseControl                 (1u)
#else
    #define LeftEyebrow_UseControl                 (0u)
#endif /* !defined(LeftEyebrow_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define LeftEyebrow_UseOneCompareMode              (0u)
#define LeftEyebrow_MinimumKillTime                (1u)
#define LeftEyebrow_EnableMode                     (0u)

#define LeftEyebrow_CompareMode1SW                 (0u)
#define LeftEyebrow_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define LeftEyebrow__B_PWM__DISABLED 0
#define LeftEyebrow__B_PWM__ASYNCHRONOUS 1
#define LeftEyebrow__B_PWM__SINGLECYCLE 2
#define LeftEyebrow__B_PWM__LATCHED 3
#define LeftEyebrow__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define LeftEyebrow__B_PWM__DBMDISABLED 0
#define LeftEyebrow__B_PWM__DBM_2_4_CLOCKS 1
#define LeftEyebrow__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define LeftEyebrow__B_PWM__ONE_OUTPUT 0
#define LeftEyebrow__B_PWM__TWO_OUTPUTS 1
#define LeftEyebrow__B_PWM__DUAL_EDGE 2
#define LeftEyebrow__B_PWM__CENTER_ALIGN 3
#define LeftEyebrow__B_PWM__DITHER 5
#define LeftEyebrow__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define LeftEyebrow__B_PWM__LESS_THAN 1
#define LeftEyebrow__B_PWM__LESS_THAN_OR_EQUAL 2
#define LeftEyebrow__B_PWM__GREATER_THAN 3
#define LeftEyebrow__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define LeftEyebrow__B_PWM__EQUAL 0
#define LeftEyebrow__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!LeftEyebrow_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!LeftEyebrow_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!LeftEyebrow_PWMModeIsCenterAligned) */
        #if (LeftEyebrow_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (LeftEyebrow_UseStatus) */

        /* Backup for Deadband parameters */
        #if(LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_256_CLOCKS || \
            LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(LeftEyebrow_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (LeftEyebrow_KillModeMinTime) */

        /* Backup control register */
        #if(LeftEyebrow_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (LeftEyebrow_UseControl) */

    #endif /* (!LeftEyebrow_UsingFixedFunction) */

}LeftEyebrow_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    LeftEyebrow_Start(void) ;
void    LeftEyebrow_Stop(void) ;

#if (LeftEyebrow_UseStatus || LeftEyebrow_UsingFixedFunction)
    void  LeftEyebrow_SetInterruptMode(uint8 interruptMode) ;
    uint8 LeftEyebrow_ReadStatusRegister(void) ;
#endif /* (LeftEyebrow_UseStatus || LeftEyebrow_UsingFixedFunction) */

#define LeftEyebrow_GetInterruptSource() LeftEyebrow_ReadStatusRegister()

#if (LeftEyebrow_UseControl)
    uint8 LeftEyebrow_ReadControlRegister(void) ;
    void  LeftEyebrow_WriteControlRegister(uint8 control)
          ;
#endif /* (LeftEyebrow_UseControl) */

#if (LeftEyebrow_UseOneCompareMode)
   #if (LeftEyebrow_CompareMode1SW)
       void    LeftEyebrow_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (LeftEyebrow_CompareMode1SW) */
#else
    #if (LeftEyebrow_CompareMode1SW)
        void    LeftEyebrow_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (LeftEyebrow_CompareMode1SW) */
    #if (LeftEyebrow_CompareMode2SW)
        void    LeftEyebrow_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (LeftEyebrow_CompareMode2SW) */
#endif /* (LeftEyebrow_UseOneCompareMode) */

#if (!LeftEyebrow_UsingFixedFunction)
    uint16   LeftEyebrow_ReadCounter(void) ;
    uint16 LeftEyebrow_ReadCapture(void) ;

    #if (LeftEyebrow_UseStatus)
            void LeftEyebrow_ClearFIFO(void) ;
    #endif /* (LeftEyebrow_UseStatus) */

    void    LeftEyebrow_WriteCounter(uint16 counter)
            ;
#endif /* (!LeftEyebrow_UsingFixedFunction) */

void    LeftEyebrow_WritePeriod(uint16 period)
        ;
uint16 LeftEyebrow_ReadPeriod(void) ;

#if (LeftEyebrow_UseOneCompareMode)
    void    LeftEyebrow_WriteCompare(uint16 compare)
            ;
    uint16 LeftEyebrow_ReadCompare(void) ;
#else
    void    LeftEyebrow_WriteCompare1(uint16 compare)
            ;
    uint16 LeftEyebrow_ReadCompare1(void) ;
    void    LeftEyebrow_WriteCompare2(uint16 compare)
            ;
    uint16 LeftEyebrow_ReadCompare2(void) ;
#endif /* (LeftEyebrow_UseOneCompareMode) */


#if (LeftEyebrow_DeadBandUsed)
    void    LeftEyebrow_WriteDeadTime(uint8 deadtime) ;
    uint8   LeftEyebrow_ReadDeadTime(void) ;
#endif /* (LeftEyebrow_DeadBandUsed) */

#if ( LeftEyebrow_KillModeMinTime)
    void LeftEyebrow_WriteKillTime(uint8 killtime) ;
    uint8 LeftEyebrow_ReadKillTime(void) ;
#endif /* ( LeftEyebrow_KillModeMinTime) */

void LeftEyebrow_Init(void) ;
void LeftEyebrow_Enable(void) ;
void LeftEyebrow_Sleep(void) ;
void LeftEyebrow_Wakeup(void) ;
void LeftEyebrow_SaveConfig(void) ;
void LeftEyebrow_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define LeftEyebrow_INIT_PERIOD_VALUE          (19000u)
#define LeftEyebrow_INIT_COMPARE_VALUE1        (0u)
#define LeftEyebrow_INIT_COMPARE_VALUE2        (0u)
#define LeftEyebrow_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    LeftEyebrow_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LeftEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LeftEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    LeftEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define LeftEyebrow_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  LeftEyebrow_CTRL_CMPMODE2_SHIFT)
#define LeftEyebrow_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  LeftEyebrow_CTRL_CMPMODE1_SHIFT)
#define LeftEyebrow_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (LeftEyebrow_UsingFixedFunction)
   #define LeftEyebrow_PERIOD_LSB              (*(reg16 *) LeftEyebrow_PWMHW__PER0)
   #define LeftEyebrow_PERIOD_LSB_PTR          ( (reg16 *) LeftEyebrow_PWMHW__PER0)
   #define LeftEyebrow_COMPARE1_LSB            (*(reg16 *) LeftEyebrow_PWMHW__CNT_CMP0)
   #define LeftEyebrow_COMPARE1_LSB_PTR        ( (reg16 *) LeftEyebrow_PWMHW__CNT_CMP0)
   #define LeftEyebrow_COMPARE2_LSB            (0x00u)
   #define LeftEyebrow_COMPARE2_LSB_PTR        (0x00u)
   #define LeftEyebrow_COUNTER_LSB             (*(reg16 *) LeftEyebrow_PWMHW__CNT_CMP0)
   #define LeftEyebrow_COUNTER_LSB_PTR         ( (reg16 *) LeftEyebrow_PWMHW__CNT_CMP0)
   #define LeftEyebrow_CAPTURE_LSB             (*(reg16 *) LeftEyebrow_PWMHW__CAP0)
   #define LeftEyebrow_CAPTURE_LSB_PTR         ( (reg16 *) LeftEyebrow_PWMHW__CAP0)
   #define LeftEyebrow_RT1                     (*(reg8 *)  LeftEyebrow_PWMHW__RT1)
   #define LeftEyebrow_RT1_PTR                 ( (reg8 *)  LeftEyebrow_PWMHW__RT1)

#else
   #if (LeftEyebrow_Resolution == 8u) /* 8bit - PWM */

       #if(LeftEyebrow_PWMModeIsCenterAligned)
           #define LeftEyebrow_PERIOD_LSB      (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define LeftEyebrow_PERIOD_LSB_PTR  ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define LeftEyebrow_PERIOD_LSB      (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define LeftEyebrow_PERIOD_LSB_PTR  ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (LeftEyebrow_PWMModeIsCenterAligned) */

       #define LeftEyebrow_COMPARE1_LSB        (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LeftEyebrow_COMPARE1_LSB_PTR    ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define LeftEyebrow_COMPARE2_LSB        (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LeftEyebrow_COMPARE2_LSB_PTR    ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define LeftEyebrow_COUNTERCAP_LSB      (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LeftEyebrow_COUNTERCAP_LSB_PTR  ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define LeftEyebrow_COUNTER_LSB         (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LeftEyebrow_COUNTER_LSB_PTR     ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define LeftEyebrow_CAPTURE_LSB         (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define LeftEyebrow_CAPTURE_LSB_PTR     ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(LeftEyebrow_PWMModeIsCenterAligned)
               #define LeftEyebrow_PERIOD_LSB      (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define LeftEyebrow_PERIOD_LSB_PTR  ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define LeftEyebrow_PERIOD_LSB      (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define LeftEyebrow_PERIOD_LSB_PTR  ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (LeftEyebrow_PWMModeIsCenterAligned) */

            #define LeftEyebrow_COMPARE1_LSB       (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LeftEyebrow_COMPARE1_LSB_PTR   ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define LeftEyebrow_COMPARE2_LSB       (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LeftEyebrow_COMPARE2_LSB_PTR   ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define LeftEyebrow_COUNTERCAP_LSB     (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LeftEyebrow_COUNTERCAP_LSB_PTR ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define LeftEyebrow_COUNTER_LSB        (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LeftEyebrow_COUNTER_LSB_PTR    ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define LeftEyebrow_CAPTURE_LSB        (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define LeftEyebrow_CAPTURE_LSB_PTR    ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(LeftEyebrow_PWMModeIsCenterAligned)
               #define LeftEyebrow_PERIOD_LSB      (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define LeftEyebrow_PERIOD_LSB_PTR  ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define LeftEyebrow_PERIOD_LSB      (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define LeftEyebrow_PERIOD_LSB_PTR  ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (LeftEyebrow_PWMModeIsCenterAligned) */

            #define LeftEyebrow_COMPARE1_LSB       (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LeftEyebrow_COMPARE1_LSB_PTR   ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define LeftEyebrow_COMPARE2_LSB       (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LeftEyebrow_COMPARE2_LSB_PTR   ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define LeftEyebrow_COUNTERCAP_LSB     (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LeftEyebrow_COUNTERCAP_LSB_PTR ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define LeftEyebrow_COUNTER_LSB        (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LeftEyebrow_COUNTER_LSB_PTR    ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define LeftEyebrow_CAPTURE_LSB        (*(reg16 *) LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define LeftEyebrow_CAPTURE_LSB_PTR    ((reg16 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define LeftEyebrow_AUX_CONTROLDP1          (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define LeftEyebrow_AUX_CONTROLDP1_PTR      ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (LeftEyebrow_Resolution == 8) */

   #define LeftEyebrow_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define LeftEyebrow_AUX_CONTROLDP0          (*(reg8 *)  LeftEyebrow_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define LeftEyebrow_AUX_CONTROLDP0_PTR      ((reg8 *)   LeftEyebrow_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (LeftEyebrow_UsingFixedFunction) */

#if(LeftEyebrow_KillModeMinTime )
    #define LeftEyebrow_KILLMODEMINTIME        (*(reg8 *)  LeftEyebrow_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define LeftEyebrow_KILLMODEMINTIME_PTR    ((reg8 *)   LeftEyebrow_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (LeftEyebrow_KillModeMinTime ) */

#if(LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_256_CLOCKS)
    #define LeftEyebrow_DEADBAND_COUNT         (*(reg8 *)  LeftEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LeftEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   LeftEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define LeftEyebrow_DEADBAND_LSB_PTR       ((reg8 *)   LeftEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define LeftEyebrow_DEADBAND_LSB           (*(reg8 *)  LeftEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (LeftEyebrow_UsingFixedFunction)
        #define LeftEyebrow_DEADBAND_COUNT         (*(reg8 *)  LeftEyebrow_PWMHW__CFG0)
        #define LeftEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   LeftEyebrow_PWMHW__CFG0)
        #define LeftEyebrow_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LeftEyebrow_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define LeftEyebrow_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define LeftEyebrow_DEADBAND_COUNT         (*(reg8 *)  LeftEyebrow_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LeftEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   LeftEyebrow_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define LeftEyebrow_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << LeftEyebrow_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define LeftEyebrow_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (LeftEyebrow_UsingFixedFunction) */
#endif /* (LeftEyebrow_DeadBandMode == LeftEyebrow__B_PWM__DBM_256_CLOCKS) */



#if (LeftEyebrow_UsingFixedFunction)
    #define LeftEyebrow_STATUS                 (*(reg8 *) LeftEyebrow_PWMHW__SR0)
    #define LeftEyebrow_STATUS_PTR             ((reg8 *) LeftEyebrow_PWMHW__SR0)
    #define LeftEyebrow_STATUS_MASK            (*(reg8 *) LeftEyebrow_PWMHW__SR0)
    #define LeftEyebrow_STATUS_MASK_PTR        ((reg8 *) LeftEyebrow_PWMHW__SR0)
    #define LeftEyebrow_CONTROL                (*(reg8 *) LeftEyebrow_PWMHW__CFG0)
    #define LeftEyebrow_CONTROL_PTR            ((reg8 *) LeftEyebrow_PWMHW__CFG0)
    #define LeftEyebrow_CONTROL2               (*(reg8 *) LeftEyebrow_PWMHW__CFG1)
    #define LeftEyebrow_CONTROL3               (*(reg8 *) LeftEyebrow_PWMHW__CFG2)
    #define LeftEyebrow_GLOBAL_ENABLE          (*(reg8 *) LeftEyebrow_PWMHW__PM_ACT_CFG)
    #define LeftEyebrow_GLOBAL_ENABLE_PTR      ( (reg8 *) LeftEyebrow_PWMHW__PM_ACT_CFG)
    #define LeftEyebrow_GLOBAL_STBY_ENABLE     (*(reg8 *) LeftEyebrow_PWMHW__PM_STBY_CFG)
    #define LeftEyebrow_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) LeftEyebrow_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define LeftEyebrow_BLOCK_EN_MASK          (LeftEyebrow_PWMHW__PM_ACT_MSK)
    #define LeftEyebrow_BLOCK_STBY_EN_MASK     (LeftEyebrow_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define LeftEyebrow_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define LeftEyebrow_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define LeftEyebrow_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define LeftEyebrow_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define LeftEyebrow_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define LeftEyebrow_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define LeftEyebrow_CTRL_ENABLE            (uint8)((uint8)0x01u << LeftEyebrow_CTRL_ENABLE_SHIFT)
    #define LeftEyebrow_CTRL_RESET             (uint8)((uint8)0x01u << LeftEyebrow_CTRL_RESET_SHIFT)
    #define LeftEyebrow_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LeftEyebrow_CTRL_CMPMODE2_SHIFT)
    #define LeftEyebrow_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LeftEyebrow_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define LeftEyebrow_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define LeftEyebrow_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << LeftEyebrow_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define LeftEyebrow_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define LeftEyebrow_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define LeftEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define LeftEyebrow_STATUS_TC_INT_EN_MASK_SHIFT            (LeftEyebrow_STATUS_TC_SHIFT - 4u)
    #define LeftEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define LeftEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT          (LeftEyebrow_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define LeftEyebrow_STATUS_TC              (uint8)((uint8)0x01u << LeftEyebrow_STATUS_TC_SHIFT)
    #define LeftEyebrow_STATUS_CMP1            (uint8)((uint8)0x01u << LeftEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define LeftEyebrow_STATUS_TC_INT_EN_MASK              (uint8)((uint8)LeftEyebrow_STATUS_TC >> 4u)
    #define LeftEyebrow_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)LeftEyebrow_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define LeftEyebrow_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define LeftEyebrow_RT1_MASK              (uint8)((uint8)0x03u << LeftEyebrow_RT1_SHIFT)
    #define LeftEyebrow_SYNC                  (uint8)((uint8)0x03u << LeftEyebrow_RT1_SHIFT)
    #define LeftEyebrow_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define LeftEyebrow_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << LeftEyebrow_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define LeftEyebrow_SYNCDSI_EN            (uint8)((uint8)0x0Fu << LeftEyebrow_SYNCDSI_SHIFT)


#else
    #define LeftEyebrow_STATUS                (*(reg8 *)   LeftEyebrow_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LeftEyebrow_STATUS_PTR            ((reg8 *)    LeftEyebrow_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define LeftEyebrow_STATUS_MASK           (*(reg8 *)   LeftEyebrow_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LeftEyebrow_STATUS_MASK_PTR       ((reg8 *)    LeftEyebrow_PWMUDB_genblk8_stsreg__MASK_REG)
    #define LeftEyebrow_STATUS_AUX_CTRL       (*(reg8 *)   LeftEyebrow_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define LeftEyebrow_CONTROL               (*(reg8 *)   LeftEyebrow_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define LeftEyebrow_CONTROL_PTR           ((reg8 *)    LeftEyebrow_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define LeftEyebrow_CTRL_ENABLE_SHIFT      (0x07u)
    #define LeftEyebrow_CTRL_RESET_SHIFT       (0x06u)
    #define LeftEyebrow_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define LeftEyebrow_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define LeftEyebrow_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define LeftEyebrow_CTRL_ENABLE            (uint8)((uint8)0x01u << LeftEyebrow_CTRL_ENABLE_SHIFT)
    #define LeftEyebrow_CTRL_RESET             (uint8)((uint8)0x01u << LeftEyebrow_CTRL_RESET_SHIFT)
    #define LeftEyebrow_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << LeftEyebrow_CTRL_CMPMODE2_SHIFT)
    #define LeftEyebrow_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << LeftEyebrow_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define LeftEyebrow_STATUS_KILL_SHIFT          (0x05u)
    #define LeftEyebrow_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define LeftEyebrow_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define LeftEyebrow_STATUS_TC_SHIFT            (0x02u)
    #define LeftEyebrow_STATUS_CMP2_SHIFT          (0x01u)
    #define LeftEyebrow_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define LeftEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT          (LeftEyebrow_STATUS_KILL_SHIFT)
    #define LeftEyebrow_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (LeftEyebrow_STATUS_FIFONEMPTY_SHIFT)
    #define LeftEyebrow_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (LeftEyebrow_STATUS_FIFOFULL_SHIFT)
    #define LeftEyebrow_STATUS_TC_INT_EN_MASK_SHIFT            (LeftEyebrow_STATUS_TC_SHIFT)
    #define LeftEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT          (LeftEyebrow_STATUS_CMP2_SHIFT)
    #define LeftEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT          (LeftEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define LeftEyebrow_STATUS_KILL            (uint8)((uint8)0x00u << LeftEyebrow_STATUS_KILL_SHIFT )
    #define LeftEyebrow_STATUS_FIFOFULL        (uint8)((uint8)0x01u << LeftEyebrow_STATUS_FIFOFULL_SHIFT)
    #define LeftEyebrow_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << LeftEyebrow_STATUS_FIFONEMPTY_SHIFT)
    #define LeftEyebrow_STATUS_TC              (uint8)((uint8)0x01u << LeftEyebrow_STATUS_TC_SHIFT)
    #define LeftEyebrow_STATUS_CMP2            (uint8)((uint8)0x01u << LeftEyebrow_STATUS_CMP2_SHIFT)
    #define LeftEyebrow_STATUS_CMP1            (uint8)((uint8)0x01u << LeftEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define LeftEyebrow_STATUS_KILL_INT_EN_MASK            (LeftEyebrow_STATUS_KILL)
    #define LeftEyebrow_STATUS_FIFOFULL_INT_EN_MASK        (LeftEyebrow_STATUS_FIFOFULL)
    #define LeftEyebrow_STATUS_FIFONEMPTY_INT_EN_MASK      (LeftEyebrow_STATUS_FIFONEMPTY)
    #define LeftEyebrow_STATUS_TC_INT_EN_MASK              (LeftEyebrow_STATUS_TC)
    #define LeftEyebrow_STATUS_CMP2_INT_EN_MASK            (LeftEyebrow_STATUS_CMP2)
    #define LeftEyebrow_STATUS_CMP1_INT_EN_MASK            (LeftEyebrow_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define LeftEyebrow_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define LeftEyebrow_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define LeftEyebrow_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define LeftEyebrow_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define LeftEyebrow_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* LeftEyebrow_UsingFixedFunction */

#endif  /* CY_PWM_LeftEyebrow_H */


/* [] END OF FILE */
