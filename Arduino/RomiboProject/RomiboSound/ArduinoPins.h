// Map of Arduino pins to avr bit, ddr, port, pin
// Credit Paul Stoffregen for idea
#ifndef ArduinoPins_h
#define ArduinoPins_h

#define PIN_BITNUM(pin) (PIN ## pin ## _BITNUM)
#define PIN_PORTREG(pin) (PIN ## pin ## _PORTREG)
#define PIN_DDRREG(pin) (PIN ## pin ## _DDRREG)
#define PIN_PINREG(pin) (PIN ## pin ## _PINREG)
#ifndef _BV
#define _BV(n) (1<<(n))
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// Mega Arduino

// Two Wire (aka I2C) ports
#define SDA_PIN 20
#define SCL_PIN 21

// SPI port
#define SS_PIN 53
#define MOSI_PIN 51
#define MISO_PIN 50
#define SCK_PIN 52

// bit number for all digital pins
#define PIN0_BITNUM 0
#define PIN1_BITNUM 1
#define PIN2_BITNUM 4
#define PIN3_BITNUM 5
#define PIN4_BITNUM 5
#define PIN5_BITNUM 3
#define PIN6_BITNUM 3
#define PIN7_BITNUM 4
#define PIN8_BITNUM 5
#define PIN9_BITNUM 6
#define PIN10_BITNUM 4
#define PIN11_BITNUM 5
#define PIN12_BITNUM 6
#define PIN13_BITNUM 7
#define PIN14_BITNUM 1
#define PIN15_BITNUM 0
#define PIN16_BITNUM 1
#define PIN17_BITNUM 0
#define PIN18_BITNUM 3
#define PIN19_BITNUM 2
#define PIN20_BITNUM 1
#define PIN21_BITNUM 0
#define PIN22_BITNUM 0
#define PIN23_BITNUM 1
#define PIN24_BITNUM 2
#define PIN25_BITNUM 3
#define PIN26_BITNUM 4
#define PIN27_BITNUM 5
#define PIN28_BITNUM 6
#define PIN29_BITNUM 7
#define PIN30_BITNUM 7
#define PIN31_BITNUM 6
#define PIN32_BITNUM 5
#define PIN33_BITNUM 4
#define PIN34_BITNUM 3
#define PIN35_BITNUM 2
#define PIN36_BITNUM 1
#define PIN37_BITNUM 0
#define PIN38_BITNUM 7
#define PIN39_BITNUM 2
#define PIN40_BITNUM 1
#define PIN41_BITNUM 0
#define PIN42_BITNUM 7
#define PIN43_BITNUM 6
#define PIN44_BITNUM 5
#define PIN45_BITNUM 4
#define PIN46_BITNUM 3
#define PIN47_BITNUM 2
#define PIN48_BITNUM 1
#define PIN49_BITNUM 0
#define PIN50_BITNUM 3
#define PIN51_BITNUM 2
#define PIN52_BITNUM 1
#define PIN53_BITNUM 0
#define PIN54_BITNUM 0
#define PIN55_BITNUM 1
#define PIN56_BITNUM 2
#define PIN57_BITNUM 3
#define PIN58_BITNUM 4
#define PIN59_BITNUM 5
#define PIN60_BITNUM 6
#define PIN61_BITNUM 7
#define PIN62_BITNUM 0
#define PIN63_BITNUM 1
#define PIN64_BITNUM 2
#define PIN65_BITNUM 3
#define PIN66_BITNUM 4
#define PIN67_BITNUM 5
#define PIN68_BITNUM 6
#define PIN69_BITNUM 7

