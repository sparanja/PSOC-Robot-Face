/*******************************************************************************
* File Name: Lip.h
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

#if !defined(CY_PWM_Lip_H)
#define CY_PWM_Lip_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 Lip_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define Lip_Resolution                     (16u)
#define Lip_UsingFixedFunction             (0u)
#define Lip_DeadBandMode                   (0u)
#define Lip_KillModeMinTime                (0u)
#define Lip_KillMode                       (0u)
#define Lip_PWMMode                        (1u)
#define Lip_PWMModeIsCenterAligned         (0u)
#define Lip_DeadBandUsed                   (0u)
#define Lip_DeadBand2_4                    (0u)

#if !defined(Lip_PWMUDB_genblk8_stsreg__REMOVED)
    #define Lip_UseStatus                  (1u)
#else
    #define Lip_UseStatus                  (0u)
#endif /* !defined(Lip_PWMUDB_genblk8_stsreg__REMOVED) */

#if !defined(Lip_PWMUDB_genblk1_ctrlreg__REMOVED)
    #define Lip_UseControl                 (1u)
#else
    #define Lip_UseControl                 (0u)
#endif /* !defined(Lip_PWMUDB_genblk1_ctrlreg__REMOVED) */

#define Lip_UseOneCompareMode              (0u)
#define Lip_MinimumKillTime                (1u)
#define Lip_EnableMode                     (0u)

#define Lip_CompareMode1SW                 (0u)
#define Lip_CompareMode2SW                 (0u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v3_30 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define Lip__B_PWM__DISABLED 0
#define Lip__B_PWM__ASYNCHRONOUS 1
#define Lip__B_PWM__SINGLECYCLE 2
#define Lip__B_PWM__LATCHED 3
#define Lip__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define Lip__B_PWM__DBMDISABLED 0
#define Lip__B_PWM__DBM_2_4_CLOCKS 1
#define Lip__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define Lip__B_PWM__ONE_OUTPUT 0
#define Lip__B_PWM__TWO_OUTPUTS 1
#define Lip__B_PWM__DUAL_EDGE 2
#define Lip__B_PWM__CENTER_ALIGN 3
#define Lip__B_PWM__DITHER 5
#define Lip__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define Lip__B_PWM__LESS_THAN 1
#define Lip__B_PWM__LESS_THAN_OR_EQUAL 2
#define Lip__B_PWM__GREATER_THAN 3
#define Lip__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define Lip__B_PWM__EQUAL 0
#define Lip__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{

    uint8 PWMEnableState;

    #if(!Lip_UsingFixedFunction)
        uint16 PWMUdb;               /* PWM Current Counter value  */
        #if(!Lip_PWMModeIsCenterAligned)
            uint16 PWMPeriod;
        #endif /* (!Lip_PWMModeIsCenterAligned) */
        #if (Lip_UseStatus)
            uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
        #endif /* (Lip_UseStatus) */

        /* Backup for Deadband parameters */
        #if(Lip_DeadBandMode == Lip__B_PWM__DBM_256_CLOCKS || \
            Lip_DeadBandMode == Lip__B_PWM__DBM_2_4_CLOCKS)
            uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
        #endif /* deadband count is either 2-4 clocks or 256 clocks */

        /* Backup Kill Mode Counter*/
        #if(Lip_KillModeMinTime)
            uint8 PWMKillCounterPeriod; /* Kill Mode period value */
        #endif /* (Lip_KillModeMinTime) */

        /* Backup control register */
        #if(Lip_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (Lip_UseControl) */

    #endif /* (!Lip_UsingFixedFunction) */

}Lip_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/

void    Lip_Start(void) ;
void    Lip_Stop(void) ;

#if (Lip_UseStatus || Lip_UsingFixedFunction)
    void  Lip_SetInterruptMode(uint8 interruptMode) ;
    uint8 Lip_ReadStatusRegister(void) ;
#endif /* (Lip_UseStatus || Lip_UsingFixedFunction) */

#define Lip_GetInterruptSource() Lip_ReadStatusRegister()

