#ifndef _APP_H
#define _APP_H

#define TESTING

#define EEPROM_DISPLAY				0

/* LCD Port Description */
#define LCD_DDR           	   		DDRC
#define LCD_DATA_PORT          		PORTC
#define LCD_ENABLE_PIN        		PC3 
#define LCD_REGISTER_SELECT_PIN     PC2
#define DISPLAY_INIT				1
#define LCD_NSCRL					3
#define FLOAT_T0_STRING				1
#define DECIMAL_PRECISION			10

/* BUZZER Port Description */
#define	BUZ_DDR						DDRC
#define	BUZ_PORT					PORTC
#define	BUZ_PIN						PC1
#define OFF_TIME					100

/* LED Port Description */

#define	LED_DDR			DDRC	
#define	LED_PORT		PORTC	
#define	LED_PIN			PC0
#define OFF_TIME		100

/* GSM Configuration*/
#define MSG_START					""
#define MSG_END						". Automated SMS By: WSS."


#define REF_VOL_256

/*GSM Port Description*/
#define GSM_GPS_DDR				DDRD
#define GSM_GPS_PORT			PORTD
#define GSM_GPS_PIN				PD7

/*GSM Define*/
#define GSMEn()				do {									\
								GSM_GPS_PORT &= ~_BV(GSM_GPS_PIN); 	\
								dlyms(500);						\
							} while(0)

#define GPSEn()				do {									\
								GSM_GPS_PORT |= _BV(GSM_GPS_PIN);		\
								dlyms(500);						\
							} while(0)
							
/*EEPROM Definition*/
#define EEPROM_DISPLAY		0

#endif
