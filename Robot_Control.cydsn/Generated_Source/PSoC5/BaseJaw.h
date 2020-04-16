/*******************************************************************************
* File Name: BaseJaw.h
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

#if !defined(CY_PWM_BaseJaw_H)
#define CY_PWM_BaseJaw_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 BaseJaw_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define BaseJaw_Resolution                     (16u)
#define BaseJaw_UsingFixedFunction             (0u)
#define BaseJaw_DeadBandMode                   (0u)
#define BaseJaw_KillModeMinTime                (0u)
#define BaseJaw_KillMode                       (0u)
#define BaseJaw_PWMMode                        (1u)
#define BaseJaw_PWMModeIsCenterAligned         (0u)
#define BaseJaw_DeadBandUsed                   (0u)
#define BaseJaw_DeadBand2_4                    (0u)

#if !defined(BaseJaw_PWMUDB_genblk8_stsreg__REMOVED)
    #define BaseJaw_UseStatus                  (1u)
#else
    #define BaseJaw_UseStatus                  (0u)
#endif /* !defined(BaseJaw_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(BaseJaw_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define BaseJaw_UseControl                 (1u)
#else
    #define BaseJaw_UseControl                 (0u)
#endif /* !defined(BaseJaw_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define BaseJaw_UseOneCompareMode              (0u)
#define BaseJaw_MinimumKillTime                (1u)
#define BaseJaw_EnableMode                     (0u)

#define BaseJaw_CompareMode1SW                 (0u)
#define BaseJaw_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define BaseJaw__B_PWM__DISABLED 0
#define BaseJaw__B_PWM__ASYNCHRONOUS 1
#define BaseJaw__B_PWM__SINGLECYCLE 2
#define BaseJaw__B_PWM__LATCHED 3
#define BaseJaw__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define BaseJaw__B_PWM__DBMDISABLED 0
#define BaseJaw__B_PWM__DBM_2_4_CLOCKS 1
#define BaseJaw__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define BaseJaw__B_PWM__ONE_OUTPUT 0
#define BaseJaw__B_PWM__TWO_OUTPUTS 1
#define BaseJaw__B_PWM__DUAL_EDGE 2
#define BaseJaw__B_PWM__CENTER_ALIGN 3
#define BaseJaw__B_PWM__DITHER 5
#define BaseJaw__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define BaseJaw__B_PWM__LESS_THAN 1
#define BaseJaw__B_PWM__LESS_THAN_OR_EQUAL 2
#define BaseJaw__B_PWM__GREATER_THAN 3
#define BaseJaw__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define BaseJaw__B_PWM__EQUAL 0
#define BaseJaw__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!BaseJaw_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!BaseJaw_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!BaseJaw_PWMModeIsCenterAligned) */
        #if (BaseJaw_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (BaseJaw_UseStatus) */

        /* Backup for Deadband parameters */
        #if(BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_256_CLOCKS || \
            BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(BaseJaw_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (BaseJaw_KillModeMinTime) */

        /* Backup control register */
        #if(BaseJaw_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (BaseJaw_UseControl) */

    #endif /* (!BaseJaw_UsingFixedFunction) */

}BaseJaw_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    BaseJaw_Start(void) ;
void    BaseJaw_Stop(void) ;

#if (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction)
    void  BaseJaw_SetInterruptMode(uint8 interruptMode) ;
    uint8 BaseJaw_ReadStatusRegister(void) ;
#endif /* (BaseJaw_UseStatus || BaseJaw_UsingFixedFunction) */

#define BaseJaw_GetInterruptSource() BaseJaw_ReadStatusRegister()

#if (BaseJaw_UseControl)
    uint8 BaseJaw_ReadControlRegister(void) ;
    void  BaseJaw_WriteControlRegister(uint8 control)
          ;
#endif /* (BaseJaw_UseControl) */

#if (BaseJaw_UseOneCompareMode)
   #if (BaseJaw_CompareMode1SW)
       void    BaseJaw_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (BaseJaw_CompareMode1SW) */
#else
    #if (BaseJaw_CompareMode1SW)
        void    BaseJaw_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (BaseJaw_CompareMode1SW) */
    #if (BaseJaw_CompareMode2SW)
        void    BaseJaw_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (BaseJaw_CompareMode2SW) */
