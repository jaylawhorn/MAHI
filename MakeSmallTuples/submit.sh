#!/bin/bash

#cmsdir=$1
#builddir=$2
#file=$3
#eosfolder=$4
#routfolder=$5

eosfolders=(/eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias1/Run2017A-v1_RAW_20170630_074719/170630_054747/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias2/Run2017A-v1_RAW_20170630_041116/170630_021144/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias3/Run2017A-v1_RAW_20170630_041236/170630_021305/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias4/Run2017A-v1_RAW_20170630_041327/170630_021354/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias5/Run2017A-v1_RAW_20170630_041430/170630_021500/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias6/Run2017A-v1_RAW_20170630_041534/170630_021604/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias7/Run2017A-v1_RAW_20170630_041639/170630_021708/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias8/Run2017A-v1_RAW_20170630_041733/170630_021802/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias9/Run2017A-v1_RAW_20170630_041833/170630_021903/0000/ \
    /eos/cms/store/user/jlawhorn/HEP17_PHASE_SCAN/ZeroBias10/Run2017A-v1_RAW_20170630_041026/170630_021057/0000/)

modifiers=(Run2017A_ZeroBias1 Run2017A_ZeroBias2 Run2017A_ZeroBias3 Run2017A_ZeroBias4 Run2017A_ZeroBias5 Run2017A_ZeroBias6 \
    Run2017A_ZeroBias7 Run2017A_ZeroBias8 Run2017A_ZeroBias9 Run2017A_ZeroBias10)

outfolder=/afs/cern.ch/work/j/jlawhorn/public/Candidacy/CMSSW_9_2_3_patch2/src/MAHI/SkimmedData/

endcount=`expr  ${#eosfolders[@]} - 1`

for i in $(seq 0 ${endcount})
do
    echo $i ${modifiers[$i]}

    for file in `ls ${eosfolders[$i]} | grep root`
    do
	bsub -q 1nh run.sh ${CMSSW_BASE} `pwd` $file ${eosfolders[$i]} $outfolder ${modifiers[$i]}
    done

done

#for file in `ls ${eosfolder} | grep root`
#do
#    #if [[ -e ${outfolder}/${file} ]]; then
#    #echo "Output file exists. Not submitting."
#    #else
#    #echo run.sh `pwd` $file $eosfolder $outfolder
#    bsub -q 1nh run.sh ${CMSSW_BASE} `pwd` $file $eosfolder $outfolder $modifier
#    #fi
#
#done