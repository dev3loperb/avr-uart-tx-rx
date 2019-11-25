#define BAUD 9600L
#define UBRRL_VALUE (F_CPU / (BAUD * 16L)) - 1

#include <avr/io.h>
#include <util/delay.h>

void initUSART() {
    UBRRL = UBRRL_VALUE;
    UBRRH = (UBRRL_VALUE) >> 8;
    UCSRB = (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void sendUART(unsigned char value)
{
    while( !(UCSRA & (1 << UDRE)) ) {};
    UDR = value;
}

unsigned char readUART( void )
{
   while( !(UCSRA & ( 1 << RXC)) ) {};
   return UDR;
}

int main(void)
{
    DDRC = 0xFF;
    initUSART();

    while (1) 
    {
        _delay_ms(1000);
        sendUART(0x2F);
        PORTC |= (1 << PORT0);
        _delay_ms(1000);
        sendUART(0x2D);
        PORTC |= (1 << PORT1);
        _delay_ms(1000);
        PORTC = 0;
    }
}
