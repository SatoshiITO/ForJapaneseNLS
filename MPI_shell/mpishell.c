#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main( int argc, char *argv[]){
  int nPE,myrank;
  char buff[128];

  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD,&nPE);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

  printf("MPI rank ID is stored in MPISHELL_MYRANK file.\n");
  sprintf(buff,"echo %d > MPISHELL_MYRANK",myrank);
  system(buff);

  if ( myrank == 0 ) fprintf(stdout,"MPI_shell: %s\n",argv[1]);
  system(argv[1]);

  MPI_Finalize();
  return 0;
}
