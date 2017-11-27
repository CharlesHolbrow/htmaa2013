
/* 
***************************************************************************
**
**  Counter/Timer Examples -- Code Examples for Tutorial
**
**  3/6/09 - Initial Creation -- jkl
**
**************************************************************************
*/

/* Include useful pre-defined functions */
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>    // Defines pins, ports, etc to make programs easier to read
#define F_CPU 1000000UL	      // Sets up the default speed for delay.h
#include <util/delay.h>

/* General Defines */
#define	TRUE	1
#define	FALSE	0

/*
**  Outputs will be on pins that Timer/Counter 1 can manipulate.
*/
#define PORT_CT	PORTB
#define DDR_CT	DDRB
#define	CT1A	PB3		// OC1A
#define	CT1B	PB4		// OC1B

// LED and Button Ports - specific to ATtiny2313
#define PORT_LED	PORTD
#define PORT_BUTTON	PORTD		// used for jumpers
#define DDR_LED   	DDRD
#define DDR_BUTTON  DDRD
#define PIN_BUTTON  PIND
#define P_LED_1		PD1			// used for init & data signal (for Debug)

// Example Selection contols
// Read inputs to know what mode to use.
#define EXAMP_SEL_IN_1	PD4
#define EXAMP_SEL_IN_2	PD5
#define EXAMP_SEL_IN_3	PD6

// Examples
#define EXAMP_0	00
#define EXAMP_1	01
#define EXAMP_2	02
#define EXAMP_3	03
#define EXAMP_4	04

//Function Declarations
void Examp_0( void );
void Examp_1( void );
void Examp_2( void );
void Examp_3( void );
void Examp_4( void );
void blinkEm( uint8_t count, uint8_t led);

int main( void ){
	uint8_t examp;
/*
** Initialization
**  Configure ports
**	Blink a led at start
**  Read Selection Bits
** Jump to selected Example
**
*/
	// Could configure clock to run at 8MHz here. Default is 1MHz
	// If changed, must fix calls to _delay_ms
/*	CLKPR = _BV(CLKPCE) ;		// Initiate write cycle for clock setting
	CLKPR = 0x00;		// Prescaler divider 1 => 8 MHz clock out
*/	

	DDR_CT |= _BV(CT1A) | _BV(CT1B) ;   /* Enable CT1 output pins */
	PORT_CT &= ~(_BV(CT1A) | _BV(CT1B));     /* Set them to lo - LEDs off */

	/* Initialize Selection Bits - Turn on pull-ups*/
	PORT_BUTTON |= _BV(EXAMP_SEL_IN_1) | _BV(EXAMP_SEL_IN_2) | _BV(EXAMP_SEL_IN_3);
	
	/* Initialize LED blinker  */
	DDR_LED |= _BV(P_LED_1);   // enable output
	
// Read the Example Selects.
// Have to reset to select a different one.
	examp = (PIN_BUTTON >> 4) & 0x07;
	
	blinkEm(1,P_LED_1);		// Blink once as init signal
	
		switch (examp){			// called functions must never return!!
			case EXAMP_0:
				Examp_0();
				break;
			case EXAMP_1: 
				Examp_1();
				break;
			case EXAMP_2: 
				Examp_2();				
				break;
			case EXAMP_3: 
				Examp_3();
				break;
			case EXAMP_4:
				Examp_4();
				break;
		}
	return(0);
}


/*
***************************************************************************
**  Example 0: 
** - CT1 in Phase & Frequency Correct PWM Mode
** - Functioning like CTC Mode:
** -- Just toggle OC1A with OCR1A as TOP
** Change frequency every 10 cycles.
***************************************************************************
*/

