/*******************************************************************************
* File Name: EyeBallVertical.h
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

#if !defined(CY_PWM_EyeBallVertical_H)
#define CY_PWM_EyeBallVertical_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EyeBallVertical_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define EyeBallVertical_Resolution                     (16u)
#define EyeBallVertical_UsingFixedFunction             (0u)
#define EyeBallVertical_DeadBandMode                   (0u)
#define EyeBallVertical_KillModeMinTime                (0u)
#define EyeBallVertical_KillMode                       (0u)
#define EyeBallVertical_PWMMode                        (1u)
#define EyeBallVertical_PWMModeIsCenterAligned         (0u)
#define EyeBallVertical_DeadBandUsed                   (0u)
#define EyeBallVertical_DeadBand2_4                    (0u)

#if !defined(EyeBallVertical_PWMUDB_genblk8_stsreg__REMOVED)
    #define EyeBallVertical_UseStatus                  (1u)
#else
    #define EyeBallVertical_UseStatus                  (0u)
#endif /* !defined(EyeBallVertical_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(EyeBallVertical_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define EyeBallVertical_UseControl                 (1u)
#else
    #define EyeBallVertical_UseControl                 (0u)
#endif /* !defined(EyeBallVertical_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define EyeBallVertical_UseOneCompareMode              (0u)
#define EyeBallVertical_MinimumKillTime                (1u)
#define EyeBallVertical_EnableMode                     (0u)

#define EyeBallVertical_CompareMode1SW                 (0u)
#define EyeBallVertical_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define EyeBallVertical__B_PWM__DISABLED 0
#define EyeBallVertical__B_PWM__ASYNCHRONOUS 1
#define EyeBallVertical__B_PWM__SINGLECYCLE 2
#define EyeBallVertical__B_PWM__LATCHED 3
#define EyeBallVertical__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define EyeBallVertical__B_PWM__DBMDISABLED 0
#define EyeBallVertical__B_PWM__DBM_2_4_CLOCKS 1
#define EyeBallVertical__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define EyeBallVertical__B_PWM__ONE_OUTPUT 0
#define EyeBallVertical__B_PWM__TWO_OUTPUTS 1
#define EyeBallVertical__B_PWM__DUAL_EDGE 2
#define EyeBallVertical__B_PWM__CENTER_ALIGN 3
#define EyeBallVertical__B_PWM__DITHER 5
#define EyeBallVertical__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define EyeBallVertical__B_PWM__LESS_THAN 1
#define EyeBallVertical__B_PWM__LESS_THAN_OR_EQUAL 2
#define EyeBallVertical__B_PWM__GREATER_THAN 3
#define EyeBallVertical__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define EyeBallVertical__B_PWM__EQUAL 0
#define EyeBallVertical__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!EyeBallVertical_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!EyeBallVertical_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!EyeBallVertical_PWMModeIsCenterAligned) */
        #if (EyeBallVertical_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (EyeBallVertical_UseStatus) */

        /* Backup for Deadband parameters */
        #if(EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_256_CLOCKS || \
            EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(EyeBallVertical_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (EyeBallVertical_KillModeMinTime) */

        /* Backup control register */
        #if(EyeBallVertical_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (EyeBallVertical_UseControl) */

    #endif /* (!EyeBallVertical_UsingFixedFunction) */

}EyeBallVertical_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    EyeBallVertical_Start(void) ;
void    EyeBallVertical_Stop(void) ;

#if (EyeBallVertical_UseStatus || EyeBallVertical_UsingFixedFunction)
    void  EyeBallVertical_SetInterruptMode(uint8 interruptMode) ;
    uint8 EyeBallVertical_ReadStatusRegister(void) ;
#endif /* (EyeBallVertical_UseStatus || EyeBallVertical_UsingFixedFunction) */

#define EyeBallVertical_GetInterruptSource() EyeBallVertical_ReadStatusRegister()

#if (EyeBallVertical_UseControl)
    uint8 EyeBallVertical_ReadControlRegister(void) ;
    void  EyeBallVertical_WriteControlRegister(uint8 control)
          ;
#endif /* (EyeBallVertical_UseControl) */

#if (EyeBallVertical_UseOneCompareMode)
   #if (EyeBallVertical_CompareMode1SW)
       void    EyeBallVertical_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (EyeBallVertical_CompareMode1SW) */
