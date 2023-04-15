//I2C Pins
#define SCL         11
#define SDA         12
#define MASTER      0
#define SLAVE       1
#define SLAVE_ADDR  (uint8_t)0b1010101      /* 7-bit Address of slave */
#define MY_ADDR     (uint8_t)0b0101010      /* 7-bit Address of this device */
#define READ        1                       /* MASTER requests the data */
#define WRITE       0                       /* MASTER sends the data */
#define ACK         0                       /* ACK bit */
#define NACK        1                       /* NOT ACK bit */

#define INPUT_MODE  pinMode(SDA, INPUT)     /* configure SDA pin as input */
#define OUTPUT_MODE pinMode(SDA, OUTPUT)    /* configure SDA pin as output */

//Global variables
uint8_t data = 'A';

/*
 * Function prototypes
 */
void sendAckNackSlave(uint8_t ack);               /* Slave send ack or nack bit */
uint8_t checkStopBit();                           /* Check stop bit */
uint8_t checkStartBit();                          /* Check start bit */
void sendStopBit();                               /* MASTER sends stop bit */
void sendStartBit();                              /* MASTER sends start bit */
void initializeSoftI2C(uint8_t asMaster);         /* initialize soft I2C */
uint8_t softI2CTransmit1ByteMaster(uint8_t data); /* soft I2C transmit 1 byte of Master */
uint8_t softI2CTransmit1ByteSlave(uint8_t data);  /* soft I2C transmit 1 byte of Slave */
uint8_t softI2CReceive1ByteMaster(uint8_t ack);   /* soft I2C receive 1 byte of Master */
uint8_t softI2CReceive1ByteSlave();               /* soft I2C receive 1 byte of Slave */

void setup() {
  Serial.begin(1000000);
  //initialize soft I2C
  initializeSoftI2C(MASTER);
  // initializeSoftI2C(SLAVE);
}

