#include "mcr.h"
#include <stdio.h> // for testing

#define TC_ADC_A0_MASK 0x01
#define TC_ADC_A1_MASK 0x02
#define TC_ADC_A2_MASK 0x04
#define TC_SPI_MISO_MASK 0x80000000
#define TEMP_BIT_MASK    0x3FFC0000
#define CURR_BIT_MASK    0x00003FFC

#define NUM_ZONES 4
#define SCK_CYCLES 32
#define BUFFER_SIZE 16


void init_adc(); //initialize spi and mux pins
uint16_t adc_spi_rx(); //Read SPI RX adc data
void select_adc_channel(uint8_t channel);//Select adc channel
uint16_t read_zone(uint8_t channel, uint16_t z_buffer[], uint16_t curr_buffer[]); //read zone and return mean

uint16_t z1_buffer[BUFFER_SIZE] = {0};
uint16_t z2_buffer[BUFFER_SIZE] = {0};
uint16_t z3_buffer[BUFFER_SIZE] = {0};
uint16_t z4_buffer[BUFFER_SIZE] = {0};

uint16_t curr1_buffer[BUFFER_SIZE] = {0};
uint16_t curr2_buffer[BUFFER_SIZE] = {0};
uint16_t curr3_buffer[BUFFER_SIZE] = {0};
uint16_t curr4_buffer[BUFFER_SIZE] = {0};


uint16_t z1_mean=0, z2_mean=0, z3_mean=0, z4_mean=0;


int main(void){ 
    init_adc();
    while(1){
        MicroSecondDelay(10);  
        z1_mean = read_zone(0, z1_buffer, curr1_buffer);

        MicroSecondDelay(10);
        z2_mean = read_zone(1, z2_buffer, curr2_buffer);

        MicroSecondDelay(10);
        z3_mean = read_zone(2, z3_buffer, curr3_buffer);

        MicroSecondDelay(10);
        z4_mean = read_zone(3, z4_buffer, curr4_buffer);   
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
    
    uint32_t value = 0;
    uint8_t bit_value = 0;
    
    //set cs low
    mcrClrTC_ADC_CS();
    MicroSecondDelay(1);
    
    for(int i=0; i<SCK_CYCLES; ++i){
        mcrClrTC_SPI_SCK();
        mcrSetTC_SPI_SCK();
        bit_value = mcrReadTC_SPI_MISO();
        if(bit_value) 
            value |= (TC_SPI_MISO_MASK >> i);   
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


uint16_t read_zone(uint8_t channel, uint16_t z_buffer[], uint16_t curr_buffer[]){
    
    uint16_t min = UINT16_MAX;
    uint16_t max = 0;
    uint16_t z_sum = 0;

    for(int i=0; i<BUFFER_SIZE; ++i){
        
        select_adc_channel(channel);
        uint32_t data = adc_spi_rx();
        
        z_buffer[i] = (data & TEMP_BIT_MASK) >> 16
        curr_buffer[i] = (data & CURR_BIT_MASK)
        z_sum += z_buffer[i];

        if(z_buffer[i] < min)
            min = z1_buffer[i];
        if(z_buffer[i] > max)
            max = z_buffer[i];  
    }

    z_sum -= min;
    z_sum -= max;

    return (z_sum/(BUFFER_SIZE-2));
}


