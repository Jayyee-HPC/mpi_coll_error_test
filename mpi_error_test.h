/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */
#ifndef __MPI_ERROR_TEST__H
#define __MPI_ERROR_TEST__H

#include "mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define ARRAYSIZE 1024

/* Bcast error test*/
int Error_Test_bcast(int argc, char **argv);

/* Gather error test*/
int Error_Test_gather(int argc, char **argv);

/* Reduce error test*/
int Error_Test_reduce(int argc, char **argv);

/* Igather error test*/
int Error_Test_igather(int argc, char **argv);

#endif //ndef __MPI_ERROR_TEST__H
