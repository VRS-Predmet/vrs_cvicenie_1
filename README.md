# Vnorené riadiace systémy 2024/25
### Harmonogram cvičení
1. Úvod do VRS
2. Grafické rozhranie CubeMX a LL-knižnica
3. Prerušenia
4. Komunikácia USART
5. Úvod do git
6. I2C senzor
7. Časovače
8. ADC prevodník
9. až 12. Semestrálne zadanie

### Bodovanie
- (10b) Úlohy na cvičeniach 1-5
- (10b) Zadanie na cvičeniach 6-8
- (35b) Semestrálne zadanie 9-12
- (45b) Skúška

Zadania odovzdajte **bez binariek** vo formáte zip/rar/tar do AIS do miesta odovzdania a potom zadania budú prezentované cvičiacemu na konci daných cvičení.

# Náplň cvičenia
- overenie nainštalovaného STM32CubeIDE
- zoznámenie sa s registrami mikrokontrolera stm32-F3xx
- priami prístup k registrom mikrokontrolera
- zoznámenie sa s perifériou GPIO – ako funguje, vlastnosti
- konfigurácia GPIO portu a jednotlivých pinov
- vypracovanie zadania 1

# Ukážkový príklad
1. Stiahnúť a nainštalovať [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)
2. Stiahnúť a nainštalovať [git](https://git-scm.com/downloads)
3. Naklonovať repozitár `vrs_cvicenie_1` vetva `master`
4. Pripraviť zariadenie podľa schémy nižšie
5. V `CubeIDE -> File -> Import -> General -> Existing Projects into Workspace` nájsť naklonovaný projekt a importovať do workspace
6. Pripojiť microkontrolér pomocou USB do počítača
7. Naflashovať projekt do zariadenia pomocou `Run -> Debug` (F11) a spustiť `Run -> Resume (F8)`

![circuit2](https://user-images.githubusercontent.com/113924824/191065787-aff20285-eef7-432f-b2cb-217aa3dedd86.png)

# GPIO port
<p align="center">
    <img src="https://bluetechs.files.wordpress.com/2013/12/115.png" width="600" title="GPIO pin block scheme">
</p>

### Nastavenie vstupného pinu
- typ vstupu: digitálny, analógový
- alternatívna funkcia
- pripojenie pull up, pull down rezistora

### Nastavenie výstupného pinu
- typ výstupu: push-pull, open-drain
- rýchlosť výstupu
- pripojenie pull up, pull down rezistora

### Registre GPIO
- Konfigurácia pinu: MODER, OTYPER, OSPEEDR, PUPDR, AFRL/H
- Čítanie vstupného pinu: IDR
- Čítanie/zápis na výstupný pin: ODR, BSRR, BRR

# Prístup k registrom

K registrom mikrokontrolera je možné pristupovať priamo pomocou adresy samotného registra.
```sh
*((volatile uint32_t *)((uint32_t)0x48000400)) = 0;
```
Hore uvedené je príklad ako pristúpiť (čítanie/zápis) k registru mikrokontrolera cez jeho adresu.
"0x48000400" je adresa v rámci adresovaného pamäťového priestoru mikrokontrolera. Adresa je 32 bitové číslo. Pre možnosť prístupu k hodnote nachádzajúcej sa na tejto adrese, je potrebné definovať adresu registra ako smerník na premennú typu uint32_t (32 bitový bezznamienkový integer).

### Maskovanie
V rámci registra majú jednotlivé bity alebo skupiny bitov svoju špeciálnu funkciu ako napr. nastavenie režimu GPIO pinu. To znamená, že ak chcem nastaviť konkrétne piny na hodnotu "0" alebo "1", nemôžem zvoliť spôsob zápisu do registra ako je to znázornené v hore uvedenom príklade, pretože všetky bity budú nastavené na hodnotu "0" (celý register je resetovaný).

Pre nastavenie konkrétnych bitov v registry sa využije "maska". Kedže sa ide nastavovať 32 bitový register, maska bude taktiež 32 bitové číslo.
- Nastavenie bitov na "1": maska sa vytvorí tak, že bity, ktoré chceme nastaviť v rámci registra budú mať hodnotu "1" a ostatné budú mať hodnotu "0". Následne sa vykoná operácia logický OR a výsledok operácie sa zapíše do registra. Takýmto spôsobom boli nastavené len tie bity, ktoré sme potrebovali nastaviť bez toho, aby sa zmenilo nastavenie ostatných bitov registra.

<pre>  0b10000000    <- register		
| 0b00100100    <- maska   
= 0b10100100    <- nové nastavenie registra </pre>

- Nastavenie bitov na "0": maska sa vytvorí tak, že bity, ktoré chceme resetovať v rámci registra budú mať hodnotu "0" a ostatné budú mať hodnotu "1". Následne sa vykoná operácia logický AND a výsledok operácie sa zapíše do registra. Takýmto spôsobom boli resetované len tie bity, ktoré sme potrebovali resetovať bez toho, aby sa zmenilo nastavenie ostatných bitov registra.

<pre>  0b11100101    <- register		
& 0b10011111    <- maska   
= 0b10000101    <- nové nastavenie registra </pre>

- Čítanie hodnoty z registra: ak chceme získať konkrétnu hodnotu bitu alebo skupiny bitov registra, taktiež použijeme masku. Maska bude mať nastavené bity na "1" na pozícii, z ktorej chcem čítať hodnotu z registra. Následne sa vykoná operácia "&" a jej výsledok sa porovná s maskou, aby sa zistilo, či sú dané bity registra nastavené na "1".

<pre>  0b10101101    <- register		
& 0b00011000    <- maska   
= 0b00001000    <- prečítaná hodnota z registra </pre>

# Práca s git
Git je nástroj, ktorý uľahčuje prácu s projektami. Umožňuje verziovanie projektu, kontrolu zmien, návrat na predchádzajúce verzie a iné. Ukážkové príklady práce s gitom ukazujú iba prácu v termináli. Existujú rôzne grafické rozhrania, napríklad SourceTree.  
Link na stiahnutie: https://git-scm.com/  
Tutoriál na prácu s git: https://www.w3schools.com/git/default.asp?remote=github

Naklonovanie projektu. Stiahne sa projekt aj s git verziovaním do priečinka.
```
git clone https://github.com/VRS-Predmet/vrs_cvicenie_1.git
```

Skontrolovanie zmien a stavu git repozitára.
```
git status
```

Uloženie zmien do projektu.
```
git add --all
git commit -m "This is a git commit"
```

Prepnutie sa na inú vetvu projektu.
```
git checkout zadanie_cv1
```


# Zadanie 1 (1b)
- Upravte ukážkový program tak, aby bol vstup (tlačidlo) načítavaný cez pin GPIOA-3 a výstup (LED) vyvedený na pin GPIOA-4.
- Ukážkový program sa nachádza vo vetve (branch) "master". Šablóna, podľa ktorej sa vypracuje zadanie, sa nachádza vo vetve "zadanie_cv1".
- Vypracovať a odovzdať do konca cvičenia. Toto zadanie je pre-rekvizita k zadaniu 2.
### Úlohy:
 1. Stiahnúť/naklonovať vetvu "zadanie_cv1", ktorá predstavuje šablónu projektu, do ktorej je nutné vypracovať nasledujúce úlohy.
 2. V súbore "Inc/assignment.h" doplniť definície makier, ktoré sa budú použivať pri nastavovaní GPIO periférii a v samotnej aplikácii.
 3. V subore "Src/main.c" implementovať konfiguráciu GPIO periférii s využitím makier z "assignment.h"
 
 <p align="center">
    <img src="https://github.com/VRS-Predmet/vrs_cvicenie_1/blob/master/documents/circuit.png" width="1000" title="LED, button and Stm32 - circuit.">
</p>
