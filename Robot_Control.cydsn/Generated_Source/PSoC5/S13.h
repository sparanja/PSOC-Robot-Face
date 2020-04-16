/*******************************************************************************
* File Name: S13.h  
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

#if !defined(CY_PINS_S13_H) /* Pins S13_H */
#define CY_PINS_S13_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S13_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S13__PORT == 15 && ((S13__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S13_Write(uint8 value);
void    S13_SetDriveMode(uint8 mode);
uint8   S13_ReadDataReg(void);
uint8   S13_Read(void);
void    S13_SetInterruptMode(uint16 position, uint16 mode);
uint8   S13_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S13_SetDriveMode() function.
     *  @{
     */
        #define S13_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S13_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S13_DM_RES_UP          PIN_DM_RES_UP
        #define S13_DM_RES_DWN         PIN_DM_RES_DWN
        #define S13_DM_OD_LO           PIN_DM_OD_LO
        #define S13_DM_OD_HI           PIN_DM_OD_HI
        #define S13_DM_STRONG          PIN_DM_STRONG
        #define S13_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S13_MASK               S13__MASK
#define S13_SHIFT              S13__SHIFT
#define S13_WIDTH              1u

/* Interrupt constants */
#if defined(S13__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S13_SetInterruptMode() function.
     *  @{
     */
        #define S13_INTR_NONE      (uint16)(0x0000u)
        #define S13_INTR_RISING    (uint16)(0x0001u)
        #define S13_INTR_FALLING   (uint16)(0x0002u)
        #define S13_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S13_INTR_MASK      (0x01u) 
#endif /* (S13__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S13_PS                     (* (reg8 *) S13__PS)
/* Data Register */
#define S13_DR                     (* (reg8 *) S13__DR)
/* Port Number */
#define S13_PRT_NUM                (* (reg8 *) S13__PRT) 
/* Connect to Analog Globals */                                                  
#define S13_AG                     (* (reg8 *) S13__AG)                       
/* Analog MUX bux enable */
#define S13_AMUX                   (* (reg8 *) S13__AMUX) 
/* Bidirectional Enable */                                                        
#define S13_BIE                    (* (reg8 *) S13__BIE)
/* Bit-mask for Aliased Register Access */
#define S13_BIT_MASK               (* (reg8 *) S13__BIT_MASK)
/* Bypass Enable */
#define S13_BYP                    (* (reg8 *) S13__BYP)
/* Port wide control signals */                                                   
#define S13_CTL                    (* (reg8 *) S13__CTL)
/* Drive Modes */
#define S13_DM0                    (* (reg8 *) S13__DM0) 
#define S13_DM1                    (* (reg8 *) S13__DM1)
#define S13_DM2                    (* (reg8 *) S13__DM2) 
/* Input Buffer Disable Override */
#define S13_INP_DIS                (* (reg8 *) S13__INP_DIS)
/* LCD Common or Segment Drive */
#define S13_LCD_COM_SEG            (* (reg8 *) S13__LCD_COM_SEG)
/* Enable Segment LCD */
#define S13_LCD_EN                 (* (reg8 *) S13__LCD_EN)
/* Slew Rate Control */
#define S13_SLW                    (* (reg8 *) S13__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S13_PRTDSI__CAPS_SEL       (* (reg8 *) S13__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S13_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S13__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S13_PRTDSI__OE_SEL0        (* (reg8 *) S13__PRTDSI__OE_SEL0) 
#define S13_PRTDSI__OE_SEL1        (* (reg8 *) S13__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S13_PRTDSI__OUT_SEL0       (* (reg8 *) S13__PRTDSI__OUT_SEL0) 
#define S13_PRTDSI__OUT_SEL1       (* (reg8 *) S13__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S13_PRTDSI__SYNC_OUT       (* (reg8 *) S13__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S13__SIO_CFG)
    #define S13_SIO_HYST_EN        (* (reg8 *) S13__SIO_HYST_EN)
    #define S13_SIO_REG_HIFREQ     (* (reg8 *) S13__SIO_REG_HIFREQ)
    #define S13_SIO_CFG            (* (reg8 *) S13__SIO_CFG)
    #define S13_SIO_DIFF           (* (reg8 *) S13__SIO_DIFF)
#endif /* (S13__SIO_CFG) */

/* Interrupt Registers */
#if defined(S13__INTSTAT)
    #define S13_INTSTAT            (* (reg8 *) S13__INTSTAT)
    #define S13_SNAP               (* (reg8 *) S13__SNAP)
    
	#define S13_0_INTTYPE_REG 		(* (reg8 *) S13__0__INTTYPE)
#endif /* (S13__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S13_H */


/* [] END OF FILE */
