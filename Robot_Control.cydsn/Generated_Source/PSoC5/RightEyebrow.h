/*******************************************************************************
* File Name: RightEyebrow.h
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

#if !defined(CY_PWM_RightEyebrow_H)
#define CY_PWM_RightEyebrow_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 RightEyebrow_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define RightEyebrow_Resolution                     (16u)
#define RightEyebrow_UsingFixedFunction             (0u)
#define RightEyebrow_DeadBandMode                   (0u)
#define RightEyebrow_KillModeMinTime                (0u)
#define RightEyebrow_KillMode                       (0u)
#define RightEyebrow_PWMMode                        (1u)
#define RightEyebrow_PWMModeIsCenterAligned         (0u)
#define RightEyebrow_DeadBandUsed                   (0u)
#define RightEyebrow_DeadBand2_4                    (0u)

#if !defined(RightEyebrow_PWMUDB_genblk8_stsreg__REMOVED)
    #define RightEyebrow_UseStatus                  (1u)
#else
    #define RightEyebrow_UseStatus                  (0u)
#endif /* !defined(RightEyebrow_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(RightEyebrow_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define RightEyebrow_UseControl                 (1u)
#else
    #define RightEyebrow_UseControl                 (0u)
#endif /* !defined(RightEyebrow_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define RightEyebrow_UseOneCompareMode              (0u)
#define RightEyebrow_MinimumKillTime                (1u)
#define RightEyebrow_EnableMode                     (0u)

#define RightEyebrow_CompareMode1SW                 (0u)
#define RightEyebrow_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define RightEyebrow__B_PWM__DISABLED 0
#define RightEyebrow__B_PWM__ASYNCHRONOUS 1
#define RightEyebrow__B_PWM__SINGLECYCLE 2
#define RightEyebrow__B_PWM__LATCHED 3
#define RightEyebrow__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define RightEyebrow__B_PWM__DBMDISABLED 0
#define RightEyebrow__B_PWM__DBM_2_4_CLOCKS 1
#define RightEyebrow__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define RightEyebrow__B_PWM__ONE_OUTPUT 0
#define RightEyebrow__B_PWM__TWO_OUTPUTS 1
#define RightEyebrow__B_PWM__DUAL_EDGE 2
#define RightEyebrow__B_PWM__CENTER_ALIGN 3
#define RightEyebrow__B_PWM__DITHER 5
#define RightEyebrow__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define RightEyebrow__B_PWM__LESS_THAN 1
#define RightEyebrow__B_PWM__LESS_THAN_OR_EQUAL 2
#define RightEyebrow__B_PWM__GREATER_THAN 3
#define RightEyebrow__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define RightEyebrow__B_PWM__EQUAL 0
#define RightEyebrow__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!RightEyebrow_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!RightEyebrow_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!RightEyebrow_PWMModeIsCenterAligned) */
        #if (RightEyebrow_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (RightEyebrow_UseStatus) */

        /* Backup for Deadband parameters */
        #if(RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_256_CLOCKS || \
            RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(RightEyebrow_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (RightEyebrow_KillModeMinTime) */

        /* Backup control register */
        #if(RightEyebrow_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (RightEyebrow_UseControl) */

    #endif /* (!RightEyebrow_UsingFixedFunction) */

}RightEyebrow_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    RightEyebrow_Start(void) ;
void    RightEyebrow_Stop(void) ;

#if (RightEyebrow_UseStatus || RightEyebrow_UsingFixedFunction)
    void  RightEyebrow_SetInterruptMode(uint8 interruptMode) ;
    uint8 RightEyebrow_ReadStatusRegister(void) ;
#endif /* (RightEyebrow_UseStatus || RightEyebrow_UsingFixedFunction) */

#define RightEyebrow_GetInterruptSource() RightEyebrow_ReadStatusRegister()

#if (RightEyebrow_UseControl)
    uint8 RightEyebrow_ReadControlRegister(void) ;
    void  RightEyebrow_WriteControlRegister(uint8 control)
          ;
#endif /* (RightEyebrow_UseControl) */

#if (RightEyebrow_UseOneCompareMode)
   #if (RightEyebrow_CompareMode1SW)
       void    RightEyebrow_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (RightEyebrow_CompareMode1SW) */
