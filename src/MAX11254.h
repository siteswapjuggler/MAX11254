// MAX11254 library for Arduino
// initial release by Sylvain GARNAVAULT - 2023/03/10

#ifndef MAX11254_h

    #define MAX11254_h
    #include "Arduino.h"
    #include "SPI.h"

    // SPI_CONFIGURATION (p08)
    #define MAX11254_SPI_SPEED       8000000L       // 8 MHz by default on SPI
    #define MAX11254_SPI_MODE        SPI_MODE0      // see SPI diagramm p20

    // READ/WRITE BITS   (p22)
    #define MAX11254_MSBS            0b11000000     // register read/write (see Table 4 p22)
    #define MAX11254_RBIT            0b1            // can be include in getCmd function
    #define MAX11254_WBIT            0b0            // can be include in getCmd function

    // REGISTER MAP      (p38)

    #define MAX11254_STAT_REG        0x00           // R    24 bit
    #define MAX11254_CTRL1_REG       0x01           // R/W  8bit
    #define MAX11254_CTRL2_REG       0x02           // R/W  8bit
    #define MAX11254_CTRL3_REG       0x03           // R/W  8bit
    #define MAX11254_GPIO_CTRL_REG   0x04           // R/W  8bit
    #define MAX11254_DELAY_REG       0x05           // R/W  16bit
    #define MAX11254_CHMAP1_REG      0x06           // R/W  24bit
    #define MAX11254_CHMAP0_REG      0x07           // R/W  24bit
    #define MAX11254_SEQ_REG         0x08           // R/W  8bit
    #define MAX11254_GPO_DIR_REG     0x09           // R/W  8bit
    #define MAX11254_SOC_REG         0x0A           // R/W  24bit
    #define MAX11254_SCGC_REG        0x0D           // R/W  24bit
    #define MAX11254_DATA0_REG       0x0E           // R    24bit
    #define MAX11254_DATA1_REG       0x0F           // R    24bit
    #define MAX11254_DATA2_REG       0x10           // R    24bit
    #define MAX11254_DATA3_REG       0x11           // R    24bit
    #define MAX11254_DATA4_REG       0x12           // R    24bit
    #define MAX11254_DATA5_REG       0x13           // R    24bit



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

            void    writeCTRL1(uint8_t val);
            void    writeCTRL2(uint8_t val);
            void    writeCTRL3(uint8_t val);
            void    writeGPIO_CTRL(uint8_t val);
            void    writeDELAY(uint16_t val);
            void    writeCHMAP0(uint32_t val);
            void    writeCHMAP1(uint32_t val);
            void    writeSEQ(uint8_t val);
        
            void    sendConversionCommand(uint8_t val);

        private:
            uint8_t _cs;                                                    // chip select pin
            uint8_t getRegisterCmdByte(uint8_t reg, bool read = false);     // calculate cmd byte
        
            void write8bitRegister(uint8_t reg, uint8_t val);               // write 8 bit register
            void write16bitRegister(uint8_t reg, uint16_t val);             // write 24 bit register
            void write24bitRegister(uint8_t reg, uint32_t val);             // write 24 bit register
        
            uint8_t  read8bitRegister(uint8_t reg);                         // read 8 bit register
            uint16_t read16bitRegister(uint8_t reg);                        // read 16 bit register
            uint32_t read24bitRegister(uint8_t reg);                        // read 24 bit register
        };

//p49

#endif // MAX11254_h
