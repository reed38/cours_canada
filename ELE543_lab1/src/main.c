/****************************Proto 1********************************************
 Author : Bruno De Kelper et Alexandre Ceriani
 Date   : 10-06-2016
 Description :
 GPIO : -User button (PB0 et PB1)
        -Reset button (NRST)
        -LED bleu (PC8) et verte (PC9)
        -Led externe au board (PC0-PC7)
        -I2C1 SDA (PB7) et SCL (PB6)
        -ADC (PA4 et PA5)
        -Bit Direction_FB (PA6 et PA7)
        -Bit Direction Gauche (LSB : PB12 MSB : PB13)
        -Bit Direction Droit (LSB : PB14 MSB : PB15)
        -Bit calibration (PA8)
        -PWM sur timer 3 channel 1 (PB4) et 2 (PB5)
        -USART2 RX (PA2) et TX (PA3)
*/

#include <stdio.h> /*sprintf*/
#include "main.h"

// Fr�quence des Ticks du SysTick (en Hz)
#define MillisecondsIT ((uint32_t) 1000)

/*Fonctions main*/
void Configure_Clock(void);

void SysTick_Handler(void) {

}


int main(void) {

	// Configure les composantes du robot
	__set_PRIMASK(1);
    Configure_Clock();
    /*Initialisation des p�riph�riques*/

	__set_PRIMASK(0);
	volatile uint32_t counter = 0;
    while (1) {
    	/*Boucle principale du programme*/
    	counter++;
    }
    return (0);
}

__INLINE void Configure_Clock(void){
	/*Il faut ajouter le code pour l'initialisation du RCC*/

	// initialising RCC->CR  to 0x00000000 so there is no undefined bits after reset
	RCC->CR=(uint32_t)0x00000000;

	//Turning on HSE, default value 8MHZ
	RCC->CR |= RCC_CR_HSEON; // HSEON = 1, HSEBYP = 1, HSION = 1

	//waiting for HSE to be stable
	while(!(RCC->CR && RCC_CR_HSERDY));

	//setting up the pre-scaler to 1
	RCC->CFGR|=RCC_CFGR_HPRE_DIV1;

	//defining the pll src
	RCC->CFGR|=RCC_CFGR_PLLSRC_0;
	RCC->CFGR&=!RCC_CFGR_PLLSRC_1;

	//starting by switching of the pll
	RCC->CFGR&=!RCC_CR_PLLON;

	//waiting until pll ready is cleared
	while(RCC->CR&RCC_CR_PLLRDY);

	//defining the pll upscaler we want 6 => 0110
	RCC->CFGR|=RCC_CFGR_PLLMUL6;

	//switching back on back the pll upscaler
	RCC->CFGR|=RCC_CR_PLLON;

	//waiting until the pll is ready again
	while(!(RCC->CR&RCC_CR_PLLRDY));


	//setting up the output of the pll as system clock
	RCC->CFGR|=RCC_CFGR_SW_PLL;




	while (!(RCC->CR & ((uint32_t) 0x02000000)));// Attend que le PLL soit prêt
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Active l'horloge du port A
	GPIOA->MODER |= GPIO_MODER_MODER8_1; // Mettre MODE en AF pour PA8
	GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEEDR8_0 || // Vitesse MAX pour PC0
	GPIO_OSPEEDR_OSPEEDR8_1;
    SystemCoreClockUpdate();	// Met � jour SystemCoreClock avec la config du RCC
    SysTick_Config(SystemCoreClock/MillisecondsIT);	// Configure le SysTick � 1 ms
}

/*End of file*/
