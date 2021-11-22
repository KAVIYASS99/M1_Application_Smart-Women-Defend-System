#include "main.h"

const char *Msg =  "Please Save me, I am @";

struct  {
	volatile int8u Sw:1;
}AppFlags;

int main(void) {
	init();
	while (TRUE) {
		if (AppFlags.Sw) {
			buzon();
			ShockOn();
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
	GICR	|= _BV(INT0);						
}
static void disptitl(void) {
	lcdclr();
	lcdws("Women Secu'y S/M");
}
static void Tmr2Init(void) {
	TCNT2	= TIMER2_RELOAD;
	TIMSK	|= _BV(TOIE2);							
	TCCR2	|=  _BV(CS22) | _BV(CS21) | _BV(CS20); 
}

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
