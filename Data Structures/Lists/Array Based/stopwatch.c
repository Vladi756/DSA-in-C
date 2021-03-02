#include <stdio.h>
#include <time.h>
#include "stopwatch.h"

//Functions of the stopwatch.h header file.
void resetStopWatch(struct StopWatch* watch) {
    watch->startTime = 0;
    watch->last = 0;
    watch->elapsed = 0;
    watch->zeros = 0;
    watch->nonZeros = 0;
}

void startStopWatch(struct StopWatch* watch) {
    watch->startTime = clock();
}

long stopStopWatch(struct StopWatch* watch) {
    long now = clock();
    watch->last = now - watch->startTime;

    if (watch->last == 0) {
        watch->zeros++;
    } else {
        watch->nonZeros++;
 }
    watch->elapsed += watch->last;
    watch->startTime = now;

    return watch->elapsed;
}

void printStopWatchReport(struct StopWatch* watch) {
    printf("%ld (%d/%d)\n", watch->elapsed, watch->zeros, watch->nonZeros);
}
