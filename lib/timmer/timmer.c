#include "timmer.h"
#include "stm32f103xb.h"
delay_init(){
    //habilito clock
    RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
    //detener el cnt para config
    TIM2->CNT=0;
    //cargar PSC
    TIM2->PSC=7;
    //cargar ARR
    TIM2->ARR=0xFFFF;
    //reiniciar CNT
    TIM2->CNT=0;
    //genero UG y limpio UIF
    TIM2->EGR|=TIM_EGR_UG;
    TIM2->SR&=~TIM_SR_UIF;
}
delay_us(uint32_t us){          //logica
    //arranco contador
    TIM2->CR1|=TIM_CR1_CEN;
    //pregunto
    while(TIM2->CNT<us);
}
delay_ms(uint32_t ms){          //logica
    //arranco contador
    TIM2->CR1|=TIM_CR1_CEN;
    //pregunto
    int t=0;
    while(t<ms){
        delay_us(1000);
        t++;
    }
}
timer_init(){
    //habilito clock
    RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
    //detener el cnt para config
    TIM2->CNT=0;
    //cargar PSC
    TIM2->PSC=7;
    //cargar ARR
    TIM2->ARR=0xFFFF;
    //reiniciar CNT
    TIM2->CNT=0;
    //habilitacion de interrupcion
    TIM2->DIER|=TIM_DIER_UIE;
    //genero UG y limpio UIF
    TIM2->EGR|=TIM_EGR_UG;
    TIM2->SR&=~TIM_SR_UIF;
    //habilita IRQ
    NVIC_EnableIRQ(TIM2_IRQn);
}

volatile int overflow;
void TIM2_IRQHandler(){
    if(TIM2->SR&TIM_SR_UIF){
        TIM2->SR&=~TIM_SR_UIF;
        overflow+=(0xFFFF+1);
    }
}

uint32_t timer_millis(){
    //arranco contador
    TIM2->CR1|=TIM_CR1_CEN;
    int t_actual=TIM2->CNT;
    int tiempo=(t_actual+overflow)/1000;
    return tiempo;
}