#include <mbed.h>
#include <DigitalOut.h>

DigitalOut led1(LED1);

extern "C" int main();

int main()
{
    while (true) {
        printf("Hello\n\r");
        led1 = !led1;
        wait(1.0);
    }
}