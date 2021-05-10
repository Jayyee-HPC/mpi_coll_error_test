#include "mpi_error_test.h"

/* Iallreduce error test*/
int Error_Test_iallreduce(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Two test case numbers is needed.\n");
        return 0;
    }

    //MPI initial
    int my_world_rank;
    int num_world_nodes;
    int i, size;
    int ierr, err;
    int *sendbuf, *recvbuf;
    MPI_Request request;
    MPI_Status status;

    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;

    int test_num = std::stoi(argv[2]);

    ierr = 0;
    err = MPI_SUCCESS;

    MPI_Comm_size(MPI_COMM_WORLD,&num_world_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_world_rank);
    ierr = MPI_SUCCESS;

    if(num_world_nodes < 3)
    {
        printf("At least 3 processes are needed.\n");
        return 0;
    }

    sendbuf = (int *)malloc(sizeof(int) * ARRAYSIZE);
    recvbuf = (int *)malloc(sizeof(int) * ARRAYSIZE);

    for(i = 0; i < ARRAYSIZE; ++i)
    {
        sendbuf[i] = i+my_world_rank*ARRAYSIZE;
    }

    for(i = 0; i < ARRAYSIZE * num_world_nodes; ++i)
    {
        recvbuf[i] = -1;
    }

    switch(test_num)
    {
        case 0:
            /* Rank 0 gather more */
            if (my_world_rank == 0) 
            {
                size = ARRAYSIZE;               
            } 
            else 
            {
                size = ARRAYSIZE/2;
            }

            err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                   
                //TODO::
            }

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }
            break;

        case 1:
            /* Rank 0 gather less */
            if (my_world_rank == 0) 
            {
                size = ARRAYSIZE/2;
            } 
            else 
            {
                size = ARRAYSIZE;
            }

            err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                 
                //TODO::
            }

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 2:
            /* NULL send buf */
            size = ARRAYSIZE;
            sendbuf = NULL;

            err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            break;

        case 3:
            /* Mismatch datatype */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_UNSIGNED, MPI_MAX, MPI_COMM_WORLD, &request);
            } 
            else 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                 
                //TODO::
            }

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 4:
            /* NULL COMM */
            size = ARRAYSIZE;

            err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_NULL, &request);
            MPI_Wait(&request, &status);

            break;

        case 6:
            /* Mismatch COMM */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_SELF, &request);
            } 
            else 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            break;

        case 7:
            /* Mismatch OP */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MAX, MPI_COMM_WORLD, &request);
            } 
            else 
            {
                err = MPI_Iallreduce(sendbuf, recvbuf, size, MPI_INT, MPI_MIN, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in allreduce test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    free(recvbuf);
    return 0;
}
