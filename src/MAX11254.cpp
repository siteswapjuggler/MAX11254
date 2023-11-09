// MAX11254 library for Arduino
// initial release by Sylvain GARNAVAULT - 2023/03/10

#include "MAX11254.h"

////////////////////////
//  INSTANCIATION     //
////////////////////////

MAX11254::MAX11254() {
    }

/////////////////////////
//  PUBLIC METHODS    //
/////////////////////////

void MAX11254::begin(uint8_t cs) {
    _cs = cs;                // choose the chip select pin
    pinMode(_cs,OUTPUT);     // set the pin as output
    digitalWrite(_cs,HIGH);  // set the pin to default HIGH state
    SPI.begin();             // initiate SPI
    }

/////////////////////////
//  READ METHODS    //
/////////////////////////

uint32_t MAX11254::readSTAT() {
    return read24bitRegister(MAX11254_STAT_REG);
    }

uint8_t MAX11254::readCTRL1() {
    return read8bitRegister(MAX11254_CTRL1_REG);
    }

uint8_t MAX11254::readCTRL2() {
    return read8bitRegister(MAX11254_CTRL2_REG);
    }

uint8_t MAX11254::readCTRL3() {
    return read8bitRegister(MAX11254_CTRL3_REG);
    }

uint8_t MAX11254::readSEQ() {
    return read8bitRegister(MAX11254_SEQ_REG);
    }

uint32_t MAX11254::readDATA0() {
    return read24bitRegister(MAX11254_DATA0_REG);
    }

uint32_t MAX11254::readDATA1() {
    return read24bitRegister(MAX11254_DATA1_REG);
    }

uint32_t MAX11254::readDATA2() {
    return read24bitRegister(MAX11254_DATA2_REG);
    }

uint32_t MAX11254::readDATA3() {
    return read24bitRegister(MAX11254_DATA3_REG);
    }

uint32_t MAX11254::readDATA4() {
    return read24bitRegister(MAX11254_DATA4_REG);
    }

uint32_t MAX11254::readDATA5() {
    return read24bitRegister(MAX11254_DATA5_REG);
    }


/////////////////////////
//  WRITE METHODS    //
/////////////////////////

void MAX11254::writeCTRL1(uint8_t val) {
    return write8bitRegister(MAX11254_CTRL1_REG, val);
    }

void MAX11254::writeCTRL2(uint8_t val) {
    return write8bitRegister(MAX11254_CTRL2_REG, val);
    }

void MAX11254::writeCTRL3(uint8_t val) {
    return write8bitRegister(MAX11254_CTRL3_REG, val);
    }

void MAX11254::writeGPIO_CTRL(uint8_t val) {
    return write8bitRegister(MAX11254_GPIO_CTRL_REG, val);
    }

void MAX11254::writeDELAY(uint16_t val) {
    return write16bitRegister(MAX11254_DELAY_REG, val);
    }

void MAX11254::writeCHMAP0(uint32_t val) {
    return write24bitRegister(MAX11254_CHMAP0_REG, val);
    }

void MAX11254::writeCHMAP1(uint32_t val) {
    return write24bitRegister(MAX11254_CHMAP1_REG, val);
    }

void MAX11254::writeSEQ(uint8_t val) {
    return write8bitRegister(MAX11254_SEQ_REG, val);
    }

////////////////////////
//  CONVERSION COMMAND    //
/////////////////////////

void MAX11254::conversionCommand(uint8_t val) {
    // conversion command (see Table 4 p22)
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(0b10000000 | (cmd & 0b111111));
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    }

/////////////////////////
//  PRIVATE METHODS    //
/////////////////////////

uint8_t MAX11254::getRegisterCmdByte(uint8_t reg, bool read) {
    // register read/write (see Table 4 p22)
    return 0b11000000 | (reg << 1) | (read ? 1 : 0);
    }

void MAX11254::write8bitRegister(uint8_t reg, uint8_t val) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg));
    SPI.transfer(val);;
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    }

void MAX11254::write16bitRegister(uint8_t reg, uint16_t val) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg));
    SPI.transfer(val>>8 & 0xFF);
    SPI.transfer(val & 0xFF);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    }
		
void MAX11254::write24bitRegister(uint8_t reg, uint32_t val) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg));
    SPI.transfer(val>>16 & 0xFF);
    SPI.transfer(val>>8 & 0xFF);
    SPI.transfer(val & 0xFF);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    }

uint8_t MAX11254::read8bitRegister(uint8_t reg) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg,true));
    uint8_t result = SPI.transfer(0x00);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return result;
    }

uint16_t MAX11254::read16bitRegister(uint8_t reg) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg,true));
    int16_t result = 0;
    result = result | SPI.transfer(0x00); result = result << 8;
    result = result | SPI.transfer(0x00);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return result;
    }

uint32_t MAX11254::read24bitRegister(uint8_t reg) {
    SPI.beginTransaction(SPISettings(MAX11254_SPI_SPEED, MSBFIRST, MAX11254_SPI_MODE));
    digitalWrite(_cs, LOW);
    SPI.transfer(getCmd(reg,true));
    int32_t result = 0;
    result = result | SPI.transfer(0x00); result = result << 8;
    result = result | SPI.transfer(0x00); result = result << 8;
    result = result | SPI.transfer(0x00);
    digitalWrite(_cs, HIGH);
    SPI.endTransaction();
    return result;
    }
