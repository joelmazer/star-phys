
//____________________________________________________________________________________________________
// Example macro for StRefMutlCorr class implementation
//   * Before accessing centrality bins via StRefMutlCorr, you must call 'init(const Int_t RunId)'
//     to specify which parameters you want to use
//     - If you stick to the one specific run, you only need to call this function once in your code.
//     - If you read data from multiple different runs, you need to call this function
//       whenever you switch to the run number
//
//   * In the standard STAR analysis maker, the best (and only) place to call 'init(...)' function 
//     is 'Make(...)'
void getCentralityBins()
{
  gSystem->Load("StRefMultCorr");
  StRefMultCorr* refmultCorrUtil = new StRefMultCorr();

  // You need to specify the run number you are going to process
  refmultCorrUtil->init(11078000);

  // Dummy refmult and primary z-vertex
  const UShort_t refmult = 100 ;
  const Double_t vz      = 20.0 ;

  // Get centrality bins
  //   see StRefMultCorr.h for the definition of centrality bins
  const Int_t cent16 = refmultCorrUtil->getCentralityBin16(refmult, vz) ;
  const Int_t cent9  = refmultCorrUtil->getCentralityBin9(refmult, vz) ;

  // Re-weighting corrections for peripheral bins
  const Double_t reweight = refmultCorrUtil->getWeight(refmult, vz) ;

  //----------------------------------------------------------------------------------------------------
  // Not really necessary for your study but if you want to see the corrected refmult distribution
  // Corrected refmult (z-vertex dependent correction)
  //  NOTE: type should be double or float, not integer
  const Double_t refmultCor = refmultCorrUtil->getRefMultCorr(refmult, vz) ;
}

