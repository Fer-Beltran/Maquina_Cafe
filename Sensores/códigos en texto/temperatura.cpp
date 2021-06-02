/*El sensor en este código solo va a marcar una vez la temperatura en celcius, lo demás va a salir error, hay que 
reiniciarlo para que vuelva a marcar la temperatura*/
/*En lugar de pc.print pueden imprimir la temperatura en la lcd*/

#include "mbed.h"
#include "DHT.h"
 
DigitalOut myled(LED1);
//Serial pc(USBTX, USBRX); ignorar esto
 
DHT sensor(PTA1,SEN11301P); // Use the SEN11301P sensor
 
int main() {
    int err;
    printf("\r\nDHT Test program");
    printf("\r\n******************\r\n");
    wait(1); // wait 1 second for device stable status
    while (1) {
        myled = 1;
        err = sensor.readData();
        if (err == 0) {
            pc.printf("Temperature is %4.2f C \r\n",sensor.ReadTemperature(CELCIUS)); //cambiar a lcd.printf

        } else
            pc.printf("\r\nErr %i \n",err); //cambiar a lcd.printf
        myled = 0;
        wait(5);
    }
}
