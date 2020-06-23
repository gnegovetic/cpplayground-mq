/*
 * Copyright (c) 2007      Sun Microsystems, Inc.  All rights reserved.
 */

/*
 * Test the connectivity between all processes.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <mpi.h>
#include <memory>
using namespace std;

int main(int argc, char **argv)
{
    MPI_Status  status;
    int         verbose = 0;
    int         rank;
    int         np;        /* number of processes in job */
    //int         peer;
    int         i;
    int         j;
    int         length;
    char        name[MPI_MAX_PROCESSOR_NAME+1];

    const int32_t kMsgSize = 4096;
    using byte = uint8_t;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    /*
     * If we cannot get the name for whatever reason, just
     * set it to unknown. */
    if (MPI_SUCCESS != MPI_Get_processor_name(name, &length)) {
        strcpy(name, "unknown");
    }

    if (argc>1 && strcmp(argv[1], "-v")==0)
        verbose = 1;

    if (verbose) {
        printf("Rank = %d, num of processes = %d\n", rank, np);
    }

    auto sendBuf = make_unique<byte[]>(kMsgSize);
    auto rcvBuf = make_unique<byte[]>(kMsgSize);

    for (i=0; i<np; i++) {
        if (rank==i) {
            /* rank i sends to and receives from each higher rank */
            for(j=i+1; j<np; j++) {
                if (verbose)
                    printf("checking connection between rank %d on %s and rank %-4d\n",
                           i, name, j);
                
                MPI_Send(sendBuf.get(), kMsgSize, MPI_BYTE, j, rank, MPI_COMM_WORLD);
                MPI_Recv(rcvBuf.get(), kMsgSize, MPI_BYTE, j, j, MPI_COMM_WORLD, &status);
            }
        } else if (rank>i) {
            /* receive from and reply to rank i */
            MPI_Recv(rcvBuf.get(), kMsgSize, MPI_BYTE, i, i, MPI_COMM_WORLD, &status);
            MPI_Send(sendBuf.get(), kMsgSize, MPI_BYTE, i, rank, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    if (verbose && rank==0)
        printf("Connectivity test on %d processes PASSED.\n", np);

    MPI_Finalize();
    return 0;
}
