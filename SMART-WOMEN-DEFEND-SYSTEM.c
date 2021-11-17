#ifndef _BUZ_H
#define _BUZ_H
#ifndef _CONST_H
#define _CONST_H
#ifndef DELAY_H
#define DELAY_H
#ifndef GPS_H
#define GPS_H
#ifndef GSM_H
#define GSM_H
#ifndef INCLUDES_H
#define INCLUDES_H
#ifndef LCD_H
#define LCD_H
#ifndef _LED_H
#define _LED_H
#ifndef SMS_H
#define SMS_H
#ifndef	_TYPES_H
#define _TYPES_H
#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H
#define EEPROM_DISPLAY		0
#ifndef MAIN_H
#define MAIN_H


typedef unsigned 	char	int8u;
typedef signed 		char 	int8s;
typedef unsigned 	short 	int16u;
typedef unsigned 	long 	int32u;


#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1

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

#define LM35_MUL_FACTOR		0.01			/* 10mv/degree */
#define STEP_SIZE			0.00488			/* 5v / 1024 */
#define ULTRASONIC_CONST	0.01724

#define	buzon()			BUZ_PORT |= _BV(BUZ_PIN)
#define	buzoff()		BUZ_PORT &= ~_BV(BUZ_PIN)

#define OUTPUT 		 0xFF

#define LCD_DOT		'.'
#define LCD_SPC		' '

#define	LED_DDR			DDRC
#define	LED_PORT		PORTC
#define	LED_PIN			PC0

#define OFF_TIME		100
#define OFF_TIME		100

#define	ledon()			LED_PORT |= _BV(LED_PIN)
#define	ledoff()		LED_PORT &= ~_BV(LED_PIN)

#define F_CPU		8000000

#define USART_BAUDRATE		9600
#define BAUD_PRESCALE		((F_CPU / (USART_BAUDRATE * 16UL)) - 1)

#define MSG_START					""
#define MSG_END						". Automated SMS By: WSS."

#define REF_VOL_256

#define GSM_GPS_DDR				DDRD
#define GSM_GPS_PORT			PORTD
#define GSM_GPS_PIN				PD7

#define GSMEn()				do {									\
								GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN); 	\
								dlyms(500);						\
							} while(0)

#define GPSEn()				do {									\
								GSM_GPS_PORT |= _BV(GSM_GPS_PIN);		\
								dlyms(500);						\
							} while(0)
							

#define PPhNum				"YOUR_PH_NUMBER"
#define FPhNum				"YOUR_PH_NUMBER"

#define INTDDR				DDRD
#define INTPORT				PORTD
#define INT0_PIN			PD2

#define SPRINK_DDR			DDRD
#define SPRINK_PORT			PORTD
#define SPRINK_PIN			PD6
#define SHOCK_PIN			PD5

#define TIMER2_RELOAD		5       
#define SPRINK_TIME			1000

#define StartTmr()			TCCR0  	|= _BV(CS01)
#define StopTmr()			TCCR0  	&= ~_BV(CS01)

#define SprinkleOn()		SPRINK_PORT |= _BV(SPRINK_PIN)
#define SprinkleOff()		SPRINK_PORT &= ~_BV(SPRINK_PIN)

#define ShockOn()			SPRINK_PORT |= _BV(SHOCK_PIN)
#define ShockOff()			SPRINK_PORT &= ~_BV(SHOCK_PIN)

#include "includes.h"
#include "dly.h"
#include "buz.h"
#include"gps.h"
#include "gsm.h"
#include "LCD.h"
#include "led.h"
#include "sms.h"
#include"uart.h"
#include 	<avr/io.h>
#include	"types.h"
#include "main.h"

#include 	<avr/io.h>
#include	<avr/interrupt.h>
#include 	<avr/pgmspace.h>
#include 	<avr/sleep.h>
#include 	<avr/eeprom.h>
#include	<util/delay.h>
#include 	<string.h>
#include	<math.h>

#include	"app.h"
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

#include	"rfid.h"
#include	"pwm.h"
#include	"sleep.h"
#include	"vr.h"
#include	"HX711.h"
#include	"loadcell.h"

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


