//User created header file used to time the code.

struct StopWatch {
    long elapsed;
    long last;
    long startTime;
    int zeros;
    int nonZeros;
};

void resetStopWatch(struct StopWatch* watch);
void startStopWatch(struct StopWatch* watch);
long stopStopWatch(struct StopWatch* watch);
void printStopWatchReport(struct StopWatch* watch);
