#include <stdint.h>
#include "stm32f4xx.h"

static void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {

    while(1)
    {
        GPIOA->ODR ^= (1 << 5);
        delay(500000);
    }
    
    return 0;
}