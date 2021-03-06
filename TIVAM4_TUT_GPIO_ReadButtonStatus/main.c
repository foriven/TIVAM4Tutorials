/****************************************************************
 *
 * www.payitforward.edu.vn
 *
 ****************************************************************/
/****************************************************************
 *
 * PIF TIVA TUTORIAL
 *
 ****************************************************************/

/****************************************************************
 *
 *	Module		: main.c
 *	Description	:
 *  Tool		: CCS 5.
 *	Chip		: TIVA C TM4C123G
 * 	History		: 01/11/2014
 *  Version     : 1.0
 *
 *	Author		: CTCNGH, Pay it Forward Club
 *	Notes		:
 *
 *
 ****************************************************************/


/****************************************************************
 * DEFINE
 ****************************************************************/
#define LED_RED		GPIO_PIN_1
#define LED_GREEN	GPIO_PIN_2
#define LED_BLUE	GPIO_PIN_3
#define SW1			GPIO_PIN_4
#define SW2 		GPIO_PIN_0


/****************************************************************
 * IMPORT
 ****************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_gpio.h"


int read;

/******************************************************************************
 * MAIN
 *****************************************************************************/
void main (void)
{

	// Configure clock 40 MHz
	SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	//PortF Enable
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	//Config GPIO that connect to LED - PIN 1,2,3
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_GREEN|LED_BLUE);
	//Turn off all LEDs
	GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, 0);
	//Config Buttons
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0x4C4F434B;	//Unlocks the GPIO Commit (GPIOCR) register for write access PF0
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = SW1;
	GPIODirModeSet(GPIO_PORTF_BASE,  SW1|SW2, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTF_BASE, SW1|SW2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	//Infinite loop
	while(1)
	{

		read=GPIOPinRead(GPIO_PORTF_BASE,SW1|SW2);
		if((read&(SW1|SW2))==0)
			GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, LED_RED);
		else if((read&SW1 )==0)
			GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, LED_GREEN);
		else if((read&SW2)==0)
			GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, LED_BLUE);
		else
			GPIOPinWrite(GPIO_PORTF_BASE,  LED_RED|LED_GREEN|LED_BLUE, 0);

	}

}

/****************************************************************
 * END OF main.c
 ****************************************************************/
