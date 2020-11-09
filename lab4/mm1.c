
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <papi.h>



int main(int argc, const char* argv[]) {


    /* PAPI variables */
    int measure;
    int * events;
    long long * values;
    int numevents;
    int retval;
    int check;
    float real_time;
    float proc_time;
    float mflops;
    long long flpins;
    char * errorstring;


    /* Start PAPI counters*/
    if (measure == 1) {
        retval = PAPI_flops(&real_time, &proc_time, &flpins, &mflops);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started\n");
    }
    if (measure == 2) {
        numevents = 2;
        events = malloc(sizeof *events * numevents);
        events[0] = PAPI_L1_DCM;
        events[1] = PAPI_TOT_CYC;
        PAPI_library_init(check);
        retval = PAPI_start_counters(events, numevents);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("PAPI started\n");
    }

    /* Measure execution counters */
    DOSOMETHING();

    /* Here is PAPI reading and printout */
    if (measure == 1) {
        retval = PAPI_flops(&real_time, &proc_time, &flpins, &mflops);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f\n", real_time, proc_time, flpins, mflops);
    }
    if (measure == 2) {
        values = malloc(sizeof *values * numevents);
        retval = PAPI_stop_counters(values, numevents);
        if (retval != PAPI_OK) {
            errorstring = PAPI_strerror(retval);
            fprintf(stderr, errorstring);
            fprintf(stderr, "\n");
            free(errorstring);
            exit(1);
        }
        printf("L1 data cache misses: %lld Total cycles: %lld\n", values[0], values[1]);
        free(values);
        free(events);
    }


    return 0;
}
