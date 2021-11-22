#ifndef MAIN_H
#define MAIN_H

#include "includes.h"

#define PPhNum				"YOUR_PH_NUMBER"
#define FPhNum				"YOUR_PH_NUMBER"

#define INTDDR				DDRD
#define INTPORT				PORTD
#define INT0_PIN			PD2

#define SHOCK_DDR           DDRD
#define SHOCK_PORT          PORTD
#define SHOCK_PIN           PD5

#define TIMER2_RELOAD		5       

#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)



#define ShockOn()			SHOCK_PORT |= _BV(SHOCK_PIN)
#define ShockOff()			SHOCK_PORT &= ~_BV(SHOCK_PIN)

static void	init		(void);
static void	disptitl 	(void);
static void	EXTINTinit	(void);
static void	Tmr2Init	(void) ;

#endif