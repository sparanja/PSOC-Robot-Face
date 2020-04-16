/*******************************************************************************
* File Name: S14.h  
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

#if !defined(CY_PINS_S14_H) /* Pins S14_H */
#define CY_PINS_S14_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S14_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S14__PORT == 15 && ((S14__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S14_Write(uint8 value);
void    S14_SetDriveMode(uint8 mode);
uint8   S14_ReadDataReg(void);
uint8   S14_Read(void);
void    S14_SetInterruptMode(uint16 position, uint16 mode);
uint8   S14_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S14_SetDriveMode() function.
     *  @{
     */
        #define S14_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S14_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S14_DM_RES_UP          PIN_DM_RES_UP
        #define S14_DM_RES_DWN         PIN_DM_RES_DWN
        #define S14_DM_OD_LO           PIN_DM_OD_LO
        #define S14_DM_OD_HI           PIN_DM_OD_HI
        #define S14_DM_STRONG          PIN_DM_STRONG
        #define S14_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S14_MASK               S14__MASK
#define S14_SHIFT              S14__SHIFT
#define S14_WIDTH              1u

/* Interrupt constants */
#if defined(S14__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S14_SetInterruptMode() function.
     *  @{
     */
        #define S14_INTR_NONE      (uint16)(0x0000u)
        #define S14_INTR_RISING    (uint16)(0x0001u)
        #define S14_INTR_FALLING   (uint16)(0x0002u)
        #define S14_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S14_INTR_MASK      (0x01u) 
#endif /* (S14__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S14_PS                     (* (reg8 *) S14__PS)
/* Data Register */
#define S14_DR                     (* (reg8 *) S14__DR)
/* Port Number */
#define S14_PRT_NUM                (* (reg8 *) S14__PRT) 
/* Connect to Analog Globals */                                                  
#define S14_AG                     (* (reg8 *) S14__AG)                       
/* Analog MUX bux enable */
#define S14_AMUX                   (* (reg8 *) S14__AMUX) 
/* Bidirectional Enable */                                                        
#define S14_BIE                    (* (reg8 *) S14__BIE)
/* Bit-mask for Aliased Register Access */
#define S14_BIT_MASK               (* (reg8 *) S14__BIT_MASK)
/* Bypass Enable */
#define S14_BYP                    (* (reg8 *) S14__BYP)
/* Port wide control signals */                                                   
#define S14_CTL                    (* (reg8 *) S14__CTL)
/* Drive Modes */
#define S14_DM0                    (* (reg8 *) S14__DM0) 
#define S14_DM1                    (* (reg8 *) S14__DM1)
#define S14_DM2                    (* (reg8 *) S14__DM2) 
/* Input Buffer Disable Override */
#define S14_INP_DIS                (* (reg8 *) S14__INP_DIS)
/* LCD Common or Segment Drive */
#define S14_LCD_COM_SEG            (* (reg8 *) S14__LCD_COM_SEG)
/* Enable Segment LCD */
#define S14_LCD_EN                 (* (reg8 *) S14__LCD_EN)
/* Slew Rate Control */
#define S14_SLW                    (* (reg8 *) S14__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S14_PRTDSI__CAPS_SEL       (* (reg8 *) S14__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S14_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S14__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S14_PRTDSI__OE_SEL0        (* (reg8 *) S14__PRTDSI__OE_SEL0) 
#define S14_PRTDSI__OE_SEL1        (* (reg8 *) S14__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S14_PRTDSI__OUT_SEL0       (* (reg8 *) S14__PRTDSI__OUT_SEL0) 
#define S14_PRTDSI__OUT_SEL1       (* (reg8 *) S14__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S14_PRTDSI__SYNC_OUT       (* (reg8 *) S14__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S14__SIO_CFG)
    #define S14_SIO_HYST_EN        (* (reg8 *) S14__SIO_HYST_EN)
    #define S14_SIO_REG_HIFREQ     (* (reg8 *) S14__SIO_REG_HIFREQ)
    #define S14_SIO_CFG            (* (reg8 *) S14__SIO_CFG)
    #define S14_SIO_DIFF           (* (reg8 *) S14__SIO_DIFF)
#endif /* (S14__SIO_CFG) */

/* Interrupt Registers */
#if defined(S14__INTSTAT)
    #define S14_INTSTAT            (* (reg8 *) S14__INTSTAT)
    #define S14_SNAP               (* (reg8 *) S14__SNAP)
    
	#define S14_0_INTTYPE_REG 		(* (reg8 *) S14__0__INTTYPE)
#endif /* (S14__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S14_H */


/* [] END OF FILE */
