#include "mcr.h"
#include <stdio.h> // for testing

#define TC_ADC_A0_MASK 0x01
#define TC_ADC_A1_MASK 0x02
#define TC_ADC_A2_MASK 0x04
#define TC_SPI_MISO_MASK 0x2000
#define ACD_12_BIT_MASK 0x3FFF

#define NUM_ZONES 4
#define SCK_CYCLES 14
#define BUFFER_SIZE 16


void init_adc(); //initialize spi and mux pins
uint16_t adc_spi_rx(); //Read SPI RX adc data
void select_adc_channel(uint8_t channel);//Select adc channel
void read_zones();//Read and get mean of thermistor zones

uint16_t z1_buffer[BUFFER_SIZE] = {0};
uint16_t z2_buffer[BUFFER_SIZE] = {0};
uint16_t z3_buffer[BUFFER_SIZE] = {0};
uint16_t z4_buffer[BUFFER_SIZE] = {0};

uint16_t zone_means[NUM_ZONES] = {0};


int main(void){ 
    init_adc();
    while(1){
        read_zones();
        MicroSecondDelay(1);
    }
    return 0;
}

void init_adc(){
    
    //set cs and clk high
    mcrSetTC_ADC_CS();
    mcrSetTC_SPI_SCK();

    //set multiplexer pins high
    //all set to high since not a defined state
    mcrSetTC_ADC_A0();
    mcrSetTC_ADC_A1();
    mcrSetTC_ADC_A2();
}

uint16_t adc_spi_rx(){
    
    uint16_t value = 0;
    uint8_t bit_value = 0;
    
    //set cs low
    mcrClrTC_ADC_CS();
    MicroSecondDelay(1);
    
    //get adc miso data
    for(int i=0; i<SCK_CYCLES; ++i){
        mcrClrTC_SPI_SCK();

        bit_value = mcrReadTC_SPI_MISO();
        if(bit_value) 
            value |= (TC_SPI_MISO_MASK >> i);

        mcrSetTC_SPI_SCK();
    }

    //set cs high
    MicroSecondDelay(1);
    mcrSetTC_ADC_CS();

    return value;
}

void select_adc_channel(uint8_t ch){
    
    // set mux pins
    (ch & TC_ADC_A0_MASK) ? mcrSetTC_ADC_A0() : mcrClrTC_ADC_A0();
    (ch & TC_ADC_A1_MASK) ? mcrSetTC_ADC_A1() : mcrClrTC_ADC_A1();
    (ch & TC_ADC_A2_MASK) ? mcrSetTC_ADC_A2() : mcrClrTC_ADC_A2();
}

void read_zones(){

    for(int i=0; i<BUFFER_SIZE; ++i){
        //read zone 1
        select_adc_channel(0);
        z1_buffer[i] = adc_spi_rx();
        zone_means[0] += (z1_buffer[i]/BUFFER_SIZE);

        //read zone 2
        select_adc_channel(1);
        z2_buffer[i] = adc_spi_rx();
        zone_means[1] += (z2_buffer[i]/BUFFER_SIZE);

        //read zone 3
        select_adc_channel(2);
        z3_buffer[i] = adc_spi_rx();
        zone_means[2] += (z3_buffer[i]/BUFFER_SIZE);

        //read zone 4
        select_adc_channel(3);
        z4_buffer[i] = adc_spi_rx();
        zone_means[3] += (z4_buffer[i]/BUFFER_SIZE);

        MicroSecondDelay(1);
    }
}
