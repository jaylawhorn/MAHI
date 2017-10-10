#!/bin/bash


#eosfolder=/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/HighPtJet80/Samples/160522_083815/0000/
eosfolder=/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias/Run2017B-v1_RAW_20170621_162843/170621_142916/0000/

#outfolder=/afs/cern.ch/work/j/jlawhorn/HighPtJet80v2/
outfolder=/afs/cern.ch/work/j/jlawhorn/public/HEP17Timing/CMSSW_9_2_0_patch5/src/PulseShapes/OUTPUT2/

for file in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${eosfolder} | grep root`
do
    #if [[ -e ${outfolder}/${file} ]]; then
    #echo "Output file exists. Not submitting."
    #else
    #echo run.sh `pwd` $file $eosfolder $outfolder
    #bsub -q 8nm run.sh ${CMSSW_BASE} $file $eosfolder $outfolder
    bsub -q 1nh run.sh `pwd` $file $eosfolder $outfolder
    #fi
    #exit
    #break

done