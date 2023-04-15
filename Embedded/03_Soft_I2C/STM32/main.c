#include <stdint.h>
#include <stdio.h>

//I2C Pins, port D
#define SCL  	0
#define SDA 	2

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
#define GPIODEN					3
#define TIM6EN					4
#define UIE						0
#define UIF						0
#define CEN						0

//Other macros
#define IRQ_NO_TIM6				54						/* IRQ number of Timer 6 */
#define HI_SPEED				3						/* GPIO port output speed: HIGH SPEED */
#define SLAVE_ADDR  			(uint8_t)0b0101010		/* 7-bit Address of slave */
#define MY_ADDR  				(uint8_t)0b1010101		/* 7-bit Address of this device */
#define READ	  				1						/* MASTER requests the data */
#define WRITE	  				0						/* MASTER sends the data */
#define ACK		  				0						/* ACK bit */
#define NACK		  			1						/* NOT ACK bit */
#define true					1
#define false					0
#define MASTER					0
#define SLAVE					1

//Global variables
uint32_t count = 0;

/*
 * Function prototypes
 */
void sendAckNackSlave(uint8_t ack);					/* Slave send ack or nack bit */
uint8_t checkStopBit();								/* Check stop bit */
uint8_t checkStartBit();							/* Check start bit */
void outputMode();									/* configure SDA pin as output */
void inputMode();									/* configure SDA pin as input */
void sendStopBit();									/* MASTER sends stop bit */
void sendStartBit();								/* MASTER sends start bit */
void initializeSoftI2C(uint8_t asMaster);			/* initialize soft I2C */
void initializeTimer6();							/* initialize Timer 6 */
void myDelay10us(uint32_t time);					/* delay 10us */
uint8_t softI2CTransmit1ByteMaster(uint8_t data);	/* soft I2C transmit 1 byte of Master */
uint8_t softI2CTransmit1ByteSlave(uint8_t data);	/* soft I2C transmit 1 byte of Slave */
uint8_t softI2CReceive1ByteMaster(uint8_t ack);		/* soft I2C receive 1 byte of Master */
uint8_t softI2CReceive1ByteSlave();					/* soft I2C receive 1 byte of Slave */

/******************************** MAIN FUNCTION *********************************/
int main(void)
{
	//1. Configure GPIOD pins as I2C pins
	initializeSoftI2C(MASTER);
	initializeSoftI2C(SLAVE);

	//2. Configure Timer 6 for delay/clock functionality, only when this device is a MASTER
//	initializeTimer6();

	while(1) {
		/*
		 * Test case for MASTER transmit 1 byte data
		 * Steps: initializeSoftI2C(MASTER), turn on initializeTimer6()
		 */
		#if 0
		uint8_t data[] = {(SLAVE_ADDR << 1) + WRITE, 'S', 'T', 'M', '3', '2'};
		uint8_t length = sizeof(data);

		sendStartBit();
		//send address + R/W bit at first loop
		for(uint8_t i = 0; i < length; ++i) {
			if(softI2CTransmit1ByteMaster(data[i]) == ACK) {
				if(i == length - 1) {	//when send last byte
					sendStopBit();
				}
				else myDelay10us(30);
			}
			else {						//when SLAVE send NACK
				sendStopBit();
				break;
			}
		}
		myDelay10us(1000000);
		#endif

		/*
		 * Test case for MASTER receive 1 byte data
		 * Steps: initializeSoftI2C(MASTER), turn on initializeTimer6()
		 */
		#if 0
		uint8_t slaveAddRW = (SLAVE_ADDR << 1) + READ;
		uint8_t data[10];
		uint8_t i = 0;

		sendStartBit();
		//send address + R/W bit at first loop
		if(softI2CTransmit1ByteMaster(slaveAddRW) == ACK) {
			while(i < 7) {				//SLAVE sends 7 bits data: ARDUINO
				myDelay10us(30);
				data[i] = softI2CReceive1ByteMaster(ACK);	//save every received byte
				++i;	//next byte
			}

		}
		//when finish, send stop bit
		sendStopBit();
		data[i] = '\0';
		printf("Received data: %s\n", data);
		myDelay10us(1000000);
		#endif

		/*
		 * Test case for SLAVE transmit 1 byte data
		 * Steps: initializeSoftI2C(SLAVE), turn off initializeTimer6()
		 */
		#if 0
		uint8_t outputBuf[] = "STM32";
		uint8_t length = sizeof(outputBuf) - 1;

		//first, verify start bit
		if (checkStartBit() == true) {
			uint8_t data = softI2CReceive1ByteSlave();		//receive address and 1 bit R/W from MASTER
			if(MY_ADDR == (data >> 1)) {					//verify address, if true, send ack
				sendAckNackSlave(ACK);
				//send data to MASTER
				for(uint8_t i = 0; i < length; ++i) {
					if(softI2CTransmit1ByteSlave(outputBuf[i]) == NACK) {
						break;
					}
					if(checkStopBit() == true) {
						break;
					}
				}
			}
			else {		//if address is not true
				sendAckNackSlave(NACK);
			}
		}
		#endif

		/*
		 * Test case for SLAVE receive 1 byte data
		 * Steps: initializeSoftI2C(SLAVE), turn off initializeTimer6()
		 */
		#if 1
		uint8_t i = 0;
		uint8_t verifyAddr;
		uint8_t data[10];

		//first, verify start bit
		if (checkStartBit() == true) {
			verifyAddr = softI2CReceive1ByteSlave();
			if(MY_ADDR == (verifyAddr >> 1)) {				//verify address, if true, send ack
				sendAckNackSlave(ACK);
				//receive bytes until encounter stop bit
				while(1) {
					data[i++] = softI2CReceive1ByteSlave();
					sendAckNackSlave(ACK);
					if(checkStopBit() == true) {
						break;
					}
				}
				data[i] = '\0';
				printf("Received data: %s\n", data);
			}
			else {			//if address is not true
				sendAckNackSlave(NACK);
			}
		}
		#endif
	}
}