void Examp_0( void )
{
	uint8_t count = 0;
	
	// Set OCR1A (TOP)
	OCR1A = 49;		// toggles every one tenth second
	
	// Configure Timer/Counter 1 
	// Select Phase & Frequency Correct PWM Mode, and OCR1A as TOP. Use WGM Bits.
	// WGM Bits are in TCCR1A and TCCR1B. Any previous settings are cleared.
	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(WGM13); 
	// Configure OC1A to Toggle at TOP.
	TCCR1A |= _BV(COM1A0);
	// Select Internal Clock Divided by 1024. This starts the Timer/Counter.
	TCCR1B |= _BV(CS12) | _BV(CS10);

	while (TRUE)	// Do this forever
	{
		// monitor the overflow flag and change the time every 10 cycles
		while ((TIFR & _BV(TOV1))==0); // wait for timer overflow
		TIFR |= _BV(TOV1);	// Clear the flag by writing 1
		
		if (count >= 10) 
		{
			if (OCR1A > 100)
			{
				OCR1A = 49;		// flash at one tenth second rate
			}
			else
			{
				OCR1A = 490;		// flash at one second rate
			}
			count = 0;			// reset count
		}
		else
		{
			count++;
		}	
	}	
}

/*
***************************************************************************
**  Example 1: 
** - CT1 in Phase & Frequency Correct PWM Mode
** - Generating a Waveform:
** -- Use ICR1 as TOP and OC1A to make waveform (arbitrary Duty Cycle).
** -- Vary OCR1A to change ON time.
***************************************************************************
*/

void Examp_1( void )
{
	uint8_t count = 0;
	
	// Set ICR1 (TOP) and OCR1A
	ICR1 = 980;			// two second cycle time
	OCR1A = 931;		// one tenth second ON time
	
	// Configure Timer/Counter 1 
	// Select Phase & Frequency Correct PWM Mode, and ICR1 as TOP. Use WGM Bits.
	// WGM Bits are in TCCR1A and TCCR1B. Any previous settings are cleared.
	TCCR1A = 0;			// Just to clear the register.
	TCCR1B = _BV(WGM13); 
	// OC1A HI when COUNT = OCR1A upcounting, LO when COUNT = OCR1A downcounting.
	TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
	// Select Internal Clock Divided by 1024. This starts the Timer/Counter.
	TCCR1B |= _BV(CS12) | _BV(CS10);	
	
	while (TRUE)	// Do this forever
	{
		// monitor the overflow flag and change the time every 10 cycles
		while ((TIFR & _BV(TOV1))==0); // wait for timer overflow
		TIFR |= _BV(TOV1);	// Clear the flag by writing 1
		
		if (count >= 10) 
		{
			if (OCR1A > 100)
			{
				OCR1A = 49;		// ON for 1.9 seconds
			}
			else
			{
				OCR1A = 931;		// ON for one tenth of a second
			}
			count = 0;			// reset count
		}
		else
		{
			count++;
		}
	}	
}

/*
***************************************************************************
**  Example 2: 
** - CT1 in Phase & Frequency Correct PWM Mode.
** - Generating a Waveform:
** -- OCR1A as TOP, OCR1B as compare, OC1B as output.
** -- Vary OCR1A to change cycle time.
***************************************************************************
*/

void Examp_2( void )
{
	uint8_t count = 0;
	
	// Set OCR1A (TOP) and OCR1B
	OCR1A = 980;	
	OCR1B = 49;
	
	// Configure Timer/Counter 1 
	// Select Phase & Frequency Correct PWM Mode, and OCR1A as TOP. Use WGM Bits.
	// WGM Bits are in TCCR1A and TCCR1B. Any previous settings are cleared.
	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(WGM13); 
	// OC1B LO when COUNT = OCR1B upcounting, HI when COUNT = OCR1B downcounting.
	TCCR1A |= _BV(COM1B1);
	// Select Internal Clock Divided by 1024. This starts the Timer/Counter.
	TCCR1B |= _BV(CS12) | _BV(CS10);	
	
	while (TRUE)	// Do this forever
	{
		// monitor the overflow flag and change the time every 10 cycles
		while ((TIFR & _BV(TOV1))==0); // wait for timer overflow
		TIFR |= _BV(TOV1);	// Clear the flag by writing 1
		
		if (count >= 10) 
		{
			if (OCR1A > 100)
			{
				OCR1A = 98;		// cycle length two tenths second
			}
			else
			{
				OCR1A = 980;		// cycle length two seconds
			}
			count = 0;			// reset count
		}
		else
		{
			count++;
		}
	}	
}

