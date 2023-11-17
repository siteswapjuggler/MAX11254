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

    // CONVERSION REGISTER

    #define MAX11254_PD_MODE               0b00010000
    #define MAX11254_CALIBRATION_MODE      0b00100000
    #define MAX11254_SEQUENCER_MODE        0b00110000

    #define MAX11254_50SPS                 0b0000
    #define MAX11254_62SPS                 0b0001
    #define MAX11254_100SPS                0b0010
    #define MAX11254_125SPS                0b0011
    #define MAX11254_200SPS                0b0100
    #define MAX11254_250SPS                0b0101
    #define MAX11254_400SPS                0b0110
    #define MAX11254_500SPS                0b0111
    #define MAX11254_800SPS                0b1000
    #define MAX11254_1000SPS               0b1001
    #define MAX11254_1600SPS               0b1010
    #define MAX11254_2000SPS               0b1011
    #define MAX11254_3200SPS               0b1100
    #define MAX11254_4000SPS               0b1101
    #define MAX11254_6400SPS               0b1110
    #define MAX11254_12800SPS              0b1111

    // SEQ REGISTER

    #define MAX11254_SEQ_RDYBEN            0b00000001
    #define MAX11254_SEQ_MDREN             0b00000010
    #define MAX11254_SEQ_GPODREN           0b00000100
    #define MAX11254_SEQ_MODE1             0b00000000
    #define MAX11254_SEQ_MODE2             0b00001000
    #define MAX11254_SEQ_MODE3             0b00010000


    // CTRL1 REGISTER

    #define MAX11254_CTRL1_FORMAT          0b00000100

    #define MAX11254_CTRL1_SCYCLE          0b00000010
    #define MAX11254_CTRL1_CONTSC          0b00000001

    #define MAX11254_CTRL1_CAL_MASK        0b11000000
    #define MAX11254_CTRL1_CAL_SELF        0b00000000
    #define MAX11254_CTRL1_CAL_OFFSET      0b01000000
    #define MAX11254_CTRL1_CAL_FULLSCALE   0b10000000

    #define MAX11254_CTRL1_PD_MASK         0b00110000
    #define MAX11254_CTRL1_PD_NOP          0b00000000
    #define MAX11254_CTRL1_PD_SLEEP        0b00010000
    #define MAX11254_CTRL1_PD_STANDBY      0b00100000
    #define MAX11254_CTRL1_PD_RESET        0b00110000
		
    // CTRL2 REGISTER
		
    #define MAX11254_CTRL2_EXTCLK          0b10000000
    #define MAX11254_CTRL2_CSSEN           0b01000000
    #define MAX11254_CTRL2_LDOEN           0b00100000
    #define MAX11254_CTRL2_LPMODE          0b00010000
    #define MAX11254_CTRL2_PGAEN           0b00001000
		
    #define MAX11254_CTRL2_PGA_MASK        0b00000111
    #define MAX11254_PGA1                  0b000
    #define MAX11254_PGA2                  0b001
    #define MAX11254_PGA4                  0b010
    #define MAX11254_PGA8                  0b011
    #define MAX11254_PGA16                 0b100
    #define MAX11254_PGA32                 0b101
    #define MAX11254_PGA64                 0b110
    #define MAX11254_PGA128                0b111

    // CTRL3 REGISTER
		
    #define MAX11254_CTRL3_GPO_MODE        0b01000000
    #define MAX11254_CTRL3_SYNC_MODE       0b00100000
    #define MAX11254_CTRL3_CALREGSEL       0b00010000
    #define MAX11254_CTRL3_NOSYSG          0b00001000
    #define MAX11254_CTRL3_NOSYSO          0b00000100
    #define MAX11254_CTRL3_NOSCG           0b00000010
    #define MAX11254_CTRL3_NOSCO           0b00000001
		

    class MAX11254 {
        public:
            MAX11254();
						
            void begin(uint8_t cs);
        
            uint32_t readSTAT();
            uint8_t  readCTRL1();
            uint8_t  readCTRL2();
            uint8_t  readCTRL3();
            uint8_t  readSEQ();
            uint32_t readDATA(uint8_t channel);
            int32_t  analogRead(uint8_t channel);   // SEQUENCER MODE 1 : Single-Channel Conversion (p23)


            void    writeCTRL1(uint8_t val);
            void    writeCTRL2(uint8_t val);
            void    writeCTRL3(uint8_t val);
            void    writeGPIO_CTRL(uint8_t val);
            void    writeDELAY(uint16_t val);
            void    writeCHMAP0(uint32_t val);
            void    writeCHMAP1(uint32_t val);
            void    writeSEQ(uint8_t val);
        
            void    sendConversionCommand(uint8_t val);
						
            void 	setPGA(uint8_t gain);
            void 	setSPS(uint8_t SPS);
            uint8_t getSPS(void);

        private:
            uint8_t  _cs;                                                   // chip select pin
            uint32_t _sr;												    // sample rate
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