#endif /* (BaseJaw_UseOneCompareMode) */

#if (!BaseJaw_UsingFixedFunction)
    uint16   BaseJaw_ReadCounter(void) ;
    uint16 BaseJaw_ReadCapture(void) ;

    #if (BaseJaw_UseStatus)
            void BaseJaw_ClearFIFO(void) ;
    #endif /* (BaseJaw_UseStatus) */

    void    BaseJaw_WriteCounter(uint16 counter)
            ;
#endif /* (!BaseJaw_UsingFixedFunction) */

void    BaseJaw_WritePeriod(uint16 period)
        ;
uint16 BaseJaw_ReadPeriod(void) ;

#if (BaseJaw_UseOneCompareMode)
    void    BaseJaw_WriteCompare(uint16 compare)
            ;
    uint16 BaseJaw_ReadCompare(void) ;
#else
    void    BaseJaw_WriteCompare1(uint16 compare)
            ;
    uint16 BaseJaw_ReadCompare1(void) ;
    void    BaseJaw_WriteCompare2(uint16 compare)
            ;
    uint16 BaseJaw_ReadCompare2(void) ;
#endif /* (BaseJaw_UseOneCompareMode) */


#if (BaseJaw_DeadBandUsed)
    void    BaseJaw_WriteDeadTime(uint8 deadtime) ;
    uint8   BaseJaw_ReadDeadTime(void) ;
#endif /* (BaseJaw_DeadBandUsed) */

#if ( BaseJaw_KillModeMinTime)
    void BaseJaw_WriteKillTime(uint8 killtime) ;
    uint8 BaseJaw_ReadKillTime(void) ;
#endif /* ( BaseJaw_KillModeMinTime) */

void BaseJaw_Init(void) ;
void BaseJaw_Enable(void) ;
void BaseJaw_Sleep(void) ;
void BaseJaw_Wakeup(void) ;
void BaseJaw_SaveConfig(void) ;
void BaseJaw_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define BaseJaw_INIT_PERIOD_VALUE          (60000u)
#define BaseJaw_INIT_COMPARE_VALUE1        (0u)
#define BaseJaw_INIT_COMPARE_VALUE2        (0u)
#define BaseJaw_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    BaseJaw_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BaseJaw_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BaseJaw_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    BaseJaw_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define BaseJaw_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  BaseJaw_CTRL_CMPMODE2_SHIFT)
#define BaseJaw_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  BaseJaw_CTRL_CMPMODE1_SHIFT)
#define BaseJaw_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (BaseJaw_UsingFixedFunction)
   #define BaseJaw_PERIOD_LSB              (*(reg16 *) BaseJaw_PWMHW__PER0)
   #define BaseJaw_PERIOD_LSB_PTR          ( (reg16 *) BaseJaw_PWMHW__PER0)
   #define BaseJaw_COMPARE1_LSB            (*(reg16 *) BaseJaw_PWMHW__CNT_CMP0)
   #define BaseJaw_COMPARE1_LSB_PTR        ( (reg16 *) BaseJaw_PWMHW__CNT_CMP0)
   #define BaseJaw_COMPARE2_LSB            (0x00u)
   #define BaseJaw_COMPARE2_LSB_PTR        (0x00u)
   #define BaseJaw_COUNTER_LSB             (*(reg16 *) BaseJaw_PWMHW__CNT_CMP0)
   #define BaseJaw_COUNTER_LSB_PTR         ( (reg16 *) BaseJaw_PWMHW__CNT_CMP0)
   #define BaseJaw_CAPTURE_LSB             (*(reg16 *) BaseJaw_PWMHW__CAP0)
   #define BaseJaw_CAPTURE_LSB_PTR         ( (reg16 *) BaseJaw_PWMHW__CAP0)
   #define BaseJaw_RT1                     (*(reg8 *)  BaseJaw_PWMHW__RT1)
   #define BaseJaw_RT1_PTR                 ( (reg8 *)  BaseJaw_PWMHW__RT1)

