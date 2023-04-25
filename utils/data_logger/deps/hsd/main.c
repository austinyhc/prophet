#include <stdio.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

int main(int argc, char *argv[])
{
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init_context(/*ctx=*/NULL, /*options=*/NULL, /*num_options=*/0);
    if (r < 0)
        return r;

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0){
        libusb_exit(NULL);
        return (int) cnt;
    }

    print_devs(devs);
    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);

    return 0;
}
