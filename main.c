#include "ad7265.h"
#include <stdio.h> // for testing

int main(void){
    
    uint16_t z1_buffer[BUFFER_SIZE] = {0};
    uint16_t z2_buffer[BUFFER_SIZE] = {0};
    uint16_t z3_buffer[BUFFER_SIZE] = {0};
    uint16_t z4_buffer[BUFFER_SIZE] = {0};

    uint16_t zone_means[NUM_ZONES] = {0};
    
    init_adc();

    while(1){
        read_zones(z1_buffer, z2_buffer, z3_buffer, z4_buffer, zone_means);
    }

    return 0;
}
