#include <msp430.h> 

/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer



    P1OUT = 0b00000000;  	// mov.b    #00000000b,&P1OUT
    P1DIR = 0b11111111;  	// mov.b    #11111111b,&P1DIR
    P2DIR = 0b00000000;  	// mov.b    #00000000b,&P2DIR

    int BIT_MASK_DOORS = 0b00001111;
    int BIT_MASK_LOCK = BIT4;
    int Car_Doors = 0;
    int Car_Lock = 0;
    int is_pressed = 0;
    while(1){
    	Car_Doors=P2IN & BIT_MASK_DOORS;

       	// doors can only lock if all doors are closed
		if(Car_Doors == BIT_MASK_DOORS){
			if((P2IN & BIT4) == BIT4){
				if(!is_pressed){
					Car_Lock ^= BIT0;
					is_pressed = 1;
				}
			}else{
				is_pressed = 0;
			}
		}

		// if	car is locked doors all doors are closed and lock alarm is off
		if(Car_Lock){
			P1OUT = ~(BIT_MASK_DOORS | BIT_MASK_LOCK);
		}else{
		//else car P1OUT depends on the input from push buttons and lock alarm is on
			P1OUT = ~Car_Doors | BIT_MASK_LOCK;
		}
    }
}


