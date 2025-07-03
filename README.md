# MAX6675 + I2C LCD on 8051 using Bit-Banged SPI & I2C

This project interfaces a MAX6675 thermocouple sensor (SPI) with a 16x2 I2C LCD using an 8051 microcontroller.  
All protocols (SPI & I2C) are implemented manually via bit-banging in Embedded C (Keil).

## Key Concepts
- Bit-banged SPI for MAX6675
- Bit-banged I2C for 16x2 LCD
- Written in Embedded C for 8051

## Output
Displays temperature with decimal precision on the I2C LCD.
