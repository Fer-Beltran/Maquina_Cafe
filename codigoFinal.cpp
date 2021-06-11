#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"
#include "DHT.h"
#include "hcsr04.h"

TextLCD lcd(PTB8, PTB9, PTB10, PTB11, PTE2, PTE3, TextLCD::LCD16x2);
Keypad kpad(PTC4, PTC3, PTC0, PTC7, PTC11, PTC10, PTC6, PTC5);
DHT DHTsensor(PTA13,SEN11301P); // Use the SEN11301P sensor
HCSR04 coffee(PTD5, PTD0);
HCSR04 milk(PTD2, PTD3);

DigitalIn touch(PTA1);
DigitalIn water(PTA2);

InterruptIn button(PTA13);

DigitalOut motor1(PTC9);
DigitalOut motor2(PTC8);
DigitalOut valve(PTD14); 
DigitalOut heater(PTA12);

PwmOut sp_motor1(PTA5);
PwmOut sp_motor2(PTA4);

int americano = 1;
int latte = 2;
int espresso = 3;

void init(void); 

void _americano(void);  //
void _latte(void);  //
void _espresso(void);  //

void pourCoffee(int time); //
void pourMilk(int time); //
void pourWater(int time); //

void heatWater(void); //
int waterTemp(void); //

int waterLevel(void);
int powderLevel(void);
void insertCoin(void);
int chooseOption(void); //
void prepareCoffee(int type); //

void flip(void);


int main(){
    
    coffee.start();
    milk.start();
    
    button.rise(&flip);
    
    while(1){
        
        char key = ' ';
        
        lcd.cls();
        lcd.printf("Select Product");
        
        int order = chooseOption();
        
        if (order == 0){
            while (order == 0){
                lcd.cls();
                lcd.printf("Invalid Product");
                wait(1);
                order = chooseOption();
            }
        }
        
        lcd.cls();
        lcd.printf("Insert coin");
        insertCoin();
        lcd.cls();
        
        int powderProd = powderLevel();
        if (powderProd == 0){
            lcd.printf("Not enough prodcuts");
            //
        }
        
        int water = waterLevel();
        if (water == 0){
            lcd.printf("Not enough product");
            //
        }
        
        heatWater();
        
        prepareCoffee(order);
        
        lcd.printf("have a good day");
    }   
}

void init(){

}

void pourCoffee(int time){
    sp_motor1.period(4.0f);

    sp_motor1.write(0.10f); // Velocidad
    motor1 = 1;
    wait(time);
    motor1 = 0;
}

void pourMilk(int time){
    sp_motor2.period(4.0f);

    sp_motor2.write(0.10f); // Velocidad
    motor2 = 1;
    wait(time);
    motor2 = 0;
}

void pourWater(int time){
    valve=0;
    wait(time);
    valve=1;
}

void _americano(void){
    int coffeeTime = 2; // Corregir
    int waterTime = 4; // Corregir
    pourCoffee(coffeeTime);
    pourWater(waterTime);
}

void _latte(void){
    int coffeeTime = 2; // Corregir
    int milkTime = 2; // Corregir
    int waterTime = 2; // Corregir
    pourCoffee(coffeeTime);
    pourMilk(milkTime);
    pourWater(waterTime);
}
    
void _espresso(void){
    int coffeeTime = 2; // Corregir
    int waterTime = 2; // Corregir
    pourCoffee(coffeeTime);
    pourWater(waterTime);
}

int chooseOption(){
    
    int chosen;
    
    char k = kpad.ReadKey();
    
    if (k == '1'){
        lcd.printf("preparing beverage");
        wait(2);
        chosen = americano;
    }
    else if (k == '2'){
        lcd.printf("preparing beverage");
        wait(2);
        chosen = latte;
    }
    else if (k == '3'){
        lcd.printf("preparing beverage");
        wait(2);
        chosen = espresso;
    }
    else{
        chosen = 0;
    }
    
    return chosen;
    
}

void heatWater(void){
    heater = 1;
    int temp = waterTemp();
    while (temp == 0){
        wait(10);
        temp = waterTemp();
    }
    heater = 0;
}

int waterTemp(){
    int hot = 0;
    int err;
    int t;
    wait(1); // wait 1 second for device stable status
    err = DHTsensor.readData();
    if (err == 0) {
        t = DHTsensor.ReadTemperature(CELCIUS);
        if (t >= 80){
            hot = 1;
        }
        else{
            hot = 0;
        }
    } else {
        lcd.printf("Error");
    }
    return hot;
}

int waterLevel(){
    int level = water.read();
    return level;
}

int powderLevel(){
    unsigned int coffeeDistance = coffee.get_dist_cm();
    unsigned int milkDistance = milk.get_dist_cm();
    
    int powders;
    
    if ((coffeeDistance > 10) || (milkDistance > 10)){
        powders = 0;
    }
    else{
        powders = 1;
    }
    
    return powders;
}

void insertCoin(){
    int coin = touch.read();
    while (coin == 0){
        wait(5);
        coin = touch.read();
    }
}

void prepareCoffee(int type){
    if (type == 1){
        _americano();
    }
    else if (type == 2){
        _latte();
    }
    else if (type == 3){
        _espresso();
    }
}

void flip(){
    while(1){
        
        char key = ' ';
        
        lcd.cls();
        lcd.printf("Select Product");
        
        int order = chooseOption();
        
        if (order == 0){
            while (order == 0){
                lcd.cls();
                lcd.printf("Invalid Product");
                wait(1);
                order = chooseOption();
            }
        }
        
        lcd.cls();
        lcd.printf("Insert coin");
        insertCoin();
        lcd.cls();
        
        int powderProd = powderLevel();
        if (powderProd == 0){
            lcd.printf("Not enough prodcuts");
            //
        }
        
        int water = waterLevel();
        if (water == 0){
            lcd.printf("Not enough product");
            //
        }
        
        heatWater();
        
        prepareCoffee(order);
    }   
}
