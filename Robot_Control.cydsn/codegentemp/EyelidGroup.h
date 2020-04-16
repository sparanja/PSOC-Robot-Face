/*******************************************************************************
* File Name: EyelidGroup.h
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

#if !defined(CY_PWM_EyelidGroup_H)
#define CY_PWM_EyelidGroup_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 EyelidGroup_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define EyelidGroup_Resolution                     (16u)
#define EyelidGroup_UsingFixedFunction             (0u)
#define EyelidGroup_DeadBandMode                   (0u)
#define EyelidGroup_KillModeMinTime                (0u)
#define EyelidGroup_KillMode                       (0u)
#define EyelidGroup_PWMMode                        (1u)
#define EyelidGroup_PWMModeIsCenterAligned         (0u)
#define EyelidGroup_DeadBandUsed                   (0u)
#define EyelidGroup_DeadBand2_4                    (0u)

#if !defined(EyelidGroup_PWMUDB_genblk8_stsreg__REMOVED)
    #define EyelidGroup_UseStatus                  (1u)
#else
    #define EyelidGroup_UseStatus                  (0u)
#endif /* !defined(EyelidGroup_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(EyelidGroup_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define EyelidGroup_UseControl                 (1u)
#else
    #define EyelidGroup_UseControl                 (0u)
#endif /* !defined(EyelidGroup_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define EyelidGroup_UseOneCompareMode              (0u)
#define EyelidGroup_MinimumKillTime                (1u)
#define EyelidGroup_EnableMode                     (0u)

#define EyelidGroup_CompareMode1SW                 (0u)
#define EyelidGroup_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define EyelidGroup__B_PWM__DISABLED 0
#define EyelidGroup__B_PWM__ASYNCHRONOUS 1
#define EyelidGroup__B_PWM__SINGLECYCLE 2
#define EyelidGroup__B_PWM__LATCHED 3
#define EyelidGroup__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define EyelidGroup__B_PWM__DBMDISABLED 0
#define EyelidGroup__B_PWM__DBM_2_4_CLOCKS 1
#define EyelidGroup__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define EyelidGroup__B_PWM__ONE_OUTPUT 0
#define EyelidGroup__B_PWM__TWO_OUTPUTS 1
#define EyelidGroup__B_PWM__DUAL_EDGE 2
#define EyelidGroup__B_PWM__CENTER_ALIGN 3
#define EyelidGroup__B_PWM__DITHER 5
#define EyelidGroup__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define EyelidGroup__B_PWM__LESS_THAN 1
#define EyelidGroup__B_PWM__LESS_THAN_OR_EQUAL 2
#define EyelidGroup__B_PWM__GREATER_THAN 3
#define EyelidGroup__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define EyelidGroup__B_PWM__EQUAL 0
#define EyelidGroup__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!EyelidGroup_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!EyelidGroup_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!EyelidGroup_PWMModeIsCenterAligned) */
        #if (EyelidGroup_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (EyelidGroup_UseStatus) */

        /* Backup for Deadband parameters */
        #if(EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_256_CLOCKS || \
            EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(EyelidGroup_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (EyelidGroup_KillModeMinTime) */

        /* Backup control register */
        #if(EyelidGroup_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (EyelidGroup_UseControl) */

    #endif /* (!EyelidGroup_UsingFixedFunction) */

}EyelidGroup_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    EyelidGroup_Start(void) ;
void    EyelidGroup_Stop(void) ;

#if (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction)
    void  EyelidGroup_SetInterruptMode(uint8 interruptMode) ;
    uint8 EyelidGroup_ReadStatusRegister(void) ;
#endif /* (EyelidGroup_UseStatus || EyelidGroup_UsingFixedFunction) */

#define EyelidGroup_GetInterruptSource() EyelidGroup_ReadStatusRegister()

#if (EyelidGroup_UseControl)
    uint8 EyelidGroup_ReadControlRegister(void) ;
    void  EyelidGroup_WriteControlRegister(uint8 control)
          ;
#endif /* (EyelidGroup_UseControl) */

#if (EyelidGroup_UseOneCompareMode)
   #if (EyelidGroup_CompareMode1SW)
       void    EyelidGroup_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (EyelidGroup_CompareMode1SW) */
