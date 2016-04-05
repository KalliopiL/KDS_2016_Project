
#include <stdlib.h>

#include <stdio.h>

#include <time.h>


int main( int argc, char *argv[] )  {

    float cords[3];

    int cords_num = atoi(argv[2]);

    char *filename = argv[1];

    FILE *f = fopen(filename, "w");

    long int ltime = time(NULL);

    int utime = (unsigned int) ltime/2;

    srand(utime);

    int i;


    for(i=0; i<cords_num; i++){

        cords[0]=(float)34*rand()/(RAND_MAX-1);

        cords[1]=(float)34*rand()/(RAND_MAX-1);

        cords[2]=(float)34*rand()/(RAND_MAX-1);

        fprintf(f,"%f %f %f\n", cords[0], cords[1], cords[2]);

    }

    fclose(f);

}
