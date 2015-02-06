#include<sys/time.h>
#include<ctime>
typedef unsigned long long timestamp_t;

static timestamp_t get_timestamp () {
    struct timeval now;
    gettimeofday (&now, NULL);
    return  (now.tv_usec + (timestamp_t)now.tv_sec * 1000000);
}
const float DIVIDE = 1000000.0L;

double compare_timestamps(timestamp_t t1, timestamp_t t2) {
    return (t2 - t1) / DIVIDE;
}

//...
//timestamp_t t0 = get_timestamp();
//Process
//timestamp_t t1 = get_timestamp();

//double secs = (t1 - t0) / 1000000.0L;
