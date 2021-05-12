#include "mpi_error_test.h"

/* Gather error test*/
int Error_Test_igatherv(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("Two test case numbers is needed.\n");
        return 0;
    }

    //MPI initial
    int my_world_rank;
    int num_world_nodes;
    int i, size, root;
    int ierr, err;
    int *sendbuf, *recvbuf;
    int *recvcounts, *displs;
    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;
    MPI_Request request;
    MPI_Status status;
    status.MPI_ERROR = MPI_SUCCESS;

    int test_num = std::stoi(argv[2]);

    ierr = 0;
    err = MPI_SUCCESS;
    root = 0;

    MPI_Comm_size(MPI_COMM_WORLD,&num_world_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_world_rank);
    ierr = MPI_SUCCESS;

    if(num_world_nodes < 3)
    {
        printf("At least 3 processes are needed.\n");
        return 0;
    }

    sendbuf = (int *)malloc(sizeof(int) * ARRAYSIZE);
    recvbuf = (int *)malloc(sizeof(int) * ARRAYSIZE * num_world_nodes);
    recvcounts = (int *)malloc(sizeof(int) * num_world_nodes);
    displs = (int *)malloc(sizeof(int) * num_world_nodes); 

    for(i = 0; i < ARRAYSIZE; ++i)
    {
        sendbuf[i] = i+my_world_rank*ARRAYSIZE;
    }

    for(i = 0; i < num_world_nodes; ++i)
    {
        recvcounts[i] = ARRAYSIZE;
        displs[i] = i * ARRAYSIZE;
    }

    if(root == my_world_rank)
    {
        for(i = 0; i < ARRAYSIZE * num_world_nodes; ++i)
        {
            recvbuf[i] = -1;
        }
    }

    switch(test_num)
    {
        case 0:
            /* Root gather more */
            root = 0;

            if (my_world_rank == root) 
            {
                size = ARRAYSIZE;
            } 
            else 
            {
                size = ARRAYSIZE/2;
            }

            err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            if (my_world_rank == 0) 
            {
                for(i = 0; i < num_world_nodes * size; ++i)
                {                   
                    if(recvbuf[i] != i)
                        ++ierr;
                }
            } 

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }
            break;

        case 1:
            /* Root gather less */
            root = 0;

            if (my_world_rank == 0) 
            {
                size = ARRAYSIZE/2;
            } 
            else 
            {
                size = ARRAYSIZE;
            }

            err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            if (my_world_rank == root) 
            {
                for(i = 0; i < num_world_nodes * size; ++i)
                {                 
                    if(recvbuf[i] != i)
                        ++ierr;
                }
            } 

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 2:
            /* NULL send buf */
            size = ARRAYSIZE;
            root = 0;
            sendbuf = NULL;

            err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
            break;

        case 3:
            /* Mismatch datatype */
            size = ARRAYSIZE;
            root = 0;

            if (my_world_rank == 0) 
            {
                err = MPI_Igatherv(sendbuf, size, MPI_UNSIGNED, recvbuf, recvcounts, displs, MPI_UNSIGNED, root, MPI_COMM_WORLD, &request);
            } 
            else 
            {
                err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            break;

        case 4:
            /* Mismatch root */
            size = ARRAYSIZE;
            root = 0;

            if (my_world_rank == 0) 
            {
                root = 0;
            } 
            else 
            {
                root = 1;
            }

            err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            break;

        case 5:
            /* NULL COMM */
            size = ARRAYSIZE;
            root = 0;

            err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_NULL, &request);
            MPI_Wait(&request, &status);

            break;

        case 6:
            /* Mismatch COMM */
            size = ARRAYSIZE;
            root = 0;

            if (my_world_rank == root) 
            {
                err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_SELF, &request);
            } 
            else 
            {
                err = MPI_Igatherv(sendbuf, size, MPI_INT, recvbuf, recvcounts, displs, MPI_INT, root, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in igatherv test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    free(recvbuf);
    free(recvcounts);
    free(displs);
    return 0;
}