void beep		(int8u nbeep, int16u ontime);
void buzinit	(void);
void dlyms(int16u dly);
void dlyus(int16u dly);
void GPSInit	(void);
void GPSgetloc	(int8u *Lat, int8u *Lon);
void blink		(int8u nblink, int8u ontime);
void ledinit	(void);
void GPSinit	(void);
void sendloc	(const char *PNum, const char *GSMMsg);
void SendOTP	(const char *PNum,const char *GSMMsg);
void SendLinkLoc(const char *PhNum, const char *GSMMsg);
void	 uartinit	(void);
void 	 putchar		(char ch);
int8u	 getchar	(void);
void 	 puts		(const char *s);
void	EnUARTInt	(void);
void	DisUARTInt	(void);


extern int16u BeepOffDly;
extern int8u OTP[5];

const char *Msg =  "I'm in Trouble & Located @";

int8u lcdptr;
const char ATCommand[] 	 = "AT\r"; 
const char ATCall[]  	 = "ATD";
const char SMSCode[]  	 = "AT+CMGF=1\r";
const char SMSNumber[] 	 = "AT+CMGS=\"0";
const char SMSSettings[]  = "AT+CNMI=2,2,2,0,0\r";
const char ATRxCall[]	  = "ATA\r";
const char ATDisCall[]	  = "ATH\r";

static void GSMerr		(void);
static int8u GSMmsgparam(void);
static int8u GSMRxResp	(void);
static int8u GSMsndphnum(const char *PhNum);
static void GSMrxack	(void);
static void  LCDEnable		(void);
static void  LCDReset		(void);
static void  LCDWriteByte	(char  ch);
void 	GSMsndmsg		(const char *PhNum, const char *GSMMsg);
int8u 	GSMinit			(void);
int8u 	gsm_call_gen	(const char *PhNum);
void	GSMRxCall		(void);		
void	GSMDisCall		(void);	

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

static void	init		(void);
static void	disptitl 	(void);
static void	EXTINTinit	(void);
static void	Tmr2Init	(void) ;

int main(void) {
	init();
	while (TRUE) {
		if (AppFlags.Sw) {
			buzon();
			ShockOn();
			SprinkleOn();
			dlyms(SPRINK_TIME);
			SprinkleOff();
			SendLinkLoc(FPhNum,Msg);
			SendLinkLoc(PPhNum,Msg);
			ShockOff();
			buzoff();
			AppFlags.Sw = FALSE;
			sleep_enable();
			sleep_cpu();
		}
		sleep_cpu();
	}
	return 0;
}
static void init(void) {
	buzinit();
	ledinit();
	beep(2,100);
	SPRINK_DDR		|= _BV(SPRINK_PIN) | _BV(SHOCK_PIN);
	SPRINK_PORT		&= ~(_BV(SPRINK_PIN) | _BV(SHOCK_PIN));
	lcdinit();
	uartinit();
	EXTINTinit();
	GPSInit();
	GSMEn();
	GSMinit();
	Tmr2Init();
	sei();
	AppFlags.Sw		= FALSE;
	disptitl();
	beep(1,100);
	sleep_enable();	
	sleep_cpu();
}
static void EXTINTinit(void) {
	INTDDR 	&= ~_BV(INT0_PIN);
	INTPORT |= _BV(INT0_PIN);
	GICR	|= _BV(INT0);						//ENABLE EXTERNAL INTERRUPT
}
static void disptitl(void) {
	lcdclr();
	lcdws("Women Secu'y S/M");
}
static void Tmr2Init(void) {
	TCNT2	= TIMER2_RELOAD;
	TIMSK	|= _BV(TOIE2);							/* ENABLE OVERFLOW INTERRUPT */
	TCCR2	|=  _BV(CS22) | _BV(CS21) | _BV(CS20); /* PRESCALAR BY 1024 */
}
/* overflows at every 100msec */
ISR(TIMER2_OVF_vect) { 
	static int8u i;
	TCNT2 = TIMER2_RELOAD;
	if (++i >= 200) i = 0;
	switch(i) {
		case 0: case 5: ledon(); break;
		case 1: case 6: ledoff(); break;
	}  
}
ISR(INT0_vect) { 
	sleep_disable();
	AppFlags.Sw = TRUE;
	GICR |= _BV(INT0);
}

struct  {
	volatile int8u Sw:1;
}AppFlags;
void dlyms(int16u dly) {
	while (dly--)
		_delay_ms(1);
}

