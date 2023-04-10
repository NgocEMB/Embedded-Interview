#include <stdint.h>

//GPIOD offset
#define GPIOD_MODER_OFFSET		0x00U
#define GPIOD_OTYPER_OFFSET		0x04U
#define GPIOD_OSPEEDR_OFFSET	0x08U
#define GPIOD_PUPDR_OFFSET		0x0CU
#define GPIOD_ODR_OFFSET		0x14U

//TIM6 offset
#define TIM6_PSC_OFFSET			0x28U
#define TIM6_ARR_OFFSET			0x2CU
#define TIM6_CR1_OFFSET			0x00U
#define TIM6_DIER_OFFSET		0x0CU
#define TIM6_CNT_OFFSET			0x24U
#define TIM6_EGR_OFFSET			0x14U
#define TIM6_SR_OFFSET			0x10U

//address macors
#define RCC_BASEADDR			0x40023800U
#define RCC_AHB1ENR_OFFSET		0x30U
#define RCC_APB1ENR_OFFSET		0x40U
#define RCC_AHB1ENR_ADDR		(RCC_BASEADDR + RCC_AHB1ENR_OFFSET)
#define RCC_APB1ENR_ADDR		(RCC_BASEADDR + RCC_APB1ENR_OFFSET)
#define TIM6_BASEADDR			0x40001000U

#define GPIOD_BASEADDR			0x40020C00U
#define GPIOD_MODER_ADDR		(GPIOD_BASEADDR + GPIOD_MODER_OFFSET)
#define GPIOD_OTYPER_ADDR		(GPIOD_BASEADDR + GPIOD_OTYPER_OFFSET)
#define GPIOD_OSPEEDR_ADDR		(GPIOD_BASEADDR + GPIOD_OSPEEDR_OFFSET)
#define GPIOD_PUPDR_ADDR		(GPIOD_BASEADDR + GPIOD_PUPDR_OFFSET)
#define GPIOD_ODR_ADDR			(GPIOD_BASEADDR + GPIOD_ODR_OFFSET)

#define TIM6_PSC_ADDR			(TIM6_BASEADDR + TIM6_PSC_OFFSET)
#define TIM6_ARR_ADDR			(TIM6_BASEADDR + TIM6_ARR_OFFSET)
#define TIM6_CR1_ADDR			(TIM6_BASEADDR + TIM6_CR1_OFFSET)
#define TIM6_CNT_ADDR			(TIM6_BASEADDR + TIM6_CNT_OFFSET)
#define TIM6_DIER_ADDR			(TIM6_BASEADDR + TIM6_DIER_OFFSET)
#define TIM6_EGR_ADDR			(TIM6_BASEADDR + TIM6_EGR_OFFSET)
#define TIM6_SR_ADDR			(TIM6_BASEADDR + TIM6_SR_OFFSET)

#define NVIC_ISER1_ADDR			0xE000E104

//bit position macros
#define GPIODEN					3
#define MODER12					24		/* bit position of mode of Pin 12 */
#define OT12					12		/* bit position of output type of Pin 12 */
#define OSPEEDR12				24		/* bit position of output speed of Pin 12 */
#define PUPDR12					24		/* bit position of pullup-pulldown of Pin 12 */
#define TIM6EN					4		/* bit position of TIM6 clock enable */
#define UIE						0		/* bit position of update interrupt enable */
#define UIF						0		/* bit position of Update interrupt flag */
#define CEN						0		/* bit position of Counter enable */

//other macros
#define OUTPUT_MODE				1		/* General purpose output mode */
#define OUTPUT_PP				0		/* Output type: push-pull */
#define OUTPUT_SPD_MED			1		/* Output speed: medium */
#define NO_PUPD					0		/* No pull-up, no pull-down */
#define HIGH					1		/* High logic level */
#define PIN_NO_12				12		/* Pin number 12 */
#define IRQ_NUM_TIM6			54		/* IRQ number of Timer 6 */

void configurationGPIOD() {
	volatile uint32_t *temp;
	//Enable clock peripheral
	temp = (uint32_t*)RCC_AHB1ENR_ADDR;
	*temp |= (1 << GPIODEN);

	//configure output mode
	temp = (uint32_t*)GPIOD_MODER_ADDR;
	*temp |= (OUTPUT_MODE << MODER12);

	//configure output type
	temp = (uint32_t*)GPIOD_OTYPER_ADDR;
	*temp |= (OUTPUT_PP << MODER12);

	//configure output speed
	temp = (uint32_t*)GPIOD_OSPEEDR_ADDR;
	*temp |= (OUTPUT_SPD_MED << OSPEEDR12);

	//configure pull-up/pull-down
	temp = (uint32_t*)GPIOD_PUPDR_ADDR;
	*temp |= (NO_PUPD << PUPDR12);

	//reset LED
	temp = (uint32_t*)GPIOD_ODR_ADDR;
	*temp &= ~(HIGH << PIN_NO_12);
}

void configurationTIMER() {
	volatile uint32_t *temp;
	//Enable clock peripheral
	temp = (uint32_t*)RCC_APB1ENR_ADDR;
	*temp |= (1 << TIM6EN);

	//Configure prescaler
	temp = (uint32_t*)TIM6_PSC_ADDR;
	*temp = 3999;	//~1s

	//Configure Auto-reload value
	temp = (uint32_t*)TIM6_ARR_ADDR;
	*temp = 3999;	//~1s

	//Enable interrupt
	temp = (uint32_t*)TIM6_DIER_ADDR;
	*temp |= (1 << UIE);

	//clear Update interrupt flag
	temp = (uint32_t*)TIM6_SR_ADDR;
	*temp &= ~(1 << UIF);

	//Enable timer
	temp = (uint32_t*)TIM6_CR1_ADDR;
	*temp |= (1 << CEN);
}

void initInterrupt() {
	volatile uint32_t *temp;
	//Enable interrupt timer
	temp = (uint32_t*)NVIC_ISER1_ADDR;
	*temp |= (1 << (IRQ_NUM_TIM6 % 32));
}

int main(void)
{
    //1. Configure LED on PD12
	configurationGPIOD();
	//2. Configure timer on TIMER 6
	configurationTIMER();
	//3. Enable interrupt
	initInterrupt();
	while(1) {

	}
}

void TIM6_DAC_IRQHandler(void) {
	//toggle LED PD12
	volatile uint32_t *temp = (uint32_t*)GPIOD_ODR_ADDR;
	*temp ^= (HIGH << PIN_NO_12);
	//CLEAR Update interrupt flag
	temp = (uint32_t*)TIM6_SR_ADDR;
	*temp &= ~(1 << UIF);
}
