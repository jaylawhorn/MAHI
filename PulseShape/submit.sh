#!/bin/bash


#eosfolder=/store/group/dpg_hcal/comm_hcal/RecoAlgos/Summer16Method2Update/HcalNtuple/HighPtJet80/Samples/160522_083815/0000/
eosfolder=/eos/cms/store/user/jlawhorn/October27_PhaseScans/ZeroBias/Run2017F-v1_RAW_20171027_105203/171027_085305/0000/

#outfolder=/afs/cern.ch/work/j/jlawhorn/HighPtJet80v2/
outfolder=/afs/cern.ch/work/j/jlawhorn/public/phaseScan/CMSSW_9_2_10/src/MAHI/PulseShape/output2/

for file in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${eosfolder} | grep root`
do
    #if [[ -e ${outfolder}/${file} ]]; then
    #echo "Output file exists. Not submitting."
    #else
    #./run.sh `pwd` $file $eosfolder $outfolder
    #bsub -q 8nm run.sh ${CMSSW_BASE} $file $eosfolder $outfolder
    bsub -q 1nh run.sh `pwd` $file $eosfolder $outfolder
    #fi
    #exit
    #break

done