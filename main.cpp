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
int tick;

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

void counter(){
    tick++;
    if(tick == 5){
        task1.signal_set(0x1);
        task2.signal_set(0x2);
        tick = 0;
    }
    task3.signal_set(0x4);
}
int moyenne(int dataset[], int N){
    int avg = 0;
    for(int i = 0; i < N; i++){
        avg += dataset[i];
    }
    return avg/N;
}

void lecture_analog() {
    while (true) {
        // synchronisation sur la période d'échantillonnage
        // lecture de l'étampe temporelle
        // lecture des échantillons analogiques
        // calcul de la nouvelle moyenne courante
        // génération éventuelle d'un événement
        Thread::signal_wait(0x1);
        
        Thread::yield();
    }
}

void lecture_num() {
    bool acquisition = true;
    bool debounce1 = false;
    bool debounce2 = false;
    int bouton1 = 0;
    int bouton2 = 0;
	int last_state1;
    int last_state2;
	
    while (true) {
        // synchronisation sur la période d'échantillonnage
        // lecture de l'étampe temporelle
        // lecture des échantillons numériques
        // prise en charge du phénomène de rebond
        // génération éventuelle d'un événement
        Thread::signal_wait(0x2);
        acquisition = !acquisition;
        
        if(debounce2){
            if(bouton2 == en_2.read()){
                led2 = !led2;
            }
            else{
                bouton2 = !bouton2;
            }
            debounce2 = false;
        }
        
        if(debounce1){
            if(bouton1 == en_1.read()){
                led1 = !led1;
            }
            else{
                bouton1 = !bouton1;
            }
            debounce1 = false;
        }
        
        if(acquisition){
            last_state1 = bouton1;
            last_state2 = bouton2;
            bouton1 = en_1.read();
            bouton2 = en_2.read();
            led3 = debounce1 = bouton1 != last_state1;
            led4 = debounce2 = bouton2 != last_state2;
        }
        Thread::yield();
    }
}

void collection() {
    while (true) {
        // attente et lecture d'un événement
        // écriture de l'événement en sortie (port série)
        Thread::signal_wait(0x4);
        Thread::yield();
    }
}

int main() {
    tick = 0;
    task1.start(lecture_analog);
    task2.start(lecture_num);
    task3.start(collection);
    timer.attach(&counter, 0.01); //timer tout les 10ms
    while(1) {
        
    }
}