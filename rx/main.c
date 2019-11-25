#define BAUD 9600L
#define UBRRL_VALUE (F_CPU / (BAUD * 16L)) - 1

#include <avr/io.h>
#include <util/delay.h>

void initUSART() {
    UBRRL = UBRRL_VALUE;
    UBRRH = (UBRRL_VALUE) >> 8;
    UCSRB = (1 << RXEN);
    UCSRC = (1 << URSEL) | (1 <<  UCSZ0) | (1 << UCSZ1);
}

unsigned char readUART()
{
    while( !(UCSRA & (1 << RXC)) ) {};
    return UDR;
}

int main(void)
{
    DDRC = 0xFF;
    initUSART();
    while(1)
    {
        unsigned char receivedValue = readUART();
        if (receivedValue == 0x2D) {
            PORTC = 0xFF;
            _delay_ms(100);
            PORTC = 0;
        }

        if (receivedValue == 0x2F)
        {
            PORTC = 0xFF;
            _delay_ms(250);
            PORTC = 0;
        }
    }
}
