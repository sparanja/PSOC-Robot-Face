/*******************************************************************************
* File Name: Neck.h
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

#if !defined(CY_PWM_Neck_H)
#define CY_PWM_Neck_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Neck_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Neck_Resolution                     (16u)
#define Neck_UsingFixedFunction             (0u)
#define Neck_DeadBandMode                   (0u)
#define Neck_KillModeMinTime                (0u)
#define Neck_KillMode                       (0u)
#define Neck_PWMMode                        (1u)
#define Neck_PWMModeIsCenterAligned         (0u)
#define Neck_DeadBandUsed                   (0u)
#define Neck_DeadBand2_4                    (0u)

#if !defined(Neck_PWMUDB_genblk8_stsreg__REMOVED)
    #define Neck_UseStatus                  (1u)
#else
    #define Neck_UseStatus                  (0u)
#endif /* !defined(Neck_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Neck_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Neck_UseControl                 (1u)
#else
    #define Neck_UseControl                 (0u)
#endif /* !defined(Neck_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Neck_UseOneCompareMode              (0u)
#define Neck_MinimumKillTime                (1u)
#define Neck_EnableMode                     (0u)

#define Neck_CompareMode1SW                 (0u)
#define Neck_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Neck__B_PWM__DISABLED 0
#define Neck__B_PWM__ASYNCHRONOUS 1
#define Neck__B_PWM__SINGLECYCLE 2
#define Neck__B_PWM__LATCHED 3
#define Neck__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Neck__B_PWM__DBMDISABLED 0
#define Neck__B_PWM__DBM_2_4_CLOCKS 1
#define Neck__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Neck__B_PWM__ONE_OUTPUT 0
#define Neck__B_PWM__TWO_OUTPUTS 1
#define Neck__B_PWM__DUAL_EDGE 2
#define Neck__B_PWM__CENTER_ALIGN 3
#define Neck__B_PWM__DITHER 5
#define Neck__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Neck__B_PWM__LESS_THAN 1
#define Neck__B_PWM__LESS_THAN_OR_EQUAL 2
#define Neck__B_PWM__GREATER_THAN 3
#define Neck__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Neck__B_PWM__EQUAL 0
#define Neck__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Neck_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Neck_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Neck_PWMModeIsCenterAligned) */
        #if (Neck_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Neck_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Neck_DeadBandMode == Neck__B_PWM__DBM_256_CLOCKS || \
            Neck_DeadBandMode == Neck__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Neck_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Neck_KillModeMinTime) */

        /* Backup control register */
        #if(Neck_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Neck_UseControl) */

    #endif /* (!Neck_UsingFixedFunction) */

}Neck_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Neck_Start(void) ;
void    Neck_Stop(void) ;

#if (Neck_UseStatus || Neck_UsingFixedFunction)
    void  Neck_SetInterruptMode(uint8 interruptMode) ;
    uint8 Neck_ReadStatusRegister(void) ;
#endif /* (Neck_UseStatus || Neck_UsingFixedFunction) */

#define Neck_GetInterruptSource() Neck_ReadStatusRegister()

#if (Neck_UseControl)
    uint8 Neck_ReadControlRegister(void) ;
    void  Neck_WriteControlRegister(uint8 control)
          ;
#endif /* (Neck_UseControl) */

#if (Neck_UseOneCompareMode)
   #if (Neck_CompareMode1SW)
       void    Neck_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Neck_CompareMode1SW) */
#else
    #if (Neck_CompareMode1SW)
        void    Neck_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Neck_CompareMode1SW) */
    #if (Neck_CompareMode2SW)
        void    Neck_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Neck_CompareMode2SW) */
#endif /* (Neck_UseOneCompareMode) */

#if (!Neck_UsingFixedFunction)
    uint16   Neck_ReadCounter(void) ;
    uint16 Neck_ReadCapture(void) ;

    #if (Neck_UseStatus)
            void Neck_ClearFIFO(void) ;
    #endif /* (Neck_UseStatus) */

    void    Neck_WriteCounter(uint16 counter)
            ;
#endif /* (!Neck_UsingFixedFunction) */

void    Neck_WritePeriod(uint16 period)
        ;
uint16 Neck_ReadPeriod(void) ;

#if (Neck_UseOneCompareMode)
    void    Neck_WriteCompare(uint16 compare)
            ;
    uint16 Neck_ReadCompare(void) ;