#else
    #if (EyelidGroup_CompareMode1SW)
        void    EyelidGroup_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (EyelidGroup_CompareMode1SW) */
    #if (EyelidGroup_CompareMode2SW)
        void    EyelidGroup_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (EyelidGroup_CompareMode2SW) */
#endif /* (EyelidGroup_UseOneCompareMode) */

#if (!EyelidGroup_UsingFixedFunction)
    uint16   EyelidGroup_ReadCounter(void) ;
    uint16 EyelidGroup_ReadCapture(void) ;

    #if (EyelidGroup_UseStatus)
            void EyelidGroup_ClearFIFO(void) ;
    #endif /* (EyelidGroup_UseStatus) */

    void    EyelidGroup_WriteCounter(uint16 counter)
            ;
#endif /* (!EyelidGroup_UsingFixedFunction) */

void    EyelidGroup_WritePeriod(uint16 period)
        ;
uint16 EyelidGroup_ReadPeriod(void) ;

#if (EyelidGroup_UseOneCompareMode)
    void    EyelidGroup_WriteCompare(uint16 compare)
            ;
    uint16 EyelidGroup_ReadCompare(void) ;
#else
    void    EyelidGroup_WriteCompare1(uint16 compare)
            ;
    uint16 EyelidGroup_ReadCompare1(void) ;
    void    EyelidGroup_WriteCompare2(uint16 compare)
            ;
    uint16 EyelidGroup_ReadCompare2(void) ;
#endif /* (EyelidGroup_UseOneCompareMode) */


#if (EyelidGroup_DeadBandUsed)
    void    EyelidGroup_WriteDeadTime(uint8 deadtime) ;
    uint8   EyelidGroup_ReadDeadTime(void) ;
#endif /* (EyelidGroup_DeadBandUsed) */

#if ( EyelidGroup_KillModeMinTime)
    void EyelidGroup_WriteKillTime(uint8 killtime) ;
    uint8 EyelidGroup_ReadKillTime(void) ;
#endif /* ( EyelidGroup_KillModeMinTime) */

void EyelidGroup_Init(void) ;
void EyelidGroup_Enable(void) ;
void EyelidGroup_Sleep(void) ;
void EyelidGroup_Wakeup(void) ;
void EyelidGroup_SaveConfig(void) ;
void EyelidGroup_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define EyelidGroup_INIT_PERIOD_VALUE          (60000u)
#define EyelidGroup_INIT_COMPARE_VALUE1        (0u)
#define EyelidGroup_INIT_COMPARE_VALUE2        (0u)
#define EyelidGroup_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    EyelidGroup_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyelidGroup_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyelidGroup_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    EyelidGroup_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define EyelidGroup_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  EyelidGroup_CTRL_CMPMODE2_SHIFT)
#define EyelidGroup_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  EyelidGroup_CTRL_CMPMODE1_SHIFT)
#define EyelidGroup_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (EyelidGroup_UsingFixedFunction)
   #define EyelidGroup_PERIOD_LSB              (*(reg16 *) EyelidGroup_PWMHW__PER0)
   #define EyelidGroup_PERIOD_LSB_PTR          ( (reg16 *) EyelidGroup_PWMHW__PER0)
   #define EyelidGroup_COMPARE1_LSB            (*(reg16 *) EyelidGroup_PWMHW__CNT_CMP0)
   #define EyelidGroup_COMPARE1_LSB_PTR        ( (reg16 *) EyelidGroup_PWMHW__CNT_CMP0)
   #define EyelidGroup_COMPARE2_LSB            (0x00u)
   #define EyelidGroup_COMPARE2_LSB_PTR        (0x00u)
   #define EyelidGroup_COUNTER_LSB             (*(reg16 *) EyelidGroup_PWMHW__CNT_CMP0)
   #define EyelidGroup_COUNTER_LSB_PTR         ( (reg16 *) EyelidGroup_PWMHW__CNT_CMP0)
   #define EyelidGroup_CAPTURE_LSB             (*(reg16 *) EyelidGroup_PWMHW__CAP0)
   #define EyelidGroup_CAPTURE_LSB_PTR         ( (reg16 *) EyelidGroup_PWMHW__CAP0)
   #define EyelidGroup_RT1                     (*(reg8 *)  EyelidGroup_PWMHW__RT1)
   #define EyelidGroup_RT1_PTR                 ( (reg8 *)  EyelidGroup_PWMHW__RT1)