void dlyus(int16u dly) {
	while (dly--)
		_delay_us(1);
}
void buzinit(void) {
	BUZ_DDR		|= _BV(BUZ_PIN);
	BUZ_PORT 	&= ~_BV(BUZ_PIN);
}

void beep(int8u nbeep, int16u ontime) {
	while(nbeep--)	{
		buzon();
		dlyms(ontime);
		buzoff();
		dlyms(100/*BeepOffDly*/);
	}
}
void GPSInit(void)
{
	GSM_GPS_DDR |= _BV(GSM_GPS_PIN);
	GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN);
}
void GPSgetloc(int8u *Lat, int8u *Lon)
{
	int8u i;
ReadAgain:
	while(getchar() != '$');
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'P')
 		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'G')
		goto ReadAgain;
	if(getchar() != 'A')
		goto ReadAgain;
	while(getchar() != ',');
	while(getchar() != ',');
	for(i = 0; i < 9; i++)
		*Lat++ = getchar();
	while(getchar() != 'N');
	while(getchar() != ',');
	for(i = 0; i < 10; i++)
		*Lon++ = getchar();
}
void GSMsndmsg(const char *PhNum, const char *GSMMsg)
{
	lcdclrr(1);
	
	lcdws("Sending SMS:");
	if(GSMsndphnum(PhNum)) {
		puts(MSG_START);
		puts(GSMMsg);
		puts(MSG_END);
		putchar(0x1A);
		GSMrxack();
	} else	GSMerr();
	lcdws("OK");
	GSMRxResp();
	dlyms(1000);
	lcdclrr(1);
}
int8u GSMinit(void)
{
	lcdclrr(1);
	lcdws("GSM: ");
	if(GSMRxResp() && GSMmsgparam() ) {
		lcdws("OK");
		dlyms(1000);
		return 1;
	} else {
		GSMerr();
		return 0;
  } 
}
static void GSMerr(void)
{
	 lcdclrr(1);
	 lcdws("FAILED !"); 
}
static int8u GSMRxResp(void)
{
	puts(ATCommand);
	while(getchar() != 'K');
	return 1;
}
static int8u GSMmsgparam(void)
{
	puts(SMSCode);
  while(getchar() != 'K');
	puts(SMSSettings);
  while(getchar() != 'K');
	return 1;
}
static int8u GSMsndphnum(const char *PhNum)
{
	puts(SMSNumber);
	puts(PhNum);
	puts("\"\r");
	while (getchar() != '>');
	return 1;
}
static void GSMrxack(void)
{
	int8u x;
	do {
	 	x = getchar();
	 }while(x != 'K' && x != 'E');
	 if(x == 'E') if(! GSMRxResp() ) GSMerr();
}
int8u gsm_call_gen(const char *PhNum)
{
	puts(ATCall);
	puts(PhNum);
	puts(";\r");
	return 1;
}
void GSMRxCall(void)
{
	puts(ATRxCall);
}
void GSMDisCall(void)
{
	puts(ATDisCall);
}
static void  LCDEnable(void)
{
    LCD_DATA_PORT &= ~ (_BV(LCD_ENABLE_PIN)); 
    dlyus(1);
    LCD_DATA_PORT |=  _BV(LCD_ENABLE_PIN);  
}

void lcdwc(int8u x)
{
    LCD_DATA_PORT &= ~ (_BV(LCD_REGISTER_SELECT_PIN)); 
    LCDWriteByte(x);
}

void lcdwd(char ch)
{
    LCD_DATA_PORT |=  _BV(LCD_REGISTER_SELECT_PIN);
    LCDWriteByte(ch);
}

void lcdws(char *s){
	while (*s) {
			#ifdef LCD_20X4
		switch(lcdptr) {
			case 0x80+20:
				lcdptr = 0xC0;
				break;
			case 0xC0+20:
				lcdptr = 0x94;
				break;
			case 0x94+20:
				lcdptr = 0xD4;
				break;
			case 0xD4+20:
				lcdptr = 0x80;
				break;
		}
		#else
			switch(lcdptr) {
				case 0x80+16:
				lcdptr = 0xC0;
				break;
				case 0xC0+16:
				lcdptr = 0x80;
				break;
			}
		#endif
		lcdwc(lcdptr++);
		lcdwd(*s++);
	}
}

