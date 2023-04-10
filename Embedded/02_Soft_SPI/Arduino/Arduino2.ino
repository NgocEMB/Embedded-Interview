#define SCK 7
#define MOSI 9
#define SS 11
#define MISO 12
#define MASTER 0
#define SLAVE 1

/*
 * Function prototypes
 */
void SPI_init();  
void SPI_Soft_Transmit_1Byte_Master(uint8_t data);
void SPI_Soft_Transmit_1Byte_Slave(uint8_t data);
uint8_t SPI_Soft_Receive_1Byte_Master();
uint8_t SPI_Soft_Receive_1Byte_Slave();

uint8_t data = 'A';

void setup() {
  Serial.begin(230400);
  SPI_init(MASTER);       //initialize soft sPI
  // SPI_init(SLAVE);
}

/******************************** MAIN FUNCTION *********************************/
void loop() {
  //Test case for SLAVE receive 1 byte data
  #if 0
  data = SPI_Soft_Receive_1Byte_Slave();
  if(data != 0x00) {
    Serial.print("Received data: ");
    Serial.println((char)data);
  }
  #endif

  //Test case for SLAVE transmit 1 byte data
  #if 0
  SPI_Soft_Transmit_1Byte_Slave(data);
  #endif

  //Test case for MASTER receive 1 byte data
	#if 0
	data = SPI_Soft_Receive_1Byte_Master();
  if(data != 0x00) {
	  Serial.print("Received data: ");
    Serial.println((char)data);
    delay(1000);
  }
	#endif

  //Test case for MASTER transmit 1 byte data
	#if 1
	SPI_Soft_Transmit_1Byte_Master(data);
	delay(1000);
	#endif
}

/*****************************************************************
 * @Name	: SPI_init
 * @Brief	: initialize soft SPI, configure GPIO pins as SPI pins
 * @Params: <1> masterOrSlave: SLAVE or MASTER
 * 			    <2>
 * @Return: none
 *****************************************************************/
void SPI_init(uint8_t masterOrSlave) {
  if (masterOrSlave == MASTER) {
    pinMode(SCK, OUTPUT);
    pinMode(MOSI, OUTPUT);
    pinMode(SS, OUTPUT);
    pinMode(MISO, INPUT);

    digitalWrite(SCK, 0);
    digitalWrite(MOSI, 0);
    digitalWrite(SS, 1);
  } else if (masterOrSlave == SLAVE) {
    pinMode(SCK, INPUT);
    pinMode(MOSI, INPUT);
    pinMode(SS, INPUT);
    pinMode(MISO, OUTPUT);

    digitalWrite(MISO, 0);
  }
}

/*****************************************************************
 * @Name	: SPI_Soft_Transmit_1Byte_Master
 * @Brief	: master transmit 1 byte
 * @Params: <1> data: data to send
 * 			    <2>
 * @Return: none
 *****************************************************************/
void SPI_Soft_Transmit_1Byte_Master(uint8_t data) {
  digitalWrite(SS, LOW);            //SS = 0 --> select slave
  uint8_t bitValue = 0x00;
  uint8_t i = 0;

  while (i < 8) {
    bitValue = (data & 0x80) >> 7;  //read MSB bit
    delayMicroseconds(10);
    digitalWrite(SCK, 1);           //clock = 1, rising edge
    digitalWrite(MOSI, bitValue);   //send data
    delayMicroseconds(10);
    digitalWrite(SCK, 0);           //clock = 0, falling edge
    ++i;
    data = data << 1;               //next bit
  }
  digitalWrite(SS, HIGH);           //SS = 1 --> not select slave
}

/*****************************************************************
 * @Name	: SPI_Soft_Transmit_1Byte_Slave
 * @Brief	: slave transmit 1 byte
 * @Params: <1> data: data to receive
 * 			    <2>
 * @Return: none
 *****************************************************************/
void SPI_Soft_Transmit_1Byte_Slave(uint8_t data) {
  uint8_t bitValue = 0x00;
  uint8_t i = 0;
  while (!digitalRead(SS) && (i < 8)) {               //slave is selected
    if (!digitalRead(SCK)) {
      bitValue = (data & 0x80) >> 7;
      while (!digitalRead(SCK) && !digitalRead(SS));  // wait until rising edge, slave is selected
      digitalWrite(MISO, bitValue);                   //send data
      ++i;                                            //next bit
      data = data << 1;
      while(digitalRead(SCK));                        // wait until falling edge then continue
    }
  }
}

/*****************************************************************
 * @Name	: SPI_Soft_Receive_1Byte_Master
 * @Brief	: master receive 1 byte
 * @Params: <1>
 * 			    <2>
 * @Return: received data
 *****************************************************************/
uint8_t SPI_Soft_Receive_1Byte_Master() {
  digitalWrite(SS, LOW);              //SS = 0 --> select slave
  uint8_t inputBuff = 0x00;
  uint8_t i = 0;

  while (i < 8) {
    inputBuff = inputBuff << 1;       //next bit, MSB first
    delayMicroseconds(10);
    digitalWrite(SCK, 1);             //generate falling edge
    delayMicroseconds(10);
    digitalWrite(SCK, 0);
    inputBuff |= digitalRead(MISO);   //then reads data on MISO pin
    ++i;
  }
  digitalWrite(SS, HIGH);             //SS = 1 --> not select slave
  return inputBuff;                   //returns received data
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
  while (!digitalRead(SS) && (i < 8)) {               //slave is selected
    if (digitalRead(SCK)) {                           //clock = 1
      inputBuff = inputBuff << 1;                     //next bit, MSB first
      while (digitalRead(SCK) && !digitalRead(SS));   // wait until falling edge, slave is selected
      inputBuff |= digitalRead(MOSI);                 //then reads data on MOSI pin
      ++i;
      while(!digitalRead(SCK));                       //wait until rising edge then continue
    }
  }
  return inputBuff;                                   //returns received data
}