#include <stdint.h>
#include <stdio.h>

//SPI Pins
#define SCK  	0
#define MOSI 	1
#define SS   	2
#define MISO 	3

//Address offset macros
#define GPIOx_MODER_OFFSET		0x00U			/* Address offset of GPIO port mode register */
#define GPIOx_OTYPER_OFFSET		0x04U			/* Address offset of GPIO port output type register */
#define GPIOx_OSPEEDR_OFFSET	0x08U			/* Address offset of GPIO port output speed register */
#define GPIOx_PUPDR_OFFSET		0x0CU			/* Address offset of GPIO port pull-up/pull-down register */
#define GPIOx_IDR_OFFSET		0x10U			/* Address offset of GPIO port input data register */
#define GPIOx_ODR_OFFSET		0x14U			/* Address offset of GPIO port output data register */

#define TIMx_CR1_OFFSET			0x00U			/* Address offset of TIM6 and TIM7 control register 1 */
#define TIMx_DIER_OFFSET		0x0CU			/* Address offset of TIM6 and TIM7 DMA/Interrupt enable register */
#define TIMx_SR_OFFSET			0x10U			/* Address offset of TIM6 and TIM7 status register */
#define TIMx_PSC_OFFSET			0x28U			/* Address offset of TIM6 and TIM7 prescaler */
#define TIMx_ARR_OFFSET			0x2CU			/* Address offset of TIM6 and TIM7 auto-reload register */

#define RCC_APB1ENR_OFFSET		0x40U			/* Address offset of RCC APB1 peripheral clock enable register */
#define RCC_AHB1ENR_OFFSET		0x30U			/* Address offset of RCC AHB1 peripheral clock enable register */

//Address macros
#define RCC_BASEADDR			0x40023800U		/* Base address of RCC */
#define GPIOD_BASEADDR			0x40020C00U		/* Base address of GPIO port D */
#define TIM6_BASEADDR			0x40001000U		/* Base address of Timer 6 */
#define NVIC_ISER1_ADDR			0xE000E104U		/* Address of Interrupt Set-enable Register 1 of NVIC */

#define GPIOD_MODER_ADDR		(GPIOD_BASEADDR + GPIOx_MODER_OFFSET)	/* Address of GPIO port mode register */
#define GPIOD_OTYPER_ADDR		(GPIOD_BASEADDR + GPIOx_OTYPER_OFFSET)	/* Address of GPIO port output type register */
#define GPIOD_OSPEEDR_ADDR	    (GPIOD_BASEADDR + GPIOx_OSPEEDR_OFFSET)	/* Address of GPIO port output speed register */
#define GPIOD_PUPDR_ADDR		(GPIOD_BASEADDR + GPIOx_PUPDR_OFFSET)	/* Address of GPIO port pull-up/pull-down register */
#define GPIOD_IDR_ADDR		    (GPIOD_BASEADDR + GPIOx_IDR_OFFSET)		/* Address of GPIO port input data register */
#define GPIOD_ODR_ADDR		    (GPIOD_BASEADDR + GPIOx_ODR_OFFSET)		/* Address of GPIO port output data register */

#define TIM6_CR1_ADDR			(TIM6_BASEADDR + TIMx_CR1_OFFSET)		/* Address of TIM6 and TIM7 control register 1 */
#define TIM6_DIER_ADDR		    (TIM6_BASEADDR + TIMx_DIER_OFFSET)		/* Address of TIM6 and TIM7 DMA/Interrupt enable register */
#define TIM6_SR_ADDR			(TIM6_BASEADDR + TIMx_SR_OFFSET)		/* Address of TIM6 and TIM7 status register */
#define TIM6_PSC_ADDR			(TIM6_BASEADDR + TIMx_PSC_OFFSET)		/* Address of TIM6 and TIM7 prescaler */
#define TIM6_ARR_ADDR			(TIM6_BASEADDR + TIMx_ARR_OFFSET)		/* Address of TIM6 and TIM7 auto-reload register */

