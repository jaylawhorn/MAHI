#!/bin/bash

cmsdir=$1
builddir=$2
file=$3
eosfolder=$4
outfolder=$5
modifier=$6

workDir=`pwd`
echo `hostname`
echo "args:    $*"

SCRAM_ARCH=slc6_amd64_gcc530

cd ${cmsdir}
eval `scramv1 runtime -sh`
#cmsenv
cd ${workDir}
which root

cp ${builddir}/Skim.C .

root -l -b -q Skim.C+\(\"${eosfolder}${file}\",\"${outfolder}${modifier}_${file}\"\)

#cp Output.root ${outfolder}${file}
#xrdcp Output.root root://eoscms/${outfolder}${file}

status=`echo $?`
echo "Status - $status"

exit $status