#else
    void    Neck_WriteCompare1(uint16 compare)
            ;
    uint16 Neck_ReadCompare1(void) ;
    void    Neck_WriteCompare2(uint16 compare)
            ;
    uint16 Neck_ReadCompare2(void) ;
#endif /* (Neck_UseOneCompareMode) */


#if (Neck_DeadBandUsed)
    void    Neck_WriteDeadTime(uint8 deadtime) ;
    uint8   Neck_ReadDeadTime(void) ;
#endif /* (Neck_DeadBandUsed) */

#if ( Neck_KillModeMinTime)
    void Neck_WriteKillTime(uint8 killtime) ;
    uint8 Neck_ReadKillTime(void) ;
#endif /* ( Neck_KillModeMinTime) */

void Neck_Init(void) ;
void Neck_Enable(void) ;
void Neck_Sleep(void) ;
void Neck_Wakeup(void) ;
void Neck_SaveConfig(void) ;
void Neck_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Neck_INIT_PERIOD_VALUE          (19000u)
#define Neck_INIT_COMPARE_VALUE1        (0u)
#define Neck_INIT_COMPARE_VALUE2        (0u)
#define Neck_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Neck_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Neck_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Neck_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Neck_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Neck_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Neck_CTRL_CMPMODE2_SHIFT)
#define Neck_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Neck_CTRL_CMPMODE1_SHIFT)
#define Neck_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Neck_UsingFixedFunction)
   #define Neck_PERIOD_LSB              (*(reg16 *) Neck_PWMHW__PER0)
   #define Neck_PERIOD_LSB_PTR          ( (reg16 *) Neck_PWMHW__PER0)
   #define Neck_COMPARE1_LSB            (*(reg16 *) Neck_PWMHW__CNT_CMP0)
   #define Neck_COMPARE1_LSB_PTR        ( (reg16 *) Neck_PWMHW__CNT_CMP0)
   #define Neck_COMPARE2_LSB            (0x00u)
   #define Neck_COMPARE2_LSB_PTR        (0x00u)
   #define Neck_COUNTER_LSB             (*(reg16 *) Neck_PWMHW__CNT_CMP0)
   #define Neck_COUNTER_LSB_PTR         ( (reg16 *) Neck_PWMHW__CNT_CMP0)
   #define Neck_CAPTURE_LSB             (*(reg16 *) Neck_PWMHW__CAP0)
   #define Neck_CAPTURE_LSB_PTR         ( (reg16 *) Neck_PWMHW__CAP0)
   #define Neck_RT1                     (*(reg8 *)  Neck_PWMHW__RT1)
   #define Neck_RT1_PTR                 ( (reg8 *)  Neck_PWMHW__RT1)

#else
   #if (Neck_Resolution == 8u) /* 8bit - PWM */

       #if(Neck_PWMModeIsCenterAligned)
           #define Neck_PERIOD_LSB      (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Neck_PERIOD_LSB_PTR  ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Neck_PERIOD_LSB      (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Neck_PERIOD_LSB_PTR  ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Neck_PWMModeIsCenterAligned) */

       #define Neck_COMPARE1_LSB        (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Neck_COMPARE1_LSB_PTR    ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Neck_COMPARE2_LSB        (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Neck_COMPARE2_LSB_PTR    ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Neck_COUNTERCAP_LSB      (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Neck_COUNTERCAP_LSB_PTR  ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Neck_COUNTER_LSB         (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Neck_COUNTER_LSB_PTR     ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Neck_CAPTURE_LSB         (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Neck_CAPTURE_LSB_PTR     ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Neck_PWMModeIsCenterAligned)
               #define Neck_PERIOD_LSB      (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Neck_PERIOD_LSB_PTR  ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Neck_PERIOD_LSB      (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Neck_PERIOD_LSB_PTR  ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Neck_PWMModeIsCenterAligned) */

            #define Neck_COMPARE1_LSB       (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Neck_COMPARE1_LSB_PTR   ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Neck_COMPARE2_LSB       (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Neck_COMPARE2_LSB_PTR   ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Neck_COUNTERCAP_LSB     (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Neck_COUNTERCAP_LSB_PTR ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Neck_COUNTER_LSB        (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Neck_COUNTER_LSB_PTR    ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Neck_CAPTURE_LSB        (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Neck_CAPTURE_LSB_PTR    ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Neck_PWMModeIsCenterAligned)
               #define Neck_PERIOD_LSB      (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Neck_PERIOD_LSB_PTR  ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Neck_PERIOD_LSB      (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Neck_PERIOD_LSB_PTR  ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Neck_PWMModeIsCenterAligned) */

            #define Neck_COMPARE1_LSB       (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Neck_COMPARE1_LSB_PTR   ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Neck_COMPARE2_LSB       (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Neck_COMPARE2_LSB_PTR   ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Neck_COUNTERCAP_LSB     (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Neck_COUNTERCAP_LSB_PTR ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Neck_COUNTER_LSB        (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Neck_COUNTER_LSB_PTR    ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Neck_CAPTURE_LSB        (*(reg16 *) Neck_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Neck_CAPTURE_LSB_PTR    ((reg16 *)  Neck_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Neck_AUX_CONTROLDP1          (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Neck_AUX_CONTROLDP1_PTR      ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Neck_Resolution == 8) */

   #define Neck_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Neck_AUX_CONTROLDP0          (*(reg8 *)  Neck_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Neck_AUX_CONTROLDP0_PTR      ((reg8 *)   Neck_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Neck_UsingFixedFunction) */

