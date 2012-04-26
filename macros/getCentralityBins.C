//----------------------------------------------------------------------------------------------------
// Example macro how to use StRefMultCorr
// $Id$
// $Log$
// Revision 1.4  2012/04/26 23:40:09  hmasui
// Added how to use CentralityMaker, StRefMultCorr::isBadRun() function to remove outliers
//
// Revision 1.3  2011/11/08 19:12:24  hmasui
// Update usage based on the latest update for 200 GeV (luminosity correction)
//
// Revision 1.2  2011/08/12 20:28:45  hmasui
// Change interface according to the update of StRefMultCorr class
//
//----------------------------------------------------------------------------------------------------

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
//
//   * Comment for luminosity (zdc coincidence rate) correction
//     - Luminosity correction is only valid for 200 GeV
//     - The default argument is 0 for zdc coincidence rate in initEvent() function, see header StRefMultCorr.h,
//       so that you can still use previous initEvent() function like
//         void StRefMultCorr::initEvent(refmult, vz) ;
//       without specifying zdc coincidence rate for lower beam energies
//
//   * You can now use the interface "CentralityMaker" class to access the StRefMultCorr
//     see the usage below.
void getCentralityBins()
{
  gSystem->Load("StRefMultCorr");
//  StRefMultCorr* refmultCorrUtil = new StRefMultCorr(); 
  StRefMultCorr* refmultCorrUtil = CentralityMaker::instance()->getRefMultCorr() ;

  // You need to specify the run number you are going to process
  refmultCorrUtil->init(11078000);

  //----------------------------------------------------------------------------------------------------
  // *** Optional functions (not necessary to call)
  //    void StRefMultCorr::print(const Optiont_t option="");
  //    Int_t StRefMultCorr::getBeginRun(const Double_t energy, const Int_t year) ;
  //    Int_t StRefMultCorr::getEndRun(const Double_t energy, const Int_t year) ;

  // Print all parameters
  //  - Don't print centrality and correction parameters without any option string (default)
  refmultCorrUtil->print("Alex");

  // Obtain begin and end run number from energy and year
  cout << "Run " << refmultCorrUtil->getBeginRun(200.0, 2010) << " - " << refmultCorrUtil->getEndRun(200.0, 2010) << endl;

  // You can check the 'bad run' based on the event-wise QA for refmult centrality
  // by using StRefMultCorr::isBadRun() function
  if ( refmultCorrUtil->isBadRun(12177061) ) {
    cout << "Run 12177061 is bad" << endl;
  }
  //----------------------------------------------------------------------------------------------------

  // Dummy refmult and primary z-vertex
  const UShort_t refmult = 100 ;
  const Double_t vz      = 20.0 ;
  const Double_t zdcCoincidenceRate = 20000 ; // Hz

  // ******* IMPORTANT ***********
  // Call initEvent(const UShort_t RefMult, const Double_t z) function
  // event-by-event at the beginning before using any other functions
  refmultCorrUtil->initEvent(refmult, vz, zdcCoincidenceRate) ;

  // Get centrality bins
  //   see StRefMultCorr.h for the definition of centrality bins
  const Int_t cent16 = refmultCorrUtil->getCentralityBin16() ;
  const Int_t cent9  = refmultCorrUtil->getCentralityBin9() ;

  // Re-weighting corrections for peripheral bins
  const Double_t reweight = refmultCorrUtil->getWeight() ;

  //----------------------------------------------------------------------------------------------------
  // Not really necessary for your study but if you want to see the corrected refmult distribution
  // Corrected refmult (z-vertex dependent correction)
  //  NOTE: type should be double or float, not integer
  const Double_t refmultCor = refmultCorrUtil->getRefMultCorr() ;
}

