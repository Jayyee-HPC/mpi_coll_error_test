#include "mpi_error_test.h"

/* Gather error test*/
int Error_Test_dgather(int argc, char **argv)
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

    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;

    int test_num = std::stoi(argv[2]);

    size = 1024*1024;

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

    sendbuf = (int *)malloc(sizeof(int) * size);
    recvbuf = (int *)malloc(sizeof(int) * size * num_world_nodes);

    for(i = 0; i < size; ++i)
    {
        sendbuf[i] = i+my_world_rank*ARRAYSIZE;
    }

    if(root == my_world_rank)
    {
        for(i = 0; i < size * num_world_nodes; ++i)
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

            } 
            else 
            {
                size = size/1024;
            }

            err = MPI_Gather(sendbuf, ARRAYSIZE/2, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);

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
                size = size/1024;
            } 
            else 
            {

            }

            err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);

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
            /* NULL recv buf */
            root = 0;
            recvbuf = NULL;

            err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);
            break;

        case 3:
            /* all use different buffer size */
            size = size - my_world_rank;

            err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);

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

        case 4:
            /* all use different buffer size */
            size = size - num_world_nodes + my_world_rank;

            err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);

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

        case 5:
            /* NULL COMM */
            root = 0;

            err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_NULL);
            break;

        case 6:
            /* Mismatch COMM */
            root = 0;

            if (my_world_rank == root) 
            {
                err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_SELF);
            } 
            else 
            {
                err = MPI_Gather(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD);
            }

            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in detailed gather test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    free(recvbuf);
    return 0;
}