#if(Neck_KillModeMinTime )
    #define Neck_KILLMODEMINTIME        (*(reg8 *)  Neck_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Neck_KILLMODEMINTIME_PTR    ((reg8 *)   Neck_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Neck_KillModeMinTime ) */

#if(Neck_DeadBandMode == Neck__B_PWM__DBM_256_CLOCKS)
    #define Neck_DEADBAND_COUNT         (*(reg8 *)  Neck_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Neck_DEADBAND_COUNT_PTR     ((reg8 *)   Neck_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Neck_DEADBAND_LSB_PTR       ((reg8 *)   Neck_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Neck_DEADBAND_LSB           (*(reg8 *)  Neck_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Neck_DeadBandMode == Neck__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Neck_UsingFixedFunction)
        #define Neck_DEADBAND_COUNT         (*(reg8 *)  Neck_PWMHW__CFG0)
        #define Neck_DEADBAND_COUNT_PTR     ((reg8 *)   Neck_PWMHW__CFG0)
        #define Neck_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Neck_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Neck_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Neck_DEADBAND_COUNT         (*(reg8 *)  Neck_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Neck_DEADBAND_COUNT_PTR     ((reg8 *)   Neck_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Neck_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Neck_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Neck_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Neck_UsingFixedFunction) */
#endif /* (Neck_DeadBandMode == Neck__B_PWM__DBM_256_CLOCKS) */



#if (Neck_UsingFixedFunction)
    #define Neck_STATUS                 (*(reg8 *) Neck_PWMHW__SR0)
    #define Neck_STATUS_PTR             ((reg8 *) Neck_PWMHW__SR0)
    #define Neck_STATUS_MASK            (*(reg8 *) Neck_PWMHW__SR0)
    #define Neck_STATUS_MASK_PTR        ((reg8 *) Neck_PWMHW__SR0)
    #define Neck_CONTROL                (*(reg8 *) Neck_PWMHW__CFG0)
    #define Neck_CONTROL_PTR            ((reg8 *) Neck_PWMHW__CFG0)
    #define Neck_CONTROL2               (*(reg8 *) Neck_PWMHW__CFG1)
    #define Neck_CONTROL3               (*(reg8 *) Neck_PWMHW__CFG2)
    #define Neck_GLOBAL_ENABLE          (*(reg8 *) Neck_PWMHW__PM_ACT_CFG)
    #define Neck_GLOBAL_ENABLE_PTR      ( (reg8 *) Neck_PWMHW__PM_ACT_CFG)
    #define Neck_GLOBAL_STBY_ENABLE     (*(reg8 *) Neck_PWMHW__PM_STBY_CFG)
    #define Neck_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Neck_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Neck_BLOCK_EN_MASK          (Neck_PWMHW__PM_ACT_MSK)
    #define Neck_BLOCK_STBY_EN_MASK     (Neck_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Neck_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Neck_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Neck_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Neck_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Neck_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Neck_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Neck_CTRL_ENABLE            (uint8)((uint8)0x01u << Neck_CTRL_ENABLE_SHIFT)
    #define Neck_CTRL_RESET             (uint8)((uint8)0x01u << Neck_CTRL_RESET_SHIFT)
    #define Neck_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Neck_CTRL_CMPMODE2_SHIFT)
    #define Neck_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Neck_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Neck_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Neck_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Neck_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Neck_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Neck_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Neck_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Neck_STATUS_TC_INT_EN_MASK_SHIFT            (Neck_STATUS_TC_SHIFT - 4u)
    #define Neck_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Neck_STATUS_CMP1_INT_EN_MASK_SHIFT          (Neck_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Neck_STATUS_TC              (uint8)((uint8)0x01u << Neck_STATUS_TC_SHIFT)
    #define Neck_STATUS_CMP1            (uint8)((uint8)0x01u << Neck_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Neck_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Neck_STATUS_TC >> 4u)
    #define Neck_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Neck_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Neck_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Neck_RT1_MASK              (uint8)((uint8)0x03u << Neck_RT1_SHIFT)
    #define Neck_SYNC                  (uint8)((uint8)0x03u << Neck_RT1_SHIFT)
    #define Neck_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Neck_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Neck_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Neck_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Neck_SYNCDSI_SHIFT)


