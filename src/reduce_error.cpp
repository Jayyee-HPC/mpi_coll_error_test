#include "mpi_error_test.h"

/* Gather error test*/
int Error_Test_reduce(int argc, char **argv)
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
    int ierr;
    int *sendbuf, *recvbuf;

    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;

    int test_num = std::stoi(argv[2]);

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
        sendbuf[i] = i+my_world_rank;
    }

    switch(test_num)
    {
        case 0:
            /* Root has larger buffer */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE/2, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            }
            break;

        case 1:
            /* Root has smaller buffer */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE/2, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            }
            break;

        case 2:
            /* NULL send buf */
            sendbuf = NULL;
            ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            break;

        case 3:
            /* Mismatch datatype */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_UNSIGNED, MPI_MAX, 0, MPI_COMM_WORLD);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            }
            break;


        case 4:
            /* Mismatch root */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 1, MPI_COMM_WORLD);
            }
            break;

        case 5:
            /* Mismatch operation */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
            }
            break;

        case 6:
            /* NULL COMM */
            ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_NULL);
            break;

        case 7:
            /* Mismatch COMM */
            if (my_world_rank == 0) 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_SELF);
            } 
            else 
            {
                ierr = MPI_Reduce(sendbuf, recvbuf, ARRAYSIZE, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
            }
            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (ierr == MPI_SUCCESS) {
        printf("Process %d found no error in reduce test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(ierr, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    free(recvbuf);
    return 0;
}
