#include "ad7265.h"

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

void read_zones(uint16_t *z1, uint16_t *z2, uint16_t *z3, uint16_t *z4, uint16_t *mean_arr){

    for(int i=0; i<BUFFER_SIZE; ++i){
        //read zone 1
        select_adc_channel(0);
        z1[i] = adc_spi_rx();
        mean_arr[0] += (z1[i]/BUFFER_SIZE);

        //read zone 2
        select_adc_channel(1);
        z2[i] = adc_spi_rx();
        mean_arr[1] += (z2[i]/BUFFER_SIZE);

        //read zone 3
        select_adc_channel(2);
        z3[i] = adc_spi_rx();
        mean_arr[2] += (z3[i]/BUFFER_SIZE);

        //read zone 4
        select_adc_channel(3);
        z4[i] = adc_spi_rx();
        mean_arr[3] += (z4[i]/BUFFER_SIZE);

        MicroSecondDelay(1);
    }
}