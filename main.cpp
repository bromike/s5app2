#include "mbed.h"
#include "rtos.h"
 

DigitalIn  button1(p15);
DigitalIn  button2(p16);

AnalogIn   pot1(p19);
AnalogIn 	 pot2(p20);

Serial pc(USBTX,USBRX);

int main() {
	while(1){
		pc.printf("Pot1 : %d\n\r", pot1.read_u16());
		pc.printf("Pot2 : %d\n\r", pot2.read_u16());
		pc.printf("Button1: %d\n\r", button1.read());
		pc.printf("Button2 :%d\n\r", button2.read());
		wait(1);
	}
}