#else
   #if (EyelidGroup_Resolution == 8u) /* 8bit - PWM */

       #if(EyelidGroup_PWMModeIsCenterAligned)
           #define EyelidGroup_PERIOD_LSB      (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define EyelidGroup_PERIOD_LSB_PTR  ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define EyelidGroup_PERIOD_LSB      (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define EyelidGroup_PERIOD_LSB_PTR  ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (EyelidGroup_PWMModeIsCenterAligned) */

       #define EyelidGroup_COMPARE1_LSB        (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyelidGroup_COMPARE1_LSB_PTR    ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define EyelidGroup_COMPARE2_LSB        (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyelidGroup_COMPARE2_LSB_PTR    ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define EyelidGroup_COUNTERCAP_LSB      (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyelidGroup_COUNTERCAP_LSB_PTR  ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define EyelidGroup_COUNTER_LSB         (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyelidGroup_COUNTER_LSB_PTR     ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define EyelidGroup_CAPTURE_LSB         (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define EyelidGroup_CAPTURE_LSB_PTR     ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(EyelidGroup_PWMModeIsCenterAligned)
               #define EyelidGroup_PERIOD_LSB      (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define EyelidGroup_PERIOD_LSB_PTR  ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define EyelidGroup_PERIOD_LSB      (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define EyelidGroup_PERIOD_LSB_PTR  ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (EyelidGroup_PWMModeIsCenterAligned) */

            #define EyelidGroup_COMPARE1_LSB       (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyelidGroup_COMPARE1_LSB_PTR   ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define EyelidGroup_COMPARE2_LSB       (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyelidGroup_COMPARE2_LSB_PTR   ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define EyelidGroup_COUNTERCAP_LSB     (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyelidGroup_COUNTERCAP_LSB_PTR ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define EyelidGroup_COUNTER_LSB        (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyelidGroup_COUNTER_LSB_PTR    ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define EyelidGroup_CAPTURE_LSB        (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define EyelidGroup_CAPTURE_LSB_PTR    ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(EyelidGroup_PWMModeIsCenterAligned)
               #define EyelidGroup_PERIOD_LSB      (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define EyelidGroup_PERIOD_LSB_PTR  ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define EyelidGroup_PERIOD_LSB      (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define EyelidGroup_PERIOD_LSB_PTR  ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (EyelidGroup_PWMModeIsCenterAligned) */

            #define EyelidGroup_COMPARE1_LSB       (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyelidGroup_COMPARE1_LSB_PTR   ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define EyelidGroup_COMPARE2_LSB       (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyelidGroup_COMPARE2_LSB_PTR   ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define EyelidGroup_COUNTERCAP_LSB     (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyelidGroup_COUNTERCAP_LSB_PTR ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define EyelidGroup_COUNTER_LSB        (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyelidGroup_COUNTER_LSB_PTR    ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define EyelidGroup_CAPTURE_LSB        (*(reg16 *) EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define EyelidGroup_CAPTURE_LSB_PTR    ((reg16 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define EyelidGroup_AUX_CONTROLDP1          (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define EyelidGroup_AUX_CONTROLDP1_PTR      ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (EyelidGroup_Resolution == 8) */

   #define EyelidGroup_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define EyelidGroup_AUX_CONTROLDP0          (*(reg8 *)  EyelidGroup_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define EyelidGroup_AUX_CONTROLDP0_PTR      ((reg8 *)   EyelidGroup_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (EyelidGroup_UsingFixedFunction) */

#if(EyelidGroup_KillModeMinTime )
    #define EyelidGroup_KILLMODEMINTIME        (*(reg8 *)  EyelidGroup_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define EyelidGroup_KILLMODEMINTIME_PTR    ((reg8 *)   EyelidGroup_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (EyelidGroup_KillModeMinTime ) */

#if(EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_256_CLOCKS)
    #define EyelidGroup_DEADBAND_COUNT         (*(reg8 *)  EyelidGroup_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyelidGroup_DEADBAND_COUNT_PTR     ((reg8 *)   EyelidGroup_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define EyelidGroup_DEADBAND_LSB_PTR       ((reg8 *)   EyelidGroup_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define EyelidGroup_DEADBAND_LSB           (*(reg8 *)  EyelidGroup_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (EyelidGroup_UsingFixedFunction)
        #define EyelidGroup_DEADBAND_COUNT         (*(reg8 *)  EyelidGroup_PWMHW__CFG0)
        #define EyelidGroup_DEADBAND_COUNT_PTR     ((reg8 *)   EyelidGroup_PWMHW__CFG0)
        #define EyelidGroup_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyelidGroup_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define EyelidGroup_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define EyelidGroup_DEADBAND_COUNT         (*(reg8 *)  EyelidGroup_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyelidGroup_DEADBAND_COUNT_PTR     ((reg8 *)   EyelidGroup_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define EyelidGroup_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << EyelidGroup_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define EyelidGroup_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (EyelidGroup_UsingFixedFunction) */
