#include <time.h>
#include "../include/tools/timer.h"

long long current_milliseconds() {
    struct timespec tp;
    clock_gettime(CLOCK_REALTIME, &tp);
    return ((long long)tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
}
