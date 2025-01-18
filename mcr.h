#ifndef MCR_H
#define MCR_H

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#define TC_PORT     PORTB

//SPI pins
#define TC_SPI_SCK  PB5
#define TC_SPI_MISO PB4
#define TC_ADC_CS   PB2

//Multipexer pins
#define TC_ADC_A0   PB0
#define TC_ADC_A1   PB1
#define TC_ADC_A2   PB2

void GPIO_init();

//SPI pin macros
void mcrSetTC_SPI_SCK();
void mcrClrTC_SPI_SCK();

uint8_t mcrReadTC_SPI_MISO();

void mcrSetTC_ADC_CS();
void mcrClrTC_ADC_CS();

//Multiplexer pin macros
void mcrSetTC_ADC_A0();
void mcrClrTC_ADC_A0();

void mcrSetTC_ADC_A1();
void mcrClrTC_ADC_A1();

void mcrSetTC_ADC_A2();
void mcrClrTC_ADC_A2();

//Delay
void MicroSecondDelay(int DelayCount);

#endif