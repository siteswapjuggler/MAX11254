// MAX11254 library for Arduino
// initial release by Sylvain GARNAVAULT - 2023/03/10

#ifndef MAX11254_h

    #define MAX11254_h
    #include "Arduino.h"
    #include "SPI.h"

    // SPI_CONFIGURATION (p08)
    #define MAX11254_SPI_SPEED       8000000L
    #define MAX11254_SPI_MODE        SPI_MODE0

    // READ/WRITE BITS   (p22)
    #define MAX11254_MSBS            0xC0
    #define MAX11254_RBIT            0b1
    #define MAX11254_WBIT            0b0

    // REGISTER MAP      (p38)

    #define MAX11254_STAT_REG        0x00       // R    24 bit
    #define MAX11254_CTRL1_REG       0x01       // R/W  8bit
    #define MAX11254_CTRL2_REG       0x02       // R/W  8bit
    #define MAX11254_CTRL3_REG       0x03       // R/W  8bit
    #define MAX11254_GPIO_CTRL_REG   0x04       // R/W  8bit
    #define MAX11254_DELAY_REG       0x05       // R/W  16bit
    #define MAX11254_CHMAP1_REG      0x06       // R/W  24bit
    #define MAX11254_CHMAP0_REG      0x07       // R/W  24bit
    #define MAX11254_SEQ_REG         0x08       // R/W  8bit
    #define MAX11254_GPO_DIR_REG     0x09       // R/W  8bit
    #define MAX11254_SOC_REG         0x0A       // R/W  24bit
    #define MAX11254_SCGC_REG        0x0D       // R/W  24bit
    #define MAX11254_DATA0_REG       0x0E       // R    24bit
    #define MAX11254_DATA1_REG       0x0F       // R    24bit
    #define MAX11254_DATA2_REG       0x10       // R    24bit
    #define MAX11254_DATA3_REG       0x11       // R    24bit
    #define MAX11254_DATA4_REG       0x12       // R    24bit
    #define MAX11254_DATA5_REG       0x13       // R    24bit



    class MAX11254 {
        public:
            MAX11254();
            void begin(uint8_t cs);
        
            uint32_t readSTAT();
            uint8_t  readCTRL1();
            uint8_t  readCTRL2();
            uint8_t  readCTRL3();
            uint8_t  readSEQ();
            uint32_t readDATA0();
            uint32_t readDATA1();
            uint32_t readDATA2();
            uint32_t readDATA3();
            uint32_t readDATA4();
            uint32_t readDATA5();

            void     writeCTRL1(uint8_t val);
            void     writeCTRL2(uint8_t val);
            void     writeCTRL3(uint8_t val);
            void     writeSEQ(uint8_t val);
            void     conversionCommand(uint8_t val);

        private:
            uint8_t _cs;                                         // chip select pin
            uint8_t getCmd(uint8_t reg, bool read = false);      // calculate cmd byte
            void write8bitCommand(uint8_t cmd);                  // write 8 bit command
            void write8bitRegister(uint8_t reg, uint8_t val);    // write 8 bit data into a register
            void write24bitRegister(uint8_t reg, uint32_t val);  // write 24 bit data into a register
            uint8_t  read8bitRegister(uint8_t reg);              // read 8 bit data in a specific register
            uint32_t read24bitRegister(uint8_t reg);             // read signed 24 bit data in a specific register
        };

#endif // MAX11254_h
