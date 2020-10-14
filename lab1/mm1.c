#include <stdio.h>
#include <stdlib.h>
 

int size = 1000;

#include <sys/time.h>
#include <time.h>

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

int mm(double** first, double** second, double** multiply)
{
  register unsigned int i,j,k; 
  double sum = 0;
  for (i = 0; i < size; i++) { //rows in multiply
    for (j = 0; j < size; j++) { //columns in multiply
      for (k = 0; k < size; k++) { //columns in first and rows in second
	    sum = sum + first[i][k]*second[k][j];
	  } 
          multiply[i][j] = sum;
	  sum = 0;
    }
  }
  return 0;
}

int main( int argc, const char* argv[] )
{
  int i,j,iret;
  double** first = (double**) malloc(size*size*sizeof(double));
  double** second = (double**) malloc(size*size*sizeof(double));
  double** multiply = (double**) malloc(size*size*sizeof(double));
  double dtime;
  for (i = 0; i < size; i++) { //rows in first
    first[i] = (double*) malloc(size*sizeof(double));
    second[i] = (double*) malloc(size*sizeof(double));
    multiply[i] = (double*) malloc(size*sizeof(double));
    for (j = 0; j < size; j++) { //columns in first
      first[i][j]=i+j;
      second[i][j]=i-j;
    }
  }
  dtime = dclock();
  iret=mm(first,second,multiply); 
  dtime = dclock()-dtime;
  printf( "Time: %le \n", dtime);
  /*  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      printf("A[%d][%d]=%le \n",i,j,multiply[i][j]); 
    }
    }*/
  fflush( stdout );
  for (i = 0; i < size; i++) { //rows in first
    free(first[i]);
    free(second[i]);
    free(multiply[i]);
  }
  free(first);
  free(second);
  free(multiply);
  return iret;
}