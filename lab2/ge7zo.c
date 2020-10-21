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
  register unsigned int i,j,k;
  register unsigned int local_size = SIZE;
  for (k = 0; k < local_size; k++) { 
    for (i = k+1; i < local_size; i++) { 
      for (j = k+1; j < local_size; j++) { 
        if (j < local_size-4) {
          register double* Ai = A[i];
          register double* Aj = A[j];
          register double* Ak = A[k];
          register double Akk = Ak[k];
          register double Aik = Ai[k];
          Ai[j]=Ai[j]-Ak[j]*(Ai[k]/Akk);
          Ai[j+1]=Ai[j+1]-Ak[j+1]*(Aik/Akk);
          Ai[j+2]=Ai[j+2]-Ak[j+2]*(Aik/Akk);
          Ai[j+3]=Ai[j+3]-Ak[j+3]*(Aik/Akk);
          j=j+4;
        } else {
          A[i][j]=A[i][j]-A[k][j]*(A[i][k]/A[k][k]);
        }
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
}