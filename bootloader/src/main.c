#include <stdint.h>
#include "stm32f4xx.h"

void jump_application(void);


static void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop");
    }
}

int main(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->MODER &= ~(0x3 << (5 * 2));
    GPIOA->MODER |=  (0x1 << (5 * 2));

    GPIOA->ODR ^= (1 << 5);

    delay(5000000);

    jump_application();

    return 0;
}

void jump_application(void)
{
    __disable_irq();

    void (*app_reset_handler)(void) = (void *) (* ((volatile uint32_t *) (0x08008000 + 4U)));

    __set_MSP(*((volatile uint32_t*) 0x08008000));

    app_reset_handler();
}