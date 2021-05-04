#include "mpi_error_test.h"

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("One OP number and one test case number are needed.\n");
        printf("Example: mpirun -np 4 ./prog 0 0 \n\t Bcast test case 0\n");
        printf("OP: \n\t 0 bcast \n\t 1 gather \n");
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
            Error_Test_gather(argc, argv);
            break;

        case 2:
            Error_Test_reduce(argc, argv);
            break;

        case 3:
            Error_Test_igather(argc, argv);
            break;
            
        default:
            printf("Collective %d is not defined.\n",op_num);
            printf("0 bcast, 1 gather, 2 reduce, 3 igather.\n");
            break;
    }

    MPI_Finalize();
    return 0;
}
