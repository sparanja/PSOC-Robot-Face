/*******************************************************************************
* File Name: S17.h  
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

#if !defined(CY_PINS_S17_H) /* Pins S17_H */
#define CY_PINS_S17_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "S17_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 S17__PORT == 15 && ((S17__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    S17_Write(uint8 value);
void    S17_SetDriveMode(uint8 mode);
uint8   S17_ReadDataReg(void);
uint8   S17_Read(void);
void    S17_SetInterruptMode(uint16 position, uint16 mode);
uint8   S17_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the S17_SetDriveMode() function.
     *  @{
     */
        #define S17_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define S17_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define S17_DM_RES_UP          PIN_DM_RES_UP
        #define S17_DM_RES_DWN         PIN_DM_RES_DWN
        #define S17_DM_OD_LO           PIN_DM_OD_LO
        #define S17_DM_OD_HI           PIN_DM_OD_HI
        #define S17_DM_STRONG          PIN_DM_STRONG
        #define S17_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define S17_MASK               S17__MASK
#define S17_SHIFT              S17__SHIFT
#define S17_WIDTH              1u

/* Interrupt constants */
#if defined(S17__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in S17_SetInterruptMode() function.
     *  @{
     */
        #define S17_INTR_NONE      (uint16)(0x0000u)
        #define S17_INTR_RISING    (uint16)(0x0001u)
        #define S17_INTR_FALLING   (uint16)(0x0002u)
        #define S17_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define S17_INTR_MASK      (0x01u) 
#endif /* (S17__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define S17_PS                     (* (reg8 *) S17__PS)
/* Data Register */
#define S17_DR                     (* (reg8 *) S17__DR)
/* Port Number */
#define S17_PRT_NUM                (* (reg8 *) S17__PRT) 
/* Connect to Analog Globals */                                                  
#define S17_AG                     (* (reg8 *) S17__AG)                       
/* Analog MUX bux enable */
#define S17_AMUX                   (* (reg8 *) S17__AMUX) 
/* Bidirectional Enable */                                                        
#define S17_BIE                    (* (reg8 *) S17__BIE)
/* Bit-mask for Aliased Register Access */
#define S17_BIT_MASK               (* (reg8 *) S17__BIT_MASK)
/* Bypass Enable */
#define S17_BYP                    (* (reg8 *) S17__BYP)
/* Port wide control signals */                                                   
#define S17_CTL                    (* (reg8 *) S17__CTL)
/* Drive Modes */
#define S17_DM0                    (* (reg8 *) S17__DM0) 
#define S17_DM1                    (* (reg8 *) S17__DM1)
#define S17_DM2                    (* (reg8 *) S17__DM2) 
/* Input Buffer Disable Override */
#define S17_INP_DIS                (* (reg8 *) S17__INP_DIS)
/* LCD Common or Segment Drive */
#define S17_LCD_COM_SEG            (* (reg8 *) S17__LCD_COM_SEG)
/* Enable Segment LCD */
#define S17_LCD_EN                 (* (reg8 *) S17__LCD_EN)
/* Slew Rate Control */
#define S17_SLW                    (* (reg8 *) S17__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define S17_PRTDSI__CAPS_SEL       (* (reg8 *) S17__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define S17_PRTDSI__DBL_SYNC_IN    (* (reg8 *) S17__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define S17_PRTDSI__OE_SEL0        (* (reg8 *) S17__PRTDSI__OE_SEL0) 
#define S17_PRTDSI__OE_SEL1        (* (reg8 *) S17__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define S17_PRTDSI__OUT_SEL0       (* (reg8 *) S17__PRTDSI__OUT_SEL0) 
#define S17_PRTDSI__OUT_SEL1       (* (reg8 *) S17__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define S17_PRTDSI__SYNC_OUT       (* (reg8 *) S17__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(S17__SIO_CFG)
    #define S17_SIO_HYST_EN        (* (reg8 *) S17__SIO_HYST_EN)
    #define S17_SIO_REG_HIFREQ     (* (reg8 *) S17__SIO_REG_HIFREQ)
    #define S17_SIO_CFG            (* (reg8 *) S17__SIO_CFG)
    #define S17_SIO_DIFF           (* (reg8 *) S17__SIO_DIFF)
#endif /* (S17__SIO_CFG) */

/* Interrupt Registers */
#if defined(S17__INTSTAT)
    #define S17_INTSTAT            (* (reg8 *) S17__INTSTAT)
    #define S17_SNAP               (* (reg8 *) S17__SNAP)
    
	#define S17_0_INTTYPE_REG 		(* (reg8 *) S17__0__INTTYPE)
#endif /* (S17__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_S17_H */


/* [] END OF FILE */
