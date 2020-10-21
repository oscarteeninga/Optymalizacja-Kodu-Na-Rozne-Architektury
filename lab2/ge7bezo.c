#include <stdio.h>
#include <stdlib.h>
 

#include <sys/time.h>
#include <time.h>

int SIZE;

static double gtod_ref_time_sec = 0.0;

/* Adapted from the bl2_clock() routine in the BLIS library */

double dclock()
{
  double         the_time, norm_sec;
  struct timeval tv;
  gettimeofday( &tv, NULL );
  if ( gtod_ref_time_sec == 0.0 )
    gtod_ref_time_sec = ( double ) tv.tv_sec;
  norm_sec = ( double ) tv.tv_sec - gtod_ref_time_sec;
  the_time = norm_sec + tv.tv_usec * 1.0e-6;
  return the_time;
}

int ge(double **A)
{
  int i,j,k;
  for (k = 0; k < SIZE; k++) { 
    for (i = k+1; i < SIZE; i++) { 
      for (j = k+1; j < SIZE; j++) { 
         A[i][j]=A[i][j]-A[k][j]*(A[i][k]/A[k][k]);
      } 
    }
  }
  return 0;
}

int main( int argc, const char* argv[] )
{
  double check=0.0;
  for (int size = 0; size <= 5000; size += 100) {
    SIZE = size;
      int i,j,k,iret;
    double **matrix = (double**) malloc(SIZE*sizeof(double*));
    double dtime;
    srand(1);
    for (i = 0; i < SIZE; i++) {
      matrix[i] = (double*) malloc(SIZE*sizeof(double));
      for (j = 0; j < SIZE; j++) { 
        matrix[i][j]=rand();
      }
    }
    // printf("call GE");
    dtime = dclock();
    iret=ge(matrix);
    dtime = dclock()-dtime;
    // printf( "Time: %le \n", dtime);
    printf("%d, %le\n", SIZE, dtime);
    for (i = 0; i < SIZE; i++) {
      for (j = 0; j < SIZE; j++) {
        check = check + matrix[i][j];
      }
    }
    // printf( "Check: %le \n", check);
    fflush( stdout );
  }



  return 0;
}