// output register for digital pins
#define PIN0_PORTREG PORTE
#define PIN1_PORTREG PORTE
#define PIN2_PORTREG PORTE
#define PIN3_PORTREG PORTE
#define PIN4_PORTREG PORTG
#define PIN5_PORTREG PORTE
#define PIN6_PORTREG PORTH
#define PIN7_PORTREG PORTH
#define PIN8_PORTREG PORTH
#define PIN9_PORTREG PORTH
#define PIN10_PORTREG PORTB
#define PIN11_PORTREG PORTB
#define PIN12_PORTREG PORTB
#define PIN13_PORTREG PORTB
#define PIN14_PORTREG PORTJ
#define PIN15_PORTREG PORTJ
#define PIN16_PORTREG PORTH
#define PIN17_PORTREG PORTH
#define PIN18_PORTREG PORTD
#define PIN19_PORTREG PORTD
#define PIN20_PORTREG PORTD
#define PIN21_PORTREG PORTD
#define PIN22_PORTREG PORTA
#define PIN23_PORTREG PORTA
#define PIN24_PORTREG PORTA
#define PIN25_PORTREG PORTA
#define PIN26_PORTREG PORTA
#define PIN27_PORTREG PORTA
#define PIN28_PORTREG PORTA
#define PIN29_PORTREG PORTA
#define PIN30_PORTREG PORTC
#define PIN31_PORTREG PORTC
#define PIN32_PORTREG PORTC
#define PIN33_PORTREG PORTC
#define PIN34_PORTREG PORTC
#define PIN35_PORTREG PORTC
#define PIN36_PORTREG PORTC
#define PIN37_PORTREG PORTC
#define PIN38_PORTREG PORTD
#define PIN39_PORTREG PORTG
#define PIN40_PORTREG PORTG
#define PIN41_PORTREG PORTG
#define PIN42_PORTREG PORTL
#define PIN43_PORTREG PORTL
#define PIN44_PORTREG PORTL
#define PIN45_PORTREG PORTL
#define PIN46_PORTREG PORTL
#define PIN47_PORTREG PORTL
#define PIN48_PORTREG PORTL
#define PIN49_PORTREG PORTL
#define PIN50_PORTREG PORTB
#define PIN51_PORTREG PORTB
#define PIN52_PORTREG PORTB
#define PIN53_PORTREG PORTB
#define PIN54_PORTREG PORTF
#define PIN55_PORTREG PORTF
#define PIN56_PORTREG PORTF
#define PIN57_PORTREG PORTF
#define PIN58_PORTREG PORTF
#define PIN59_PORTREG PORTF
#define PIN60_PORTREG PORTF
#define PIN61_PORTREG PORTF
#define PIN62_PORTREG PORTK
#define PIN63_PORTREG PORTK
#define PIN64_PORTREG PORTK
#define PIN65_PORTREG PORTK
#define PIN66_PORTREG PORTK
#define PIN67_PORTREG PORTK
#define PIN68_PORTREG PORTK
#define PIN69_PORTREG PORTK