#define RCC_APB1ENR_ADDR		(RCC_BASEADDR + RCC_APB1ENR_OFFSET)		/* Address of RCC APB1 peripheral clock enable register */
#define RCC_AHB1ENR_ADDR		(RCC_BASEADDR + RCC_AHB1ENR_OFFSET)		/* Address of RCC AHB1 peripheral clock enable register */

//Bit position macros
#define MASTER					0
#define SLAVE					1
#define GPIODEN					3
#define TIM6EN					4
#define UIE						0
#define UIF						0
#define CEN						0

//Other macros
#define IRQ_NO_TIM6				54				/* IRQ number of Timer 6 */
#define HI_SPEED				3				/* GPIO port output speed: HIGH SPEED */
#define PULL_UP					1				/* GPIO port pull-up */

uint32_t count = 0;
uint8_t data = 'S';

/*
 * Function prototypes
 */
void initializeSoftSPI(uint8_t asMaster);
void initializeTimer6();
void myDelay10us(uint32_t time);
void SPI_Soft_Transmit_1Byte_Master(uint8_t data);
void SPI_Soft_Transmit_1Byte_Slave(uint8_t data);
uint8_t SPI_Soft_Receive_1Byte_Master();
uint8_t SPI_Soft_Receive_1Byte_Slave();

/******************************** MAIN FUNCTION *********************************/
int main(void)
{
    //1. Configure GPIOD pins as SPI pins
//	initializeSoftSPI(MASTER);
	initializeSoftSPI(SLAVE);

	//2. Configure Timer 6 for delay/clock functionality, only when this device is a MASTER
	initializeTimer6();

	while(1) {
		//Test case for MASTER transmit 1 byte data
		#if 0
		SPI_Soft_Transmit_1Byte_Master(data);
		myDelay10us(1000000);
		#endif

		//Test case for MASTER receive 1 byte data
		#if 0
		data = SPI_Soft_Receive_1Byte_Master();
		if(data != 0x00) {
			printf("Received data: %c\n", data);
			myDelay10us(1000000);
		}
		#endif

		//Test case for SLAVE transmit 1 byte data
		#if 0
		SPI_Soft_Transmit_1Byte_Slave(data);
		#endif

		//Test case for SLAVE receive 1 byte data
		#if 1
		data = SPI_Soft_Receive_1Byte_Slave();
		if(data != 0x00) {
			printf("Received data: %c\n", data);
		}
		#endif
	}
}

