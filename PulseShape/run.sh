#!/bin/bash

builddir=$1
file=$2
eosfolder=$3
outfolder=$4

workDir=`pwd`
echo `hostname`
echo "args:    $*"

SCRAM_ARCH=slc6_amd64_gcc491

cd ${builddir}
eval `scramv1 runtime -sh`
#cmsenv
cd ${workDir}
which root

cp ${builddir}/makeRecHitTree.C .
cp ${builddir}/rootlogon.C .

root -l -q makeRecHitTree.C+\(\"${eosfolder}${file}\",\"${outfolder}${file}\"\)

status=`echo $?`
echo "Status - $status"

exit $status