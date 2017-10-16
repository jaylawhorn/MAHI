doSkim=0
doMatrix=0
doPlot=1


pfgFolder=/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/Samples/
#pfgFolder=/eos/cms/store/user/jlawhorn/HEP17_TIMED_IN/
baseFolder=/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI/

filelist=(`ls ${baseFolder}/SkimmedData/*root`)

if [ ${doSkim} -eq 1 ]; then
    filelist=(`ls ${pfgFolder}/*root`)
elif [ ${doPlot} -eq 1 ]; then
    filelist=(`ls ${baseFolder}/CovarianceMatrixFiles/*root`)
fi

for ((i=0; i<${#filelist[@]}; i++))
do
    outname=${filelist[i]##*/}
    if [ ${doSkim} -eq 1 ]; then 
	outname=${outname%.*}
    elif [ ${doPlot} -eq 1 ]; then
	outname=${outname%.*}
    else
	outname=${outname%_*}
    fi
    echo $outname
    if [ ${doSkim} -eq 1 ]; then
	if [ ! -e ${baseFolder}/SkimmedData/${outname}_skim.root ]; then
	    echo root -l -q MakeSmallTuples/Skim.C+\(\"${filelist[i]}\",\"${baseFolder}/SkimmedData/${outname}_skim.root\"\)
	    root -l -q MakeSmallTuples/Skim.C+\(\"${filelist[i]}\",\"${baseFolder}/SkimmedData/${outname}_skim.root\"\)
	fi
    fi
    if [ ${doMatrix} -eq 1 ]; then
	if [ ! -e ${baseFolder}/CovarianceMatrixFiles/${outname}.root ]; then
	    echo root -l -q CovarianceMatrices/MakeCovMatrixFromNoise.C+\(\"${baseFolder}\",\"${outname}\"\)
	    root -l -q CovarianceMatrices/MakeCovMatrixFromNoise.C+\(\"${baseFolder}\",\"${outname}\"\)

	fi
    fi    
    if [ ${doPlot} -eq 1 ]; then
	if [ ! -e ${baseFolder}/CovarianceMatrixPlots/${outname}.png ]; then
	    echo root -l -q CovarianceMatrices/DrawCorrelationMatrix.C+\(\"${baseFolder}\",\"${outname}\"\)
	    root -l -q CovarianceMatrices/DrawCorrelationMatrix.C+\(\"${baseFolder}\",\"${outname}\"\)
	fi
    fi
done