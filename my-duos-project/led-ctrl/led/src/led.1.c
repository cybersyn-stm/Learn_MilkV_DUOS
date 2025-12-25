#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define LED "509"
int main() {
    int i = 10;
    // OPEN LED GPIO
    int fd = open("/sys/class/gpio/export", O_WRONLY);

    if (fd == -1) {
        printf("export open error\n");
        return -1;
    }
    write(fd, "509", sizeof("509"));
    close(fd);
    // SET DIRECTION
    fd = open("/sys/class/gpio/gpio509/direction", O_RDWR);
    if (fd == -1) {
        printf("direction open error\n");
        return -1;
    }
    write(fd, "out", sizeof("out"));
    close(fd);
    // SET VALUE
    fd = open("/sys/class/gpio/gpio509/value", O_RDWR);
    if (fd == -1) {
        printf("value open error\n");
        return -1;
    }
    while (i--) {
        write(fd, "1", sizeof("1"));
        usleep(500000); // 500ms
        write(fd, "0", sizeof("0"));
        usleep(500000);
    }
    close(fd);

    return 0;
}