#if (Lip_UseControl)
    uint8 Lip_ReadControlRegister(void) ;
    void  Lip_WriteControlRegister(uint8 control)
          ;
#endif /* (Lip_UseControl) */

#if (Lip_UseOneCompareMode)
   #if (Lip_CompareMode1SW)
       void    Lip_SetCompareMode(uint8 comparemode)
               ;
   #endif /* (Lip_CompareMode1SW) */
#else
    #if (Lip_CompareMode1SW)
        void    Lip_SetCompareMode1(uint8 comparemode)
                ;
    #endif /* (Lip_CompareMode1SW) */
    #if (Lip_CompareMode2SW)
        void    Lip_SetCompareMode2(uint8 comparemode)
                ;
    #endif /* (Lip_CompareMode2SW) */
#endif /* (Lip_UseOneCompareMode) */

#if (!Lip_UsingFixedFunction)
    uint16   Lip_ReadCounter(void) ;
    uint16 Lip_ReadCapture(void) ;

    #if (Lip_UseStatus)
            void Lip_ClearFIFO(void) ;
    #endif /* (Lip_UseStatus) */

    void    Lip_WriteCounter(uint16 counter)
            ;
#endif /* (!Lip_UsingFixedFunction) */

void    Lip_WritePeriod(uint16 period)
        ;
uint16 Lip_ReadPeriod(void) ;

#if (Lip_UseOneCompareMode)
    void    Lip_WriteCompare(uint16 compare)
            ;
    uint16 Lip_ReadCompare(void) ;
#else
    void    Lip_WriteCompare1(uint16 compare)
            ;
    uint16 Lip_ReadCompare1(void) ;
    void    Lip_WriteCompare2(uint16 compare)
            ;
    uint16 Lip_ReadCompare2(void) ;
#endif /* (Lip_UseOneCompareMode) */


#if (Lip_DeadBandUsed)
    void    Lip_WriteDeadTime(uint8 deadtime) ;
    uint8   Lip_ReadDeadTime(void) ;
#endif /* (Lip_DeadBandUsed) */

#if ( Lip_KillModeMinTime)
    void Lip_WriteKillTime(uint8 killtime) ;
    uint8 Lip_ReadKillTime(void) ;
#endif /* ( Lip_KillModeMinTime) */

