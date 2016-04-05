#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stddef.h>
#include <sys/sysinfo.h>

//The function that counts the POSIX time


main()
{
    struct timespec start,end;

    clock_gettime(CLOCK_MONOTONIC, &start);
   
    //waiting for crucial functions

    clock_gettime(CLOCK_MONOTONIC, &end );

    const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
    long timeElapsed_s = end.tv_sec - start.tv_sec;
    long timeElapsed_n = end.tv_nsec - start.tv_nsec;
    //if we have a negative number in timeElapsed_n , borrow a carry from seconds
    if ( timeElapsed_n < 0 ) 
    {
        timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;
        timeElapsed_s--;
    }
    printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
}
