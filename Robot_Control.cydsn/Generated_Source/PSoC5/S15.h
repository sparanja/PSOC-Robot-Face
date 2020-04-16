/*******************************************************************************
* File Name: S15.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_S15_H) /* Pins S15_H */
#define CY_PINS_S15_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S15_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S15__PORT == 15 && ((S15__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S15_Write(uint8 value);
void    S15_SetDriveMode(uint8 mode);
uint8   S15_ReadDataReg(void);
uint8   S15_Read(void);
void    S15_SetInterruptMode(uint16 position, uint16 mode);
uint8   S15_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S15_SetDriveMode() function.
     *  @{
     */
        #define S15_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S15_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S15_DM_RES_UP          PIN_DM_RES_UP
        #define S15_DM_RES_DWN         PIN_DM_RES_DWN
        #define S15_DM_OD_LO           PIN_DM_OD_LO
        #define S15_DM_OD_HI           PIN_DM_OD_HI
        #define S15_DM_STRONG          PIN_DM_STRONG
        #define S15_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S15_MASK               S15__MASK
#define S15_SHIFT              S15__SHIFT
#define S15_WIDTH              1u

/* Interrupt constants */
#if defined(S15__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S15_SetInterruptMode() function.
     *  @{
     */
        #define S15_INTR_NONE      (uint16)(0x0000u)
        #define S15_INTR_RISING    (uint16)(0x0001u)
        #define S15_INTR_FALLING   (uint16)(0x0002u)
        #define S15_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S15_INTR_MASK      (0x01u) 
#endif /* (S15__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S15_PS                     (* (reg8 *) S15__PS)
/* Data Register */
#define S15_DR                     (* (reg8 *) S15__DR)
/* Port Number */
#define S15_PRT_NUM                (* (reg8 *) S15__PRT) 
/* Connect to Analog Globals */                                                  
#define S15_AG                     (* (reg8 *) S15__AG)                       
/* Analog MUX bux enable */
#define S15_AMUX                   (* (reg8 *) S15__AMUX) 
/* Bidirectional Enable */                                                        
#define S15_BIE                    (* (reg8 *) S15__BIE)
/* Bit-mask for Aliased Register Access */
#define S15_BIT_MASK               (* (reg8 *) S15__BIT_MASK)
/* Bypass Enable */
#define S15_BYP                    (* (reg8 *) S15__BYP)
/* Port wide control signals */                                                   
#define S15_CTL                    (* (reg8 *) S15__CTL)
/* Drive Modes */
#define S15_DM0                    (* (reg8 *) S15__DM0) 
#define S15_DM1                    (* (reg8 *) S15__DM1)
#define S15_DM2                    (* (reg8 *) S15__DM2) 
/* Input Buffer Disable Override */
#define S15_INP_DIS                (* (reg8 *) S15__INP_DIS)
/* LCD Common or Segment Drive */
#define S15_LCD_COM_SEG            (* (reg8 *) S15__LCD_COM_SEG)
/* Enable Segment LCD */
#define S15_LCD_EN                 (* (reg8 *) S15__LCD_EN)
/* Slew Rate Control */
#define S15_SLW                    (* (reg8 *) S15__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S15_PRTDSI__CAPS_SEL       (* (reg8 *) S15__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S15_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S15__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S15_PRTDSI__OE_SEL0        (* (reg8 *) S15__PRTDSI__OE_SEL0) 
#define S15_PRTDSI__OE_SEL1        (* (reg8 *) S15__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S15_PRTDSI__OUT_SEL0       (* (reg8 *) S15__PRTDSI__OUT_SEL0) 
#define S15_PRTDSI__OUT_SEL1       (* (reg8 *) S15__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S15_PRTDSI__SYNC_OUT       (* (reg8 *) S15__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S15__SIO_CFG)
    #define S15_SIO_HYST_EN        (* (reg8 *) S15__SIO_HYST_EN)
    #define S15_SIO_REG_HIFREQ     (* (reg8 *) S15__SIO_REG_HIFREQ)
    #define S15_SIO_CFG            (* (reg8 *) S15__SIO_CFG)
    #define S15_SIO_DIFF           (* (reg8 *) S15__SIO_DIFF)
#endif /* (S15__SIO_CFG) */

/* Interrupt Registers */
#if defined(S15__INTSTAT)
    #define S15_INTSTAT            (* (reg8 *) S15__INTSTAT)
    #define S15_SNAP               (* (reg8 *) S15__SNAP)
    
	#define S15_0_INTTYPE_REG 		(* (reg8 *) S15__0__INTTYPE)
#endif /* (S15__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S15_H */


/* [] END OF FILE */