/******************************** MAIN FUNCTION *********************************/
void loop() {
//Test case for SLAVE receive 1 byte data --> initializeSoftI2C(SLAVE)
#if 0
  //first, verify start bit
  if (checkStartBit() == true) {
    data = softI2CReceive1ByteSlave();
    if(MY_ADDR == (data >> 1)) {            //verify address, if true, send ack
      sendAckNackSlave(ACK);
      //receive bytes until encounter stop bit
      while(1) {
        data = softI2CReceive1ByteSlave();
        sendAckNackSlave(ACK);
        Serial.print((char)data);
        if(checkStopBit() == true) {
          break;
        }
      }
      Serial.println();
    }
    else {        //if address is not true
      sendAckNackSlave(NACK);
    }
  }
#endif

//Test case for SLAVE transmit 1 byte data --> initializeSoftI2C(SLAVE)
#if 0
  uint8_t outputBuf[] = "ARDUINO";
  uint8_t length = sizeof(outputBuf) - 1;

  //first, verify start bit
  if (checkStartBit() == true) {
    data = softI2CReceive1ByteSlave();    //receive address and 1 bit R/W from MASTER
    if(MY_ADDR == (data >> 1)) {          //verify address, if true, send ack
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
    else {      //if address is not true
      sendAckNackSlave(NACK);
    }
  }
#endif

//Test case for MASTER receive 1 byte data --> initializeSoftI2C(MASTER)
#if 0
	uint8_t slaveAddRW = (SLAVE_ADDR << 1) + READ;
	uint8_t data[10];
	uint8_t i = 0;

	sendStartBit();
  //send address + R/W bit at first loop
	if(softI2CTransmit1ByteMaster(slaveAddRW) == ACK) {
		while(i < 5) {                                //MASTER sends 5 bits data: STM32
			delayMicroseconds(30);
			data[i] = softI2CReceive1ByteMaster(ACK);   //save every received byte
      Serial.print((char)data[i]);
			++i;    //next byte
		}
	}
  //when finish, send stop bit
	sendStopBit();
	Serial.println();
	delay(1000);
#endif

//Test case for MASTER transmit 1 byte data --> initializeSoftI2C(MASTER)
#if 1
	uint8_t data[] = "0ARDUINO";
  data[0] = (SLAVE_ADDR << 1) + WRITE;
	uint8_t length = sizeof(data);

	sendStartBit();
	//send address + R/W bit at first loop
	for(uint8_t i = 0; i < length; ++i) {
		if(softI2CTransmit1ByteMaster(data[i]) == ACK) {
			if(i == length - 1) {	        //when send last byte
				sendStopBit();
			}
			else delayMicroseconds(30);
		}
		else {                          //when SLAVE send NACK
			sendStopBit();
			break;
		}
	}
	delay(1000);
#endif
}

/*****************************************************************
 * @Name	: initializeSoftI2C
 * @Brief	: initialize soft I2C, configure GPIO pins as I2C pins
 * @Params	: <1> asMaster: SLAVE or MASTER
 * 			  <2>
 * @Return	: none
 *****************************************************************/
void initializeSoftI2C(uint8_t asMaster) {
  if (asMaster == MASTER) {
    //Set pin mode as output/input for SCL, SDA pins
    pinMode(SCL, OUTPUT);  //output
    pinMode(SDA, OUTPUT);  //output
    //when reset/idle, SCL = 1, SDA = 1
    digitalWrite(SCL, 1);
    digitalWrite(SDA, 1);
  } else if (asMaster == SLAVE) {
    //Set pin mode as output/input for SCL, SDA pins
    pinMode(SCL, INPUT);  //input
    pinMode(SDA, INPUT);  //input
  }
}

/*****************************************************************
 * @Name	: softI2CTransmit1ByteMaster
 * @Brief	: master transmit 1 byte
 * @Params: <1> data: data to send
 * 			    <2>
 * @Return: ack/nack from slave
 *****************************************************************/
uint8_t softI2CTransmit1ByteMaster(uint8_t data) {
  uint8_t i = 0;
	uint8_t ack;
  OUTPUT_MODE;                      //set output on SDA pin to send

  while(i < 8) {    
    if(data & 0x80)                 //push data on SDA pin
      digitalWrite(SDA, HIGH);
    else digitalWrite(SDA, LOW);
    digitalWrite(SCL, HIGH);        //clock = 1
    delayMicroseconds(10);
    digitalWrite(SCL, LOW);         //clock = 0
    delayMicroseconds(10);
    ++i;                            //next bit
    data = data << 1;
  }  

  INPUT_MODE;                       //set input on SDA pin to read
  digitalWrite(SCL, HIGH);          //clock = 1
  delayMicroseconds(10);
  ack = digitalRead(SDA);           //read ACK bit
  digitalWrite(SCL, LOW);           //clock = 0

  return ack;
}

/*****************************************************************
 * @Name	: softI2CTransmit1ByteSlave
 * @Brief	: slave transmit 1 byte
 * @Params: <1> data: data to send
 * 			    <2>
 * @Return: ack/nack from master
 *****************************************************************/
uint8_t softI2CTransmit1ByteSlave(uint8_t data) {
  OUTPUT_MODE;                    //set output on SDA pin to send
  uint8_t i = 0;
  uint8_t ack;

  while (i < 8) {
    if(data & 0x80)					      //push data on SDA pin
		 digitalWrite(SDA, HIGH);
		else 
		 digitalWrite(SDA, LOW);
    while(!digitalRead(SCL));     //wait till SCL = 1
    while(digitalRead(SCL));      //wait till SCL = 0
    ++i;                          //next bit
    data = data << 1;
  }
  INPUT_MODE;                     //set input on SDA pin to read
  while(!digitalRead(SCL));       //wait till SCL = 1
  ack = digitalRead(SDA);         //read ack bit on SDA
  while(digitalRead(SCL));        //wait till SCL = 0

  return ack;
}

/*****************************************************************
 * @Name	: softI2CReceive1ByteMaster
 * @Brief	: master receive 1 byte
 * @Params: <1> ack: ACK or NACK bit send to SLAVE
 * 			    <2>
 * @Return: received data
 *****************************************************************/
uint8_t softI2CReceive1ByteMaster(uint8_t ack) {
  uint8_t i = 0;
	uint8_t inputBuf = 0x00;
  INPUT_MODE;

  while(i < 8) {
    inputBuf <<= 1;                 //MSB --> LSB
    digitalWrite(SCL, HIGH);        //clock = 1
    delayMicroseconds(10);
    inputBuf |= digitalRead(SDA);   //read 1 bit on SDA
    digitalWrite(SCL, LOW);         //clock = 0
    delayMicroseconds(10);
    ++i;                            //next bit
  }

  OUTPUT_MODE;
  if(ack == NACK)                   //send nack
    digitalWrite(SDA, HIGH);
  else                              //send ack
    digitalWrite(SDA, LOW);
  digitalWrite(SCL, HIGH);          //clock = 1
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);           //clock = 0
  delayMicroseconds(10);
  INPUT_MODE;                       //release SDA

  return inputBuf;
}

