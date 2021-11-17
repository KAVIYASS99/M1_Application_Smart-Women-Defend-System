/*Buzzer Definition*/
#ifndef _BUZ_H
#define _BUZ_H

#include	"includes.h"

#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1

#define	buzon()			BUZ_PORT |= _BV(BUZ_PIN)
#define	buzoff()		BUZ_PORT &= ~_BV(BUZ_PIN)

void beep		(int8u nbeep, int16u ontime);
void buzinit	(void);

#endif

/*Constant Definition*/
#ifndef _CONST_H
#define _CONST_H

#define OK					1
#define FAILED				0

#define INPUT_PORT			0x00
#define OUTPUT_PORT			0xFF
#define OUTPUT_PIN			1
#define INPUT_PIN			0

#define ENABLE				1
#define DISABLE				0

#define FALSE				0
#define TRUE				1

#define HIGH				1
#define LOW					0

#define DISP_DLY			1000


#define ALRT_DLY			250
#define IND_DLY				150

#define LM35_MUL_FACTOR		0.01			
#define STEP_SIZE			0.00488			
#define ULTRASONIC_CONST	0.01724

#endif

/*Delay definition*/
#ifndef DELAY_H
#define DELAY_H

#include "includes.h"
void dlyms(int16u dly);
void dlyus(int16u dly);

#endif

/*GPS Definition*/
#ifndef GPS_H
#define GPS_H

#include "includes.h"

void GPSInit	(void);
void GPSgetloc	(int8u *Lat, int8u *Lon);

#endif

/*GSM Definition*/
#ifndef GSM_H
#define GSM_H

#include "includes.h"

void 	GSMsndmsg		(const char *PhNum, const char *GSMMsg);
int8u 	GSMinit			(void);
int8u 	gsm_call_gen	(const char *PhNum);
void	GSMRxCall		(void);		
void	GSMDisCall		(void);	

#endif

/*Include Definition*/
/#ifndef INCLUDES_H
#define INCLUDES_H

#include 	<avr/io.h>
#include	<avr/interrupt.h>
#include 	<avr/pgmspace.h>
#include 	<avr/sleep.h>
#include 	<avr/eeprom.h>
#include	<util/delay.h>
#include 	<string.h>
#include	<math.h>

#include	"app.H"
#include 	"const.h"
#include	"types.h"
#include 	"dly.h"
#include	"buz.h"
#include	"led.h"
#include	"motor.h"
#include	"servo.h"
#include 	"lcd.h"
#include 	"uart.h"
#include	"gsm.h"
#include	"gps.h"
#include	"sms.h"
#include 	"adc.h"
#include 	"mkb.h"
#include	"relay.h"
//#include	"otp.h"
#include	"rfid.h"
#include	"pwm.h"
#include	"sleep.h"
#include	"vr.h"
#include	"HX711.h"
#include	"loadcell.h"
//#include	"ult.h"
#include	"mps20n40.h"
#include	"rf.h"
#include	"image_bmp.h"
#include	"font5x8.h"
#include	"graphics.h"
#include	"KS0108.h"
#include	"ts.h"
#include	"alcohol.h"
#include	"fire.h"
#include	"relay.h"
#include	"apr.h"
#include	"lm35.h"
#include	"sw.h"

#endif

/*LCD Definition*/
#ifndef LCD_H
#define LCD_H

#include "includes.h"

#define OUTPUT 		 0xFF
#define LCD_DOT		'.'
#define LCD_SPC		' '

void lcdwc			(int8u command);
void lcdwd			(char ch);
void lcdws			(char *s);
void lcdinit		(void);
void lcddinit		(void);
void lcdclrr		(int8u rowno);
void lcdclr			(void);
void lcdr1			(void);
void lcdr2			(void);
void itoa			(signed int n, char s[]);
void reverse		(char s[]);
void lcdwint		(int8u loc,signed int x);
void lcdwlng		(int8u loc,unsigned long x);
void ltoa			(unsigned long n, char s[]);
double atof			(char *s);
void lcdclrr		(int8u rowno);
void lcdscrolinit	(void);

#if defined FLOAT_T0_STRING > 0

void ftoa(float n, char *res, int afterpoint);
int intToStr(int x, char str[], int d);
void rever(char *str, int len);
#endif

#endif

/*LED Definition*/
#ifndef _LED_H
#define _LED_H

#include 	<avr/io.h>
#include	"types.h"

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100

#define	ledon()			LED_PORT |= _BV(LED_PIN)
#define	ledoff()		LED_PORT &= ~_BV(LED_PIN)

void blink		(int8u nblink, int8u ontime);
void ledinit	(void);

#endif

/* SMS Definition*/
#ifndef SMS_H
#define SMS_H

#include "includes.h"

void GPSinit	(void);
void sendloc	(const char *PNum, const char *GSMMsg);
void SendOTP	(const char *PNum,const char *GSMMsg);
void SendLinkLoc(const char *PhNum, const char *GSMMsg);

#endif

/*Types Definition*/
#ifndef	_TYPES_H
#define _TYPES_H

typedef unsigned 	char	int8u;
typedef signed 		char 	int8s;
typedef unsigned 	short 	int16u;
typedef unsigned 	long 	int32u;

#endif

/*UART Definition*/
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include "includes.h"

#define F_CPU		8000000

#define USART_BAUDRATE		9600
#define BAUD_PRESCALE		((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

void	 uartinit	(void);
void 	 putchar		(char ch);
int8u	 getchar	(void);
void 	 puts		(const char *s);
void	EnUARTInt	(void);
void	DisUARTInt	(void);
#endif