/*
***************************************************************************
**  Example 3: 
**	- CT1 in Fast PWM showing pulse alignment on rising edge.
**	-- OC1A and OC1B are outputs. 
**  -- Change OCR1B to change OC1B ON time.
***************************************************************************
*/

void Examp_3( void )
{
	uint8_t count = 0;
	
	// Set ICR1 (TOP), OCR1A and OCR1B
	ICR1 = 1960;
	OCR1A = 980;
	OCR1B = 490;
	
	// Configure Timer/Counter 1 
	// Select Fast PWM Mode, and ICR1 as TOP. Use WGM Bits.
	// WGM Bits are in TCCR1A and TCCR1B. Any previous settings are cleared.
	TCCR1A = _BV(WGM11);
	TCCR1B = _BV(WGM13) | _BV(WGM12); 
	// OC1A,B HI at TOP, LO when COUNT = OCR1A,B upcounting.
	TCCR1A |= _BV(COM1B1) | _BV(COM1A1);
	// Select Internal Clock Divided by 1024. This starts the Timer/Counter.
	TCCR1B |= _BV(CS12) | _BV(CS10);	
	
	while (TRUE)	// Do this forever
	{
		// monitor the overflow flag and change the time every 10 cycles
		while ((TIFR & _BV(TOV1))==0); // wait for timer overflow
		TIFR |= _BV(TOV1);	// Clear the flag by writing 1
		
		if (count >= 10) 
		{
			if (OCR1B > 100)
			{
				OCR1B = 98;		// ON one tenth second
			}
			else
			{
				OCR1B = 490;		// ON one half second
			}
			count = 0;			// reset count
		}
		else
		{
			count++;
		}
	}	
}

/*
***************************************************************************
**  Example 4: 
**	- CT1 in Phase & Frequency Correct PWM showing pulse alignment at center
**	-- OC1A and OC1B are outputs. 
**  -- Change OCR1B to change OC1B ON time.
***************************************************************************
*/

void Examp_4( void )
{
	uint8_t count = 0;
	
	// Set ICR1 (TOP), OCR1A and OCR1B
	ICR1 = 980;
	OCR1A = 490;
	OCR1B = 735;
	
	// Configure Timer/Counter 1 
	// Select Phase & Frequency Correct PWM Mode, and ICR1 as TOP. Use WGM Bits.
	// WGM Bits are in TCCR1A and TCCR1B. Any previous settings are cleared.
	TCCR1A = 0;			// Just clear register.
	TCCR1B = _BV(WGM13); 
	// OC1A,B HI when COUNT = OCR1A,B upcounting, LO when COUNT = OCR1A,B downcounting.
	TCCR1A |= _BV(COM1A1) |  _BV(COM1A0) |  _BV(COM1B1) |  _BV(COM1B0);
	// Select Internal Clock Divided by 1024. This starts the Timer/Counter.
	TCCR1B |= _BV(CS12) | _BV(CS10);	
	
	while (TRUE)	// Do this forever
	{
		// monitor the overflow flag and change the time every 10 cycles
		while ((TIFR & _BV(TOV1))==0); // wait for timer overflow
		TIFR |= _BV(TOV1);	// Clear the flag by writing 1
		
		if (count >= 10) 
		{
			if (OCR1B > 800)
			{
				OCR1B = 735;		// ON one half second
			}
			else
			{
				OCR1B = 931;		// ON two tenths second
			}
			count = 0;			// reset count
		}
		else
		{
			count++;
		}
	}	
}


/*------------------------------------------------------------------------
**  blinkEm - function to blink LED for count passed in
**		Assumes that leds are all on the same port. 1MHz Clock rate.
** ---------------------------------------------------------------------*/
void blinkEm( uint8_t count, uint8_t led){
	uint8_t i;
	while (count > 0){
		PORT_LED |= _BV(led);
		for (i=0;i<5;i++)
		{
			_delay_ms(200);
		}
		PORT_LED &= ~_BV(led);
		for (i=0;i<5;i++)
		{
			_delay_ms(200);
		}
		count--;
	}
}
