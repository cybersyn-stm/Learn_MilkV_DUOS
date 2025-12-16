#include <stdio.h>
#include <unistd.h>
#include <wiringx.h>

int main() {
    // Duo/Duo256M: LED = 25
    // DuoS:        LED =  0
    int DUO_LED = 0;

    // Duo:     milkv_duo
    // Duo256M: milkv_duo256m
    // DuoS:    milkv_duos
    if (wiringXSetup("milkv_duos", NULL) == -1) {
        printf("wiringX 初始化失败\n");
        return 1;
    }

    if (wiringXValidGPIO(DUO_LED) != 0) {
        printf("无效的 GPIO %d\n", DUO_LED);
        wiringXGC();
        return 1;
    }

    pinMode(DUO_LED, PINMODE_OUTPUT);

    for (;;) {
        printf("Duo LED GPIO (wiringX) %d: 高电平\n", DUO_LED);
        printf("LED 亮 1 秒\n");
        digitalWrite(DUO_LED, HIGH);
        sleep(1);
        printf("Duo LED GPIO (wiringX) %d: 低电平\n", DUO_LED);
        printf("LED 灭 1 秒\n");
        digitalWrite(DUO_LED, LOW);
        sleep(1);
    }

    wiringXGC();
    return 0;
}
