#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <_stdlib.h>
#include <sys/ioctl.h>
#include <linux/input.h>

#define EVENT_FILE "/dev/input/by-path/platform-i8042-serio-0-event-kb"

int pressed_keys[256] = {0};

void print_event(struct input_event *event) {
    switch(event -> type) {
        case EV_KEY:
            switch(event -> value) {
                case 0:
                    fprintf("ex1.txt", "Released 0x%04x (%d)\n", event->code, event->code);
                    pressed_keys[event->code] = 0;
                break;
                case 1:
                    fprintf("ex1.txt", "Pressed 0x%04x (%d)\n", event->code, event->code);
                    pressed_keys[event->code] = 1;
                break;
                case 2:
                    fprintf("ex1.txt", "Repeated 0x%04x (%d)\n", event->code, event->code);
                break;
                default:
                    break;
            }
        break;
        default:
            break;
    }
}

void shortcut() {
    if (pressed_keys[0x19] && pressed_keys[0x12]) {
        fprintf("ex1.txt", "I passed the Exam!\n");
    }

    if (pressed_keys[0x2e] && pressed_keys[0x1e] && pressed_keys[0x19]) {
        fprintf("ex1.txt", "I passed the Exam!\n");
    }
}

int main() {
    int fd;
    struct input_event event;

    fd = open(EVENT_FILE, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open input device");
        return EXIT_FAILURE;
    }

    while(1) {
        ssize_t  bytesRead = read(fd, &event, sizeof(struct input_event));
        if (bytesRead == -1) {
            perror("Error reading event");
            close(fd);
            return EXIT_FAILURE;
        }

        if (event.type == EV_KEY && (event.value == 0 || event.value == 1 || event.value == 2)) {
            print_event(&event);
            shortcut();
        }

        if (event.type == EV_KEY && event.code == 0x2d && event.value == 1) {
            break;
        }
    }

    close(fd);
    printf("End\n");

    return 0;
}