#else
    #if (EyeBallVertical_CompareMode1SW)
        void    EyeBallVertical_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (EyeBallVertical_CompareMode1SW) */
    #if (EyeBallVertical_CompareMode2SW)
        void    EyeBallVertical_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (EyeBallVertical_CompareMode2SW) */
#endif /* (EyeBallVertical_UseOneCompareMode) */

#if (!EyeBallVertical_UsingFixedFunction)
    uint16   EyeBallVertical_ReadCounter(void) ;
    uint16 EyeBallVertical_ReadCapture(void) ;

    #if (EyeBallVertical_UseStatus)
            void EyeBallVertical_ClearFIFO(void) ;
    #endif /* (EyeBallVertical_UseStatus) */

    void    EyeBallVertical_WriteCounter(uint16 counter)
            ;
#endif /* (!EyeBallVertical_UsingFixedFunction) */

void    EyeBallVertical_WritePeriod(uint16 period)
        ;
uint16 EyeBallVertical_ReadPeriod(void) ;

#if (EyeBallVertical_UseOneCompareMode)
    void    EyeBallVertical_WriteCompare(uint16 compare)
            ;
    uint16 EyeBallVertical_ReadCompare(void) ;
#else
    void    EyeBallVertical_WriteCompare1(uint16 compare)
            ;
    uint16 EyeBallVertical_ReadCompare1(void) ;
    void    EyeBallVertical_WriteCompare2(uint16 compare)
            ;
    uint16 EyeBallVertical_ReadCompare2(void) ;
#endif /* (EyeBallVertical_UseOneCompareMode) */


#if (EyeBallVertical_DeadBandUsed)
    void    EyeBallVertical_WriteDeadTime(uint8 deadtime) ;
    uint8   EyeBallVertical_ReadDeadTime(void) ;
#endif /* (EyeBallVertical_DeadBandUsed) */

#if ( EyeBallVertical_KillModeMinTime)
    void EyeBallVertical_WriteKillTime(uint8 killtime) ;
    uint8 EyeBallVertical_ReadKillTime(void) ;
#endif /* ( EyeBallVertical_KillModeMinTime) */

void EyeBallVertical_Init(void) ;
void EyeBallVertical_Enable(void) ;
void EyeBallVertical_Sleep(void) ;
void EyeBallVertical_Wakeup(void) ;
void EyeBallVertical_SaveConfig(void) ;
void EyeBallVertical_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define EyeBallVertical_INIT_PERIOD_VALUE          (60000u)
#define EyeBallVertical_INIT_COMPARE_VALUE1        (0u)
#define EyeBallVertical_INIT_COMPARE_VALUE2        (0u)
#define EyeBallVertical_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    EyeBallVertical_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallVertical_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallVertical_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyeBallVertical_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define EyeBallVertical_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  EyeBallVertical_CTRL_CMPMODE2_SHIFT)
#define EyeBallVertical_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  EyeBallVertical_CTRL_CMPMODE1_SHIFT)
#define EyeBallVertical_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (EyeBallVertical_UsingFixedFunction)
   #define EyeBallVertical_PERIOD_LSB              (*(reg16 *) EyeBallVertical_PWMHW__PER0)
   #define EyeBallVertical_PERIOD_LSB_PTR          ( (reg16 *) EyeBallVertical_PWMHW__PER0)
   #define EyeBallVertical_COMPARE1_LSB            (*(reg16 *) EyeBallVertical_PWMHW__CNT_CMP0)
   #define EyeBallVertical_COMPARE1_LSB_PTR        ( (reg16 *) EyeBallVertical_PWMHW__CNT_CMP0)
   #define EyeBallVertical_COMPARE2_LSB            (0x00u)
   #define EyeBallVertical_COMPARE2_LSB_PTR        (0x00u)
   #define EyeBallVertical_COUNTER_LSB             (*(reg16 *) EyeBallVertical_PWMHW__CNT_CMP0)
   #define EyeBallVertical_COUNTER_LSB_PTR         ( (reg16 *) EyeBallVertical_PWMHW__CNT_CMP0)
   #define EyeBallVertical_CAPTURE_LSB             (*(reg16 *) EyeBallVertical_PWMHW__CAP0)
   #define EyeBallVertical_CAPTURE_LSB_PTR         ( (reg16 *) EyeBallVertical_PWMHW__CAP0)
   #define EyeBallVertical_RT1                     (*(reg8 *)  EyeBallVertical_PWMHW__RT1)
   #define EyeBallVertical_RT1_PTR                 ( (reg8 *)  EyeBallVertical_PWMHW__RT1)

