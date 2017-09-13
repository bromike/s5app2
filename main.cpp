#include "mbed.h"
#include "rtos.h"
#include <string>

typedef struct{
    string type;
    int16_t timestamp;
} mail_t;

DigitalIn en_1(p15);
DigitalIn en_2(p16);
AnalogIn ea_1(p19);
AnalogIn ea_2(p20);
Queue<uint32_t, 5> queue;
Mail<mail_t, 16> mailbox;
Ticker timer;

string time_converter(int16_t time)
{
    int a = time / 31557600;
    time = 31557600 * a;
    int m = time / 2630000;
    time = 2630000 * m;
    
    //AA:MM:JJ:HH:MM:SS
    return "  ";
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
void lecture_num(void const *args) {
    while (true) {
    // synchronisation sur la période d'échantillonnage
    // lecture de l'étampe temporelle
    // lecture des échantillons numériques
    // prise en charge du phénomène de rebond
    // génération éventuelle d'un événement
    }
}
void collection(void const *args) {
    while (true) {
    // attente et lecture d'un événement
    // écriture de l'événement en sortie (port série)
    }
}
int main() {
    Thread task1;
    Thread task2;
    while(1) {
    }
}