/*****************************************************************
 * @Name	: softI2CReceive1ByteSlave
 * @Brief	: slave receive 1 byte
 * @Params: <1>
 * 			    <2>
 * @Return: received data
 *****************************************************************/
uint8_t softI2CReceive1ByteSlave() {
  INPUT_MODE;
  uint8_t inputBuf = 0x00;
  uint8_t i = 0;


  while (i < 8) {
    inputBuf <<= 1;                 //MSB --> LSB
    while (!digitalRead(SCL));      //wait until SCL rising/high
    delayMicroseconds(2);
    inputBuf |= digitalRead(SDA);   //read 1 bit on SDA
    ++i;                            //next bit
    while (digitalRead(SCL));       //wait until SCL low again
  }
  return inputBuf;
}

/*****************************************************************
 * @Name	: sendStopBit
 * @Brief	: master send stop bit
 * @Params: <1>
 * 			    <2>
 * @Return: none
 *****************************************************************/
void sendStopBit() {
  OUTPUT_MODE;                //set output on SDA pin to send

  //push SDA from low to high when SCL high
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(30);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(10);
} 

/*****************************************************************
 * @Name	: sendStartBit
 * @Brief	: master send start bit
 * @Params: <1>
 * 			    <2>
 * @Return: none
 *****************************************************************/
void sendStartBit() {
  OUTPUT_MODE;                //set output on SDA pin to send

  //pull SDA to low when SCL high
  digitalWrite(SDA, HIGH);
  delayMicroseconds(10);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(10);
  digitalWrite(SDA, LOW);
  delayMicroseconds(10);
  digitalWrite(SCL, LOW);
  delayMicroseconds(10);
}

/*****************************************************************
 * @Name	: checkStartBit
 * @Brief	: slave checks start bit
 * @Params	: <1>
 * 			  <2>
 * @Return	: true - is start bit; false - is not start bit
 *****************************************************************/
uint8_t checkStartBit() {
  INPUT_MODE;                                  //set input on SDA pin to read

  if (digitalRead(SCL) && digitalRead(SDA)) {  //SCL = 1, SDA = 1
    while (digitalRead(SCL)) {                 //SCL = 1
      if (!digitalRead(SDA))                   //SDA falling when SCL = 1 --> start bit
      {
        while (digitalRead(SCL));              //wait until SCL = 0 then continue
        return true;
      }
    }
  }
  return false;
}

/*****************************************************************
 * @Name	: checkStopBit
 * @Brief	: slave checks stop bit
 * @Params: <1> 
 * 			    <2>
 * @Return: true - is stop bit; false - is not stop bit
 *****************************************************************/
uint8_t checkStopBit() {
  INPUT_MODE;                                 //set input on SDA pin to read
  while (!digitalRead(SCL))                   //wait till SCL = 1
  {
    if (digitalRead(SDA)) return false;       //SDA = 1 when SCL = 0 --> is not stop bit
  }
  if (!digitalRead(SDA)) {                    //SDA = 0
    while (digitalRead(SCL)) {                //SCL = 1
      if (digitalRead(SDA)) return true;      //SDA rising when SCL = 1 --> is stop bit
    }
  }
  return false;
}

/*****************************************************************
 * @Name	: sendAckNackSlave
 * @Brief	: slave sends ack or nack bit to MASTER
 * @Params: <1> ack: ACK or NACK to send
 * 			    <2>
 * @Return: none
 *****************************************************************/
void sendAckNackSlave(uint8_t ack) {
  OUTPUT_MODE;                                    //set output on SDA pin to send
  if (ack == ACK) digitalWrite(SDA, ACK);         //put ACK/NACK on SDA pin
  else if (ack == NACK) digitalWrite(SDA, NACK);
  while (!digitalRead(SCL));                      //wait until SCL rising/high
  while (digitalRead(SCL));                       //wait until SCL low again
  INPUT_MODE;                                     //release SDA pin
}