void lcdinit(void)
{
    LCD_DDR = (LCD_DDR & 0x03) | 0xfc;
	LCD_DATA_PORT    &=  0x03;

	dlyms(40);
	LCDReset();
    lcdwc(0x28);
    lcdwc(0x0C);
    lcdwc(0x06);
    lcdwc(0x01); 
	lcdclr();
	#if DISPLAY_INIT > 0
		lcddinit();
	#endif
}
static void LCDReset(void)
{
	lcdwc(0x33);
	dlyms(5);
	lcdwc(0x33);
	dlyus(500);
	lcdwc(0x32);
	dlyus(500);
}
void lcdscrolinit(void)
{
	lcdwc(0x01);
	lcdwc(0x20);
	lcdwc(0x07);
	lcdwc(0x8f);
}
void lcddinit(void)
{
	int8u i, j, adr;
	
	lcdws("  INITIALIZING");
	lcdr2();
	for ( j = 0; j < LCD_NSCRL; j++ ) {
		adr = 0xc0;						// 2nd row, first coloumn
		for ( i = 0; i < 16; i++ ) {
			lcdwc(adr);			
			lcdwd(LCD_DOT);				
			if ( i < 8 ) dlyms(200+(50*i)); else dlyms(25);
			lcdwc(adr);			
			lcdwd(LCD_SPC);			
			adr++;					// increment display aadress
		}
	} 
}

static void  LCDWriteByte(char  LCDData)
{
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|(LCDData & 0xF0);
    LCDEnable();
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F)|((LCDData << 4) & 0xF0);
    LCDEnable();
    dlyus(750);
}
void lcdclr(void)
{
	lcdwc(0x01);
	lcdptr = 0x80;	  /* Clear display LCD */
}
void lcdclrr(int8u rowno){
	int8u i;
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
	for (i = 0; i < 16; i++)
		lcdwd(LCD_SPC);
	switch (rowno) {
		case 0:
				lcdr1();
				break;
		case 1:
				lcdr2();
				break;
	}
 }
 void lcdr1(void)
 {
	lcdwc(0x80); 	  /* Begin at Line 1 */
	lcdptr = 0x80;
 }
  void lcdr2(void)
 {
	lcdwc(0xc0); 	  /* Begin at Line 1 */
	lcdptr = 0xc0;
 }
 void lcdwint(int8u loc,signed int x)
 {
	 int8u str[10];
	 lcdptr = loc;
	 lcdws("   ");
	 lcdptr = loc;
	 itoa(x, str);
	 lcdws(str);
 }
 void lcdwlng(int8u loc,unsigned long x)
 {
	 int8u str[24];
	 lcdptr = loc;
	 lcdws("           ");
	 lcdptr = loc;
	 ltoa(x, str);
	 lcdws(str);
}

