#include "mpi_error_test.h"

void printf_test_list(void)
{
    printf("0 bcast, 1 exscan, 2 gather, 3, gatherv, 4 reduce, 5 scan, 6 scatter, 7 scatterv.\n");
    printf("8 allgather, 9 allgatherv, 10 allreduce, 11 alltoall, 12 alltoallv, 13 alltoallw.\n");
    printf("14 ibcast, 15 iexscan, 16 igather, 17, igatherv, 18 ireduce, 19 iscan, 20 iscatter, 21 iscatterv.\n");
    printf("22 iallgather, 23 iallgatherv, 24 iallreduce, 25 ialltoall, 26 ialltoallv, 27 ialltoallw.\n");
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("One OP number and one test case number are needed.\n");
        printf("Example: mpirun -np 4 ./prog 0 0 \n\t Bcast test case 0\n");
        printf_test_list();
        return 0;
    }

    //MPI initial    
    MPI_Init(&argc,&argv);

    int op_num = std::stoi(argv[1]);

    switch(op_num)
    {
        case 0:
            Error_Test_bcast(argc, argv);
            break;

        case 1:
            Error_Test_exscan(argc, argv);
            break;

        case 2:
            Error_Test_gather(argc, argv);
            break;

        case 3:
            Error_Test_gatherv(argc, argv);
            break;

        case 4:
            Error_Test_reduce(argc, argv);
            break;

        case 5:
            Error_Test_scan(argc, argv);
            break;
            
        case 6:
            Error_Test_scatter(argc, argv);
            break;

        case 7:
            Error_Test_scatterv(argc, argv);
            break;

        case 8:
            Error_Test_allgather(argc, argv);
            break;

        case 9:
            Error_Test_allgatherv(argc, argv);   

        case 10:
            Error_Test_allreduce(argc, argv); 

        case 11:
            Error_Test_alltoall(argc, argv); 
           
        case 12:
            Error_Test_alltoallv(argc, argv); 
            
        case 13:
            Error_Test_alltoallw(argc, argv); 

        case 14:
            Error_Test_ibcast(argc, argv);
            break;

        case 15:
            Error_Test_iexscan(argc, argv);
            break;

        case 16:
            Error_Test_igather(argc, argv);
            break;

        case 17:
            Error_Test_igatherv(argc, argv);
            break;

        case 18:
            Error_Test_ireduce(argc, argv);
            break;

        case 19:
            Error_Test_iscan(argc, argv);
            break;
            
        case 20:
            Error_Test_iscatter(argc, argv);
            break;

        case 21:
            Error_Test_iscatterv(argc, argv);
            break;

        case 22:
            Error_Test_iallgather(argc, argv);
            break;

        case 23:
            Error_Test_iallgatherv(argc, argv);   

        case 24:
            Error_Test_iallreduce(argc, argv); 

        case 25:
            Error_Test_ialltoall(argc, argv); 
           
        case 26:
            Error_Test_ialltoallv(argc, argv); 
            
        case 27:
            Error_Test_ialltoallw(argc, argv); 

        default:
            printf("Collective %d is not defined.\n",op_num);
            printf_test_list();
            break;
    }

    MPI_Finalize();
    return 0;
}