#endif /* (EyelidGroup_DeadBandMode == EyelidGroup__B_PWM__DBM_256_CLOCKS) */



#if (EyelidGroup_UsingFixedFunction)
    #define EyelidGroup_STATUS                 (*(reg8 *) EyelidGroup_PWMHW__SR0)
    #define EyelidGroup_STATUS_PTR             ((reg8 *) EyelidGroup_PWMHW__SR0)
    #define EyelidGroup_STATUS_MASK            (*(reg8 *) EyelidGroup_PWMHW__SR0)
    #define EyelidGroup_STATUS_MASK_PTR        ((reg8 *) EyelidGroup_PWMHW__SR0)
    #define EyelidGroup_CONTROL                (*(reg8 *) EyelidGroup_PWMHW__CFG0)
    #define EyelidGroup_CONTROL_PTR            ((reg8 *) EyelidGroup_PWMHW__CFG0)
    #define EyelidGroup_CONTROL2               (*(reg8 *) EyelidGroup_PWMHW__CFG1)
    #define EyelidGroup_CONTROL3               (*(reg8 *) EyelidGroup_PWMHW__CFG2)
    #define EyelidGroup_GLOBAL_ENABLE          (*(reg8 *) EyelidGroup_PWMHW__PM_ACT_CFG)
    #define EyelidGroup_GLOBAL_ENABLE_PTR      ( (reg8 *) EyelidGroup_PWMHW__PM_ACT_CFG)
    #define EyelidGroup_GLOBAL_STBY_ENABLE     (*(reg8 *) EyelidGroup_PWMHW__PM_STBY_CFG)
    #define EyelidGroup_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) EyelidGroup_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define EyelidGroup_BLOCK_EN_MASK          (EyelidGroup_PWMHW__PM_ACT_MSK)
    #define EyelidGroup_BLOCK_STBY_EN_MASK     (EyelidGroup_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define EyelidGroup_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define EyelidGroup_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define EyelidGroup_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define EyelidGroup_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define EyelidGroup_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define EyelidGroup_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define EyelidGroup_CTRL_ENABLE            (uint8)((uint8)0x01u << EyelidGroup_CTRL_ENABLE_SHIFT)
    #define EyelidGroup_CTRL_RESET             (uint8)((uint8)0x01u << EyelidGroup_CTRL_RESET_SHIFT)
    #define EyelidGroup_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyelidGroup_CTRL_CMPMODE2_SHIFT)
    #define EyelidGroup_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyelidGroup_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define EyelidGroup_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define EyelidGroup_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << EyelidGroup_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define EyelidGroup_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define EyelidGroup_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define EyelidGroup_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define EyelidGroup_STATUS_TC_INT_EN_MASK_SHIFT            (EyelidGroup_STATUS_TC_SHIFT - 4u)
    #define EyelidGroup_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define EyelidGroup_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyelidGroup_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define EyelidGroup_STATUS_TC              (uint8)((uint8)0x01u << EyelidGroup_STATUS_TC_SHIFT)
    #define EyelidGroup_STATUS_CMP1            (uint8)((uint8)0x01u << EyelidGroup_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define EyelidGroup_STATUS_TC_INT_EN_MASK              (uint8)((uint8)EyelidGroup_STATUS_TC >> 4u)
    #define EyelidGroup_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)EyelidGroup_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define EyelidGroup_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define EyelidGroup_RT1_MASK              (uint8)((uint8)0x03u << EyelidGroup_RT1_SHIFT)
    #define EyelidGroup_SYNC                  (uint8)((uint8)0x03u << EyelidGroup_RT1_SHIFT)
    #define EyelidGroup_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define EyelidGroup_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << EyelidGroup_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define EyelidGroup_SYNCDSI_EN            (uint8)((uint8)0x0Fu << EyelidGroup_SYNCDSI_SHIFT)