#else
   #if (BaseJaw_Resolution == 8u) /* 8bit - PWM */

       #if(BaseJaw_PWMModeIsCenterAligned)
           #define BaseJaw_PERIOD_LSB      (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define BaseJaw_PERIOD_LSB_PTR  ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define BaseJaw_PERIOD_LSB      (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define BaseJaw_PERIOD_LSB_PTR  ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (BaseJaw_PWMModeIsCenterAligned) */

       #define BaseJaw_COMPARE1_LSB        (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BaseJaw_COMPARE1_LSB_PTR    ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define BaseJaw_COMPARE2_LSB        (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BaseJaw_COMPARE2_LSB_PTR    ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define BaseJaw_COUNTERCAP_LSB      (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BaseJaw_COUNTERCAP_LSB_PTR  ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define BaseJaw_COUNTER_LSB         (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BaseJaw_COUNTER_LSB_PTR     ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define BaseJaw_CAPTURE_LSB         (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define BaseJaw_CAPTURE_LSB_PTR     ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(BaseJaw_PWMModeIsCenterAligned)
               #define BaseJaw_PERIOD_LSB      (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define BaseJaw_PERIOD_LSB_PTR  ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define BaseJaw_PERIOD_LSB      (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define BaseJaw_PERIOD_LSB_PTR  ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (BaseJaw_PWMModeIsCenterAligned) */

            #define BaseJaw_COMPARE1_LSB       (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BaseJaw_COMPARE1_LSB_PTR   ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define BaseJaw_COMPARE2_LSB       (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BaseJaw_COMPARE2_LSB_PTR   ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define BaseJaw_COUNTERCAP_LSB     (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BaseJaw_COUNTERCAP_LSB_PTR ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define BaseJaw_COUNTER_LSB        (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BaseJaw_COUNTER_LSB_PTR    ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define BaseJaw_CAPTURE_LSB        (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define BaseJaw_CAPTURE_LSB_PTR    ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(BaseJaw_PWMModeIsCenterAligned)
               #define BaseJaw_PERIOD_LSB      (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define BaseJaw_PERIOD_LSB_PTR  ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define BaseJaw_PERIOD_LSB      (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define BaseJaw_PERIOD_LSB_PTR  ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (BaseJaw_PWMModeIsCenterAligned) */

            #define BaseJaw_COMPARE1_LSB       (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BaseJaw_COMPARE1_LSB_PTR   ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define BaseJaw_COMPARE2_LSB       (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BaseJaw_COMPARE2_LSB_PTR   ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define BaseJaw_COUNTERCAP_LSB     (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BaseJaw_COUNTERCAP_LSB_PTR ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define BaseJaw_COUNTER_LSB        (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BaseJaw_COUNTER_LSB_PTR    ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define BaseJaw_CAPTURE_LSB        (*(reg16 *) BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define BaseJaw_CAPTURE_LSB_PTR    ((reg16 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define BaseJaw_AUX_CONTROLDP1          (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define BaseJaw_AUX_CONTROLDP1_PTR      ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (BaseJaw_Resolution == 8) */

   #define BaseJaw_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define BaseJaw_AUX_CONTROLDP0          (*(reg8 *)  BaseJaw_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define BaseJaw_AUX_CONTROLDP0_PTR      ((reg8 *)   BaseJaw_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (BaseJaw_UsingFixedFunction) */

#if(BaseJaw_KillModeMinTime )
    #define BaseJaw_KILLMODEMINTIME        (*(reg8 *)  BaseJaw_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define BaseJaw_KILLMODEMINTIME_PTR    ((reg8 *)   BaseJaw_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (BaseJaw_KillModeMinTime ) */

#if(BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_256_CLOCKS)
    #define BaseJaw_DEADBAND_COUNT         (*(reg8 *)  BaseJaw_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BaseJaw_DEADBAND_COUNT_PTR     ((reg8 *)   BaseJaw_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define BaseJaw_DEADBAND_LSB_PTR       ((reg8 *)   BaseJaw_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define BaseJaw_DEADBAND_LSB           (*(reg8 *)  BaseJaw_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (BaseJaw_UsingFixedFunction)
        #define BaseJaw_DEADBAND_COUNT         (*(reg8 *)  BaseJaw_PWMHW__CFG0)
        #define BaseJaw_DEADBAND_COUNT_PTR     ((reg8 *)   BaseJaw_PWMHW__CFG0)
        #define BaseJaw_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BaseJaw_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define BaseJaw_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define BaseJaw_DEADBAND_COUNT         (*(reg8 *)  BaseJaw_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BaseJaw_DEADBAND_COUNT_PTR     ((reg8 *)   BaseJaw_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define BaseJaw_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << BaseJaw_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define BaseJaw_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (BaseJaw_UsingFixedFunction) */
