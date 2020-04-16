/*******************************************************************************
* File Name: S9.h  
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

#if !defined(CY_PINS_S9_H) /* Pins S9_H */
#define CY_PINS_S9_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S9_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S9__PORT == 15 && ((S9__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S9_Write(uint8 value);
void    S9_SetDriveMode(uint8 mode);
uint8   S9_ReadDataReg(void);
uint8   S9_Read(void);
void    S9_SetInterruptMode(uint16 position, uint16 mode);
uint8   S9_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S9_SetDriveMode() function.
     *  @{
     */
        #define S9_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S9_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S9_DM_RES_UP          PIN_DM_RES_UP
        #define S9_DM_RES_DWN         PIN_DM_RES_DWN
        #define S9_DM_OD_LO           PIN_DM_OD_LO
        #define S9_DM_OD_HI           PIN_DM_OD_HI
        #define S9_DM_STRONG          PIN_DM_STRONG
        #define S9_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S9_MASK               S9__MASK
#define S9_SHIFT              S9__SHIFT
#define S9_WIDTH              1u

/* Interrupt constants */
#if defined(S9__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S9_SetInterruptMode() function.
     *  @{
     */
        #define S9_INTR_NONE      (uint16)(0x0000u)
        #define S9_INTR_RISING    (uint16)(0x0001u)
        #define S9_INTR_FALLING   (uint16)(0x0002u)
        #define S9_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S9_INTR_MASK      (0x01u) 
#endif /* (S9__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S9_PS                     (* (reg8 *) S9__PS)
/* Data Register */
#define S9_DR                     (* (reg8 *) S9__DR)
/* Port Number */
#define S9_PRT_NUM                (* (reg8 *) S9__PRT) 
/* Connect to Analog Globals */                                                  
#define S9_AG                     (* (reg8 *) S9__AG)                       
/* Analog MUX bux enable */
#define S9_AMUX                   (* (reg8 *) S9__AMUX) 
/* Bidirectional Enable */                                                        
#define S9_BIE                    (* (reg8 *) S9__BIE)
/* Bit-mask for Aliased Register Access */
#define S9_BIT_MASK               (* (reg8 *) S9__BIT_MASK)
/* Bypass Enable */
#define S9_BYP                    (* (reg8 *) S9__BYP)
/* Port wide control signals */                                                   
#define S9_CTL                    (* (reg8 *) S9__CTL)
/* Drive Modes */
#define S9_DM0                    (* (reg8 *) S9__DM0) 
#define S9_DM1                    (* (reg8 *) S9__DM1)
#define S9_DM2                    (* (reg8 *) S9__DM2) 
/* Input Buffer Disable Override */
#define S9_INP_DIS                (* (reg8 *) S9__INP_DIS)
/* LCD Common or Segment Drive */
#define S9_LCD_COM_SEG            (* (reg8 *) S9__LCD_COM_SEG)
/* Enable Segment LCD */
#define S9_LCD_EN                 (* (reg8 *) S9__LCD_EN)
/* Slew Rate Control */
#define S9_SLW                    (* (reg8 *) S9__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S9_PRTDSI__CAPS_SEL       (* (reg8 *) S9__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S9_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S9__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S9_PRTDSI__OE_SEL0        (* (reg8 *) S9__PRTDSI__OE_SEL0) 
#define S9_PRTDSI__OE_SEL1        (* (reg8 *) S9__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S9_PRTDSI__OUT_SEL0       (* (reg8 *) S9__PRTDSI__OUT_SEL0) 
#define S9_PRTDSI__OUT_SEL1       (* (reg8 *) S9__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S9_PRTDSI__SYNC_OUT       (* (reg8 *) S9__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S9__SIO_CFG)
    #define S9_SIO_HYST_EN        (* (reg8 *) S9__SIO_HYST_EN)
    #define S9_SIO_REG_HIFREQ     (* (reg8 *) S9__SIO_REG_HIFREQ)
    #define S9_SIO_CFG            (* (reg8 *) S9__SIO_CFG)
    #define S9_SIO_DIFF           (* (reg8 *) S9__SIO_DIFF)
#endif /* (S9__SIO_CFG) */

/* Interrupt Registers */
#if defined(S9__INTSTAT)
    #define S9_INTSTAT            (* (reg8 *) S9__INTSTAT)
    #define S9_SNAP               (* (reg8 *) S9__SNAP)
    
	#define S9_0_INTTYPE_REG 		(* (reg8 *) S9__0__INTTYPE)
#endif /* (S9__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S9_H */


/* [] END OF FILE */
