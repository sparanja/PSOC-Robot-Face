/*******************************************************************************
* File Name: S16.h  
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

#if !defined(CY_PINS_S16_H) /* Pins S16_H */
#define CY_PINS_S16_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S16_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S16__PORT == 15 && ((S16__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S16_Write(uint8 value);
void    S16_SetDriveMode(uint8 mode);
uint8   S16_ReadDataReg(void);
uint8   S16_Read(void);
void    S16_SetInterruptMode(uint16 position, uint16 mode);
uint8   S16_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S16_SetDriveMode() function.
     *  @{
     */
        #define S16_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S16_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S16_DM_RES_UP          PIN_DM_RES_UP
        #define S16_DM_RES_DWN         PIN_DM_RES_DWN
        #define S16_DM_OD_LO           PIN_DM_OD_LO
        #define S16_DM_OD_HI           PIN_DM_OD_HI
        #define S16_DM_STRONG          PIN_DM_STRONG
        #define S16_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S16_MASK               S16__MASK
#define S16_SHIFT              S16__SHIFT
#define S16_WIDTH              1u

/* Interrupt constants */
#if defined(S16__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S16_SetInterruptMode() function.
     *  @{
     */
        #define S16_INTR_NONE      (uint16)(0x0000u)
        #define S16_INTR_RISING    (uint16)(0x0001u)
        #define S16_INTR_FALLING   (uint16)(0x0002u)
        #define S16_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S16_INTR_MASK      (0x01u) 
#endif /* (S16__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S16_PS                     (* (reg8 *) S16__PS)
/* Data Register */
#define S16_DR                     (* (reg8 *) S16__DR)
/* Port Number */
#define S16_PRT_NUM                (* (reg8 *) S16__PRT) 
/* Connect to Analog Globals */                                                  
#define S16_AG                     (* (reg8 *) S16__AG)                       
/* Analog MUX bux enable */
#define S16_AMUX                   (* (reg8 *) S16__AMUX) 
/* Bidirectional Enable */                                                        
#define S16_BIE                    (* (reg8 *) S16__BIE)
/* Bit-mask for Aliased Register Access */
#define S16_BIT_MASK               (* (reg8 *) S16__BIT_MASK)
/* Bypass Enable */
#define S16_BYP                    (* (reg8 *) S16__BYP)
/* Port wide control signals */                                                   
#define S16_CTL                    (* (reg8 *) S16__CTL)
/* Drive Modes */
#define S16_DM0                    (* (reg8 *) S16__DM0) 
#define S16_DM1                    (* (reg8 *) S16__DM1)
#define S16_DM2                    (* (reg8 *) S16__DM2) 
/* Input Buffer Disable Override */
#define S16_INP_DIS                (* (reg8 *) S16__INP_DIS)
/* LCD Common or Segment Drive */
#define S16_LCD_COM_SEG            (* (reg8 *) S16__LCD_COM_SEG)
/* Enable Segment LCD */
#define S16_LCD_EN                 (* (reg8 *) S16__LCD_EN)
/* Slew Rate Control */
#define S16_SLW                    (* (reg8 *) S16__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S16_PRTDSI__CAPS_SEL       (* (reg8 *) S16__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S16_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S16__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S16_PRTDSI__OE_SEL0        (* (reg8 *) S16__PRTDSI__OE_SEL0) 
#define S16_PRTDSI__OE_SEL1        (* (reg8 *) S16__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S16_PRTDSI__OUT_SEL0       (* (reg8 *) S16__PRTDSI__OUT_SEL0) 
#define S16_PRTDSI__OUT_SEL1       (* (reg8 *) S16__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S16_PRTDSI__SYNC_OUT       (* (reg8 *) S16__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S16__SIO_CFG)
    #define S16_SIO_HYST_EN        (* (reg8 *) S16__SIO_HYST_EN)
    #define S16_SIO_REG_HIFREQ     (* (reg8 *) S16__SIO_REG_HIFREQ)
    #define S16_SIO_CFG            (* (reg8 *) S16__SIO_CFG)
    #define S16_SIO_DIFF           (* (reg8 *) S16__SIO_DIFF)
#endif /* (S16__SIO_CFG) */

/* Interrupt Registers */
#if defined(S16__INTSTAT)
    #define S16_INTSTAT            (* (reg8 *) S16__INTSTAT)
    #define S16_SNAP               (* (reg8 *) S16__SNAP)
    
	#define S16_0_INTTYPE_REG 		(* (reg8 *) S16__0__INTTYPE)
#endif /* (S16__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S16_H */


/* [] END OF FILE */
