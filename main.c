#include<avr/io.h>
#include<avr/interrupt.h>

void mTimer(int count);


int main(int argc char *argv[]){

    DDRD = 0xff;

    while(1){

        //another test
        PORTD = 0b01000000; //D5 green
        mTimer(1000);


        PORTD = 0b00010000; //D2 red
        mTimer(1000);


    }


}


void mTimer(int count){

    int i = 0;


    TCCR1B |= _BV(CS10); // Sets bit 0 of the timer counter control register to 1: enables timer with no prescaling

    TCCR1B |= _BV(WGM12); //Enables clear timer on compare mode by writing a 1 to to the WGM12 bit (bit 3) of the TCCR1B register 

    OCR1A = 0x03E8; //Sets the output compare register to 0x03E8 == 1000 in decimal.

    TCNT1 = 0x0000; //Sets initial value of the timer to 0

    //May or may not work
    TIMSK1 |= _BV(OCIE1A); //Sets the OCIE1A bit to 1 in the timer interrupt mask register; enables the timer output compare interrupt 
    //TIMSK1 |= 0x02; 
    //TIMSK1 = TIMSK1 | 0b00000010;

    TIFR1 |= _BV(OCF1A); //OCF1A is automatically cleared when the output compare interrupt is triggered, writing a 1 to this bit 
                        // also does this

    while(i < count){

        if ((TIFR1 & 0x02) == 0x02){

            TIFR1 |= _BV(OCF1A); //Is this even necessary? Shouldn't it clear automatically once the output compare inter. is triggered?
            
            i++;
      
        }
    }

    return;
}