#endif /* (BaseJaw_DeadBandMode == BaseJaw__B_PWM__DBM_256_CLOCKS) */



#if (BaseJaw_UsingFixedFunction)
    #define BaseJaw_STATUS                 (*(reg8 *) BaseJaw_PWMHW__SR0)
    #define BaseJaw_STATUS_PTR             ((reg8 *) BaseJaw_PWMHW__SR0)
    #define BaseJaw_STATUS_MASK            (*(reg8 *) BaseJaw_PWMHW__SR0)
    #define BaseJaw_STATUS_MASK_PTR        ((reg8 *) BaseJaw_PWMHW__SR0)
    #define BaseJaw_CONTROL                (*(reg8 *) BaseJaw_PWMHW__CFG0)
    #define BaseJaw_CONTROL_PTR            ((reg8 *) BaseJaw_PWMHW__CFG0)
    #define BaseJaw_CONTROL2               (*(reg8 *) BaseJaw_PWMHW__CFG1)
    #define BaseJaw_CONTROL3               (*(reg8 *) BaseJaw_PWMHW__CFG2)
    #define BaseJaw_GLOBAL_ENABLE          (*(reg8 *) BaseJaw_PWMHW__PM_ACT_CFG)
    #define BaseJaw_GLOBAL_ENABLE_PTR      ( (reg8 *) BaseJaw_PWMHW__PM_ACT_CFG)
    #define BaseJaw_GLOBAL_STBY_ENABLE     (*(reg8 *) BaseJaw_PWMHW__PM_STBY_CFG)
    #define BaseJaw_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) BaseJaw_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define BaseJaw_BLOCK_EN_MASK          (BaseJaw_PWMHW__PM_ACT_MSK)
    #define BaseJaw_BLOCK_STBY_EN_MASK     (BaseJaw_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define BaseJaw_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define BaseJaw_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define BaseJaw_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define BaseJaw_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define BaseJaw_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define BaseJaw_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define BaseJaw_CTRL_ENABLE            (uint8)((uint8)0x01u << BaseJaw_CTRL_ENABLE_SHIFT)
    #define BaseJaw_CTRL_RESET             (uint8)((uint8)0x01u << BaseJaw_CTRL_RESET_SHIFT)
    #define BaseJaw_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BaseJaw_CTRL_CMPMODE2_SHIFT)
    #define BaseJaw_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BaseJaw_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define BaseJaw_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define BaseJaw_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << BaseJaw_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define BaseJaw_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define BaseJaw_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define BaseJaw_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define BaseJaw_STATUS_TC_INT_EN_MASK_SHIFT            (BaseJaw_STATUS_TC_SHIFT - 4u)
    #define BaseJaw_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define BaseJaw_STATUS_CMP1_INT_EN_MASK_SHIFT          (BaseJaw_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define BaseJaw_STATUS_TC              (uint8)((uint8)0x01u << BaseJaw_STATUS_TC_SHIFT)
    #define BaseJaw_STATUS_CMP1            (uint8)((uint8)0x01u << BaseJaw_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define BaseJaw_STATUS_TC_INT_EN_MASK              (uint8)((uint8)BaseJaw_STATUS_TC >> 4u)
    #define BaseJaw_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)BaseJaw_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define BaseJaw_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define BaseJaw_RT1_MASK              (uint8)((uint8)0x03u << BaseJaw_RT1_SHIFT)
    #define BaseJaw_SYNC                  (uint8)((uint8)0x03u << BaseJaw_RT1_SHIFT)
    #define BaseJaw_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define BaseJaw_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << BaseJaw_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define BaseJaw_SYNCDSI_EN            (uint8)((uint8)0x0Fu << BaseJaw_SYNCDSI_SHIFT)


