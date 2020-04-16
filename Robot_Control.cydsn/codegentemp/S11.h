/*******************************************************************************
* File Name: S11.h  
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

#if !defined(CY_PINS_S11_H) /* Pins S11_H */
#define CY_PINS_S11_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S11_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S11__PORT == 15 && ((S11__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S11_Write(uint8 value);
void    S11_SetDriveMode(uint8 mode);
uint8   S11_ReadDataReg(void);
uint8   S11_Read(void);
void    S11_SetInterruptMode(uint16 position, uint16 mode);
uint8   S11_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S11_SetDriveMode() function.
     *  @{
     */
        #define S11_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S11_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S11_DM_RES_UP          PIN_DM_RES_UP
        #define S11_DM_RES_DWN         PIN_DM_RES_DWN
        #define S11_DM_OD_LO           PIN_DM_OD_LO
        #define S11_DM_OD_HI           PIN_DM_OD_HI
        #define S11_DM_STRONG          PIN_DM_STRONG
        #define S11_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S11_MASK               S11__MASK
#define S11_SHIFT              S11__SHIFT
#define S11_WIDTH              1u

/* Interrupt constants */
#if defined(S11__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S11_SetInterruptMode() function.
     *  @{
     */
        #define S11_INTR_NONE      (uint16)(0x0000u)
        #define S11_INTR_RISING    (uint16)(0x0001u)
        #define S11_INTR_FALLING   (uint16)(0x0002u)
        #define S11_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S11_INTR_MASK      (0x01u) 
#endif /* (S11__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S11_PS                     (* (reg8 *) S11__PS)
/* Data Register */
#define S11_DR                     (* (reg8 *) S11__DR)
/* Port Number */
#define S11_PRT_NUM                (* (reg8 *) S11__PRT) 
/* Connect to Analog Globals */                                                  
#define S11_AG                     (* (reg8 *) S11__AG)                       
/* Analog MUX bux enable */
#define S11_AMUX                   (* (reg8 *) S11__AMUX) 
/* Bidirectional Enable */                                                        
#define S11_BIE                    (* (reg8 *) S11__BIE)
/* Bit-mask for Aliased Register Access */
#define S11_BIT_MASK               (* (reg8 *) S11__BIT_MASK)
/* Bypass Enable */
#define S11_BYP                    (* (reg8 *) S11__BYP)
/* Port wide control signals */                                                   
#define S11_CTL                    (* (reg8 *) S11__CTL)
/* Drive Modes */
#define S11_DM0                    (* (reg8 *) S11__DM0) 
#define S11_DM1                    (* (reg8 *) S11__DM1)
#define S11_DM2                    (* (reg8 *) S11__DM2) 
/* Input Buffer Disable Override */
#define S11_INP_DIS                (* (reg8 *) S11__INP_DIS)
/* LCD Common or Segment Drive */
#define S11_LCD_COM_SEG            (* (reg8 *) S11__LCD_COM_SEG)
/* Enable Segment LCD */
#define S11_LCD_EN                 (* (reg8 *) S11__LCD_EN)
/* Slew Rate Control */
#define S11_SLW                    (* (reg8 *) S11__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S11_PRTDSI__CAPS_SEL       (* (reg8 *) S11__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S11_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S11__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S11_PRTDSI__OE_SEL0        (* (reg8 *) S11__PRTDSI__OE_SEL0) 
#define S11_PRTDSI__OE_SEL1        (* (reg8 *) S11__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S11_PRTDSI__OUT_SEL0       (* (reg8 *) S11__PRTDSI__OUT_SEL0) 
#define S11_PRTDSI__OUT_SEL1       (* (reg8 *) S11__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S11_PRTDSI__SYNC_OUT       (* (reg8 *) S11__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S11__SIO_CFG)
    #define S11_SIO_HYST_EN        (* (reg8 *) S11__SIO_HYST_EN)
    #define S11_SIO_REG_HIFREQ     (* (reg8 *) S11__SIO_REG_HIFREQ)
    #define S11_SIO_CFG            (* (reg8 *) S11__SIO_CFG)
    #define S11_SIO_DIFF           (* (reg8 *) S11__SIO_DIFF)
#endif /* (S11__SIO_CFG) */

/* Interrupt Registers */
#if defined(S11__INTSTAT)
    #define S11_INTSTAT            (* (reg8 *) S11__INTSTAT)
    #define S11_SNAP               (* (reg8 *) S11__SNAP)
    
	#define S11_0_INTTYPE_REG 		(* (reg8 *) S11__0__INTTYPE)
#endif /* (S11__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S11_H */


/* [] END OF FILE */
