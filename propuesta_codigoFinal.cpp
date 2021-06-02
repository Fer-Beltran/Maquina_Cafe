#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"

TextLCD lcd(PTB8, PTB9, PTB10, PTB11, PTE2, PTE3, TextLCD::LCD16x2);
Keypad kpad(PTC4, PTC3, PTC0, PTC7, PTC11, PTC10, PTC6, PTC5);

int americano = 1;
int latte = 2;
int espresso = 3;

void americano(void);
void latte(void);
void espresso(void);

void pourCoffee(int time);
void pourMilk(int time);
void pourWater(int time);

void heatWater(void);
int waterTemp(void);

int waterLevel(void);
int powderLevel(void);
void insertCoin(void);
int chooseOption(void);
void prepareCoffee(int type);


int main(){
    
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