/*****************************************************************
 * @Name	: initializeSoftSPI
 * @Brief	: initialize soft SPI, configure GPIO pins as SPI pins
 * @Params	: <1> asMaster: SLAVE or MASTER
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void initializeSoftSPI(uint8_t asMaster) {
	volatile uint32_t *pRegister;

	//Enable peripheral clock
	pRegister = (uint32_t *)RCC_AHB1ENR_ADDR;
	*pRegister |= (1 << GPIODEN);

	//Set pin mode as output/input for SCK, MOSI, MISO, SS pins
	pRegister = (uint32_t *)GPIOD_MODER_ADDR;
	if(asMaster == MASTER) {
		*pRegister |= (1 << (SCK * 2));
		*pRegister |= (1 << (SS * 2));
		*pRegister |= (1 << (MOSI * 2));
		*pRegister &= ~(1 << (MISO * 2));	//input
	}
	else if(asMaster == SLAVE) {
		*pRegister &= ~(1 << (MOSI * 2));	//input
		*pRegister |= (1 << (MISO * 2));
		*pRegister &= ~(1 << (SS * 2));		//input
		*pRegister &= ~(1 << (SCK * 2));
	}

	//Set output type: push-pull
	pRegister = (uint32_t *)GPIOD_OTYPER_ADDR;
	if(asMaster == MASTER) {
		*pRegister &= ~(1 << SCK);
		*pRegister &= ~(1 << MOSI);
		*pRegister &= ~(1 << SS);
	}
	else if(asMaster == SLAVE) {
		*pRegister &= ~(1 << MISO);
	}

	//Set output speed
	pRegister = (uint32_t *)GPIOD_OSPEEDR_ADDR;
	if(asMaster == MASTER) {
		*pRegister |= (HI_SPEED << (SCK * 2));
		*pRegister |= (HI_SPEED << (SS * 2));
		*pRegister |= (HI_SPEED << (MOSI * 2));
	}
	else if(asMaster == SLAVE) {
		*pRegister |= (HI_SPEED << (MISO * 2));
	}

	//Set pull-up
	pRegister = (uint32_t *)GPIOD_PUPDR_ADDR;
	if(asMaster == MASTER) {
		*pRegister |= (PULL_UP << (MISO * 2));
	}
	else if(asMaster == SLAVE) {
		*pRegister |= (PULL_UP << (MOSI * 2));
		*pRegister |= (PULL_UP << (SS * 2));
		*pRegister |= (PULL_UP << (SCK * 2));
	}

	//when reset
	pRegister = (uint32_t *)GPIOD_ODR_ADDR;
	if(asMaster == MASTER) {
		*pRegister &= ~(1 << MOSI);		//MOSI = 0
		*pRegister &= ~(1 << SCK);		//SCK = 0
		*pRegister |= (1 << SS);		//SS  = 1 --> not select
	}
	else if(asMaster == SLAVE) {
		*pRegister &= ~(1 << MISO);		//MISO = 0
	}
}

/*****************************************************************
 * @Name	: initializeTimer6
 * @Brief	: initialize Timer 6, configure timer 6 and interrupt timer
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void initializeTimer6() {
	volatile uint32_t *pRegister;

	//Enable peripheral clock
	pRegister = (uint32_t *)RCC_APB1ENR_ADDR;
	*pRegister |= (1 << TIM6EN);

	//Set prescaler value
	pRegister = (uint32_t *)TIM6_PSC_ADDR;
	*pRegister = 12;		//interrupt every 10us

	//Set auto-reload value
	pRegister = (uint32_t *)TIM6_ARR_ADDR;
	*pRegister = 11;

	//Enable update interrupt
	pRegister = (uint32_t *)TIM6_DIER_ADDR;
	*pRegister |= (1 << UIE);

	//Clear update interrupt flag
	pRegister = (uint32_t *)TIM6_SR_ADDR;
	*pRegister &= ~(1 << UIF);

	//Enable interrupt
	pRegister = (uint32_t *)NVIC_ISER1_ADDR;
	*pRegister |= (1 << (IRQ_NO_TIM6 % 32));
}

/*****************************************************************
 * @Name	: myDelay10us
 * @Brief	: generate delay 10(x 1,2,3,4,5,...)us by timer
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void myDelay10us(uint32_t time) {	//time là bội của 10
	//Enable timer
	volatile uint32_t *pRegister = (uint32_t *)TIM6_CR1_ADDR;
	*pRegister |= (1 << CEN);

	count = 0;

	while(count < (time/10));
	//Disable timer
	pRegister = (uint32_t *)TIM6_CR1_ADDR;
	*pRegister &= ~(1 << CEN);
}

/*****************************************************************
 * @Name	: SPI_Soft_Transmit_1Byte_Master
 * @Brief	: master transmit 1 byte
 * @Params	: <1> data: data to send
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void SPI_Soft_Transmit_1Byte_Master(uint8_t data) {
	volatile uint32_t *pData = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	*pData &= ~(1 << SS);				//SS = 0 --> select slave
	uint8_t bitValue = 0x00;
	uint8_t i = 0;

	while(i < 8) {
		bitValue = data & 0x80;			//read MSB bit
		myDelay10us(10);
		*pData |= (1 << SCK);			//clock = 1, rising edge
		if(bitValue > 0)				//send data
			*pData |= (1 << MOSI);
		else *pData &= ~(1 << MOSI);
		myDelay10us(10);
		*pData &= ~(1 << SCK);			//clock = 0, falling edge
		++i;							//next bit
		data = data << 1;
	}
	*pData |= (1 << SS);				//SS = 1 --> not select slave
}

/*****************************************************************
 * @Name	: SPI_Soft_Transmit_1Byte_Slave
 * @Brief	: slave transmit 1 byte
 * @Params	: <1> data: data to receive
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void SPI_Soft_Transmit_1Byte_Slave(uint8_t data) {
	uint8_t bitValue = 0x00;
	uint8_t i = 0;
	volatile uint32_t *pData = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pCheck = (uint32_t *)GPIOD_IDR_ADDR;	//input data register

	while(!(*pCheck & (1 << SS)) && (i < 8)) {	//slave is selected
		if(!(*pCheck & (1 << SCK))) {			//clock = 0
			bitValue = data & 0x80;
			while(!(*pCheck & (1 << SCK)) && !(*pCheck & (1 << SS)));	// wait until rising edge, slave is selected
			if(bitValue > 0)					//send data
				*pData |= (1 << MISO);
			else *pData &= ~(1 << MISO);
			++i;								//next bit
			data = data << 1;
			while(*pCheck & (1 << SCK));		// wait until falling edge then continue
		}
	}
}

/*****************************************************************
 * @Name	: SPI_Soft_Receive_1Byte_Master
 * @Brief	: master receive 1 byte
 * @Params	: <1>
 * 			  <2>
 * @Return	: received data
 *****************************************************************/
