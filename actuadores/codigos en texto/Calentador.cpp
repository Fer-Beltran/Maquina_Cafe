/*Calienta por 5 minutos y luego lo apaga*/

#include "mbed.h"
 
DigitalOut c(PTA1);
 
int main() {
 c=0;
 wait(300);
 c=1;
}