#else
    #if (RightEyebrow_CompareMode1SW)
        void    RightEyebrow_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (RightEyebrow_CompareMode1SW) */
    #if (RightEyebrow_CompareMode2SW)
        void    RightEyebrow_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (RightEyebrow_CompareMode2SW) */
#endif /* (RightEyebrow_UseOneCompareMode) */

#if (!RightEyebrow_UsingFixedFunction)
    uint16   RightEyebrow_ReadCounter(void) ;
    uint16 RightEyebrow_ReadCapture(void) ;

    #if (RightEyebrow_UseStatus)
            void RightEyebrow_ClearFIFO(void) ;
    #endif /* (RightEyebrow_UseStatus) */

    void    RightEyebrow_WriteCounter(uint16 counter)
            ;
#endif /* (!RightEyebrow_UsingFixedFunction) */

void    RightEyebrow_WritePeriod(uint16 period)
        ;
uint16 RightEyebrow_ReadPeriod(void) ;

#if (RightEyebrow_UseOneCompareMode)
    void    RightEyebrow_WriteCompare(uint16 compare)
            ;
    uint16 RightEyebrow_ReadCompare(void) ;
#else
    void    RightEyebrow_WriteCompare1(uint16 compare)
            ;
    uint16 RightEyebrow_ReadCompare1(void) ;
    void    RightEyebrow_WriteCompare2(uint16 compare)
            ;
    uint16 RightEyebrow_ReadCompare2(void) ;
#endif /* (RightEyebrow_UseOneCompareMode) */


#if (RightEyebrow_DeadBandUsed)
    void    RightEyebrow_WriteDeadTime(uint8 deadtime) ;
    uint8   RightEyebrow_ReadDeadTime(void) ;
#endif /* (RightEyebrow_DeadBandUsed) */

#if ( RightEyebrow_KillModeMinTime)
    void RightEyebrow_WriteKillTime(uint8 killtime) ;
    uint8 RightEyebrow_ReadKillTime(void) ;
#endif /* ( RightEyebrow_KillModeMinTime) */

void RightEyebrow_Init(void) ;
void RightEyebrow_Enable(void) ;
void RightEyebrow_Sleep(void) ;
void RightEyebrow_Wakeup(void) ;
void RightEyebrow_SaveConfig(void) ;
void RightEyebrow_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define RightEyebrow_INIT_PERIOD_VALUE          (19000u)
#define RightEyebrow_INIT_COMPARE_VALUE1        (0u)
#define RightEyebrow_INIT_COMPARE_VALUE2        (0u)
#define RightEyebrow_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    RightEyebrow_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RightEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RightEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    RightEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define RightEyebrow_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  RightEyebrow_CTRL_CMPMODE2_SHIFT)
#define RightEyebrow_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  RightEyebrow_CTRL_CMPMODE1_SHIFT)
#define RightEyebrow_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (RightEyebrow_UsingFixedFunction)
   #define RightEyebrow_PERIOD_LSB              (*(reg16 *) RightEyebrow_PWMHW__PER0)
   #define RightEyebrow_PERIOD_LSB_PTR          ( (reg16 *) RightEyebrow_PWMHW__PER0)
   #define RightEyebrow_COMPARE1_LSB            (*(reg16 *) RightEyebrow_PWMHW__CNT_CMP0)
   #define RightEyebrow_COMPARE1_LSB_PTR        ( (reg16 *) RightEyebrow_PWMHW__CNT_CMP0)
   #define RightEyebrow_COMPARE2_LSB            (0x00u)
   #define RightEyebrow_COMPARE2_LSB_PTR        (0x00u)
   #define RightEyebrow_COUNTER_LSB             (*(reg16 *) RightEyebrow_PWMHW__CNT_CMP0)
   #define RightEyebrow_COUNTER_LSB_PTR         ( (reg16 *) RightEyebrow_PWMHW__CNT_CMP0)
   #define RightEyebrow_CAPTURE_LSB             (*(reg16 *) RightEyebrow_PWMHW__CAP0)
   #define RightEyebrow_CAPTURE_LSB_PTR         ( (reg16 *) RightEyebrow_PWMHW__CAP0)
   #define RightEyebrow_RT1                     (*(reg8 *)  RightEyebrow_PWMHW__RT1)
   #define RightEyebrow_RT1_PTR                 ( (reg8 *)  RightEyebrow_PWMHW__RT1)

