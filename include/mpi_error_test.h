/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */
#ifndef __MPI_ERROR_TEST__H
#define __MPI_ERROR_TEST__H

#include <mpi.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#define VERBOSE 1
#define ARRAYSIZE 10

/***************************One to all, blocking************************************/
/* Bcast error test*/
int Error_Test_bcast(int argc, char **argv);

/* Scan error test*/
int Error_Test_exscan(int argc, char **argv);

/* Gather error test*/
int Error_Test_gather(int argc, char **argv);

/* Gatherv error test*/
int Error_Test_gatherv(int argc, char **argv);

/* Reduce error test*/
int Error_Test_reduce(int argc, char **argv);

/* Scan error test*/
int Error_Test_scan(int argc, char **argv);

/* Scatter error test*/
int Error_Test_scatter(int argc, char **argv);

/* Scatterv error test*/
int Error_Test_scatterv(int argc, char **argv);


/***************************One to all, non-blocking********************************/
/* Ibcast error test*/
int Error_Test_ibcast(int argc, char **argv);

/* Iscan error test*/
int Error_Test_iexscan(int argc, char **argv);

/* Igather error test*/
int Error_Test_igather(int argc, char **argv);

/* Igatherv error test*/
int Error_Test_igatherv(int argc, char **argv);

/* Ireduce error test*/
int Error_Test_ireduce(int argc, char **argv);

/* Iscan error test*/
int Error_Test_iscan(int argc, char **argv);

/* Iscatter error test*/
int Error_Test_iscatter(int argc, char **argv);

/* Iscatterv error test*/
int Error_Test_iscatterv(int argc, char **argv);


/***************************All to all, blocking************************************/
/* Allgather error test*/
int Error_Test_allgather(int argc, char **argv);

/* Allgatherv error test*/
int Error_Test_allgatherv(int argc, char **argv);

/* Allreduce error test*/
int Error_Test_allreduce(int argc, char **argv);

/* Alltoall error test*/
int Error_Test_alltoall(int argc, char **argv);

/* Alltoallv error test*/
int Error_Test_alltoallv(int argc, char **argv);

/* Alltoallw error test*/
int Error_Test_alltoallw(int argc, char **argv);


/***************************All to all, non-blocking********************************/
/* Iallgather error test*/
int Error_Test_iallgather(int argc, char **argv);

/* Iallgatherv error test*/
int Error_Test_iallgatherv(int argc, char **argv);

/* Iallreduce error test*/
int Error_Test_iallreduce(int argc, char **argv);

/* Ialltoall error test*/
int Error_Test_ialltoall(int argc, char **argv);

/* Ialltoallv error test*/
int Error_Test_ialltoallv(int argc, char **argv);

/* Ialltoallw error test*/
int Error_Test_ialltoallw(int argc, char **argv);

/***************************Detailed tests******************************************/
int Error_Test_dgather(int argc, char **argv);

#endif //ndef __MPI_ERROR_TEST__H
