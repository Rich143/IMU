#include "common.h"
#include "Timer/Timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

PRIVATE unsigned long milliseconds;

/* Setup a millisecond timer on 8 bit timer 1
 * Use a prescale of 64
 * with F_CPU of 160000 
 * set OCR0A to 249 to generate 1 ms tic
 * OCR0A = (1/desired frequency)/(1/Timer Frequency)-1
*/
tStatus Timer_Init() {
    TCCR0A = _BV(WGM01); // enable ctc mode
    TCCR0B = _BV(CS01) | _BV(CS00); // /64 prescaler
    OCR0A = 249;
    TIMSK0 = _BV(OCIE0A);

    milliseconds = 0;

    sei();

    return SUCCESS;
}

ISR(TIMER0_COMPA_vect) {
    milliseconds++;
}

unsigned long millis() {
    return milliseconds;
}
