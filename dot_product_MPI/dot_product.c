#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NELMS 1000000
#define MASTER 0
#define MAXPROCS 16

int DOT();
void INIT();

int main(int argc, char **argv) {
  int VECTORX[NELMS], VECTORY[NELMS];
  int PRODUCT, TMPPROD, SIDX, EIDX, SIZE, PID, NPROCS, RANK;
  double STIME, ETIME;
  MPI_Status STATUS;
  MPI_Comm WORLD;

  INIT(VECTORX, NELMS);
  INIT(VECTORY, NELMS);
  MPI_Init(&argc, &argv);
  WORLD = MPI_COMM_WORLD;
  MPI_Comm_size(WORLD, &NPROCS);
  MPI_Comm_rank(WORLD, &PID);  
  STIME = MPI_Wtime();  
  SIZE = NELMS/NPROCS;
  SIDX = PID*SIZE;
  EIDX = SIDX + SIZE;
  
  PRODUCT = DOT(SIDX, EIDX, VECTORX, VECOTRY);
  if(PID == MASTER) {
	for(int i = 1; i < NPROCS; i++){
	  MPI_Recv(&TMPPROD, 1, MPI_INT, i, 123, WORLD, &STATUS);
	  PRODUCT += TMPPROD;
	}
  }
  else{MPI_Send(&PRODUCT, 1, MPI_INT, MASTER, 123, WORLD);}
  
  ETIME = MPI_Wtime();

  if (PID == MASTER) {
    printf("PID=%d: final prod=%d\n", PID, PRODUCT);
    printf("PID=%d: elapsed=%f\n", PID, ETIME-STIME);
  }
  MPI_Finalize();
}

void INIT(int *X,int Y){
  for(int i = 0; i < Y; i++) {*X++ = Y;}
}

int DOT(int X,int Y, int *VECTORX, int *VECTORY){
  int PRODUCT=0;
  for(int i = X; i < Y; i++){PRODUCT = PRODUCT + VECTORX[i]*VECTORY[i];}
  return PRODUCT;
}
