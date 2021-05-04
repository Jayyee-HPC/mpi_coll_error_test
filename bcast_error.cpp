#include "mpi_error_test.h"

/* Bcast error test*/
int Error_Test_bcast(int argc, char **argv)
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
    int *sendbuf;
    char str[MPI_MAX_ERROR_STRING + 1];
    int slen;

    int test_num = std::stoi(argv[2]);
    ierr = 0;
    err = MPI_SUCCESS;
    root = 0;

    MPI_Comm_size(MPI_COMM_WORLD,&num_world_nodes);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_world_rank);


    if(num_world_nodes < 3)
    {
        printf("At least 3 processes are needed, only %d provided.\n", num_world_nodes);
        return 0;
    }

    sendbuf = (int *)malloc(sizeof(int) * ARRAYSIZE);

    if(my_world_rank == 0)
    {
        for(i = 0; i < ARRAYSIZE; ++i)
        {
            sendbuf[i] = i;
        }
    }
    else
    {
        for(i = 0; i < ARRAYSIZE; ++i)
        {
            sendbuf[i] = -1;
        }
    }

    switch(test_num)
    {
        case 0:
            /* Root send more */
            if (my_world_rank == root) 
            {
                size = ARRAYSIZE;
            }
            else
            {
                size = ARRAYSIZE/2;
            }

            err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);

            for (i = 0; i < size; ++i)
            {
                if(sendbuf[i] != i)
                    ++ierr;
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            ierr = 0;

            for (i = size; i < ARRAYSIZE; ++i)
            {
                if(root == my_world_rank && sendbuf[i] != i)
                {
                    ++ierr;
                }
                else if (root != my_world_rank && sendbuf[i] != -1)
                {
                    ++ierr;
                }
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on unexpected modifications\n", my_world_rank, ierr);
            }

            break;

        case 1:
            /* Root send less */
            if (my_world_rank == root) 
            {
                size = ARRAYSIZE/2;
            }
            else
            {
                size = ARRAYSIZE;
            }

            err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);

            for (i = 0; i < ARRAYSIZE/2; ++i)
            {
                if(sendbuf[i] != i)
                    ++ierr;
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            ierr = 0;

            for (i = ARRAYSIZE/2; i < ARRAYSIZE; ++i)
            {
                if(root == my_world_rank && sendbuf[i] != i)
                {
                    ++ierr;
                }
                else if (root != my_world_rank && sendbuf[i] != -1)
                {
                    ++ierr;
                }
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on unexpected modifications\n", my_world_rank, ierr);
            }
            break;

        case 2:
            /* NULL send buf */
            sendbuf = NULL;
            size = ARRAYSIZE;
            root = 0;

            err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);
            break;

        case 3:
            /* Mismatch datatype */
            size = ARRAYSIZE;
            root = 0;

            if (my_world_rank == 0) 
            {
                err = MPI_Bcast(sendbuf, size, MPI_UNSIGNED, root, MPI_COMM_WORLD);
            } 
            else 
            {
                err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);
            }

            for (i = 0; i < size; ++i)
            {
                if(sendbuf[i] != i)
                    ++ierr;
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 4:
            /* Mismatch root */
            size = ARRAYSIZE;

            if (my_world_rank == 0) 
            {
                root = 0;
            } 
            else
            {
                root = 5;
            }

            err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);

            for (i = 0; i < size; ++i)
            {
                if(sendbuf[i] != i)
                    ++ierr;
            }

            if (ierr)
            {
                printf("Rank %d, %d errors on receive\n", my_world_rank, ierr);
            }

            break;

        case 5:
            /* NULL COMM */
            size = ARRAYSIZE;
            root = 0;

            err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_NULL);
            break;

        case 6:
            /* Mismatch COMM */
            size = ARRAYSIZE;
            root = 0;

            if (my_world_rank == 0) 
            {
                err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_SELF);
            } 
            else 
            {
                err = MPI_Bcast(sendbuf, size, MPI_INT, root, MPI_COMM_WORLD);
            }
            break;

        default:
            printf("Test case %d is not defined.\n",test_num);
            break;
    }

    if (err == MPI_SUCCESS) {
        printf("Process %d found no error in bcast test %d \n", my_world_rank, test_num);
    } else {      
        MPI_Error_string(err, str, &slen); 
        printf("Process %d found error; message is: %s\n", my_world_rank, str);
    }

    free(sendbuf);
    return 0;
}
