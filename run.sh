pfgFolder=/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/Samples/
baseFolder=/afs/cern.ch/work/j/jlawhorn/public/CMSSW_9_2_10/src/MAHI/

filelist=(`ls ${pfgFolder}*root`)

doSkim=0
doMatrix=1
doPlot=0


for ((i=0; i<${#filelist[@]}; i++))
do
    outname=${filelist[i]##*/}
    outname=${outname%.*}
    echo $outname
    if [ ${doSkim} -eq 1 ]; then
	if [ ! -e ${baseFolder}/SkimmedData/${outname}_small.root ]; then
	    echo root -l -q MakeSmallTuples/Skim.C+\(\"${filelist[i]}\",\"${baseFolder}/SkimmedData/${outname}_small.root\"\)
	    root -l -q MakeSmallTuples/Skim.C+\(\"${filelist[i]}\",\"${baseFolder}/SkimmedData/${outname}_small.root\"\)
	fi
    fi
    if [ ${doMatrix} -eq 1 ]; then
	if [ ! -e ${baseFolder}/CovarianceMatrixFiles/${outname}.root ]; then
	    echo root -l -q CovarianceMatrices/MakeCovMatrixFromNoise.C+\(\"${baseFolder}\",\"${outname}\"\)
	fi
    fi    
    if [ ${doPlot} -eq 1 ]; then
	if [ ! -e ${baseFolder}/CovarianceMatrixPlots/${outname}.png ]; then
	    echo root -l -q CovarianceMatrices/DrawCovarianceMatrix.C+\(\"${baseFolder}\",\"${outname}\"\)
	fi
    fi
done