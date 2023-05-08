//
// Created by 廖哲賢 on 2021/7/27.
//

#ifndef ECC_PLATEFORM_H
#define ECC_PLATEFORM_H

#include "types.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

static int default_RNG(uint8_t *dest, unsigned size) {
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd == -1) {
        fd = open("/dev/random", O_RDONLY | O_CLOEXEC);
        if (fd == -1) {
            return 0;
        }
    }

    char *ptr = (char *)dest;
    size_t left = size;
    while (left > 0) {
        ssize_t bytes_read = read(fd, ptr, left);
        if (bytes_read <= 0) { // read failed
            close(fd);
            return 0;
        }
        left -= bytes_read;
        ptr += bytes_read;
    }

    close(fd);
    return 1;
}
#endif //ECC_PLATEFORM_H