#else
    #define Neck_STATUS                (*(reg8 *)   Neck_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Neck_STATUS_PTR            ((reg8 *)    Neck_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Neck_STATUS_MASK           (*(reg8 *)   Neck_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Neck_STATUS_MASK_PTR       ((reg8 *)    Neck_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Neck_STATUS_AUX_CTRL       (*(reg8 *)   Neck_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Neck_CONTROL               (*(reg8 *)   Neck_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Neck_CONTROL_PTR           ((reg8 *)    Neck_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Neck_CTRL_ENABLE_SHIFT      (0x07u)
    #define Neck_CTRL_RESET_SHIFT       (0x06u)
    #define Neck_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Neck_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Neck_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Neck_CTRL_ENABLE            (uint8)((uint8)0x01u << Neck_CTRL_ENABLE_SHIFT)
    #define Neck_CTRL_RESET             (uint8)((uint8)0x01u << Neck_CTRL_RESET_SHIFT)
    #define Neck_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Neck_CTRL_CMPMODE2_SHIFT)
    #define Neck_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Neck_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Neck_STATUS_KILL_SHIFT          (0x05u)
    #define Neck_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Neck_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Neck_STATUS_TC_SHIFT            (0x02u)
    #define Neck_STATUS_CMP2_SHIFT          (0x01u)
    #define Neck_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Neck_STATUS_KILL_INT_EN_MASK_SHIFT          (Neck_STATUS_KILL_SHIFT)
    #define Neck_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Neck_STATUS_FIFONEMPTY_SHIFT)
    #define Neck_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Neck_STATUS_FIFOFULL_SHIFT)
    #define Neck_STATUS_TC_INT_EN_MASK_SHIFT            (Neck_STATUS_TC_SHIFT)
    #define Neck_STATUS_CMP2_INT_EN_MASK_SHIFT          (Neck_STATUS_CMP2_SHIFT)
    #define Neck_STATUS_CMP1_INT_EN_MASK_SHIFT          (Neck_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Neck_STATUS_KILL            (uint8)((uint8)0x00u << Neck_STATUS_KILL_SHIFT )
    #define Neck_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Neck_STATUS_FIFOFULL_SHIFT)
    #define Neck_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Neck_STATUS_FIFONEMPTY_SHIFT)
    #define Neck_STATUS_TC              (uint8)((uint8)0x01u << Neck_STATUS_TC_SHIFT)
    #define Neck_STATUS_CMP2            (uint8)((uint8)0x01u << Neck_STATUS_CMP2_SHIFT)
    #define Neck_STATUS_CMP1            (uint8)((uint8)0x01u << Neck_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Neck_STATUS_KILL_INT_EN_MASK            (Neck_STATUS_KILL)
    #define Neck_STATUS_FIFOFULL_INT_EN_MASK        (Neck_STATUS_FIFOFULL)
    #define Neck_STATUS_FIFONEMPTY_INT_EN_MASK      (Neck_STATUS_FIFONEMPTY)
    #define Neck_STATUS_TC_INT_EN_MASK              (Neck_STATUS_TC)
    #define Neck_STATUS_CMP2_INT_EN_MASK            (Neck_STATUS_CMP2)
    #define Neck_STATUS_CMP1_INT_EN_MASK            (Neck_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Neck_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Neck_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Neck_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Neck_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Neck_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Neck_UsingFixedFunction */

#endif  /* CY_PWM_Neck_H */


/* [] END OF FILE */
