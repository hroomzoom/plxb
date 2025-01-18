#include "mcr.h"

void GPIO_init(){
    //Set SPI pins
    DDRB |=  (1 << TC_SPI_SCK);
    DDRB &= ~(1 << TC_SPI_MISO);
    DDRB |=  (1 << TC_ADC_CS);

    //Set Multiplexer pins
    DDRB |=  (1 << TC_ADC_A0);
    DDRB |=  (1 << TC_ADC_A1);
    DDRB |=  (1 << TC_ADC_A2);
}

//SPI pin macros
void mcrSetTC_SPI_SCK(){
    TC_PORT |= (1 << TC_SPI_SCK);
}
void mcrClrTC_SPI_SCK(){
    TC_PORT &= ~(1 << TC_SPI_SCK);
}

uint8_t mcrReadTC_SPI_MISO(){
    if(TC_PORT & ( 1 << TC_SPI_MISO))
        return 1;
    else
        return 0;
}

void mcrSetTC_ADC_CS(){
    TC_PORT |= (1 << TC_ADC_CS);
}
void mcrClrTC_ADC_CS(){
    TC_PORT &= ~(1 << TC_ADC_CS);
}

//Multiplexer pin macros
void mcrSetTC_ADC_A0(){
    TC_PORT |= (1 << TC_ADC_A0);
}
void mcrClrTC_ADC_A0(){
    TC_PORT &= ~(1 << TC_ADC_A0);
}

void mcrSetTC_ADC_A1(){
    TC_PORT |= (1 << TC_ADC_A1);
}
void mcrClrTC_ADC_A1(){
    TC_PORT &= ~(1 << TC_ADC_A1);
}

void mcrSetTC_ADC_A2(){
    TC_PORT |= (1 << TC_ADC_A2);
}
void mcrClrTC_ADC_A2(){
    TC_PORT &= ~(1 << TC_ADC_A2);
}

//Delay
void MicroSecondDelay(int DelayCount){
    for(int i=0; i<DelayCount; ++i)
        _delay_us(1); 
}