#else
   #if (EyeBallVertical_Resolution == 8u) /* 8bit - PWM */

       #if(EyeBallVertical_PWMModeIsCenterAligned)
           #define EyeBallVertical_PERIOD_LSB      (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define EyeBallVertical_PERIOD_LSB_PTR  ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define EyeBallVertical_PERIOD_LSB      (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define EyeBallVertical_PERIOD_LSB_PTR  ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (EyeBallVertical_PWMModeIsCenterAligned) */

       #define EyeBallVertical_COMPARE1_LSB        (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeBallVertical_COMPARE1_LSB_PTR    ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyeBallVertical_COMPARE2_LSB        (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeBallVertical_COMPARE2_LSB_PTR    ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyeBallVertical_COUNTERCAP_LSB      (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeBallVertical_COUNTERCAP_LSB_PTR  ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyeBallVertical_COUNTER_LSB         (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeBallVertical_COUNTER_LSB_PTR     ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyeBallVertical_CAPTURE_LSB         (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define EyeBallVertical_CAPTURE_LSB_PTR     ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(EyeBallVertical_PWMModeIsCenterAligned)
               #define EyeBallVertical_PERIOD_LSB      (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define EyeBallVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define EyeBallVertical_PERIOD_LSB      (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define EyeBallVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (EyeBallVertical_PWMModeIsCenterAligned) */

            #define EyeBallVertical_COMPARE1_LSB       (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeBallVertical_COMPARE1_LSB_PTR   ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyeBallVertical_COMPARE2_LSB       (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeBallVertical_COMPARE2_LSB_PTR   ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyeBallVertical_COUNTERCAP_LSB     (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeBallVertical_COUNTERCAP_LSB_PTR ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyeBallVertical_COUNTER_LSB        (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeBallVertical_COUNTER_LSB_PTR    ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyeBallVertical_CAPTURE_LSB        (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define EyeBallVertical_CAPTURE_LSB_PTR    ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(EyeBallVertical_PWMModeIsCenterAligned)
               #define EyeBallVertical_PERIOD_LSB      (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define EyeBallVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define EyeBallVertical_PERIOD_LSB      (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define EyeBallVertical_PERIOD_LSB_PTR  ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (EyeBallVertical_PWMModeIsCenterAligned) */

            #define EyeBallVertical_COMPARE1_LSB       (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeBallVertical_COMPARE1_LSB_PTR   ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyeBallVertical_COMPARE2_LSB       (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeBallVertical_COMPARE2_LSB_PTR   ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyeBallVertical_COUNTERCAP_LSB     (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeBallVertical_COUNTERCAP_LSB_PTR ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyeBallVertical_COUNTER_LSB        (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeBallVertical_COUNTER_LSB_PTR    ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyeBallVertical_CAPTURE_LSB        (*(reg16 *) EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define EyeBallVertical_CAPTURE_LSB_PTR    ((reg16 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define EyeBallVertical_AUX_CONTROLDP1          (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define EyeBallVertical_AUX_CONTROLDP1_PTR      ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (EyeBallVertical_Resolution == 8) */

   #define EyeBallVertical_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define EyeBallVertical_AUX_CONTROLDP0          (*(reg8 *)  EyeBallVertical_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define EyeBallVertical_AUX_CONTROLDP0_PTR      ((reg8 *)   EyeBallVertical_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (EyeBallVertical_UsingFixedFunction) */

#if(EyeBallVertical_KillModeMinTime )
    #define EyeBallVertical_KILLMODEMINTIME        (*(reg8 *)  EyeBallVertical_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define EyeBallVertical_KILLMODEMINTIME_PTR    ((reg8 *)   EyeBallVertical_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (EyeBallVertical_KillModeMinTime ) */

#if(EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_256_CLOCKS)
    #define EyeBallVertical_DEADBAND_COUNT         (*(reg8 *)  EyeBallVertical_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeBallVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallVertical_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyeBallVertical_DEADBAND_LSB_PTR       ((reg8 *)   EyeBallVertical_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define EyeBallVertical_DEADBAND_LSB           (*(reg8 *)  EyeBallVertical_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (EyeBallVertical_UsingFixedFunction)
        #define EyeBallVertical_DEADBAND_COUNT         (*(reg8 *)  EyeBallVertical_PWMHW__CFG0)
        #define EyeBallVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallVertical_PWMHW__CFG0)
        #define EyeBallVertical_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeBallVertical_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define EyeBallVertical_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define EyeBallVertical_DEADBAND_COUNT         (*(reg8 *)  EyeBallVertical_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeBallVertical_DEADBAND_COUNT_PTR     ((reg8 *)   EyeBallVertical_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyeBallVertical_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyeBallVertical_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define EyeBallVertical_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (EyeBallVertical_UsingFixedFunction) */
