#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include "main.h"
int Binary(unsigned int num) {
    int holder[32];
    unsigned int index = 0;
    int count = 0;
int i;
    if (num == 0) {
        count += write(1, "0", 1);
        return count;
    }
    while (num > 0) {
        holder[index++] = '0' + num % 2;
        num /= 2;
    }
    i = index - 1;
    while (i >= 0) {
        char c = holder[i];
        count += write(1, &c, 1);
        i--;
    }
    return (count);
}
