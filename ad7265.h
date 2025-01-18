#ifndef AD7265_H
#define AD7265_H

#include "mcr.h"

#define TC_ADC_A0_MASK 0x01
#define TC_ADC_A1_MASK 0x02
#define TC_ADC_A2_MASK 0x04
#define TC_SPI_MISO_MASK 0x2000
#define ACD_12_BIT_MASK 0x3FFF

#define NUM_ZONES 4
#define SCK_CYCLES 14
#define BUFFER_SIZE 16

//initialize spi and mux pins
void init_adc();

//Read SPI RX adc data
uint16_t adc_spi_rx();

//Select adc channel
void select_adc_channel(uint8_t channel);

//Read and get mean of thermistor zones
void read_zones(uint16_t *z1, uint16_t *z2, uint16_t *z3, uint16_t *z4, uint16_t *mean_arr);

#endif