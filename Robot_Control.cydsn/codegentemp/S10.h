/*******************************************************************************
* File Name: S10.h  
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

#if !defined(CY_PINS_S10_H) /* Pins S10_H */
#define CY_PINS_S10_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S10_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S10__PORT == 15 && ((S10__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S10_Write(uint8 value);
void    S10_SetDriveMode(uint8 mode);
uint8   S10_ReadDataReg(void);
uint8   S10_Read(void);
void    S10_SetInterruptMode(uint16 position, uint16 mode);
uint8   S10_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S10_SetDriveMode() function.
     *  @{
     */
        #define S10_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S10_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S10_DM_RES_UP          PIN_DM_RES_UP
        #define S10_DM_RES_DWN         PIN_DM_RES_DWN
        #define S10_DM_OD_LO           PIN_DM_OD_LO
        #define S10_DM_OD_HI           PIN_DM_OD_HI
        #define S10_DM_STRONG          PIN_DM_STRONG
        #define S10_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S10_MASK               S10__MASK
#define S10_SHIFT              S10__SHIFT
#define S10_WIDTH              1u

/* Interrupt constants */
#if defined(S10__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S10_SetInterruptMode() function.
     *  @{
     */
        #define S10_INTR_NONE      (uint16)(0x0000u)
        #define S10_INTR_RISING    (uint16)(0x0001u)
        #define S10_INTR_FALLING   (uint16)(0x0002u)
        #define S10_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S10_INTR_MASK      (0x01u) 
#endif /* (S10__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S10_PS                     (* (reg8 *) S10__PS)
/* Data Register */
#define S10_DR                     (* (reg8 *) S10__DR)
/* Port Number */
#define S10_PRT_NUM                (* (reg8 *) S10__PRT) 
/* Connect to Analog Globals */                                                  
#define S10_AG                     (* (reg8 *) S10__AG)                       
/* Analog MUX bux enable */
#define S10_AMUX                   (* (reg8 *) S10__AMUX) 
/* Bidirectional Enable */                                                        
#define S10_BIE                    (* (reg8 *) S10__BIE)
/* Bit-mask for Aliased Register Access */
#define S10_BIT_MASK               (* (reg8 *) S10__BIT_MASK)
/* Bypass Enable */
#define S10_BYP                    (* (reg8 *) S10__BYP)
/* Port wide control signals */                                                   
#define S10_CTL                    (* (reg8 *) S10__CTL)
/* Drive Modes */
#define S10_DM0                    (* (reg8 *) S10__DM0) 
#define S10_DM1                    (* (reg8 *) S10__DM1)
#define S10_DM2                    (* (reg8 *) S10__DM2) 
/* Input Buffer Disable Override */
#define S10_INP_DIS                (* (reg8 *) S10__INP_DIS)
/* LCD Common or Segment Drive */
#define S10_LCD_COM_SEG            (* (reg8 *) S10__LCD_COM_SEG)
/* Enable Segment LCD */
#define S10_LCD_EN                 (* (reg8 *) S10__LCD_EN)
/* Slew Rate Control */
#define S10_SLW                    (* (reg8 *) S10__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S10_PRTDSI__CAPS_SEL       (* (reg8 *) S10__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S10_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S10__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S10_PRTDSI__OE_SEL0        (* (reg8 *) S10__PRTDSI__OE_SEL0) 
#define S10_PRTDSI__OE_SEL1        (* (reg8 *) S10__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S10_PRTDSI__OUT_SEL0       (* (reg8 *) S10__PRTDSI__OUT_SEL0) 
#define S10_PRTDSI__OUT_SEL1       (* (reg8 *) S10__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S10_PRTDSI__SYNC_OUT       (* (reg8 *) S10__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S10__SIO_CFG)
    #define S10_SIO_HYST_EN        (* (reg8 *) S10__SIO_HYST_EN)
    #define S10_SIO_REG_HIFREQ     (* (reg8 *) S10__SIO_REG_HIFREQ)
    #define S10_SIO_CFG            (* (reg8 *) S10__SIO_CFG)
    #define S10_SIO_DIFF           (* (reg8 *) S10__SIO_DIFF)
#endif /* (S10__SIO_CFG) */

/* Interrupt Registers */
#if defined(S10__INTSTAT)
    #define S10_INTSTAT            (* (reg8 *) S10__INTSTAT)
    #define S10_SNAP               (* (reg8 *) S10__SNAP)
    
	#define S10_0_INTTYPE_REG 		(* (reg8 *) S10__0__INTTYPE)
#endif /* (S10__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S10_H */


/* [] END OF FILE */
