/*******************************************************************************
* File Name: S1.h  
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

#if !defined(CY_PINS_S1_H) /* Pins S1_H */
#define CY_PINS_S1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S1__PORT == 15 && ((S1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S1_Write(uint8 value);
void    S1_SetDriveMode(uint8 mode);
uint8   S1_ReadDataReg(void);
uint8   S1_Read(void);
void    S1_SetInterruptMode(uint16 position, uint16 mode);
uint8   S1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S1_SetDriveMode() function.
     *  @{
     */
        #define S1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S1_DM_RES_UP          PIN_DM_RES_UP
        #define S1_DM_RES_DWN         PIN_DM_RES_DWN
        #define S1_DM_OD_LO           PIN_DM_OD_LO
        #define S1_DM_OD_HI           PIN_DM_OD_HI
        #define S1_DM_STRONG          PIN_DM_STRONG
        #define S1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S1_MASK               S1__MASK
#define S1_SHIFT              S1__SHIFT
#define S1_WIDTH              1u

/* Interrupt constants */
#if defined(S1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S1_SetInterruptMode() function.
     *  @{
     */
        #define S1_INTR_NONE      (uint16)(0x0000u)
        #define S1_INTR_RISING    (uint16)(0x0001u)
        #define S1_INTR_FALLING   (uint16)(0x0002u)
        #define S1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S1_INTR_MASK      (0x01u) 
#endif /* (S1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S1_PS                     (* (reg8 *) S1__PS)
/* Data Register */
#define S1_DR                     (* (reg8 *) S1__DR)
/* Port Number */
#define S1_PRT_NUM                (* (reg8 *) S1__PRT) 
/* Connect to Analog Globals */                                                  
#define S1_AG                     (* (reg8 *) S1__AG)                       
/* Analog MUX bux enable */
#define S1_AMUX                   (* (reg8 *) S1__AMUX) 
/* Bidirectional Enable */                                                        
#define S1_BIE                    (* (reg8 *) S1__BIE)
/* Bit-mask for Aliased Register Access */
#define S1_BIT_MASK               (* (reg8 *) S1__BIT_MASK)
/* Bypass Enable */
#define S1_BYP                    (* (reg8 *) S1__BYP)
/* Port wide control signals */                                                   
#define S1_CTL                    (* (reg8 *) S1__CTL)
/* Drive Modes */
#define S1_DM0                    (* (reg8 *) S1__DM0) 
#define S1_DM1                    (* (reg8 *) S1__DM1)
#define S1_DM2                    (* (reg8 *) S1__DM2) 
/* Input Buffer Disable Override */
#define S1_INP_DIS                (* (reg8 *) S1__INP_DIS)
/* LCD Common or Segment Drive */
#define S1_LCD_COM_SEG            (* (reg8 *) S1__LCD_COM_SEG)
/* Enable Segment LCD */
#define S1_LCD_EN                 (* (reg8 *) S1__LCD_EN)
/* Slew Rate Control */
#define S1_SLW                    (* (reg8 *) S1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S1_PRTDSI__CAPS_SEL       (* (reg8 *) S1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S1_PRTDSI__OE_SEL0        (* (reg8 *) S1__PRTDSI__OE_SEL0) 
#define S1_PRTDSI__OE_SEL1        (* (reg8 *) S1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S1_PRTDSI__OUT_SEL0       (* (reg8 *) S1__PRTDSI__OUT_SEL0) 
#define S1_PRTDSI__OUT_SEL1       (* (reg8 *) S1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S1_PRTDSI__SYNC_OUT       (* (reg8 *) S1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S1__SIO_CFG)
    #define S1_SIO_HYST_EN        (* (reg8 *) S1__SIO_HYST_EN)
    #define S1_SIO_REG_HIFREQ     (* (reg8 *) S1__SIO_REG_HIFREQ)
    #define S1_SIO_CFG            (* (reg8 *) S1__SIO_CFG)
    #define S1_SIO_DIFF           (* (reg8 *) S1__SIO_DIFF)
#endif /* (S1__SIO_CFG) */

/* Interrupt Registers */
#if defined(S1__INTSTAT)
    #define S1_INTSTAT            (* (reg8 *) S1__INTSTAT)
    #define S1_SNAP               (* (reg8 *) S1__SNAP)
    
	#define S1_0_INTTYPE_REG 		(* (reg8 *) S1__0__INTTYPE)
#endif /* (S1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S1_H */


/* [] END OF FILE */