// direction control register for digital pins
#define PIN0_DDRREG DDRE
#define PIN1_DDRREG DDRE
#define PIN2_DDRREG DDRE
#define PIN3_DDRREG DDRE
#define PIN4_DDRREG DDRG
#define PIN5_DDRREG DDRE
#define PIN6_DDRREG DDRH
#define PIN7_DDRREG DDRH
#define PIN8_DDRREG DDRH
#define PIN9_DDRREG DDRH
#define PIN10_DDRREG DDRB
#define PIN11_DDRREG DDRB
#define PIN12_DDRREG DDRB
#define PIN13_DDRREG DDRB
#define PIN14_DDRREG DDRJ
#define PIN15_DDRREG DDRJ
#define PIN16_DDRREG DDRH
#define PIN17_DDRREG DDRH
#define PIN18_DDRREG DDRD
#define PIN19_DDRREG DDRD
#define PIN20_DDRREG DDRD
#define PIN21_DDRREG DDRD
#define PIN22_DDRREG DDRA
#define PIN23_DDRREG DDRA
#define PIN24_DDRREG DDRA
#define PIN25_DDRREG DDRA
#define PIN26_DDRREG DDRA
#define PIN27_DDRREG DDRA
#define PIN28_DDRREG DDRA
#define PIN29_DDRREG DDRA
#define PIN30_DDRREG DDRC
#define PIN31_DDRREG DDRC
#define PIN32_DDRREG DDRC
#define PIN33_DDRREG DDRC
#define PIN34_DDRREG DDRC
#define PIN35_DDRREG DDRC
#define PIN36_DDRREG DDRC
#define PIN37_DDRREG DDRC
#define PIN38_DDRREG DDRD
#define PIN39_DDRREG DDRG
#define PIN40_DDRREG DDRG
#define PIN41_DDRREG DDRG
#define PIN42_DDRREG DDRL
#define PIN43_DDRREG DDRL
#define PIN44_DDRREG DDRL
#define PIN45_DDRREG DDRL
#define PIN46_DDRREG DDRL
#define PIN47_DDRREG DDRL
#define PIN48_DDRREG DDRL
#define PIN49_DDRREG DDRL
#define PIN50_DDRREG DDRB
#define PIN51_DDRREG DDRB
#define PIN52_DDRREG DDRB
#define PIN53_DDRREG DDRB
#define PIN54_DDRREG DDRF
#define PIN55_DDRREG DDRF
#define PIN56_DDRREG DDRF
#define PIN57_DDRREG DDRF
#define PIN58_DDRREG DDRF
#define PIN59_DDRREG DDRF
#define PIN60_DDRREG DDRF
#define PIN61_DDRREG DDRF
#define PIN62_DDRREG DDRK
#define PIN63_DDRREG DDRK
#define PIN64_DDRREG DDRK
#define PIN65_DDRREG DDRK
#define PIN66_DDRREG DDRK
#define PIN67_DDRREG DDRK
#define PIN68_DDRREG DDRK
#define PIN69_DDRREG DDRK

// input register for digital pins
#define PIN0_PINREG PINE
#define PIN1_PINREG PINE
#define PIN2_PINREG PINE
#define PIN3_PINREG PINE
#define PIN4_PINREG PING
#define PIN5_PINREG PINE
#define PIN6_PINREG PINH
#define PIN7_PINREG PINH
#define PIN8_PINREG PINH
#define PIN9_PINREG PINH
#define PIN10_PINREG PINB
#define PIN11_PINREG PINB
#define PIN12_PINREG PINB
#define PIN13_PINREG PINB
#define PIN14_PINREG PINJ
#define PIN15_PINREG PINJ
#define PIN16_PINREG PINH
#define PIN17_PINREG PINH
#define PIN18_PINREG PIND
#define PIN19_PINREG PIND
#define PIN20_PINREG PIND
#define PIN21_PINREG PIND
#define PIN22_PINREG PINA
#define PIN23_PINREG PINA
#define PIN24_PINREG PINA
#define PIN25_PINREG PINA
#define PIN26_PINREG PINA
#define PIN27_PINREG PINA
#define PIN28_PINREG PINA
#define PIN29_PINREG PINA
#define PIN30_PINREG PINC
#define PIN31_PINREG PINC
#define PIN32_PINREG PINC
#define PIN33_PINREG PINC
#define PIN34_PINREG PINC
#define PIN35_PINREG PINC
#define PIN36_PINREG PINC
#define PIN37_PINREG PINC
#define PIN38_PINREG PIND
#define PIN39_PINREG PING
#define PIN40_PINREG PING
#define PIN41_PINREG PING
#define PIN42_PINREG PINL
#define PIN43_PINREG PINL
#define PIN44_PINREG PINL
#define PIN45_PINREG PINL
#define PIN46_PINREG PINL
#define PIN47_PINREG PINL
#define PIN48_PINREG PINL
#define PIN49_PINREG PINL
#define PIN50_PINREG PINB
#define PIN51_PINREG PINB
#define PIN52_PINREG PINB
#define PIN53_PINREG PINB
#define PIN54_PINREG PINF
#define PIN55_PINREG PINF
#define PIN56_PINREG PINF
#define PIN57_PINREG PINF
#define PIN58_PINREG PINF
#define PIN59_PINREG PINF
#define PIN60_PINREG PINF
#define PIN61_PINREG PINF
#define PIN62_PINREG PINK
#define PIN63_PINREG PINK
#define PIN64_PINREG PINK
#define PIN65_PINREG PINK
#define PIN66_PINREG PINK
#define PIN67_PINREG PINK
#define PIN68_PINREG PINK
#define PIN69_PINREG PINK

