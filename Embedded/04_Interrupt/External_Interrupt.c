/*
 * External interrupt occurs on PA0 when USER BUTTON is pressed, using rising trigger
 * Then the LED on PD12 toggles every time the button pressed
 */

#include <stdint.h>

/*
 * Some address macros
 */
#define RCC_AHB1ENR_ADDR		(0x40023800U + 0x30U)
#define RCC_APB2ENR_ADDR		(0x40023800U + 0x44U)

//GPIOA registers' addresses
#define GPIOA_MODER_ADDR		(0x40020000U + 0x00U)
#define GPIOA_OSPEEDR_ADDR		(0x40020000U + 0x08U)
#define GPIOA_PUPDR_ADDR		(0x40020000U + 0x0CU)
#define GPIOA_IDR_ADDR			(0x40020000U + 0x10U)

//GPIOD registers' addresses
#define GPIOD_MODER_ADDR		(0x40020C00U + 0x00U)
#define GPIOD_OTYPER_ADDR		(0x40020C00U + 0x04U)
#define GPIOD_OSPEEDR_ADDR		(0x40020C00U + 0x08U)
#define GPIOD_PUPDR_ADDR		(0x40020C00U + 0x0CU)
#define GPIOD_ODR_ADDR			(0x40020C00U + 0x14U)

//NVIC interrupt set enable on line 6
#define NVIC_ISER0_ADDR			0xE000E100U

//SYSCFG external interrupt configuration register 2
#define SYSCFG_EXTICR1_ADDR		(0x40013800U + 0x08U)

//EXTI's registers addresses
#define EXTI_IMR_ADDR			(0x40013C00U + 0x00U)
#define EXTI_RTSR_ADDR			(0x40013C00U + 0x08U)
#define EXTI_PR_ADDR			(0x40013C00U + 0x14U)

void GPIO_init() {
	uint32_t *pReg;

	//1. Enable peripheral clock for GPIOA and GPIOD
	pReg = (uint32_t *)RCC_AHB1ENR_ADDR;
	*pReg |= (1 << 0) | (1 << 3);

	//2. Configure Button
	pReg = (uint32_t *)GPIOA_MODER_ADDR;
	*pReg &= ~(1 << 0);						//set input mode on PA0
	pReg = (uint32_t *)GPIOA_OSPEEDR_ADDR;
	*pReg |= (2 << 0);						//set high speed on PA0
	pReg = (uint32_t *)GPIOA_PUPDR_ADDR;
	*pReg &= ~(1 << 0);						//set no pull-up, pull-down on PA0

	//3. Configure LED
	pReg = (uint32_t *)GPIOD_MODER_ADDR;
	*pReg |= (1 << (12 * 2));				//set output mode on PD12
	pReg = (uint32_t *)GPIOD_OTYPER_ADDR;
	*pReg &= ~(1 << 0);						//set output push-pull on PD12
	pReg = (uint32_t *)GPIOD_OSPEEDR_ADDR;
	*pReg |= (2 << (12 * 2));				//set high speed on PD12
	pReg = (uint32_t *)GPIOD_PUPDR_ADDR;
	*pReg &= ~(1 << (12 * 2));				//set no pull-up, pull-down on PD12

	//4. When reset, LED on
	pReg = (uint32_t *)GPIOD_ODR_ADDR;
	*pReg |= (1 << 12);
}

void interrupt_init() {
	uint32_t *pReg;

	//1. System configuration controller clock enable
	pReg = (uint32_t *)RCC_APB2ENR_ADDR;
	*pReg |= (1 << 14);

	//2. Select the source input for the EXTI0 external interrupt: PA0
	pReg = (uint32_t *)SYSCFG_EXTICR1_ADDR;
	*pReg &= ~(1 << 0);	//line 0 port A

	//3. Set Rising trigger edge
	pReg = (uint32_t *)EXTI_RTSR_ADDR;
	*pReg |= (1 << 0);

	//4. Enable interrupt on line 0
	pReg = (uint32_t *)EXTI_IMR_ADDR;
	*pReg |= (1 << 0);

	//5. Enable interrupt of NVIC on line 6
	pReg = (uint32_t *)NVIC_ISER0_ADDR;
	*pReg |= (1 << 6);
}

int main(void)
{
	//Initialize GPIOA as button and GPIOD as LED
	GPIO_init();

	//Initialize external interrupt on user button/GPIOA pin 0
	interrupt_init();

	while(1) {
	}
}

void EXTI0_IRQHandler(void) {
	uint32_t *pReg;
	//Toggle LED
	pReg = (uint32_t *)GPIOD_ODR_ADDR;
	*pReg ^= (1 << 12);

	//Clear corresponding pending bit of Pending register EXTI_PR by writing 1
	pReg = (uint32_t *)EXTI_PR_ADDR;
	*pReg |= (1 << 0);
}