#else
   #if (RightEyebrow_Resolution == 8u) /* 8bit - PWM */

       #if(RightEyebrow_PWMModeIsCenterAligned)
           #define RightEyebrow_PERIOD_LSB      (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define RightEyebrow_PERIOD_LSB_PTR  ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define RightEyebrow_PERIOD_LSB      (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define RightEyebrow_PERIOD_LSB_PTR  ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (RightEyebrow_PWMModeIsCenterAligned) */

       #define RightEyebrow_COMPARE1_LSB        (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define RightEyebrow_COMPARE1_LSB_PTR    ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define RightEyebrow_COMPARE2_LSB        (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define RightEyebrow_COMPARE2_LSB_PTR    ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define RightEyebrow_COUNTERCAP_LSB      (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define RightEyebrow_COUNTERCAP_LSB_PTR  ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define RightEyebrow_COUNTER_LSB         (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define RightEyebrow_COUNTER_LSB_PTR     ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define RightEyebrow_CAPTURE_LSB         (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define RightEyebrow_CAPTURE_LSB_PTR     ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(RightEyebrow_PWMModeIsCenterAligned)
               #define RightEyebrow_PERIOD_LSB      (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define RightEyebrow_PERIOD_LSB_PTR  ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define RightEyebrow_PERIOD_LSB      (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define RightEyebrow_PERIOD_LSB_PTR  ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (RightEyebrow_PWMModeIsCenterAligned) */

            #define RightEyebrow_COMPARE1_LSB       (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define RightEyebrow_COMPARE1_LSB_PTR   ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define RightEyebrow_COMPARE2_LSB       (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define RightEyebrow_COMPARE2_LSB_PTR   ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define RightEyebrow_COUNTERCAP_LSB     (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define RightEyebrow_COUNTERCAP_LSB_PTR ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define RightEyebrow_COUNTER_LSB        (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define RightEyebrow_COUNTER_LSB_PTR    ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define RightEyebrow_CAPTURE_LSB        (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define RightEyebrow_CAPTURE_LSB_PTR    ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(RightEyebrow_PWMModeIsCenterAligned)
               #define RightEyebrow_PERIOD_LSB      (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define RightEyebrow_PERIOD_LSB_PTR  ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define RightEyebrow_PERIOD_LSB      (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define RightEyebrow_PERIOD_LSB_PTR  ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (RightEyebrow_PWMModeIsCenterAligned) */

            #define RightEyebrow_COMPARE1_LSB       (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define RightEyebrow_COMPARE1_LSB_PTR   ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define RightEyebrow_COMPARE2_LSB       (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define RightEyebrow_COMPARE2_LSB_PTR   ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define RightEyebrow_COUNTERCAP_LSB     (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define RightEyebrow_COUNTERCAP_LSB_PTR ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define RightEyebrow_COUNTER_LSB        (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define RightEyebrow_COUNTER_LSB_PTR    ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define RightEyebrow_CAPTURE_LSB        (*(reg16 *) RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define RightEyebrow_CAPTURE_LSB_PTR    ((reg16 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define RightEyebrow_AUX_CONTROLDP1          (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define RightEyebrow_AUX_CONTROLDP1_PTR      ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (RightEyebrow_Resolution == 8) */

   #define RightEyebrow_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define RightEyebrow_AUX_CONTROLDP0          (*(reg8 *)  RightEyebrow_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define RightEyebrow_AUX_CONTROLDP0_PTR      ((reg8 *)   RightEyebrow_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (RightEyebrow_UsingFixedFunction) */

#if(RightEyebrow_KillModeMinTime )
    #define RightEyebrow_KILLMODEMINTIME        (*(reg8 *)  RightEyebrow_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define RightEyebrow_KILLMODEMINTIME_PTR    ((reg8 *)   RightEyebrow_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (RightEyebrow_KillModeMinTime ) */

#if(RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_256_CLOCKS)
    #define RightEyebrow_DEADBAND_COUNT         (*(reg8 *)  RightEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define RightEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   RightEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define RightEyebrow_DEADBAND_LSB_PTR       ((reg8 *)   RightEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define RightEyebrow_DEADBAND_LSB           (*(reg8 *)  RightEyebrow_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (RightEyebrow_UsingFixedFunction)
        #define RightEyebrow_DEADBAND_COUNT         (*(reg8 *)  RightEyebrow_PWMHW__CFG0)
        #define RightEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   RightEyebrow_PWMHW__CFG0)
        #define RightEyebrow_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << RightEyebrow_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define RightEyebrow_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define RightEyebrow_DEADBAND_COUNT         (*(reg8 *)  RightEyebrow_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define RightEyebrow_DEADBAND_COUNT_PTR     ((reg8 *)   RightEyebrow_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define RightEyebrow_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << RightEyebrow_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define RightEyebrow_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (RightEyebrow_UsingFixedFunction) */
