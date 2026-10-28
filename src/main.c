#include "stm32f103xb.h"
#include "pwm.h"
#include "adc.h"
int pote = 0, led = 6;
int conversion = 0, valor = 0;

int main(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    adc_init();
    pwm_init(1,1000);

    
    while(1){
        conversion = adc_read(pote);
        valor = (conversion*100)/4095;
        pwm(1,valor);
    }
}