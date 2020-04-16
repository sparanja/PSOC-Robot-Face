/*******************************************************************************
* File Name: S5.h  
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

#if !defined(CY_PINS_S5_H) /* Pins S5_H */
#define CY_PINS_S5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S5_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S5__PORT == 15 && ((S5__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S5_Write(uint8 value);
void    S5_SetDriveMode(uint8 mode);
uint8   S5_ReadDataReg(void);
uint8   S5_Read(void);
void    S5_SetInterruptMode(uint16 position, uint16 mode);
uint8   S5_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S5_SetDriveMode() function.
     *  @{
     */
        #define S5_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S5_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S5_DM_RES_UP          PIN_DM_RES_UP
        #define S5_DM_RES_DWN         PIN_DM_RES_DWN
        #define S5_DM_OD_LO           PIN_DM_OD_LO
        #define S5_DM_OD_HI           PIN_DM_OD_HI
        #define S5_DM_STRONG          PIN_DM_STRONG
        #define S5_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S5_MASK               S5__MASK
#define S5_SHIFT              S5__SHIFT
#define S5_WIDTH              1u

/* Interrupt constants */
#if defined(S5__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S5_SetInterruptMode() function.
     *  @{
     */
        #define S5_INTR_NONE      (uint16)(0x0000u)
        #define S5_INTR_RISING    (uint16)(0x0001u)
        #define S5_INTR_FALLING   (uint16)(0x0002u)
        #define S5_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S5_INTR_MASK      (0x01u) 
#endif /* (S5__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S5_PS                     (* (reg8 *) S5__PS)
/* Data Register */
#define S5_DR                     (* (reg8 *) S5__DR)
/* Port Number */
#define S5_PRT_NUM                (* (reg8 *) S5__PRT) 
/* Connect to Analog Globals */                                                  
#define S5_AG                     (* (reg8 *) S5__AG)                       
/* Analog MUX bux enable */
#define S5_AMUX                   (* (reg8 *) S5__AMUX) 
/* Bidirectional Enable */                                                        
#define S5_BIE                    (* (reg8 *) S5__BIE)
/* Bit-mask for Aliased Register Access */
#define S5_BIT_MASK               (* (reg8 *) S5__BIT_MASK)
/* Bypass Enable */
#define S5_BYP                    (* (reg8 *) S5__BYP)
/* Port wide control signals */                                                   
#define S5_CTL                    (* (reg8 *) S5__CTL)
/* Drive Modes */
#define S5_DM0                    (* (reg8 *) S5__DM0) 
#define S5_DM1                    (* (reg8 *) S5__DM1)
#define S5_DM2                    (* (reg8 *) S5__DM2) 
/* Input Buffer Disable Override */
#define S5_INP_DIS                (* (reg8 *) S5__INP_DIS)
/* LCD Common or Segment Drive */
#define S5_LCD_COM_SEG            (* (reg8 *) S5__LCD_COM_SEG)
/* Enable Segment LCD */
#define S5_LCD_EN                 (* (reg8 *) S5__LCD_EN)
/* Slew Rate Control */
#define S5_SLW                    (* (reg8 *) S5__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S5_PRTDSI__CAPS_SEL       (* (reg8 *) S5__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S5_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S5__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S5_PRTDSI__OE_SEL0        (* (reg8 *) S5__PRTDSI__OE_SEL0) 
#define S5_PRTDSI__OE_SEL1        (* (reg8 *) S5__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S5_PRTDSI__OUT_SEL0       (* (reg8 *) S5__PRTDSI__OUT_SEL0) 
#define S5_PRTDSI__OUT_SEL1       (* (reg8 *) S5__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S5_PRTDSI__SYNC_OUT       (* (reg8 *) S5__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S5__SIO_CFG)
    #define S5_SIO_HYST_EN        (* (reg8 *) S5__SIO_HYST_EN)
    #define S5_SIO_REG_HIFREQ     (* (reg8 *) S5__SIO_REG_HIFREQ)
    #define S5_SIO_CFG            (* (reg8 *) S5__SIO_CFG)
    #define S5_SIO_DIFF           (* (reg8 *) S5__SIO_DIFF)
#endif /* (S5__SIO_CFG) */

/* Interrupt Registers */
#if defined(S5__INTSTAT)
    #define S5_INTSTAT            (* (reg8 *) S5__INTSTAT)
    #define S5_SNAP               (* (reg8 *) S5__SNAP)
    
	#define S5_0_INTTYPE_REG 		(* (reg8 *) S5__0__INTTYPE)
#endif /* (S5__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S5_H */


/* [] END OF FILE */
