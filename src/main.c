#include <avr/io.h>
#include <util/delay.h>

void burst() {
    for(uint8_t i = 0; i < 21; i++) {
        PORTB |= 1<<PB4;
        _delay_us(13);
        PORTB &= ~(1<<PB4);
        _delay_us(13);
    }
}

void burst2() {
    for(uint16_t i = 0; i < 342; i++) {
        PORTB |= 1<<PB4;
        _delay_us(13);
        PORTB &= ~(1<<PB4);
        _delay_us(13);
    }
}

void send0() {
    burst();
    _delay_us(500.0);
}

void send1() {
    burst();
    _delay_us(1600.0);
}

void sendbyte(uint8_t b) {
    for (uint8_t i = 0; i < 8; i++) {
        if (b & 1) {
            send1();
        } else {
            send0();
        }
        b /= 2;
    }
}

void send_comm(uint8_t address, uint8_t command) {
    burst2();
    _delay_us(4500);
    sendbyte(address);
    sendbyte(~address);
    sendbyte(command);
    sendbyte(~command);
    burst();
}

int main(void) {
    // Set up Port B pin 4 mode to output
    DDRB = 1<<DDB4;

    // Enable clock prescaler change
    //CLKPR |= 1<<CLKPCE;
    // Set clock prescaler to 4, resulting in 1.2MHz clock frequency
    //CLKPR = 1<<CLKPS1;

    while(1) {
        send_comm(0xFF, 0b11110000);
        for(int i =0;i<5;i++){
            _delay_ms(1000.0);
        }
    }
}