#endif /* (RightEyebrow_DeadBandMode == RightEyebrow__B_PWM__DBM_256_CLOCKS) */



#if (RightEyebrow_UsingFixedFunction)
    #define RightEyebrow_STATUS                 (*(reg8 *) RightEyebrow_PWMHW__SR0)
    #define RightEyebrow_STATUS_PTR             ((reg8 *) RightEyebrow_PWMHW__SR0)
    #define RightEyebrow_STATUS_MASK            (*(reg8 *) RightEyebrow_PWMHW__SR0)
    #define RightEyebrow_STATUS_MASK_PTR        ((reg8 *) RightEyebrow_PWMHW__SR0)
    #define RightEyebrow_CONTROL                (*(reg8 *) RightEyebrow_PWMHW__CFG0)
    #define RightEyebrow_CONTROL_PTR            ((reg8 *) RightEyebrow_PWMHW__CFG0)
    #define RightEyebrow_CONTROL2               (*(reg8 *) RightEyebrow_PWMHW__CFG1)
    #define RightEyebrow_CONTROL3               (*(reg8 *) RightEyebrow_PWMHW__CFG2)
    #define RightEyebrow_GLOBAL_ENABLE          (*(reg8 *) RightEyebrow_PWMHW__PM_ACT_CFG)
    #define RightEyebrow_GLOBAL_ENABLE_PTR      ( (reg8 *) RightEyebrow_PWMHW__PM_ACT_CFG)
    #define RightEyebrow_GLOBAL_STBY_ENABLE     (*(reg8 *) RightEyebrow_PWMHW__PM_STBY_CFG)
    #define RightEyebrow_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) RightEyebrow_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define RightEyebrow_BLOCK_EN_MASK          (RightEyebrow_PWMHW__PM_ACT_MSK)
    #define RightEyebrow_BLOCK_STBY_EN_MASK     (RightEyebrow_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define RightEyebrow_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define RightEyebrow_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define RightEyebrow_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define RightEyebrow_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define RightEyebrow_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define RightEyebrow_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define RightEyebrow_CTRL_ENABLE            (uint8)((uint8)0x01u << RightEyebrow_CTRL_ENABLE_SHIFT)
    #define RightEyebrow_CTRL_RESET             (uint8)((uint8)0x01u << RightEyebrow_CTRL_RESET_SHIFT)
    #define RightEyebrow_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << RightEyebrow_CTRL_CMPMODE2_SHIFT)
    #define RightEyebrow_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << RightEyebrow_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define RightEyebrow_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define RightEyebrow_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << RightEyebrow_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define RightEyebrow_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define RightEyebrow_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define RightEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define RightEyebrow_STATUS_TC_INT_EN_MASK_SHIFT            (RightEyebrow_STATUS_TC_SHIFT - 4u)
    #define RightEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define RightEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT          (RightEyebrow_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define RightEyebrow_STATUS_TC              (uint8)((uint8)0x01u << RightEyebrow_STATUS_TC_SHIFT)
    #define RightEyebrow_STATUS_CMP1            (uint8)((uint8)0x01u << RightEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define RightEyebrow_STATUS_TC_INT_EN_MASK              (uint8)((uint8)RightEyebrow_STATUS_TC >> 4u)
    #define RightEyebrow_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)RightEyebrow_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define RightEyebrow_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define RightEyebrow_RT1_MASK              (uint8)((uint8)0x03u << RightEyebrow_RT1_SHIFT)
    #define RightEyebrow_SYNC                  (uint8)((uint8)0x03u << RightEyebrow_RT1_SHIFT)
    #define RightEyebrow_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define RightEyebrow_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << RightEyebrow_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define RightEyebrow_SYNCDSI_EN            (uint8)((uint8)0x0Fu << RightEyebrow_SYNCDSI_SHIFT)