void ltoa(unsigned long n, char s[])
{
	int i;
	
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	s[i] = '\0';
	reverse(s);
}
 void itoa(signed int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

#if FLOAT_T0_STRING > 0

// reverses a string 'str' of length 'len'
void rever(char *str, int len)
{
	int i=0, j=len-1, temp;
	while (i<j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++; j--;
	}
}

// Converts a given integer x to string str[].  d is the number
// of digits required in output. If d is more than the number
// of digits in x, then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	rever(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating point number to string.
void ftoa(float n, char *res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0)
	{
		res[i] = '.';  // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter is needed
		// to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}


#endif
/* atof: convert string s to double ; pointer version */
double atof(char *s)
{
	double val,power;
	int sign;
	
	for(; isspace(*s); s++);	/* skip white spaces */
	sign = (*s == '-')? -1:1;
	if (*s == '+' || *s == '-')
		s++;
	for (val = 0.0; isdigit(*s); s++)
		val = 10.0 * val + (*s - '0');
	if (*s == '.')
		s++;
	for (power = 1.0; isdigit(*s); s++) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
	}
	return (float)(sign * val) / power;
}

	 
void reverse(char s[])
{
	int c,i,j;
	for (i = 0, j = strlen(s)-1; i < j; i++,j--) 
		c = s[i], s[i] = s[j], s[j] = c;
} 
void ledinit(void)
{
	LED_DDR 		|= _BV(LED_PIN);
	LED_PORT 		&= ~_BV(LED_PIN);
}

void blink(int8u nblink, int8u ontime)
{
	while(nblink--){
		ledon();
		dlyms(ontime);
		ledoff();
		dlyms(100);
	}
}
void SendOTP(const char *PNum,const char *GSMMsg)
{
	int8u gsmmsg[150];
	gsmmsg[0] = '\0';
	
	genOTP(OTP);
	strcat(gsmmsg,GSMMsg);
	strcat(gsmmsg,OTP);
	
	GSMEn();
	GSMsndmsg(PNum, gsmmsg);
}

void sendloc(const char *PhNum, const char *GSMMsg)
{
	int8u i;
	int8u lat[11];
	int8u lon[11];
	int8u gsmmsg[150];

	gsmmsg[0] = '\0';

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';

	GPSEn();
	GPSgetloc(lat,lon);

	strcat(gsmmsg,GSMMsg);
	strcat(gsmmsg," LAT:");
	strcat(gsmmsg,lat);
	strcat(gsmmsg," & LON: ");
	strcat(gsmmsg,lon);

	GSMEn();
	GSMsndmsg(PhNum, gsmmsg);
}

void SendLinkLoc(const char *PhNum, const char *GSMMsg)
{
	int8u i;
	int8u lat[11];
	int8u lon[11];
	int8u gsmmsg[150];
	int8u latl[3];
	int8u latu[10];	
	int8u lonl[4];
	int8u lonu[9];
	
	float latdec;
	float londec;

	gsmmsg[0] = '\0';

	for (i = 0; i < 10; i++)
		lat[i] = lon[i] = '0';

	lat[10] = lon[10] = '\0';
	
	lat[0] = lon[0] = '\0';
	

	strcat(gsmmsg,GSMMsg);
	
	strcat(gsmmsg," http://maps.google.com/maps?q=");
	
	#ifdef DEMO
		strcat(gsmmsg,"12.2766");
		strcat(gsmmsg,",");
		strcat(gsmmsg,"76.62022");
	#else	
		GPSEn();
		GPSgetloc(lat,lon);
		
		#ifdef DISPLAY_LOC
			lcdclr();
			lcdws(lat);
			lcdr2();
			lcdws(lon);
			dlyms(10000);
			lcdclr();
		#endif 
		
			
		for (i = 0; i < 2; i++)
			latl[i] = lat[i];
			
		latl[i] = '\0';
		
		for (i = 2; i < 10; i++)
			latu[i-2] = lat[i];
			
		latu[i-2] = '\0';
		
			
		latdec = (atof(latl)) +  ((atof(latu)) / 60.0);
			
		ftoa(latdec, lat, 4);
	
		
		for (i = 0; i < 3; i++)
			lonl[i] = lon[i];
			
		lonl[i] = '\0';
			
		for (i = 3; i < 10; i++)
			lonu[i-3] = lon[i];
			
		lonu[i-3] = '\0';
			
		londec = atof(lonl) + ( atof(lonu) / 60.0 );
			
		ftoa(londec, lon,4);
		
					
		strcat(gsmmsg,lat);
		strcat(gsmmsg,",");
		strcat(gsmmsg,lon); 
		
	#endif
	
	GSMEn();
	GSMsndmsg(PhNum, gsmmsg);
}
void uartinit(void)
{
	UCSRB |= _BV(RXEN) | _BV(TXEN);					//Turn on transmission and reception
	UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1); //use 8-bit character size, select the UCSRL
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}
void putchar(char ch)
{
	while((UCSRA & _BV(UDRE)) == 0) {};
	UDR = ch;
	
}
int8u getchar(void)
{
	while((UCSRA & _BV(RXC) ) == 0) {};
	return UDR;
}
void puts(const char *s)
{
	while(*s) {
		putchar(*s++);
		dlyms(1);
	}
}
void EnUARTInt(void)
{
	int8u tmp;
	tmp = UDR;
	tmp = UDR;
	tmp = UDR;
	UCSRB |= (1 << 7);	/* Enable receive complete INT */
}
void DisUARTInt(void)
{
	int8u tmp;
	tmp = UDR;
	tmp = UDR;
	tmp = UDR;
	UCSRB &= ~(1 << 7);	/* Disable receive complete INT  */
	
}
#if defined FLOAT_T0_STRING > 0
void ftoa(float n, char *res, int afterpoint);
int intToStr(int x, char str[], int d);
void rever(char *str, int len);
#endif

#endif
