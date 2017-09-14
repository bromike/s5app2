#include "mbed.h"
#include "rtos.h"
#include <string>

typedef struct{
    string type;
    int16_t timestamp;
} mail_t;

Serial pc(USBTX, USBRX); 
DigitalIn en_1(p15);
DigitalIn en_2(p16);
AnalogIn ea_1(p19);
AnalogIn ea_2(p20);
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);
Queue<uint32_t, 5> queue;
Mail<mail_t, 16> mailbox;
Ticker timer;

Thread task1;
Thread task2;
Thread task3;

void time_converter(int16_t time)
{
    int a = time / 31557600;
    time = 31557600 * a;
    int m = time / 2630000;
    time = 2630000 * m;
    int j = time / 86400;
    time = 86400 * j;
    int h = time / 3600;
    time = 3600 * h;
    int mm = time / 60;
    time = 60 * mm;
    
    //AA:MM:JJ:HH:MM:SS
    pc.printf("%d:%d:%d:%d:%d:%d", a, m, j, h, mm, time);
}

void lecture_analog(void const *args) {
    while (true) {
        // synchronisation sur la période d'échantillonnage
        // lecture de l'étampe temporelle
        // lecture des échantillons analogiques
        // calcul de la nouvelle moyenne courante
        // génération éventuelle d'un événement
    }
}
void lecture_num() {
    bool acquisition = true;
    bool debounce1 = false;
    bool debounce2 = false;
    int bouton1 = 0;
    int bouton2 = 0;
    while (true) {
        // synchronisation sur la période d'échantillonnage
        // lecture de l'étampe temporelle
        // lecture des échantillons numériques
        // prise en charge du phénomène de rebond
        // génération éventuelle d'un événement
        acquisition = !acquisition;
        
        if(debounce2){
            led2 = bouton2 = en_2.read();
            debounce2 = false;
        }
        
        if(debounce1){
            led1 = bouton1 = en_1.read();
            debounce1 = false;
        }
        
        if(acquisition){
            int last_state1 = bouton1;
            int last_state2 = bouton2;
            bouton1 = en_1.read();
            bouton2 = en_2.read();
            led3 = debounce1 = bouton1 != last_state1;
            led4 = debounce2 = bouton2 != last_state2;
        }
        
        Thread::wait(50);
    }
}
void collection(void const *args) {
    while (true) {
        // attente et lecture d'un événement
        // écriture de l'événement en sortie (port série)
    }
}
int main() {
    //task1.start(lecture_analog);
    task2.start(lecture_num);
    //task3.start(collection);
    while(1) {
    }
}