#endif /* (EyeBallVertical_DeadBandMode == EyeBallVertical__B_PWM__DBM_256_CLOCKS) */



#if (EyeBallVertical_UsingFixedFunction)
    #define EyeBallVertical_STATUS                 (*(reg8 *) EyeBallVertical_PWMHW__SR0)
    #define EyeBallVertical_STATUS_PTR             ((reg8 *) EyeBallVertical_PWMHW__SR0)
    #define EyeBallVertical_STATUS_MASK            (*(reg8 *) EyeBallVertical_PWMHW__SR0)
    #define EyeBallVertical_STATUS_MASK_PTR        ((reg8 *) EyeBallVertical_PWMHW__SR0)
    #define EyeBallVertical_CONTROL                (*(reg8 *) EyeBallVertical_PWMHW__CFG0)
    #define EyeBallVertical_CONTROL_PTR            ((reg8 *) EyeBallVertical_PWMHW__CFG0)
    #define EyeBallVertical_CONTROL2               (*(reg8 *) EyeBallVertical_PWMHW__CFG1)
    #define EyeBallVertical_CONTROL3               (*(reg8 *) EyeBallVertical_PWMHW__CFG2)
    #define EyeBallVertical_GLOBAL_ENABLE          (*(reg8 *) EyeBallVertical_PWMHW__PM_ACT_CFG)
    #define EyeBallVertical_GLOBAL_ENABLE_PTR      ( (reg8 *) EyeBallVertical_PWMHW__PM_ACT_CFG)
    #define EyeBallVertical_GLOBAL_STBY_ENABLE     (*(reg8 *) EyeBallVertical_PWMHW__PM_STBY_CFG)
    #define EyeBallVertical_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) EyeBallVertical_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define EyeBallVertical_BLOCK_EN_MASK          (EyeBallVertical_PWMHW__PM_ACT_MSK)
    #define EyeBallVertical_BLOCK_STBY_EN_MASK     (EyeBallVertical_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define EyeBallVertical_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define EyeBallVertical_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define EyeBallVertical_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define EyeBallVertical_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define EyeBallVertical_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define EyeBallVertical_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define EyeBallVertical_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeBallVertical_CTRL_ENABLE_SHIFT)
    #define EyeBallVertical_CTRL_RESET             (uint8)((uint8)0x01u << EyeBallVertical_CTRL_RESET_SHIFT)
    #define EyeBallVertical_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeBallVertical_CTRL_CMPMODE2_SHIFT)
    #define EyeBallVertical_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeBallVertical_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EyeBallVertical_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define EyeBallVertical_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << EyeBallVertical_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define EyeBallVertical_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define EyeBallVertical_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define EyeBallVertical_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeBallVertical_STATUS_TC_INT_EN_MASK_SHIFT            (EyeBallVertical_STATUS_TC_SHIFT - 4u)
    #define EyeBallVertical_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define EyeBallVertical_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeBallVertical_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define EyeBallVertical_STATUS_TC              (uint8)((uint8)0x01u << EyeBallVertical_STATUS_TC_SHIFT)
    #define EyeBallVertical_STATUS_CMP1            (uint8)((uint8)0x01u << EyeBallVertical_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define EyeBallVertical_STATUS_TC_INT_EN_MASK              (uint8)((uint8)EyeBallVertical_STATUS_TC >> 4u)
    #define EyeBallVertical_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)EyeBallVertical_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define EyeBallVertical_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define EyeBallVertical_RT1_MASK              (uint8)((uint8)0x03u << EyeBallVertical_RT1_SHIFT)
    #define EyeBallVertical_SYNC                  (uint8)((uint8)0x03u << EyeBallVertical_RT1_SHIFT)
    #define EyeBallVertical_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define EyeBallVertical_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << EyeBallVertical_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define EyeBallVertical_SYNCDSI_EN            (uint8)((uint8)0x0Fu << EyeBallVertical_SYNCDSI_SHIFT)


