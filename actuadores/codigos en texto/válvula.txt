/*abre válvula por 5 minutos y luego la cierra*/

#include "mbed.h"
 
DigitalOut abrir(PTA1);
 
int main() {
 abrir=0;
 wait(300);
 abrir=1;
}