/*****************************************************************
 * @Name	: outputMode
 * @Brief	: configure SDA pin as output
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void outputMode() {
	volatile uint32_t *pRegister;
	//1. Configure to output
	pRegister = (uint32_t *)GPIOD_MODER_ADDR;		//configure mode
	*pRegister |= (1 << (SDA * 2));
	pRegister = (uint32_t *)GPIOD_OSPEEDR_ADDR;		//configure speed
	*pRegister |= (HI_SPEED << (SDA * 2));
	pRegister = (uint32_t *)GPIOD_OTYPER_ADDR;		//Set output type: open-drain
	*pRegister |= (1 << SDA);
}

/*****************************************************************
 * @Name	: inputMode
 * @Brief	: configure SDA pin as input
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void inputMode() {
	volatile uint32_t *pRegister;
	//1. Configure to input
	pRegister = (uint32_t *)GPIOD_MODER_ADDR;		//configure mode
	*pRegister &= ~(1 << (SDA * 2));
	pRegister = (uint32_t *)GPIOD_PUPDR_ADDR;		//configure no pull-up pull-down
	*pRegister &= ~(1 << (SDA * 2));
}

/*****************************************************************
 * @Name	: initializeSoftI2C
 * @Brief	: initialize soft I2C, configure GPIO pins as I2C pins
 * @Params	: <1> asMaster: SLAVE or MASTER
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void initializeSoftI2C(uint8_t asMaster) {
	volatile uint32_t *pRegister;

	//Enable peripheral clock
	pRegister = (uint32_t *)RCC_AHB1ENR_ADDR;
	*pRegister |= (1 << GPIODEN);

	if(asMaster == MASTER) {
		//Set pin mode as output/input for SCL, SDA pins
		pRegister = (uint32_t *)GPIOD_MODER_ADDR;
		*pRegister |= (1 << (SCL * 2));		//output
		*pRegister |= (1 << (SDA * 2));		//output

		//Set output type: open-drain
		pRegister = (uint32_t *)GPIOD_OTYPER_ADDR;
		*pRegister |= (1 << SCL);
		*pRegister |= (1 << SDA);

		//Set output speed
		pRegister = (uint32_t *)GPIOD_OSPEEDR_ADDR;
		*pRegister |= (HI_SPEED << (SCL * 2));
		*pRegister |= (HI_SPEED << (SDA * 2));

		//when reset/idle, SCL = 1, SDA = 1
		pRegister = (uint32_t *)GPIOD_ODR_ADDR;
		*pRegister |= (1 << SCL);
		*pRegister |= (1 << SDA);
	}
	else if(asMaster == SLAVE) {
		//Set pin mode as output/input for SCL, SDA pins
		pRegister = (uint32_t *)GPIOD_MODER_ADDR;
		*pRegister &= ~(1 << (SCL * 2));	//input
		*pRegister &= ~(1 << (SDA * 2));	//input

		//Set pull-up
		pRegister = (uint32_t *)GPIOD_PUPDR_ADDR;
		*pRegister &= ~(1 << (SCL * 2));
		*pRegister &= ~(1 << (SDA * 2));
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
 * @Name	: sendAckNackSlave
 * @Brief	: slave sends ack or nack bit to MASTER
 * @Params	: <1> ack: ACK or NACK to send
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void sendAckNackSlave(uint8_t ack) {
	volatile uint32_t *pSDA = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pSCL = (uint32_t *)GPIOD_IDR_ADDR;	//input data register

	outputMode();					//set output on SDA pin to send
	if(ack == ACK)					//put ACK/NACK on SDA pin
		*pSDA &= ~(1 << SDA);
	else if(ack == NACK)
		*pSDA |= (1 << SDA);
	while(!(*pSCL & (1 << SCL)));	//wait until SCL rising/high
	while(*pSCL & (1 << SCL));		//wait until SCL low again
	inputMode();					//release SDA pin
}

/*****************************************************************
 * @Name	: checkStopBit
 * @Brief	: slave checks stop bit
 * @Params	: <1>
 * 			  <2>
 * @Return	: true - is stop bit; false - is not stop bit
 *****************************************************************/
