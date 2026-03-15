# Moduł Systemowy HD44780 LCD Driver & PCB Adapter Collection

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Hardware](https://img.shields.io/badge/Hardware-KiCad-orange.svg)
![Status](https://img.shields.io/badge/Status-Completed-green.svg)

## 📖 O projekcie

Niniejsze repozytorium zawiera kompleksowe rozwiązanie dla obsługi popularnych wyświetlaczy znakowych LCD opartych na sterowniku **HD44780**. Projekt składa się z dwóch głównych filarów:
1.  **Warstwa sprzętowa:** Projekty płytek drukowanych (PCB) wykonane w środowisku **KiCad**, służące jako adaptery i moduły interfejsowe dla wyświetlaczy 16x2, 20x4 oraz 40x2.
2.  **Warstwa programowa:** Biblioteki sterowników napisane w języku C, obsługujące różne tryby komunikacji (I2C, 4-bit, 8-bit) ze szczególnym naciskiem na optymalizację (odczyt flagi zajętości - Busy Flag).

---

## 🛠️ Funkcjonalności

### 🔌 Hardware (Projekty PCB)
Projekty płytek zostały przygotowane w programie **KiCad**. Repozytorium zawiera pliki produkcyjne oraz źródłowe dla kilku wariantów:
* **Wersje jedno- i dwuwarstwowe:** Dostosowane do różnych metod produkcji (domowe trawienie vs profesjonalna produkcja).
* **Uniwersalność:** Obsługa popularnych formatów wyświetlaczy: 16x2, 20x4 oraz 40x2.
* **Adaptery I2C:** Projekty integrujące ekspandery portów (np. PCF8574) bezpośrednio z wyświetlaczem, co redukuje liczbę wymaganych pinów mikrokontrolera.

### 💻 Software (Sterowniki)
Kod źródłowy zawiera implementację sterowników w różnych konfiguracjach sprzętowych:
* **Obsługa I2C:** Sterowanie poprzez ekspander (PCF8574), idealne dla systemów z ograniczoną liczbą GPIO.
* **Tryb równoległy (4-bit i 8-bit):** Klasyczne sterowanie bezpośrednie.
* **Busy Flag Check:** Zaimplementowany mechanizm odczytu flagi zajętości sterownika HD44780. Pozwala to na uniknięcie sztywnych opóźnień (`delay`), co znacząco zwiększa wydajność całego systemu wbudowanego.
* **Interfejs szeregowy:** Alternatywne metody komunikacji.

---

## 📂 Struktura Repozytorium

Poniżej znajduje się opis zawartości kluczowych katalogów:

### Projekty KiCad
* `/Wersja_z_I2C_8bit_...` - Projekt dwuwarstwowej płytki z integracją I2C.
* `/Wersja_16x2_20x4_...` - Uniwersalna płytka jednowarstwowa dla standardowych wyświetlaczy.
* `/wersja_ostateczna_wyswietlacz_pcf_v1` - Finalna wersja adaptera z układem PCF.

### Kod Źródłowy
* `/wyswietlacz_interfejs_4_bit_BusyFlag` - Sterownik 4-bitowy z odczytem BF.
* `/testy_z_ekspanderem_pcf` - Kod testowy dla komunikacji I2C.
* `/wyswietlacz_interfejs_8_bit` - Podstawowa obsługa w trybie 8-bitowym.

---

## 🔧 Technologie i Narzędzia

* **Projektowanie PCB:** KiCad EDA
* **Język programowania:** C (Embedded)
* **Hardware:** Wyświetlacze HD44780, Ekspandery PCF8574
* **Protokoły:** I2C, Parallel Interface

---
