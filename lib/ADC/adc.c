#include "adc.h"
#include "stm32f103xb.h"
void adc_init(){
    //habilito clocks
    RCC-> APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_ADC1EN;
    //enciendo el ADC
    ADC1-> CR2 |= ADC_CR2_ADON;
    for(int i=0;i<1000;i++);
    //reinicio registros
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while(ADC1->CR2 & ADC_CR2_RSTCAL);
    //calibracion
    ADC1->CR2 |= ADC_CR2_CAL;
    while(ADC1->CR2 & ADC_CR2_CAL);
    //defino cómo se dispara una conversión regular
    ADC1->CR2 |= ADC_CR2_EXTSEL;
    ADC1->CR2 |= ADC_CR2_EXTTRIG;
}
int adc_read(unsigned int canal){
    //segun que canal este usando, voy a poner ese pin como entrada analogica(poner todo en 0)
    if(canal<8) GPIOA -> CRL &=~(0XF<<(canal*4));
    else        GPIOB -> CRL &=~(0XF<<((canal%2)*4));
    //pongo en 111 el tiempo de muestreo en el canal que este usando
    ADC1->SMPR2 |= (0b111 <<(canal*3));
    //para q se haga la conversion primero
    ADC1->SQR3|=canal;
    //empezar la conversion SWSTART
    ADC1->CR2 |= ADC_CR2_SWSTART;
    //espero a q termine la conversion EOC
    ADC1->SR |= ADC_SR_EOC;
    while(!(ADC1->SR & ADC_SR_EOC));
    //retornar la conversion DR
    return ADC1->DR;
}