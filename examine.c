#include <stdio.h>

#include <stdlib.h>

#include <omp.h>

#include <unistd.h>

#include <time.h>

#include <stddef.h>

#include <sys/sysinfo.h>


#define LIMIT_MIN 12.0      // Define the minimun value of accepted coordinates

#define LIMIT_MAX 30.0      // Define the maximum value of accepted coordinates



int mp(char *filename)
{


	int total_cords_within_lim = 0;

	FILE* fp = fopen(filename, "r");

	if(fp == NULL)

	{

		fprintf(stderr, "File '%s', could not be opened...\n", filename);

       		return(-1);

	}

	int cords_total = 0;

	char line[100];

	while(fscanf(fp, "%s", line) != EOF)

    	{

    		cords_total++;

	}
	cords_total/=3;
	fclose(fp);


	
#pragma omp parallel
	
	{
	
	FILE* fp2 = fopen(filename, "r");

	
		//Every thread gets to examine some lines
	//printf("aaaaaaaaaaaaaaaaaaaaa %d",omp_get_num_threads());
	int id = omp_get_thread_num();

	int threads_total = omp_get_num_threads();
	//printf("aaaaaaaaaa %d \n",cords_total);

	int start = id * cords_total / threads_total;
	
	int end = (id+1) * cords_total / threads_total -1;
	printf("start = %d",start);
	printf("end = %d",end);
	if( (threads_total-1 == id) && (end+1 != cords_total) )

	{

		end = cords_total-1;

	}
	//printf("%d",start);
	//printf("%d",end);
	
	int lines_read=0;

    	int cords_within_lim = 0;

    	float cords_val[3] = {0, 0, 0};

	for(lines_read=start; lines_read<=end; lines_read++)

	{

		fscanf(fp2,"%f %f %f", &cords_val[0], &cords_val[1], &cords_val[2]);

		if(lines_read >= start)

		{

			if(cords_val[0] >= LIMIT_MIN && cords_val[0] <= LIMIT_MAX && cords_val[1] >= LIMIT_MIN && cords_val[1] <= LIMIT_MAX && 	cords_val[2] >= LIMIT_MIN && cords_val[2] <= LIMIT_MAX)
 
			{

		    		cords_within_lim++;

			}

		}

	}

	fclose(fp2);
	//printf("%d ",cords_within_lim);
	

#pragma omp for reduction(+:total_cords_within_lim)

		for(id=0; id<threads_total; id++)

		{

			total_cords_within_lim += cords_within_lim;

		}

	}

	//printf("%d",total_cords_within_lim);
	//printf("%d",cords_within_lim);
	return total_cords_within_lim;

}



int not_mp(char *filename) {


	int cords_total = 0;

    	int cords_within_lim = 0;

    	float cords_val[3] = {0, 0, 0};


    	
FILE* fp = fopen(filename, "r"); //Open the file with the specified filename

    	if(fp == NULL)      // Verify that the file opened succesfully
    
	{

        	fprintf(stderr, "File '%s', could not be opened...\n", filename);

        	return(-1);

    	}


    	while(fscanf(fp,"%f %f %f",&cords_val[0],&cords_val[1],&cords_val[2]) !=EOF)
	// Read the coordinates line by line, in triads

    	{

    		// This part executes for each triad between the boundaries

        	if(cords_val[0] >= LIMIT_MIN && cords_val[0] <= LIMIT_MAX && cords_val[1] >= LIMIT_MIN && cords_val[1] <= LIMIT_MAX && cords_val[2] >= LIMIT_MIN && cords_val[2] <= LIMIT_MAX)
 
      	{

            cords_within_lim++;
     
        }

        cords_total++;
      	// Update the total number of coordinates read

    	}


    fclose(fp);     // Close the file before quiting

    return cords_within_lim;

}



int main(int argc, char* argv[])
{


	struct timespec start,end;


    	clock_gettime(CLOCK_MONOTONIC, &start);

    
    	//printf("not-mp result: %d\n", not_mp(argv[3]));

    	printf("mp result: %d\n", mp(argv[3]));

    
    	clock_gettime(CLOCK_MONOTONIC, &end );


    	const int DAS_NANO_SECONDS_IN_SEC = 1000000000;

    	long timeElapsed_s = end.tv_sec - start.tv_sec;

    	long timeElapsed_n = end.tv_nsec - start.tv_nsec;

    	//if we have a negative number in timeElapsed_n, borrow a carry from seconds

    	if ( timeElapsed_n < 0 )
 
    	{

        	timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;

        	timeElapsed_s--;

    	}

    	printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);

    	return 0;

}

