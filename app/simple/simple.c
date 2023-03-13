#include "stm32l4xx.h"
#include "stm32l4r9xx.h"

asm (".word 0x20001000");
asm (".word main");

int main() {
    int c;
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);
    GPIOE->MODER = 0xfffffff7;
    GPIOE->OTYPER = 0x00000000;

    while(1) {
        GPIOE->BSRR = (1 <<  17);
        for (c = 0; c < 100000; c++);

        GPIOE->BSRR = (1 <<  1);
        for (c = 0; c < 100000; c++);
    }
}