uint8_t checkStopBit() {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_IDR_ADDR;
	inputMode();									//set input on SDA pin to read

	while(!(*pReg & (1 << SCL))) {
		if(*pReg & (1 << SDA)) return false;		//SDA = 1 when SCL = 0 --> is not stop bit
	}
	if(!(*pReg & (1 << SDA))) {						//SDA = 0
		while(*pReg & (1 << SCL)) {					//SCL = 1
			if(*pReg & (1 << SDA)) return true;		//SDA rising when SCL = 1 --> is stop bit
		}
	}
	return false;
}

/*****************************************************************
 * @Name	: checkStartBit
 * @Brief	: slave checks start bit
 * @Params	: <1>
 * 			  <2>
 * @Return	: true - is start bit; false - is not start bit
 *****************************************************************/
uint8_t checkStartBit() {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_IDR_ADDR;
	inputMode();	//set input on SDA pin to read

	if((*pReg & (1 << SCL)) && (*pReg & (1 << SDA))) {	//SCL = 1, SDA = 1
		while(*pReg & (1 << SCL)) {						//SCL = 1
			if(!(*pReg & (1 << SDA))) {					//SDA falling when SCL = 1 --> start bit
				while(*pReg & (1 << SCL));				//wait until SCL = 0 then continue
				return true;
			}
		}
	}
	return false;
}

/*****************************************************************
 * @Name	: sendStartBit
 * @Brief	: master send start bit
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void sendStartBit() {
	uint32_t *pReg = (uint32_t *)GPIOD_ODR_ADDR;
	outputMode();				//set output on SDA pin to send

	//pull SDA to low when SCL high
	*pReg |= (1 << SDA);
	myDelay10us(10);
	*pReg |= (1 << SCL);
	myDelay10us(10);
	*pReg &= ~(1 << SDA);
	myDelay10us(10);
	*pReg &= ~(1 << SCL);
	myDelay10us(10);
}

/*****************************************************************
 * @Name	: sendStopBit
 * @Brief	: master send stop bit
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void sendStopBit() {
	uint32_t *pReg = (uint32_t *)GPIOD_ODR_ADDR;
	outputMode();				//set output on SDA pin to send

	//push SDA from low to high when SCL high
	*pReg &= ~(1 << SDA);
	myDelay10us(10);
	*pReg |= (1 << SCL);
	myDelay10us(30);
	*pReg |= (1 << SDA);
	myDelay10us(10);
}

/*****************************************************************
 * @Name	: softI2CTransmit1ByteMaster
 * @Brief	: master transmit 1 byte
 * @Params	: <1> data: data to send
 * 			  <2>
 * @Return	: ack/nack from slave
 *****************************************************************/
