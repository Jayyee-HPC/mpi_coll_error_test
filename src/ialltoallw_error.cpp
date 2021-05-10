#include "mpi_error_test.h"

/* Gather error test*/
int Error_Test_ialltoallw(int argc, char **argv)
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
    int *sendcounts, *sdispls, *recvcounts, *rdispls;
    MPI_Datatype *sendtypes, *recvtypes;
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
    recvbuf = (int *)malloc(sizeof(int) * ARRAYSIZE * num_world_nodes);
    sendcounts = (int *)malloc(sizeof(int) * num_world_nodes);
    sdispls = (int *)malloc(sizeof(int) * num_world_nodes);
    recvcounts = (int *)malloc(sizeof(int) * num_world_nodes);
    rdispls = (int *)malloc(sizeof(int) * num_world_nodes);
    sendtypes = (MPI_Datatype *)malloc(sizeof(MPI_Datatype) * num_world_nodes);
    recvtypes = (MPI_Datatype *)malloc(sizeof(MPI_Datatype) * num_world_nodes);

    for(i = 0; i < ARRAYSIZE; ++i)
    {
        sendbuf[i] = i+my_world_rank*ARRAYSIZE;
    }

    for(i = 0; i < ARRAYSIZE * num_world_nodes; ++i)
    {
        recvbuf[i] = -1;
    }

    for(i = 0; i < num_world_nodes; ++i)
    {
        sendcounts[i] = ARRAYSIZE;
        sdispls[i] = i * ARRAYSIZE;
        recvcounts[i] = ARRAYSIZE;
        rdispls[i] = i * ARRAYSIZE;
        sendtypes[i] = MPI_INT;
        recvtypes[i] = MPI_INT;
    }

    switch(test_num)
    {
        case 0:
            /* Rank 0 send more */
            if (my_world_rank != 0) 
            {
                for(i = 0; i < num_world_nodes; ++i)
                {
                    sendcounts[i] = ARRAYSIZE/2;
                    recvcounts[i] = ARRAYSIZE/2;
                }
            }

            err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                   
                //TODO
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
                for(i = 0; i < num_world_nodes; ++i)
                {
                    sendcounts[i] = ARRAYSIZE/2;
                    recvcounts[i] = ARRAYSIZE/2;
                }
            } 

            err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                 
                //TODO
            }

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 2:
            /* NULL send buf */
            sendbuf = NULL;

            err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            break;

        case 3:
            /* Mismatch datatype */

            if (my_world_rank == 0) 
            {
                for(i = 0; i < num_world_nodes; ++i)
                {
                    sendtypes[i] = MPI_UNSIGNED;
                    recvtypes[i] = MPI_UNSIGNED;
                }

                err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_WORLD, &request);
            } 
            else 
            {
                err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            for(i = 0; i < num_world_nodes * size; ++i)
            {                 
                //TODO
            }

            if(ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 4:
            /* NULL COMM */

            err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_NULL, &request);
            MPI_Wait(&request, &status);

            break;

        case 6:
            /* Mismatch COMM */

            if (my_world_rank == 0) 
            {
                err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_SELF, &request);
            } 
            else 
            {
                err = MPI_Ialltoallw(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts,rdispls, recvtypes, MPI_COMM_NULL, &request);
            }
            MPI_Wait(&request, &status);

            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in ialltoallw test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    free(recvbuf);
    free(sendcounts);
    free(sdispls);
    free(recvcounts);
    free(rdispls);
    return 0;
}
