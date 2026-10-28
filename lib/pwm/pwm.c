#include "pwm.h"
#include "stm32f103xb.h"
void pwm_init(uint8_t canal, uint32_t frec){
        //habilito clock del timmer 3
        RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;
        //configuro
        TIM3->PSC = 7;
        TIM3->ARR = ((1000000/frec)-1);
        TIM3->EGR |= TIM_EGR_UG;
        TIM3->CR1 |= TIM_CR1_CEN;
        //switcheo en canal
        switch(canal){
                case 1:
                        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                        GPIOA->CRL &=~ (0xF<<(6)*4);
                        GPIOA->CRL |= (0xB<<(6)*4);
                        TIM3->CCMR1 &=~ (0b111<<4);
                        TIM3->CCMR1 |= (0b110<<4);
                        TIM3->CCER |= TIM_CCER_CC1E;
                        break;
                case 2:
                        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
                        GPIOA->CRL &=~ (0xF<<(7)*4);
                        GPIOA->CRL |= (0xB<<(7)*4);
                        TIM3->CCMR1 &=~ (0b111<<12);
                        TIM3->CCMR1 |= (0b110<<12);
                        TIM3->CCER |= TIM_CCER_CC2E;
                        break;
                case 3:
                        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                        GPIOB->CRL &=~ (0xF<<(0)*4);
                        GPIOB->CRL |= (0xB<<(0)*4);
                        TIM3->CCMR2 &=~ (0b111<<4);
                        TIM3->CCMR2 |= (0b110<<4);
                        TIM3->CCER |= TIM_CCER_CC3E;
                        break;
                case 4:
                        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
                        GPIOB->CRL &=~ (0xF<<(1)*4);
                        GPIOB->CRL |= (0xB<<(1)*4);
                        TIM3->CCMR2 &=~ (0b111<<12);
                        TIM3->CCMR2 |= (0b110<<12);
                        TIM3->CCER |= TIM_CCER_CC4E;
                        break;
                default:
                        break;
        }
}

void pwm(uint8_t canal , uint8_t duty){
        if(duty>100) duty = 100;
        if(canal==1)             TIM3->CCR1 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==2)        TIM3->CCR2 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==3)        TIM3->CCR3 = (((TIM3->ARR+1)*duty)/100);
        else if(canal==4)        TIM3->CCR4 = (((TIM3->ARR+1)*duty)/100);
}