#else
    #define EyeBallVertical_STATUS                (*(reg8 *)   EyeBallVertical_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeBallVertical_STATUS_PTR            ((reg8 *)    EyeBallVertical_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyeBallVertical_STATUS_MASK           (*(reg8 *)   EyeBallVertical_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeBallVertical_STATUS_MASK_PTR       ((reg8 *)    EyeBallVertical_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyeBallVertical_STATUS_AUX_CTRL       (*(reg8 *)   EyeBallVertical_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define EyeBallVertical_CONTROL               (*(reg8 *)   EyeBallVertical_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define EyeBallVertical_CONTROL_PTR           ((reg8 *)    EyeBallVertical_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define EyeBallVertical_CTRL_ENABLE_SHIFT      (0x07u)
    #define EyeBallVertical_CTRL_RESET_SHIFT       (0x06u)
    #define EyeBallVertical_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define EyeBallVertical_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define EyeBallVertical_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define EyeBallVertical_CTRL_ENABLE            (uint8)((uint8)0x01u << EyeBallVertical_CTRL_ENABLE_SHIFT)
    #define EyeBallVertical_CTRL_RESET             (uint8)((uint8)0x01u << EyeBallVertical_CTRL_RESET_SHIFT)
    #define EyeBallVertical_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyeBallVertical_CTRL_CMPMODE2_SHIFT)
    #define EyeBallVertical_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyeBallVertical_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define EyeBallVertical_STATUS_KILL_SHIFT          (0x05u)
    #define EyeBallVertical_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define EyeBallVertical_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define EyeBallVertical_STATUS_TC_SHIFT            (0x02u)
    #define EyeBallVertical_STATUS_CMP2_SHIFT          (0x01u)
    #define EyeBallVertical_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define EyeBallVertical_STATUS_KILL_INT_EN_MASK_SHIFT          (EyeBallVertical_STATUS_KILL_SHIFT)
    #define EyeBallVertical_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (EyeBallVertical_STATUS_FIFONEMPTY_SHIFT)
    #define EyeBallVertical_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (EyeBallVertical_STATUS_FIFOFULL_SHIFT)
    #define EyeBallVertical_STATUS_TC_INT_EN_MASK_SHIFT            (EyeBallVertical_STATUS_TC_SHIFT)
    #define EyeBallVertical_STATUS_CMP2_INT_EN_MASK_SHIFT          (EyeBallVertical_STATUS_CMP2_SHIFT)
    #define EyeBallVertical_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyeBallVertical_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define EyeBallVertical_STATUS_KILL            (uint8)((uint8)0x00u << EyeBallVertical_STATUS_KILL_SHIFT )
    #define EyeBallVertical_STATUS_FIFOFULL        (uint8)((uint8)0x01u << EyeBallVertical_STATUS_FIFOFULL_SHIFT)
    #define EyeBallVertical_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << EyeBallVertical_STATUS_FIFONEMPTY_SHIFT)
    #define EyeBallVertical_STATUS_TC              (uint8)((uint8)0x01u << EyeBallVertical_STATUS_TC_SHIFT)
    #define EyeBallVertical_STATUS_CMP2            (uint8)((uint8)0x01u << EyeBallVertical_STATUS_CMP2_SHIFT)
    #define EyeBallVertical_STATUS_CMP1            (uint8)((uint8)0x01u << EyeBallVertical_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define EyeBallVertical_STATUS_KILL_INT_EN_MASK            (EyeBallVertical_STATUS_KILL)
    #define EyeBallVertical_STATUS_FIFOFULL_INT_EN_MASK        (EyeBallVertical_STATUS_FIFOFULL)
    #define EyeBallVertical_STATUS_FIFONEMPTY_INT_EN_MASK      (EyeBallVertical_STATUS_FIFONEMPTY)
    #define EyeBallVertical_STATUS_TC_INT_EN_MASK              (EyeBallVertical_STATUS_TC)
    #define EyeBallVertical_STATUS_CMP2_INT_EN_MASK            (EyeBallVertical_STATUS_CMP2)
    #define EyeBallVertical_STATUS_CMP1_INT_EN_MASK            (EyeBallVertical_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define EyeBallVertical_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define EyeBallVertical_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define EyeBallVertical_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define EyeBallVertical_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define EyeBallVertical_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* EyeBallVertical_UsingFixedFunction */

#endif  /* CY_PWM_EyeBallVertical_H */


/* [] END OF FILE */
