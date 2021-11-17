#include "buz.h"
#include "dly.h"
#include"gps.h"
#include "gsm.h"
#include "LCD.h"
#include "led.h"
#include "sms.h"
#include"uart.h"


/* Buzzer Program*/
extern int16u BeepOffDly;

void buzinit(void) {
	BUZ_DDR		|= _BV(BUZ_PIN);
	BUZ_PORT 	&= ~_BV(BUZ_PIN);
}

void beep(int8u nbeep, int16u ontime) {
	while(nbeep--)	{
		buzon();
		dlyms(ontime);
		buzoff();
		dlyms(100);  
	}
}

/*Delay Program*/
void dlyms(int16u dly) {
	while (dly--)
		_delay_ms(1);
}

void dlyus(int16u dly) {
	while (dly--)
		_delay_us(1);
}
/*GPS Program*/
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

/* GSM AT Commands*/
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

/*GSM Program*/
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

/*LCD Program*/
static void  LCDEnable		(void);
static void  LCDReset		(void);
static void  LCDWriteByte	(char  ch);

int8u lcdptr;

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
		adr = 0xc0;						
		for ( i = 0; i < 16; i++ ) {
			lcdwc(adr);			
			lcdwd(LCD_DOT);				
			if ( i < 8 ) dlyms(200+(50*i)); else dlyms(25);
			lcdwc(adr);			
			lcdwd(LCD_SPC);			
			adr++;					
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
	lcdptr = 0x80;	  
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
	lcdwc(0x80); 	  
	lcdptr = 0x80;
 }
  void lcdr2(void)
 {
	lcdwc(0xc0); 	  
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

int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x)
	{
		str[i++] = (x%10) + '0';
		x = x/10;
	}
	
	while (i < d)
	str[i++] = '0';
	
	rever(str, i);
	str[i] = '\0';
	return i;
}

void ftoa(float n, char *res, int afterpoint)
{
	int ipart = (int)n;
	
	float fpart = n - (float)ipart;
	
	int i = intToStr(ipart, res, 0);
	
	if (afterpoint != 0)
	{
		res[i] = '.';  
		
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}


#endif
double atof(char *s)
{
	double val,power;
	int sign;
	
	for(; isspace(*s); s++);	
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

/*LED Program*/
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

/*SMS Program*/
extern int8u OTP[5];

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

/*UART Program*/
void uartinit(void)
{
	UCSRB |= _BV(RXEN) | _BV(TXEN);					
	UCSRC |= _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1); 
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
	UCSRB |= (1 << 7);	
}
void DisUARTInt(void)
{
	int8u tmp;
	tmp = UDR;
	tmp = UDR;
	tmp = UDR;
	UCSRB &= ~(1 << 7);	
	
}