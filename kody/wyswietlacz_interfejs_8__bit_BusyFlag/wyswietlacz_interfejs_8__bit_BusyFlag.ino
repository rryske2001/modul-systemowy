#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

#define RS PB5 
#define EN PB4 
#define RW PB3 

#define D0 PD0 
#define D1 PD1
#define D2 PD2
#define D3 PD3
#define D4 PD4
#define D5 PD5
#define D6 PD6
#define D7 PD7 

uint16_t seconds = 0;

void lcd_enable(){
  PORTB |= (1<<EN);
  _delay_us(1);
  PORTB &= ~(1<<EN);
  _delay_us(1);
}

void lcd_send(uint8_t data, uint8_t is_data){
  if (is_data) PORTB |= (1<<RS);
  else PORTB &= ~(1<<RS);

  PORTD = data;
  lcd_enable();
  wait_until_BS();
}

void lcd_command(uint8_t cmd){
  lcd_send(cmd, 0);
}

void lcd_data(uint8_t data){ 
  lcd_send(data, 1);
}

bool checkBS(){
    DDRD = 0x00; 
    PORTD = 0xFF; 

    PORTB &= ~(1 << RS);
    PORTB |= (1 << RW); 

    PORTB |= (1<<EN);
    _delay_us(1);

    bool busy = (PIND & (1 << PD7));
    PORTB &= ~(1<<EN);

    DDRD = 0xFF;

    PORTB &= ~(1 << RW); 

    return busy;
}

void wait_until_BS(){
  while(checkBS()==1){
    _delay_us(1);
  }
}

void lcd_init(){
  DDRB |=(1<<RS)|(1<<EN)|(1<<RW);
  DDRD |=(1<<D0)|(1<<D1)|(1<<D2)|(1<<D3)|(1<<D4)|(1<<D5)|(1<<D6)|(1<<D7);
  _delay_ms(40);

  PORTD = 0b00000011 << 4;
  lcd_enable();
  _delay_ms(5);
  
  lcd_enable();
  _delay_us(150);

  lcd_enable();
  wait_until_BS();
  

  lcd_command(0b00111000); 
  lcd_command(0b00001100); 
  lcd_command(0b00000001); 

  lcd_command(0b00000110); 
}

void lcd_set_cursor(uint8_t row, uint8_t col){
  uint8_t pos = 0;
  if(row==0) pos = col;
  else pos = 0b01000000 + col;
  lcd_command(0b10000000 | pos);
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void timer1_init(){
  TCCR1B |= (1<<WGM12)|(1<<CS12)|(1<<CS10); 
  OCR1A = 15624; 
  TIMSK1 |= (1<<OCIE1A);
  sei();
}

int main(void){
  lcd_init();
  timer1_init();
  
  lcd_set_cursor(0, 0);
  lcd_print("Hello World");

  char buffer[16];
  while (1){
    lcd_set_cursor(1,0);
    sprintf(buffer, "%u", seconds);
    lcd_print(buffer);
  }
  
  return 0;
}
ISR(TIMER1_COMPA_vect){
  seconds++;
}
