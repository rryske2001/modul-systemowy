#include <avr/io.h>
#include <util/delay.h>

// Adres PCF8574N (ustawiony wedlug ustawienia pinow A0, A1, A2 na układzie)
#define PCF8574_ADDRESS 0x20

//Definicje pinow uzytych w PCF8574
#define D0 0 //P0
#define D1 1
#define D2 2
#define D3 3
#define D4 4
#define D5 5
#define D6 6
#define D7 7 //P7

// Funkcja inicjalizujaca magistralę I2C
void I2C_Init() {
    // Ustawienie predkosci magistrali I2C na 100kHz (dla zegara 16MHz)
    TWSR = 0x00; // Preskaler = 1
    TWBR = 0x48; // Predkosc = 16MHz / (16 + 2*TWBR*Prescaler) -> 100kHz
    TWCR = (1 << TWEN); // Wlaczenie TWI
}

// Funkcja rozpoczęcia transmisji I2C
void I2C_Start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Start
    while (!(TWCR & (1 << TWINT))); // Czekaj na zakonczenie transmisji
}

// Funkcja zatrzymania transmisji I2C
void I2C_Stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Stop
}

// Funkcja wysyłania danych przez I2C
void I2C_Write(uint8_t data) {
    TWDR = data; // Ładuj dane do rejestru
    TWCR = (1 << TWEN) | (1 << TWINT); // Rozpocznij transmisje
    while (!(TWCR & (1 << TWINT))); // Czekaj na zakonczenie transmisji
}

// Funkcja komunikacji z PCF8574 - zapis wartosci na piny
void PCF8574_Write(uint8_t data) {
    I2C_Start();
    I2C_Write(PCF8574_ADDRESS << 1); // wyslanie adresu ukladu z bitem zapisu (R/W = 0)
    I2C_Write(data);                 // wyslanie danych
    I2C_Stop();
    
}

//Funkcja komunikacji z PCF8574 - odczyt wartosci z pinow
uint8_t PCF8574_Read() { 
    uint8_t data;
    I2C_Start();
    I2C_Write((PCF8574_ADDRESS << 1) | 1); // wyslanie adresu ukladu z bitem odczytu (R/W = 1)
    TWCR = (1 << TWEN) | (1 << TWINT);     // oczekiwanie na dane
    while (!(TWCR & (1 << TWINT)));
    data = TWDR;                           // pobranie danych
    I2C_Stop();
    return data;
}

//Funkcja glowna
int main() {
    I2C_Init();

    while (1) {
      PCF8574_Write(1<<D0);
      _delay_ms(200);
      PCF8574_Write(0<<D0);
      _delay_ms(200);
    }

    return 0;
}
