#!/bin/sh -x
#PJM --rsc-list "rscgrp=small"
#PJM --rsc-list "node=1"
#PJM --mpi "proc=4"
#PJM --rsc-list "elapse=00:03:00"
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* /home/hp******/k*****/public/bin/mpich-3.0.3-gnu/bin/mpiexec.hydra %0:../"
#PJM --stgin "rank=* ./a.out %r:./"
#PJM -S
#
. /work/system/Env_base
#
### Hello world!
#../mpiexec.hydra ./a.out
mpiexec.hydra ./a.out
