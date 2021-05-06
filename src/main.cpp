#include "mpi_error_test.h"

static void printf_test_list(void)
{
    printf("0 bcast, 1 exscan, 2 gather, 3 reduce, 3 igather, 4 scan, 5 scatter, 6 scatterv.\n");
    printf("7 igather.\n");
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
            Error_Test_reduce(argc, argv);
            break;

        case 4:
            Error_Test_scan(argc, argv);
            break;
            
        case 5:
            Error_Test_scatter(argc, argv);
            break;

        case 6:
            Error_Test_scatterv(argc, argv);
            break;

        case 7:
            Error_Test_igather(argc, argv);
            break;

        default:
            printf("Collective %d is not defined.\n",op_num);
            printf_test_list();
            break;
    }

    MPI_Finalize();
    return 0;
}