uint8_t softI2CTransmit1ByteMaster(uint8_t data) {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pACK = (uint32_t *)GPIOD_IDR_ADDR;	//input data register
	uint8_t i = 0;
	uint8_t ack;

	outputMode();						//set output on SDA pin to send

	while(i < 8) {
		if(data & 0x80)					//push data on SDA pin
			*pReg |= (1 << SDA);
		else *pReg &= ~(1 << SDA);

		*pReg |= (1 << SCL);			//clock = 1
		myDelay10us(10);
		*pReg &= ~(1 << SCL);			//clock = 0
		myDelay10us(10);
		++i;							//next bit
		data = data << 1;
	}

	inputMode();						//set input on SDA pin to read
	*pReg |= (1 << SCL);				//clock = 1
	myDelay10us(10);
	ack = (*pACK & (1 << SDA)) >> SDA;	//read ACK bit
	*pReg &= ~(1 << SCL);				//clock = 0

	return ack;
}

/*****************************************************************
 * @Name	: softI2CTransmit1ByteSlave
 * @Brief	: slave transmit 1 byte
 * @Params	: <1> data: data to send
 * 			  <2>
 * @Return	: ack/nack from master
 *****************************************************************/
uint8_t softI2CTransmit1ByteSlave(uint8_t data) {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pInput = (uint32_t *)GPIOD_IDR_ADDR;	//input data register
	uint8_t i = 0;
	uint8_t ack;
	outputMode();							//set output on SDA pin to send

	while(i < 8) {
		if(data & 0x80)						//push data on SDA pin
			*pReg |= (1 << SDA);
		else
			*pReg &= ~(1 << SDA);
		while(!(*pInput & (1 << SCL)));		//wait till SCL = 1
		while(*pInput & (1 << SCL));		//wait till SCL = 0
		++i;
		data = data << 1;					//next bit
	}

	inputMode();							//set input on SDA pin to read
	while(!(*pInput & (1 << SCL)));			//wait till SCL = 1
	ack = (*pInput & (1 << SDA)) >> SDA;	//read ack bit on SDA
	while(*pInput & (1 << SCL));			//wait till SCL = 0

	return ack;
}

/*****************************************************************
 * @Name	: softI2CReceive1ByteMaster
 * @Brief	: master receive 1 byte
 * @Params	: <1> ack: ACK or NACK bit send to SLAVE
 * 			  <2>
 * @Return	: received data
 *****************************************************************/
uint8_t softI2CReceive1ByteMaster(uint8_t ack) {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_ODR_ADDR;	//output data register
	volatile uint32_t *pInput = (uint32_t *)GPIOD_IDR_ADDR;	//input data register
	uint8_t i = 0;
	uint8_t inputBuf = 0x00;
	inputMode();

	while(i < 8) {
		inputBuf <<= 1;					//MSB --> LSB
		*pReg |= (1 << SCL);			//clock = 1
		myDelay10us(10);
		inputBuf |= (*pInput & (1 << SDA)) >> SDA;		//read 1 bit on SDA
		*pReg &= ~(1 << SCL);			//clock = 0
		myDelay10us(10);
		++i;							//next bit
	}
	outputMode();
	if(ack == NACK)
		*pReg |= (1 << SDA);			//send nack
	else if(ack == ACK)
		*pReg &= ~(1 << SDA);			//send ack
	*pReg |= (1 << SCL);				//clock = 1
	myDelay10us(10);
	*pReg &= ~(1 << SCL);				//clock = 0
	myDelay10us(10);
	inputMode();						//release SDA

	return inputBuf;
}

/*****************************************************************
 * @Name	: softI2CReceive1ByteSlave
 * @Brief	: slave receive 1 byte
 * @Params	: <1>
 * 			  <2>
 * @Return	: received data
 *****************************************************************/
uint8_t softI2CReceive1ByteSlave() {
	volatile uint32_t *pReg = (uint32_t *)GPIOD_IDR_ADDR;
	inputMode();
	uint8_t inputBuf = 0x00;
	uint8_t i = 0;

	while(i < 8) {
		inputBuf <<= 1;  							//MSB --> LSB
		while(!(*pReg & (1 << SCL)));				//wait until SCL rising/high
		//delay 2us
		inputBuf |= (*pReg & (1 << SDA)) >> SDA;	//read 1 bit on SDA
		++i;										//next bit
		while(*pReg & (1 << SCL));					//wait until SCL low again
	}
	return inputBuf;
}

/*****************************************************************
 * @Name	: TIM6_DAC_IRQHandler
 * @Brief	: ISR of Timer 6, called every 10us to create delay time
 * @Params	: <1>
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void TIM6_DAC_IRQHandler(void) {
	++count;		//used in delay function

	//Clear update interrupt flag
	volatile uint32_t *pRegister = (uint32_t *)TIM6_SR_ADDR;
	*pRegister &= ~(1 << UIF);
}
