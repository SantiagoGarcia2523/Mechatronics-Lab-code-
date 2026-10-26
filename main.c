#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "clock.h"
#include "wait.h"
#include "gpio.h"
#include "pwm.h"




#define RED_LED (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 1*4)))
#define RED_LED_MASK    0x00000002
#define GREEN_LED (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 3*4)))
#define GREEN_LED_MASK 0x08
#define BLUE_LED_MASK 0x04
#define BLUE_LED (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 2*4)))


//subroutines
void delay(void);
void coilA_ON(void);
void coilB_ON(void);
void coilC_ON(void);
void coilA_OFF(void);
void coilB_OFF(void);
void coilC_OFF(void);
void coilA_Standby(void);
void coilB_Standby(void);
void coilC_Standby(void);
void coilA_Positive(void);
void coilB_Positive(void);
void coilC_Positive(void);
void coilA_Negative(void);
void coilB_Negative(void);
void coilC_Negative(void);
void coilA_Float(void);
void coilB_Float(void);
void coilC_Float(void);
void commutate(uint8_t state);







int main(void)
{
        initSystemClockTo40Mhz();
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R3;
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R1;
        SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
        _delay_cycles(3);


        initGPIO();
       // pwm_init();
        uint8_t state;

        while(1){
            for (state = 0; state < 6; state++)
                {
                    commutate(state);
                    waitMicrosecond(5000);
                }
        }


	return 0;
}

void delay(void){
    //1s delay
    waitMicrosecond(1000000);
}




void commutate(uint8_t state){
    coilA_Float();
    coilB_Float();
    coilC_Float();

    switch(state){
    // angle 0 degrees
    case 0:
        coilA_Positive();
        coilB_Negative();
        coilC_Float();

        break;

    case 1:
        coilA_Float();
        coilB_Negative();
        coilC_Positive();

        break;

    case 2:
        coilA_Negative();
        coilB_Float();
        coilC_Positive();

        break;

    case 3:
        coilA_Negative();
        coilB_Positive();
        coilC_Float();

        break;
    case 4:
        coilA_Float();
        coilB_Positive();
        coilC_Negative();
        break;
    case 5:
        coilA_Positive();
        coilB_Float();
        coilC_Negative();
        break;
    }
}


//-------------------------------------
//states

//enable high,direction high
void coilA_Positive(void){

    GPIO_PORTC_DATA_R |= COIL_A_DIR;
    GPIO_PORTC_DATA_R |= COIL_A_ENABLE;
}

void coilB_Positive(void){

    GPIO_PORTC_DATA_R |= COIL_B_DIR;
    GPIO_PORTB_DATA_R |= COIL_B_ENABLE;
}
void coilC_Positive(void){

    GPIO_PORTC_DATA_R |= COIL_C_DIR;
    GPIO_PORTB_DATA_R |= COIL_C_ENABLE;
}

//enable high direction low
void coilA_Negative(void){

    GPIO_PORTC_DATA_R &= ~COIL_A_DIR;
    GPIO_PORTC_DATA_R |= COIL_A_ENABLE;
}
void coilB_Negative(void){

    GPIO_PORTC_DATA_R &= ~COIL_B_DIR;
    GPIO_PORTB_DATA_R |= COIL_B_ENABLE;
}

void coilC_Negative(void){

    GPIO_PORTC_DATA_R &= ~COIL_C_DIR;
    GPIO_PORTB_DATA_R |= COIL_C_ENABLE;

}
//disable gpio (enable low) (direction does not matter)
void coilA_Float(void){
    GPIO_PORTC_DATA_R &= ~COIL_A_ENABLE;

}
void coilB_Float(void){
    GPIO_PORTB_DATA_R &= ~COIL_B_ENABLE;
}
void coilC_Float(void){
    GPIO_PORTB_DATA_R &= ~COIL_C_ENABLE;
}

void initHallSensors(void){

}

void readHallState(void){

}