uint8_t SPI_Soft_Receive_1Byte_Master() {
	volatile uint32_t *pData = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pInBuf = (uint32_t *)GPIOD_IDR_ADDR; //input data register
	*pData &= ~(1 << SS);				//SS = 0 --> select slave
	uint8_t inputBuff = 0x00;
	uint8_t i = 0;

	while(i < 8) {
		inputBuff = inputBuff << 1;		//next bit, MSB first
		myDelay10us(20);
		*pData |= (1 << SCK);			//generate falling edge
		myDelay10us(20);
		*pData &= ~(1 << SCK);
		inputBuff |= (*pInBuf & (1 << MISO)) >> MISO;	//then reads data on MISO pin
		++i;
	}
	*pData |= (1 << SS);				//SS = 1 --> not select slave
	return inputBuff;					//returns received data
}

/*****************************************************************
 * @Name	: SPI_Soft_Receive_1Byte_Slave
 * @Brief	: slave receive 1 byte
 * @Params	: <1>
 * 			  <2>
 * @Return	: received data
 *****************************************************************/
uint8_t SPI_Soft_Receive_1Byte_Slave() {
	uint8_t inputBuff = 0x00;
	uint8_t i = 0;
	volatile uint32_t *pCheck = (uint32_t *)GPIOD_IDR_ADDR; 	//input data register

	while(!(*pCheck & (1 << SS)) && (i < 8)) {			//slave is selected
		if(*pCheck & (1 << SCK)) {						//clock = 1
			inputBuff = inputBuff << 1;					//next bit, MSB first
			while((*pCheck & (1 << SCK)) && !(*pCheck & (1 << SS)));	// wait until falling edge, slave is selected
			inputBuff |= (*pCheck & (1 << MOSI)) >> MOSI;		//then reads data on MOSI pin
			++i;
			while(!(*pCheck & (1 << SCK)));				// wait until rising edge then continue
		}
	}
	return inputBuff;		//returns received data
}

/*****************************************************************
 * @Name	: TIM6_DAC_IRQHandler
 * @Brief	: ISR of Timer 6, called every 10us to create delay time
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void TIM6_DAC_IRQHandler(void) {
	++count;

	//Clear update interrupt flag
	volatile uint32_t *pRegister = (uint32_t *)TIM6_SR_ADDR;
	*pRegister &= ~(1 << UIF);
 }