#else
    #define RightEyebrow_STATUS                (*(reg8 *)   RightEyebrow_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define RightEyebrow_STATUS_PTR            ((reg8 *)    RightEyebrow_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define RightEyebrow_STATUS_MASK           (*(reg8 *)   RightEyebrow_PWMUDB_genblk8_stsreg__MASK_REG)
    #define RightEyebrow_STATUS_MASK_PTR       ((reg8 *)    RightEyebrow_PWMUDB_genblk8_stsreg__MASK_REG)
    #define RightEyebrow_STATUS_AUX_CTRL       (*(reg8 *)   RightEyebrow_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define RightEyebrow_CONTROL               (*(reg8 *)   RightEyebrow_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define RightEyebrow_CONTROL_PTR           ((reg8 *)    RightEyebrow_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define RightEyebrow_CTRL_ENABLE_SHIFT      (0x07u)
    #define RightEyebrow_CTRL_RESET_SHIFT       (0x06u)
    #define RightEyebrow_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define RightEyebrow_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define RightEyebrow_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define RightEyebrow_CTRL_ENABLE            (uint8)((uint8)0x01u << RightEyebrow_CTRL_ENABLE_SHIFT)
    #define RightEyebrow_CTRL_RESET             (uint8)((uint8)0x01u << RightEyebrow_CTRL_RESET_SHIFT)
    #define RightEyebrow_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << RightEyebrow_CTRL_CMPMODE2_SHIFT)
    #define RightEyebrow_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << RightEyebrow_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define RightEyebrow_STATUS_KILL_SHIFT          (0x05u)
    #define RightEyebrow_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define RightEyebrow_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define RightEyebrow_STATUS_TC_SHIFT            (0x02u)
    #define RightEyebrow_STATUS_CMP2_SHIFT          (0x01u)
    #define RightEyebrow_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define RightEyebrow_STATUS_KILL_INT_EN_MASK_SHIFT          (RightEyebrow_STATUS_KILL_SHIFT)
    #define RightEyebrow_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (RightEyebrow_STATUS_FIFONEMPTY_SHIFT)
    #define RightEyebrow_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (RightEyebrow_STATUS_FIFOFULL_SHIFT)
    #define RightEyebrow_STATUS_TC_INT_EN_MASK_SHIFT            (RightEyebrow_STATUS_TC_SHIFT)
    #define RightEyebrow_STATUS_CMP2_INT_EN_MASK_SHIFT          (RightEyebrow_STATUS_CMP2_SHIFT)
    #define RightEyebrow_STATUS_CMP1_INT_EN_MASK_SHIFT          (RightEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define RightEyebrow_STATUS_KILL            (uint8)((uint8)0x00u << RightEyebrow_STATUS_KILL_SHIFT )
    #define RightEyebrow_STATUS_FIFOFULL        (uint8)((uint8)0x01u << RightEyebrow_STATUS_FIFOFULL_SHIFT)
    #define RightEyebrow_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << RightEyebrow_STATUS_FIFONEMPTY_SHIFT)
    #define RightEyebrow_STATUS_TC              (uint8)((uint8)0x01u << RightEyebrow_STATUS_TC_SHIFT)
    #define RightEyebrow_STATUS_CMP2            (uint8)((uint8)0x01u << RightEyebrow_STATUS_CMP2_SHIFT)
    #define RightEyebrow_STATUS_CMP1            (uint8)((uint8)0x01u << RightEyebrow_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define RightEyebrow_STATUS_KILL_INT_EN_MASK            (RightEyebrow_STATUS_KILL)
    #define RightEyebrow_STATUS_FIFOFULL_INT_EN_MASK        (RightEyebrow_STATUS_FIFOFULL)
    #define RightEyebrow_STATUS_FIFONEMPTY_INT_EN_MASK      (RightEyebrow_STATUS_FIFONEMPTY)
    #define RightEyebrow_STATUS_TC_INT_EN_MASK              (RightEyebrow_STATUS_TC)
    #define RightEyebrow_STATUS_CMP2_INT_EN_MASK            (RightEyebrow_STATUS_CMP2)
    #define RightEyebrow_STATUS_CMP1_INT_EN_MASK            (RightEyebrow_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define RightEyebrow_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define RightEyebrow_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define RightEyebrow_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define RightEyebrow_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define RightEyebrow_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* RightEyebrow_UsingFixedFunction */

#endif  /* CY_PWM_RightEyebrow_H */


/* [] END OF FILE */
