#!/bin/bash -x
#PJM --rsc-list "rscgrp=small"
#PJM --rsc-list "elapse=00:30:00"
#PJM --rsc-list "node=1"
#PJM --mpi "proc=1"
#PJM --mpi "use-rankdir"
#PJM --stg-transfiles all
#PJM --stgin "rank=0 /home/hp******/k*****/public/R-3.0.1.tar.gz 0:../"
#PJM --stgin "rank=* ./sample.r %r:./"
##PJM --stgout "rank=* %r:result.txt ./Result/result%r.txt"
#PJM -S
#
. /work/system/Env_base
#
#cd ..
tar xvzf ../R-3.0.1.tar.gz
cd R-3.0.1
export R_HOME=`pwd`/lib64/R
export LD_LIBRARY_PATH=$R_HOME/lib:$LD_LIBRARY_PATH
cd ..
#
./R-3.0.1/lib64/R/bin/exec/R --no-save --vanilla < ./sample.r