#else
    #define BaseJaw_STATUS                (*(reg8 *)   BaseJaw_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BaseJaw_STATUS_PTR            ((reg8 *)    BaseJaw_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define BaseJaw_STATUS_MASK           (*(reg8 *)   BaseJaw_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BaseJaw_STATUS_MASK_PTR       ((reg8 *)    BaseJaw_PWMUDB_genblk8_stsreg__MASK_REG)
    #define BaseJaw_STATUS_AUX_CTRL       (*(reg8 *)   BaseJaw_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define BaseJaw_CONTROL               (*(reg8 *)   BaseJaw_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define BaseJaw_CONTROL_PTR           ((reg8 *)    BaseJaw_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define BaseJaw_CTRL_ENABLE_SHIFT      (0x07u)
    #define BaseJaw_CTRL_RESET_SHIFT       (0x06u)
    #define BaseJaw_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define BaseJaw_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define BaseJaw_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define BaseJaw_CTRL_ENABLE            (uint8)((uint8)0x01u << BaseJaw_CTRL_ENABLE_SHIFT)
    #define BaseJaw_CTRL_RESET             (uint8)((uint8)0x01u << BaseJaw_CTRL_RESET_SHIFT)
    #define BaseJaw_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << BaseJaw_CTRL_CMPMODE2_SHIFT)
    #define BaseJaw_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << BaseJaw_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define BaseJaw_STATUS_KILL_SHIFT          (0x05u)
    #define BaseJaw_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define BaseJaw_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define BaseJaw_STATUS_TC_SHIFT            (0x02u)
    #define BaseJaw_STATUS_CMP2_SHIFT          (0x01u)
    #define BaseJaw_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define BaseJaw_STATUS_KILL_INT_EN_MASK_SHIFT          (BaseJaw_STATUS_KILL_SHIFT)
    #define BaseJaw_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (BaseJaw_STATUS_FIFONEMPTY_SHIFT)
    #define BaseJaw_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (BaseJaw_STATUS_FIFOFULL_SHIFT)
    #define BaseJaw_STATUS_TC_INT_EN_MASK_SHIFT            (BaseJaw_STATUS_TC_SHIFT)
    #define BaseJaw_STATUS_CMP2_INT_EN_MASK_SHIFT          (BaseJaw_STATUS_CMP2_SHIFT)
    #define BaseJaw_STATUS_CMP1_INT_EN_MASK_SHIFT          (BaseJaw_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define BaseJaw_STATUS_KILL            (uint8)((uint8)0x00u << BaseJaw_STATUS_KILL_SHIFT )
    #define BaseJaw_STATUS_FIFOFULL        (uint8)((uint8)0x01u << BaseJaw_STATUS_FIFOFULL_SHIFT)
    #define BaseJaw_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << BaseJaw_STATUS_FIFONEMPTY_SHIFT)
    #define BaseJaw_STATUS_TC              (uint8)((uint8)0x01u << BaseJaw_STATUS_TC_SHIFT)
    #define BaseJaw_STATUS_CMP2            (uint8)((uint8)0x01u << BaseJaw_STATUS_CMP2_SHIFT)
    #define BaseJaw_STATUS_CMP1            (uint8)((uint8)0x01u << BaseJaw_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define BaseJaw_STATUS_KILL_INT_EN_MASK            (BaseJaw_STATUS_KILL)
    #define BaseJaw_STATUS_FIFOFULL_INT_EN_MASK        (BaseJaw_STATUS_FIFOFULL)
    #define BaseJaw_STATUS_FIFONEMPTY_INT_EN_MASK      (BaseJaw_STATUS_FIFONEMPTY)
    #define BaseJaw_STATUS_TC_INT_EN_MASK              (BaseJaw_STATUS_TC)
    #define BaseJaw_STATUS_CMP2_INT_EN_MASK            (BaseJaw_STATUS_CMP2)
    #define BaseJaw_STATUS_CMP1_INT_EN_MASK            (BaseJaw_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define BaseJaw_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define BaseJaw_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define BaseJaw_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define BaseJaw_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define BaseJaw_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* BaseJaw_UsingFixedFunction */

#endif  /* CY_PWM_BaseJaw_H */


/* [] END OF FILE */