#elif defined (__AVR_ATmega644P__)
// Sanguino

#error Sanguino not defined

#else // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
// 168 and 328 Arduinos

// Two Wire (aka I2C) ports
#define SDA_PIN 18
#define SCL_PIN 19

// SPI port
#define SS_PIN 10
#define MOSI_PIN 11
#define MISO_PIN 12
#define SCK_PIN 13

// bit number for digital pins
#define PIN0_BITNUM 0
#define PIN1_BITNUM 1
#define PIN2_BITNUM 2
#define PIN3_BITNUM 3
#define PIN4_BITNUM 4
#define PIN5_BITNUM 5
#define PIN6_BITNUM 6
#define PIN7_BITNUM 7
#define PIN8_BITNUM 0
#define PIN9_BITNUM 1
#define PIN10_BITNUM 2
#define PIN11_BITNUM 3
#define PIN12_BITNUM 4
#define PIN13_BITNUM 5
#define PIN14_BITNUM 0
#define PIN15_BITNUM 1
#define PIN16_BITNUM 2
#define PIN17_BITNUM 3
#define PIN18_BITNUM 4
#define PIN19_BITNUM 5

// output register for all pins
#define PIN0_PORTREG PORTD
#define PIN1_PORTREG PORTD
#define PIN2_PORTREG PORTD
#define PIN3_PORTREG PORTD
#define PIN4_PORTREG PORTD
#define PIN5_PORTREG PORTD
#define PIN6_PORTREG PORTD
#define PIN7_PORTREG PORTD
#define PIN8_PORTREG PORTB
#define PIN9_PORTREG PORTB
#define PIN10_PORTREG PORTB
#define PIN11_PORTREG PORTB
#define PIN12_PORTREG PORTB
#define PIN13_PORTREG PORTB
#define PIN14_PORTREG PORTC
#define PIN15_PORTREG PORTC
#define PIN16_PORTREG PORTC
#define PIN17_PORTREG PORTC
#define PIN18_PORTREG PORTC
#define PIN19_PORTREG PORTC

// direction control register for digital pins
#define PIN0_DDRREG DDRD
#define PIN1_DDRREG DDRD
#define PIN2_DDRREG DDRD
#define PIN3_DDRREG DDRD
#define PIN4_DDRREG DDRD
#define PIN5_DDRREG DDRD
#define PIN6_DDRREG DDRD
#define PIN7_DDRREG DDRD
#define PIN8_DDRREG DDRB
#define PIN9_DDRREG DDRB
#define PIN10_DDRREG DDRB
#define PIN11_DDRREG DDRB
#define PIN12_DDRREG DDRB
#define PIN13_DDRREG DDRB
#define PIN14_DDRREG DDRC
#define PIN15_DDRREG DDRC
#define PIN16_DDRREG DDRC
#define PIN17_DDRREG DDRC
#define PIN18_DDRREG DDRC
#define PIN19_DDRREG DDRC

// input register for digital pins
#define PIN0_PINREG PIND
#define PIN1_PINREG PIND
#define PIN2_PINREG PIND
#define PIN3_PINREG PIND
#define PIN4_PINREG PIND
#define PIN5_PINREG PIND
#define PIN6_PINREG PIND
#define PIN7_PINREG PIND
#define PIN8_PINREG PINB
#define PIN9_PINREG PINB
#define PIN10_PINREG PINB
#define PIN11_PINREG PINB
#define PIN12_PINREG PINB
#define PIN13_PINREG PINB
#define PIN14_PINREG PINC
#define PIN15_PINREG PINC
#define PIN16_PINREG PINC
#define PIN17_PINREG PINC
#define PIN18_PINREG PINC
#define PIN19_PINREG PINC
#endif // defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#endif // ArduinoPins_h
