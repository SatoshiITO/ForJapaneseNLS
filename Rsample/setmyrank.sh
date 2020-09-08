#/bin/bash
MYRANK=`cat MPISHELL_MYRANK`
echo $MYRANK
sed s/jobID/${MYRANK}/g < ../template.r > sample.r
