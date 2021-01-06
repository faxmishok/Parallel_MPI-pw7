#include	<stdio.h>
#include	<mpi.h>

void main(int argc, char *argv[])
{
  int rank, size, left_proc, right_proc;
  int val, sum, tmp;
  MPI_Status recv_status, send_status;
  MPI_Request send_request;

  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
     
  if ((left_proc=(rank-1)) < 0) left_proc = size-1;
  if ((right_proc=(rank+1)) == size) right_proc = 0;
  
  val = rank;
  sum = 0;
  do {
    MPI_Issend(&val,1,MPI_INT,right_proc,99,MPI_COMM_WORLD,&send_request);
    MPI_Recv(&tmp,1,MPI_INT,left_proc,99,MPI_COMM_WORLD,&recv_status);
    MPI_Wait(&send_request,&send_status);
    val = tmp;
    sum += val;
  } while (val != rank);

  printf("Proc %d sum = %d \n", rank, sum);

  MPI_Finalize();

}