/// led.c
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
    int fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd == -1) {
        printf("export open error\n");
        return -1;
    } else {
        printf("export open success!\n");
    }
    write(fd, "509", sizeof("509"));
    close(fd);

    fd = open("/sys/class/gpio/gpio509/direction", O_RDWR);
    if (fd == -1) {
        printf("direction open error\n");
        return -1;
    } else {
        printf("direction open success!\n");
    }
    write(fd, "out", sizeof("out"));
    close(fd);

    fd = open("/sys/class/gpio/gpio509/value", O_RDWR);
    if (fd == -1) {
        printf("value open error\n");
        return -1;
    } else {
        printf("value open success!\n");
    }
    printf("Led will flashing!!!!!\n");
    int i = 20;
    while (i--) {
        i % 2 == 0 ? write(fd, "1", sizeof("1")) : write(fd, "0", sizeof("0"));
        sleep(1);
        printf("Led flashing,count %d\n", i);
    }

    close(fd);

    return 0;
}
