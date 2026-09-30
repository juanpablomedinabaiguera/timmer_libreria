#include "pwm.h"
#include "stm32f103xb.h"
pwm_init(uint8_t canal, uint32_t frec){
    //habilito clock del timmer 3
    RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
    //switcheo en canal
    switch(canal){
        case 1:
                RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                TIM3->CNT=0;

                break;
        case 2:
                RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                TIM3->CNT=0;

                break;
        case 3:
                RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                TIM3->CNT=0;

                break;
        case 4:
                RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                TIM3->CNT=0;

                break;
        default:
                break;
    }

}

pwm(uint8_t canal , uint8_t duty){

}