#else
    #define EyelidGroup_STATUS                (*(reg8 *)   EyelidGroup_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyelidGroup_STATUS_PTR            ((reg8 *)    EyelidGroup_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define EyelidGroup_STATUS_MASK           (*(reg8 *)   EyelidGroup_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyelidGroup_STATUS_MASK_PTR       ((reg8 *)    EyelidGroup_PWMUDB_genblk8_stsreg__MASK_REG)
    #define EyelidGroup_STATUS_AUX_CTRL       (*(reg8 *)   EyelidGroup_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define EyelidGroup_CONTROL               (*(reg8 *)   EyelidGroup_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define EyelidGroup_CONTROL_PTR           ((reg8 *)    EyelidGroup_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define EyelidGroup_CTRL_ENABLE_SHIFT      (0x07u)
    #define EyelidGroup_CTRL_RESET_SHIFT       (0x06u)
    #define EyelidGroup_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define EyelidGroup_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define EyelidGroup_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define EyelidGroup_CTRL_ENABLE            (uint8)((uint8)0x01u << EyelidGroup_CTRL_ENABLE_SHIFT)
    #define EyelidGroup_CTRL_RESET             (uint8)((uint8)0x01u << EyelidGroup_CTRL_RESET_SHIFT)
    #define EyelidGroup_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << EyelidGroup_CTRL_CMPMODE2_SHIFT)
    #define EyelidGroup_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << EyelidGroup_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define EyelidGroup_STATUS_KILL_SHIFT          (0x05u)
    #define EyelidGroup_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define EyelidGroup_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define EyelidGroup_STATUS_TC_SHIFT            (0x02u)
    #define EyelidGroup_STATUS_CMP2_SHIFT          (0x01u)
    #define EyelidGroup_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define EyelidGroup_STATUS_KILL_INT_EN_MASK_SHIFT          (EyelidGroup_STATUS_KILL_SHIFT)
    #define EyelidGroup_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (EyelidGroup_STATUS_FIFONEMPTY_SHIFT)
    #define EyelidGroup_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (EyelidGroup_STATUS_FIFOFULL_SHIFT)
    #define EyelidGroup_STATUS_TC_INT_EN_MASK_SHIFT            (EyelidGroup_STATUS_TC_SHIFT)
    #define EyelidGroup_STATUS_CMP2_INT_EN_MASK_SHIFT          (EyelidGroup_STATUS_CMP2_SHIFT)
    #define EyelidGroup_STATUS_CMP1_INT_EN_MASK_SHIFT          (EyelidGroup_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define EyelidGroup_STATUS_KILL            (uint8)((uint8)0x00u << EyelidGroup_STATUS_KILL_SHIFT )
    #define EyelidGroup_STATUS_FIFOFULL        (uint8)((uint8)0x01u << EyelidGroup_STATUS_FIFOFULL_SHIFT)
    #define EyelidGroup_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << EyelidGroup_STATUS_FIFONEMPTY_SHIFT)
    #define EyelidGroup_STATUS_TC              (uint8)((uint8)0x01u << EyelidGroup_STATUS_TC_SHIFT)
    #define EyelidGroup_STATUS_CMP2            (uint8)((uint8)0x01u << EyelidGroup_STATUS_CMP2_SHIFT)
    #define EyelidGroup_STATUS_CMP1            (uint8)((uint8)0x01u << EyelidGroup_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define EyelidGroup_STATUS_KILL_INT_EN_MASK            (EyelidGroup_STATUS_KILL)
    #define EyelidGroup_STATUS_FIFOFULL_INT_EN_MASK        (EyelidGroup_STATUS_FIFOFULL)
    #define EyelidGroup_STATUS_FIFONEMPTY_INT_EN_MASK      (EyelidGroup_STATUS_FIFONEMPTY)
    #define EyelidGroup_STATUS_TC_INT_EN_MASK              (EyelidGroup_STATUS_TC)
    #define EyelidGroup_STATUS_CMP2_INT_EN_MASK            (EyelidGroup_STATUS_CMP2)
    #define EyelidGroup_STATUS_CMP1_INT_EN_MASK            (EyelidGroup_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define EyelidGroup_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define EyelidGroup_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define EyelidGroup_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define EyelidGroup_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define EyelidGroup_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* EyelidGroup_UsingFixedFunction */

#endif  /* CY_PWM_EyelidGroup_H */


/* [] END OF FILE */
