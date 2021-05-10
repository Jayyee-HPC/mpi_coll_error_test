#include "mpi_error_test.h"

/* Iscatter error test*/
int Error_Test_iscatter(int argc, char **argv)
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
    int err, ierr;
    int *sendbuf, *recvbuf;
    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;
    MPI_Request request;
    MPI_Status status;

    int test_num = std::stoi(argv[2]);
    ierr = 0;
    err = MPI_SUCCESS;

    MPI_Comm_size(MPI_COMM_WORLD,&num_world_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_world_rank);


    if(num_world_nodes < 3)
    {
        printf("At least 3 processes are needed, only %d provided.\n", num_world_nodes);
        return 0;
    }

    sendbuf = (int *)malloc(sizeof(int) * ARRAYSIZE * num_world_nodes);
    recvbuf = (int *)malloc(sizeof(int) * ARRAYSIZE);

    root = 0;
    if(my_world_rank == root)
    {
        for(i = 0; i < ARRAYSIZE * num_world_nodes; ++i)
        {
            sendbuf[i] = i + my_world_rank * ARRAYSIZE;
        }
    }

    for(i = 0; i < ARRAYSIZE; ++i)
    {
        recvbuf[i] = -1;
    }


    switch(test_num)
    {
        case 0:
            /* rank 0 scatter more */
            if (my_world_rank == 0) 
            {
                size = ARRAYSIZE;
            }
            else
            {
                size = ARRAYSIZE/2;
            }

            err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            if(VERBOSE)
            {
                ierr = 0;
                for(int i = 0; i < size; ++i)
                {
                    if(recvbuf[i] != i + my_world_rank*size)
                    {
                        ++ierr;
                    }
                }

                if(ierr)
                {
                    printf("Rank %d, %d errors \n", my_world_rank, ierr);
                }
            }

            break;

        case 1:
            /* Root scatter less */
            if (my_world_rank == 0) 
            {
                size = ARRAYSIZE/2;
            }
            else
            {
                size = ARRAYSIZE;
            }

            err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            if(VERBOSE)
            {
                ierr = 0;
                for(int i = 0; i < size; ++i)
                {
                    if(recvbuf[i] != i + my_world_rank*size)
                    {
                        ++ierr;
                    }
                }

                if(ierr)
                {
                    printf("Rank %d, %d errors \n", my_world_rank, ierr);
                }
            }


            break;

        case 2:
            /* NULL send buf */
            sendbuf = NULL;
            size = ARRAYSIZE;

            err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);

            if(VERBOSE)
            {
                ierr = 0;
                for(int i = 0; i < size; ++i)
                {
                    /* TODO: */

                }

                if(ierr)
                {
                    printf("Rank %d, %d errors \n", my_world_rank, ierr);
                }
            }

            break;

        case 3:
            /* Mismatch datatype */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                err = MPI_Iscatter(sendbuf, size, MPI_UNSIGNED, recvbuf, size, MPI_UNSIGNED, root, MPI_COMM_WORLD, &request);
            } 
            else 
            {
                err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            if(VERBOSE)
            {
                ierr = 0;
                for(int i = 0; i < size; ++i)
                {
                    if(recvbuf[i] != i + my_world_rank*size)
                    {
                        ++ierr;
                    }
                }

                if(ierr)
                {
                    printf("Rank %d, %d errors \n", my_world_rank, ierr);
                }
            }


            break;

        case 4:
            /* NULL COMM */
            size = ARRAYSIZE;

            err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_NULL, &request);
            MPI_Wait(&request, &status);

            break;

        case 5:
            /* Mismatch COMM */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_SELF, &request);
            } 
            else 
            {
                err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            }
            MPI_Wait(&request, &status);

            break;

        case 6:
            /* Mismatch root */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                root = 0;
            } 
            else 
            {
                root = 1;
            }

            err = MPI_Iscatter(sendbuf, size, MPI_INT, recvbuf, size, MPI_INT, root, MPI_COMM_WORLD, &request);
            MPI_Wait(&request, &status);
            
            if(VERBOSE)
            {
                ierr = 0;
                for(int i = 0; i < size; ++i)
                {
                    if(recvbuf[i] != i + my_world_rank*size)
                    {
                        ++ierr;
                    }
                }

                if(ierr)
                {
                    printf("Rank %d, %d errors \n", my_world_rank, ierr);
                }
            }

            break;    

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in iscatter test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(recvbuf);
    free(sendbuf);
    return 0;
}
