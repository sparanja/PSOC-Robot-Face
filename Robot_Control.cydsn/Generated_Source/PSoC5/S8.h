/*******************************************************************************
* File Name: S8.h  
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

#if !defined(CY_PINS_S8_H) /* Pins S8_H */
#define CY_PINS_S8_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S8_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S8__PORT == 15 && ((S8__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S8_Write(uint8 value);
void    S8_SetDriveMode(uint8 mode);
uint8   S8_ReadDataReg(void);
uint8   S8_Read(void);
void    S8_SetInterruptMode(uint16 position, uint16 mode);
uint8   S8_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S8_SetDriveMode() function.
     *  @{
     */
        #define S8_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S8_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S8_DM_RES_UP          PIN_DM_RES_UP
        #define S8_DM_RES_DWN         PIN_DM_RES_DWN
        #define S8_DM_OD_LO           PIN_DM_OD_LO
        #define S8_DM_OD_HI           PIN_DM_OD_HI
        #define S8_DM_STRONG          PIN_DM_STRONG
        #define S8_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S8_MASK               S8__MASK
#define S8_SHIFT              S8__SHIFT
#define S8_WIDTH              1u

/* Interrupt constants */
#if defined(S8__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S8_SetInterruptMode() function.
     *  @{
     */
        #define S8_INTR_NONE      (uint16)(0x0000u)
        #define S8_INTR_RISING    (uint16)(0x0001u)
        #define S8_INTR_FALLING   (uint16)(0x0002u)
        #define S8_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S8_INTR_MASK      (0x01u) 
#endif /* (S8__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S8_PS                     (* (reg8 *) S8__PS)
/* Data Register */
#define S8_DR                     (* (reg8 *) S8__DR)
/* Port Number */
#define S8_PRT_NUM                (* (reg8 *) S8__PRT) 
/* Connect to Analog Globals */                                                  
#define S8_AG                     (* (reg8 *) S8__AG)                       
/* Analog MUX bux enable */
#define S8_AMUX                   (* (reg8 *) S8__AMUX) 
/* Bidirectional Enable */                                                        
#define S8_BIE                    (* (reg8 *) S8__BIE)
/* Bit-mask for Aliased Register Access */
#define S8_BIT_MASK               (* (reg8 *) S8__BIT_MASK)
/* Bypass Enable */
#define S8_BYP                    (* (reg8 *) S8__BYP)
/* Port wide control signals */                                                   
#define S8_CTL                    (* (reg8 *) S8__CTL)
/* Drive Modes */
#define S8_DM0                    (* (reg8 *) S8__DM0) 
#define S8_DM1                    (* (reg8 *) S8__DM1)
#define S8_DM2                    (* (reg8 *) S8__DM2) 
/* Input Buffer Disable Override */
#define S8_INP_DIS                (* (reg8 *) S8__INP_DIS)
/* LCD Common or Segment Drive */
#define S8_LCD_COM_SEG            (* (reg8 *) S8__LCD_COM_SEG)
/* Enable Segment LCD */
#define S8_LCD_EN                 (* (reg8 *) S8__LCD_EN)
/* Slew Rate Control */
#define S8_SLW                    (* (reg8 *) S8__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S8_PRTDSI__CAPS_SEL       (* (reg8 *) S8__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S8_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S8__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S8_PRTDSI__OE_SEL0        (* (reg8 *) S8__PRTDSI__OE_SEL0) 
#define S8_PRTDSI__OE_SEL1        (* (reg8 *) S8__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S8_PRTDSI__OUT_SEL0       (* (reg8 *) S8__PRTDSI__OUT_SEL0) 
#define S8_PRTDSI__OUT_SEL1       (* (reg8 *) S8__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S8_PRTDSI__SYNC_OUT       (* (reg8 *) S8__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S8__SIO_CFG)
    #define S8_SIO_HYST_EN        (* (reg8 *) S8__SIO_HYST_EN)
    #define S8_SIO_REG_HIFREQ     (* (reg8 *) S8__SIO_REG_HIFREQ)
    #define S8_SIO_CFG            (* (reg8 *) S8__SIO_CFG)
    #define S8_SIO_DIFF           (* (reg8 *) S8__SIO_DIFF)
#endif /* (S8__SIO_CFG) */

/* Interrupt Registers */
#if defined(S8__INTSTAT)
    #define S8_INTSTAT            (* (reg8 *) S8__INTSTAT)
    #define S8_SNAP               (* (reg8 *) S8__SNAP)
    
	#define S8_0_INTTYPE_REG 		(* (reg8 *) S8__0__INTTYPE)
#endif /* (S8__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S8_H */


/* [] END OF FILE */