void Lip_Init(void) ;
void Lip_Enable(void) ;
void Lip_Sleep(void) ;
void Lip_Wakeup(void) ;
void Lip_SaveConfig(void) ;
void Lip_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define Lip_INIT_PERIOD_VALUE          (60000u)
#define Lip_INIT_COMPARE_VALUE1        (0u)
#define Lip_INIT_COMPARE_VALUE2        (0u)
#define Lip_INIT_INTERRUPTS_MODE       (uint8)(((uint8)(0u <<   \
                                                    Lip_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lip_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lip_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                    (uint8)((uint8)(0u <<  \
                                                    Lip_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define Lip_DEFAULT_COMPARE2_MODE      (uint8)((uint8)1u <<  Lip_CTRL_CMPMODE2_SHIFT)
#define Lip_DEFAULT_COMPARE1_MODE      (uint8)((uint8)1u <<  Lip_CTRL_CMPMODE1_SHIFT)
#define Lip_INIT_DEAD_TIME             (1u)


/********************************
*         Registers
******************************** */

#if (Lip_UsingFixedFunction)
   #define Lip_PERIOD_LSB              (*(reg16 *) Lip_PWMHW__PER0)
   #define Lip_PERIOD_LSB_PTR          ( (reg16 *) Lip_PWMHW__PER0)
   #define Lip_COMPARE1_LSB            (*(reg16 *) Lip_PWMHW__CNT_CMP0)
   #define Lip_COMPARE1_LSB_PTR        ( (reg16 *) Lip_PWMHW__CNT_CMP0)
   #define Lip_COMPARE2_LSB            (0x00u)
   #define Lip_COMPARE2_LSB_PTR        (0x00u)
   #define Lip_COUNTER_LSB             (*(reg16 *) Lip_PWMHW__CNT_CMP0)
   #define Lip_COUNTER_LSB_PTR         ( (reg16 *) Lip_PWMHW__CNT_CMP0)
   #define Lip_CAPTURE_LSB             (*(reg16 *) Lip_PWMHW__CAP0)
   #define Lip_CAPTURE_LSB_PTR         ( (reg16 *) Lip_PWMHW__CAP0)
   #define Lip_RT1                     (*(reg8 *)  Lip_PWMHW__RT1)
   #define Lip_RT1_PTR                 ( (reg8 *)  Lip_PWMHW__RT1)

#else
   #if (Lip_Resolution == 8u) /* 8bit - PWM */

       #if(Lip_PWMModeIsCenterAligned)
           #define Lip_PERIOD_LSB      (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
           #define Lip_PERIOD_LSB_PTR  ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #else
           #define Lip_PERIOD_LSB      (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__F0_REG)
           #define Lip_PERIOD_LSB_PTR  ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__F0_REG)
       #endif /* (Lip_PWMModeIsCenterAligned) */

       #define Lip_COMPARE1_LSB        (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lip_COMPARE1_LSB_PTR    ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__D0_REG)
       #define Lip_COMPARE2_LSB        (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lip_COMPARE2_LSB_PTR    ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
       #define Lip_COUNTERCAP_LSB      (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lip_COUNTERCAP_LSB_PTR  ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__A1_REG)
       #define Lip_COUNTER_LSB         (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lip_COUNTER_LSB_PTR     ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__A0_REG)
       #define Lip_CAPTURE_LSB         (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__F1_REG)
       #define Lip_CAPTURE_LSB_PTR     ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__F1_REG)

   #else
        #if(CY_PSOC3) /* 8-bit address space */
            #if(Lip_PWMModeIsCenterAligned)
               #define Lip_PERIOD_LSB      (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
               #define Lip_PERIOD_LSB_PTR  ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #else
               #define Lip_PERIOD_LSB      (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__F0_REG)
               #define Lip_PERIOD_LSB_PTR  ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__F0_REG)
            #endif /* (Lip_PWMModeIsCenterAligned) */

            #define Lip_COMPARE1_LSB       (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lip_COMPARE1_LSB_PTR   ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__D0_REG)
            #define Lip_COMPARE2_LSB       (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lip_COMPARE2_LSB_PTR   ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__D1_REG)
            #define Lip_COUNTERCAP_LSB     (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lip_COUNTERCAP_LSB_PTR ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__A1_REG)
            #define Lip_COUNTER_LSB        (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lip_COUNTER_LSB_PTR    ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__A0_REG)
            #define Lip_CAPTURE_LSB        (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__F1_REG)
            #define Lip_CAPTURE_LSB_PTR    ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__F1_REG)
        #else
            #if(Lip_PWMModeIsCenterAligned)
               #define Lip_PERIOD_LSB      (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
               #define Lip_PERIOD_LSB_PTR  ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #else
               #define Lip_PERIOD_LSB      (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
               #define Lip_PERIOD_LSB_PTR  ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
            #endif /* (Lip_PWMModeIsCenterAligned) */

            #define Lip_COMPARE1_LSB       (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lip_COMPARE1_LSB_PTR   ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
            #define Lip_COMPARE2_LSB       (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lip_COMPARE2_LSB_PTR   ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
            #define Lip_COUNTERCAP_LSB     (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lip_COUNTERCAP_LSB_PTR ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
            #define Lip_COUNTER_LSB        (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lip_COUNTER_LSB_PTR    ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
            #define Lip_CAPTURE_LSB        (*(reg16 *) Lip_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
            #define Lip_CAPTURE_LSB_PTR    ((reg16 *)  Lip_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
        #endif /* (CY_PSOC3) */

       #define Lip_AUX_CONTROLDP1          (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define Lip_AUX_CONTROLDP1_PTR      ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (Lip_Resolution == 8) */

   #define Lip_COUNTERCAP_LSB_PTR_8BIT ( (reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__A1_REG)
   #define Lip_AUX_CONTROLDP0          (*(reg8 *)  Lip_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define Lip_AUX_CONTROLDP0_PTR      ((reg8 *)   Lip_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (Lip_UsingFixedFunction) */

#if(Lip_KillModeMinTime )
    #define Lip_KILLMODEMINTIME        (*(reg8 *)  Lip_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define Lip_KILLMODEMINTIME_PTR    ((reg8 *)   Lip_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (Lip_KillModeMinTime ) */

#if(Lip_DeadBandMode == Lip__B_PWM__DBM_256_CLOCKS)
    #define Lip_DEADBAND_COUNT         (*(reg8 *)  Lip_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lip_DEADBAND_COUNT_PTR     ((reg8 *)   Lip_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define Lip_DEADBAND_LSB_PTR       ((reg8 *)   Lip_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define Lip_DEADBAND_LSB           (*(reg8 *)  Lip_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(Lip_DeadBandMode == Lip__B_PWM__DBM_2_4_CLOCKS)
    
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (Lip_UsingFixedFunction)
        #define Lip_DEADBAND_COUNT         (*(reg8 *)  Lip_PWMHW__CFG0)
        #define Lip_DEADBAND_COUNT_PTR     ((reg8 *)   Lip_PWMHW__CFG0)
        #define Lip_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lip_DEADBAND_COUNT_SHIFT)

        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define Lip_DEADBAND_COUNT_SHIFT   (0x06u)
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define Lip_DEADBAND_COUNT         (*(reg8 *)  Lip_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lip_DEADBAND_COUNT_PTR     ((reg8 *)   Lip_PWMUDB_genblk7_dbctrlreg__CONTROL_REG)
        #define Lip_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << Lip_DEADBAND_COUNT_SHIFT)

        /* As defined by the verilog implementation of the Control Register */
        #define Lip_DEADBAND_COUNT_SHIFT   (0x00u)
    #endif /* (Lip_UsingFixedFunction) */
#endif /* (Lip_DeadBandMode == Lip__B_PWM__DBM_256_CLOCKS) */



#if (Lip_UsingFixedFunction)
    #define Lip_STATUS                 (*(reg8 *) Lip_PWMHW__SR0)
    #define Lip_STATUS_PTR             ((reg8 *) Lip_PWMHW__SR0)
    #define Lip_STATUS_MASK            (*(reg8 *) Lip_PWMHW__SR0)
    #define Lip_STATUS_MASK_PTR        ((reg8 *) Lip_PWMHW__SR0)
    #define Lip_CONTROL                (*(reg8 *) Lip_PWMHW__CFG0)
    #define Lip_CONTROL_PTR            ((reg8 *) Lip_PWMHW__CFG0)
    #define Lip_CONTROL2               (*(reg8 *) Lip_PWMHW__CFG1)
    #define Lip_CONTROL3               (*(reg8 *) Lip_PWMHW__CFG2)
    #define Lip_GLOBAL_ENABLE          (*(reg8 *) Lip_PWMHW__PM_ACT_CFG)
    #define Lip_GLOBAL_ENABLE_PTR      ( (reg8 *) Lip_PWMHW__PM_ACT_CFG)
    #define Lip_GLOBAL_STBY_ENABLE     (*(reg8 *) Lip_PWMHW__PM_STBY_CFG)
    #define Lip_GLOBAL_STBY_ENABLE_PTR ( (reg8 *) Lip_PWMHW__PM_STBY_CFG)


    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define Lip_BLOCK_EN_MASK          (Lip_PWMHW__PM_ACT_MSK)
    #define Lip_BLOCK_STBY_EN_MASK     (Lip_PWMHW__PM_STBY_MSK)
    
    /* Control Register definitions */
    #define Lip_CTRL_ENABLE_SHIFT      (0x00u)

    /* As defined by Register map as MODE_CFG bits in CFG2*/
    #define Lip_CTRL_CMPMODE1_SHIFT    (0x04u)

    /* As defined by Register map */
    #define Lip_CTRL_DEAD_TIME_SHIFT   (0x06u)  

    /* Fixed Function Block Only CFG register bit definitions */
    /*  Set to compare mode */
    #define Lip_CFG0_MODE              (0x02u)   

    /* Enable the block to run */
    #define Lip_CFG0_ENABLE            (0x01u)   
    
    /* As defined by Register map as DB bit in CFG0 */
    #define Lip_CFG0_DB                (0x20u)   

    /* Control Register Bit Masks */
    #define Lip_CTRL_ENABLE            (uint8)((uint8)0x01u << Lip_CTRL_ENABLE_SHIFT)
    #define Lip_CTRL_RESET             (uint8)((uint8)0x01u << Lip_CTRL_RESET_SHIFT)
    #define Lip_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lip_CTRL_CMPMODE2_SHIFT)
    #define Lip_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lip_CTRL_CMPMODE1_SHIFT)

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define Lip_CTRL2_IRQ_SEL_SHIFT    (0x00u)
    #define Lip_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << Lip_CTRL2_IRQ_SEL_SHIFT)

    /* Status Register Bit Locations */
    /* As defined by Register map as TC in SR0 */
    #define Lip_STATUS_TC_SHIFT        (0x07u)   
    
    /* As defined by the Register map as CAP_CMP in SR0 */
    #define Lip_STATUS_CMP1_SHIFT      (0x06u)   

    /* Status Register Interrupt Enable Bit Locations */
    #define Lip_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)
    #define Lip_STATUS_TC_INT_EN_MASK_SHIFT            (Lip_STATUS_TC_SHIFT - 4u)
    #define Lip_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)
    #define Lip_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lip_STATUS_CMP1_SHIFT - 4u)

    /* Status Register Bit Masks */
    #define Lip_STATUS_TC              (uint8)((uint8)0x01u << Lip_STATUS_TC_SHIFT)
    #define Lip_STATUS_CMP1            (uint8)((uint8)0x01u << Lip_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks */
    #define Lip_STATUS_TC_INT_EN_MASK              (uint8)((uint8)Lip_STATUS_TC >> 4u)
    #define Lip_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)Lip_STATUS_CMP1 >> 4u)

    /*RT1 Synch Constants */
    #define Lip_RT1_SHIFT             (0x04u)

    /* Sync TC and CMP bit masks */
    #define Lip_RT1_MASK              (uint8)((uint8)0x03u << Lip_RT1_SHIFT)
    #define Lip_SYNC                  (uint8)((uint8)0x03u << Lip_RT1_SHIFT)
    #define Lip_SYNCDSI_SHIFT         (0x00u)

    /* Sync all DSI inputs */
    #define Lip_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << Lip_SYNCDSI_SHIFT)

    /* Sync all DSI inputs */
    #define Lip_SYNCDSI_EN            (uint8)((uint8)0x0Fu << Lip_SYNCDSI_SHIFT)


#else
    #define Lip_STATUS                (*(reg8 *)   Lip_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lip_STATUS_PTR            ((reg8 *)    Lip_PWMUDB_genblk8_stsreg__STATUS_REG )
    #define Lip_STATUS_MASK           (*(reg8 *)   Lip_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lip_STATUS_MASK_PTR       ((reg8 *)    Lip_PWMUDB_genblk8_stsreg__MASK_REG)
    #define Lip_STATUS_AUX_CTRL       (*(reg8 *)   Lip_PWMUDB_genblk8_stsreg__STATUS_AUX_CTL_REG)
    #define Lip_CONTROL               (*(reg8 *)   Lip_PWMUDB_genblk1_ctrlreg__CONTROL_REG)
    #define Lip_CONTROL_PTR           ((reg8 *)    Lip_PWMUDB_genblk1_ctrlreg__CONTROL_REG)


    /***********************************
    *          Constants
    ***********************************/

    /* Control Register bit definitions */
    #define Lip_CTRL_ENABLE_SHIFT      (0x07u)
    #define Lip_CTRL_RESET_SHIFT       (0x06u)
    #define Lip_CTRL_CMPMODE2_SHIFT    (0x03u)
    #define Lip_CTRL_CMPMODE1_SHIFT    (0x00u)
    #define Lip_CTRL_DEAD_TIME_SHIFT   (0x00u)   /* No Shift Needed for UDB block */
    
    /* Control Register Bit Masks */
    #define Lip_CTRL_ENABLE            (uint8)((uint8)0x01u << Lip_CTRL_ENABLE_SHIFT)
    #define Lip_CTRL_RESET             (uint8)((uint8)0x01u << Lip_CTRL_RESET_SHIFT)
    #define Lip_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << Lip_CTRL_CMPMODE2_SHIFT)
    #define Lip_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << Lip_CTRL_CMPMODE1_SHIFT)

    /* Status Register Bit Locations */
    #define Lip_STATUS_KILL_SHIFT          (0x05u)
    #define Lip_STATUS_FIFONEMPTY_SHIFT    (0x04u)
    #define Lip_STATUS_FIFOFULL_SHIFT      (0x03u)
    #define Lip_STATUS_TC_SHIFT            (0x02u)
    #define Lip_STATUS_CMP2_SHIFT          (0x01u)
    #define Lip_STATUS_CMP1_SHIFT          (0x00u)

    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define Lip_STATUS_KILL_INT_EN_MASK_SHIFT          (Lip_STATUS_KILL_SHIFT)
    #define Lip_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    (Lip_STATUS_FIFONEMPTY_SHIFT)
    #define Lip_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      (Lip_STATUS_FIFOFULL_SHIFT)
    #define Lip_STATUS_TC_INT_EN_MASK_SHIFT            (Lip_STATUS_TC_SHIFT)
    #define Lip_STATUS_CMP2_INT_EN_MASK_SHIFT          (Lip_STATUS_CMP2_SHIFT)
    #define Lip_STATUS_CMP1_INT_EN_MASK_SHIFT          (Lip_STATUS_CMP1_SHIFT)

    /* Status Register Bit Masks */
    #define Lip_STATUS_KILL            (uint8)((uint8)0x00u << Lip_STATUS_KILL_SHIFT )
    #define Lip_STATUS_FIFOFULL        (uint8)((uint8)0x01u << Lip_STATUS_FIFOFULL_SHIFT)
    #define Lip_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << Lip_STATUS_FIFONEMPTY_SHIFT)
    #define Lip_STATUS_TC              (uint8)((uint8)0x01u << Lip_STATUS_TC_SHIFT)
    #define Lip_STATUS_CMP2            (uint8)((uint8)0x01u << Lip_STATUS_CMP2_SHIFT)
    #define Lip_STATUS_CMP1            (uint8)((uint8)0x01u << Lip_STATUS_CMP1_SHIFT)

    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define Lip_STATUS_KILL_INT_EN_MASK            (Lip_STATUS_KILL)
    #define Lip_STATUS_FIFOFULL_INT_EN_MASK        (Lip_STATUS_FIFOFULL)
    #define Lip_STATUS_FIFONEMPTY_INT_EN_MASK      (Lip_STATUS_FIFONEMPTY)
    #define Lip_STATUS_TC_INT_EN_MASK              (Lip_STATUS_TC)
    #define Lip_STATUS_CMP2_INT_EN_MASK            (Lip_STATUS_CMP2)
    #define Lip_STATUS_CMP1_INT_EN_MASK            (Lip_STATUS_CMP1)

    /* Datapath Auxillary Control Register bit definitions */
    #define Lip_AUX_CTRL_FIFO0_CLR         (0x01u)
    #define Lip_AUX_CTRL_FIFO1_CLR         (0x02u)
    #define Lip_AUX_CTRL_FIFO0_LVL         (0x04u)
    #define Lip_AUX_CTRL_FIFO1_LVL         (0x08u)
    #define Lip_STATUS_ACTL_INT_EN_MASK    (0x10u) /* As defined for the ACTL Register */
#endif /* Lip_UsingFixedFunction */

#endif  /* CY_PWM_Lip_H */


/* [] END OF FILE */
