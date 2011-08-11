//----------------------------------------------------------------------------------------------------
// $Id$
// $Log$
// Revision 1.2  2011/08/11 23:51:10  hmasui
// Suppress cout in the setParameterIndex function. Use TError for error messages.
//
// Revision 1.1  2011/08/11 18:38:28  hmasui
// First version of Refmult correction class
//
//----------------------------------------------------------------------------------------------------

#include <fstream>
#include <iostream>
#include <string>
#include "StRefMultCorr.h"
#include "TError.h"
#include "TRandom.h"
#include "TString.h"

ClassImp(StRefMultCorr)

using std::cout ;
using std::endl ;
using std::ifstream ;
using std::string ;
using std::vector ;

//____________________________________________________________________________________________________
// Default constructor
StRefMultCorr::StRefMultCorr()
{
  // Clear all data members
  clear() ;

  // Read parameters
  read() ;
}

//____________________________________________________________________________________________________
// Default destructor
StRefMultCorr::~StRefMultCorr()
{
}

//____________________________________________________________________________________________________
void StRefMultCorr::clear()
{
  // Clear all arrays, and set parameter index = -1

  mStart_runId.clear() ;
  mStop_runId.clear() ;
  mStart_zvertex.clear() ;
  mStop_zvertex.clear() ;
  mNormalize_stop.clear() ;

  for(Int_t i=0;i<mNCentrality;i++) {
    mCentrality_bins[i].clear() ;
  }
  mParameterIndex = -1 ;
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isIndexOk() const
{
  // mParameterIndex not initialized (-1)
  if ( mParameterIndex == -1 ) {
    Error("StRefMultCorr::isNparSetOk", "mParameterIndex = -1. Call init(const Int_t RunId) function to initialize centrality bins, corrections");
    return kFALSE ;
  }

  // Out of bounds
  if ( mParameterIndex >= (Int_t)mStart_runId.size() ) {
    Error("StRefMultCorr::isNparSetOk",
        Form("mParameterIndex = %d > max number of parameter set = %d. Make sure you put correct index for this energy",
          mParameterIndex, mStart_runId.size()));
    return kFALSE ;
  }

  return kTRUE ;
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isZvertexOk(const Double_t z) const
{
  // Primary z-vertex check
  return ( z > mStart_zvertex[mParameterIndex] && z < mStop_zvertex[mParameterIndex] ) ;
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isRefMultOk(const UShort_t RefMult, const Double_t z) const
{
  // Invalid index
  if ( !isIndexOk() ) return kFALSE ;

  // select 0-80%
  const Double_t RefMult_corr = getRefMultCorr(RefMult,z); // First correct for the z-vertex dependence

  return (RefMult_corr > mCentrality_bins[0][mParameterIndex] && RefMult_corr < mCentrality_bins[mNCentrality][mParameterIndex]);
}

//____________________________________________________________________________________________________
Bool_t StRefMultCorr::isCentralityOk(const Int_t icent, const UShort_t RefMult, const Double_t z) const
{
  // Invalid centrality id
  if ( icent < -1 || icent >= mNCentrality+1 ) return kFALSE ;

  // Invalid index
  if ( !isIndexOk() ) return kFALSE ;

  // select 0-80%
  const Double_t RefMult_corr = getRefMultCorr(RefMult,z); // First correct for the z-vertex dependence

  // Special case
  // 1. 80-100% for icent=-1
  if ( icent == -1 ) return (RefMult_corr <= mCentrality_bins[0][mParameterIndex]);

  // 2. icent = mNCentrality
  if ( icent == mNCentrality ) return (RefMult_corr <= mCentrality_bins[mNCentrality][mParameterIndex]);

  const Bool_t ok = (RefMult_corr > mCentrality_bins[icent][mParameterIndex] && RefMult_corr <= mCentrality_bins[icent+1][mParameterIndex]);
//  if(ok){
//    cout << "StRefMultCorr::isCentralityOk  refmultcorr = " << RefMult_corr
//      << "  min. bin = " << mCentrality_bins[icent][mParameterIndex]
//      << "  max. bin = " << mCentrality_bins[icent+1][mParameterIndex]
//      << endl;
//  }
  return ok ;
}

//____________________________________________________________________________________________________
void StRefMultCorr::init(const Int_t RunId)
{
  // Initialization

  // call setParameterIndex
  setParameterIndex(RunId) ;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::setParameterIndex(const Int_t RunId)
{
  // Determine the corresponding parameter set for the input RunId
  for(UInt_t npar = 0; npar < mStart_runId.size(); npar++)
  {
    if(RunId >= mStart_runId[npar] && RunId <= mStop_runId[npar])
    {
      mParameterIndex = npar ;
//      cout << "StRefMultCorr::setParameterIndex  Parameter set = " << mParameterIndex << " for RUN " << RunId << endl;
      break ;
    }
  }

  if(mParameterIndex == -1){
    Error("StRefMultCorr::setParameterIndex", "Parameter set does not exist for RUN %d", RunId);
  }
  //else cout << "Parameter set = " << npar_set << endl;

  return mParameterIndex ;
}


//____________________________________________________________________________________________________
Double_t StRefMultCorr::getRefMultCorr(const UShort_t RefMult, const Double_t z) const
{
  // Apply correction if parameter index & z-vertex are ok
  if (!isIndexOk() || !isZvertexOk(z)) return RefMult ;

  // Correction function for RefMult, takes into account z_vertex dependence

  // par0 to par5 define the parameters of a polynomial to parametrize z_vertex dependence of RefMult
  const Double_t par0 = 4.02745e+02;
  const Double_t par1 = 4.51653e-01;
  const Double_t par2 = 3.51459e-04;
  const Double_t par3 = -4.99006e-05;
  const Double_t par4 = 0.0;
  const Double_t par5 = 0.0;

  const Double_t  RefMult_ref = par0; // Reference mean RefMult at z=0
  const Double_t  RefMult_z = par0 + par1*z + par2*z*z + par3*z*z*z + par4*z*z*z*z + par5*z*z*z*z*z; // Parametrization of mean RefMult vs. z_vertex position
  Double_t  Hovno = 1.0; // Correction factor for RefMult, takes into account z_vertex dependence

  if(RefMult_z > 0.0)
  {
    Hovno = RefMult_ref/RefMult_z;
  }

  Double_t RefMult_d = (Double_t)(RefMult)+gRandom->Rndm()-0.5; // random sampling over bin width -> avoid peak structures in corrected distribution
  const Double_t RefMult_corr  = RefMult_d*Hovno;
//  cout << "Input RefMult = " << RefMult << ", input z = " << z << ", RefMult_corr = " << RefMult_corr << endl;
  return RefMult_corr ;
}
/*
//____________________________________________________________________________________________________
Double_t StRefMultCorr::getRefMultCorr(const UShort_t RefMult, const Double_t z) const
{
  // Apply correction if parameter index & z-vertex are ok
  if (!isIndexOk() || !isZvertexOk(z)) return RefMult ;

  // Correction function for RefMult, takes into account z_vertex dependence

// par0 to par5 define the parameters of a polynomial to parametrize z_vertex dependence of RefMult
  const Double_t par0 = 1.14384e+02;
  const Double_t par1 = 9.65079e-02;
  const Double_t par2 = 2.00631e-03;
  const Double_t par3 = 5.92159e-05;
  const Double_t par4 = -5.53470e-07;
  const Double_t par5 = -7.02779e-08;

  const Double_t  RefMult_ref = par0; // Reference mean RefMult at z=0
  const Double_t  RefMult_z = par0 + par1*z + par2*z*z + par3*z*z*z + par4*z*z*z*z + par5*z*z*z*z*z; // Parametrization of mean RefMult vs. z_vertex position
  Double_t  Hovno = 1.0; // Correction factor for RefMult, takes into account z_vertex dependence

  if(RefMult_z > 0.0)
  {
    Hovno = RefMult_ref/RefMult_z;
  }

  Double_t RefMult_d = (Double_t)(RefMult)+ran.Rndm()-0.5; // random sampling over bin width -> avoid peak structures in corrected distribution
  const Double_t RefMult_corr  = RefMult_d*Hovno;
//  cout << "Input RefMult = " << RefMult << ", input z = " << z << ", RefMult_corr = " << RefMult_corr << endl;
  return RefMult_corr ;
}
*/
//____________________________________________________________________________________________________
Double_t StRefMultCorr::getWeight(const UShort_t RefMult, const Double_t z) const
{
  Double_t Weight = 1.0;

  // Invalid index
  if( !isIndexOk() ) return Weight ;

  // Calculates weight for low RefMult. Takes into account the efficiency loss of the trigger.
  const Double_t RefMult_corr = getRefMultCorr(RefMult,z); // First correct for the z-vertex dependence

  const Double_t par0 =   1.03165e+00;
  const Double_t par1 =   6.22542e+01;
  const Double_t par2 =   5.04440e+01;
  const Double_t par3 =  -3.85695e+01;
  const Double_t par4 =  -6.69691e-06;

  // Additional z-vetex dependent correction
  //const Double_t A = ((1.27/1.21))/(30.0*30.0); // Don't ask...
  const Double_t A = (0.05/0.21)/(30.0*30.0); // Don't ask...

  if(isRefMultOk(RefMult, z) // 0-80%
      && RefMult_corr < mNormalize_stop[mParameterIndex] // re-weighting only apply up to normalization point
      && RefMult_corr != -(par3/par2) // avoid denominator = 0
    )
  {
    Weight = par0 + par1/(par2*RefMult_corr + par3) + par4*(par2*RefMult_corr + par3); // Parametrization of MC/data RefMult ratio
    Weight = Weight + (Weight-1.0)*(A*z*z); // z-dependent weight correction
  }

  return Weight;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::getCentralityBin16(const UShort_t RefMult, const Double_t z) const
{
  Int_t CentBin16 = -1;

  // Invalid index
  if( !isIndexOk() ) return CentBin16 ;

//  const Double_t RefMult_corr = getRefMultCorr(RefMult,z); // First correct for the z-vertex dependence
  while(CentBin16 < mNCentrality && !isCentralityOk(CentBin16, RefMult, z) )
  {
    CentBin16++;
  }

  // return -1 if CentBin16 = 16 (very large refmult, refmult>5000)
  return (CentBin16==16) ? -1 : CentBin16;
}

//____________________________________________________________________________________________________
Int_t StRefMultCorr::getCentralityBin9(const UShort_t RefMult, const Double_t z) const
{
  Int_t CentBin9 = -1;

  // Invalid index
  if ( !isIndexOk() ) return CentBin9 ;

  const Int_t CentBin16 = getCentralityBin16(RefMult,z); // Centrality bin 16
  const Bool_t isCentralityOk = CentBin16 >= 0 && CentBin16 < mNCentrality ;

  // No centrality is defined
  if (!isCentralityOk) return CentBin9 ;

  const Double_t RefMult_corr = getRefMultCorr(RefMult,z); // First correct for the z-vertex dependence

  // First handle the exceptions
  if(RefMult_corr > mCentrality_bins[15][mParameterIndex] && RefMult_corr <= mCentrality_bins[16][mParameterIndex])
  {
    CentBin9 = 8; // most central 5%
  }
  else if(RefMult_corr > mCentrality_bins[14][mParameterIndex] && RefMult_corr <= mCentrality_bins[15][mParameterIndex])
  {
    CentBin9 = 7; // most central 5-10%
  }
  else
  {
    CentBin9 = (Int_t)(0.5*CentBin16);
  }

  return CentBin9;
}

//____________________________________________________________________________________________________
void StRefMultCorr::read()
{
  // Open the parameter file and read the data
  // Assume input file "Centrality_def.txt" is placed under StRoot/StRefMultCorr
  //  const Char_t* inputFileName("/star/u/aschmah/glauber/RefMult_corr/StRoot/StRefMultCorr/Centrality_def.txt");
//  const Char_t* inputFileName("/u/aschmah/STAR/glauber/RefMultCorr/StRoot/StRefMultCorr/Centrality_def.txt");
  const Char_t* inputFileName("StRoot/StRefMultCorr/Centrality_def.txt");
  ifstream ParamFile(inputFileName);
  if(!ParamFile){
    cout << "StRefMultCorr::read  cannot open " << inputFileName << endl;
    return;
  }
  cout << "StRefMultCorr::read  Open " << inputFileName << endl;

//  Int_t input_counter = 0;
  string line ;
  getline(ParamFile,line);
//  cout << line << endl;

//  if(strcmp(line1,"Start_runId") == 0) // strcmp returns 0 if both string are identical
  if(line.find("Start_runId")!=string::npos)
  {
    //cout << "Initial line" << endl;
    while(ParamFile.good())
    {
      Int_t startRunId, stopRunId ;
      Double_t startZvertex, stopZvertex ;
      ParamFile >> startRunId >> stopRunId >> startZvertex >> stopZvertex ;
      mStart_runId.push_back( startRunId ) ;
      mStop_runId.push_back( stopRunId ) ;
      mStart_zvertex.push_back( startZvertex ) ;
      mStop_zvertex.push_back( stopZvertex ) ;
      for(Int_t i=0;i<mNCentrality;i++) {
        Int_t centralitybins;
        ParamFile >> centralitybins;
        mCentrality_bins[i].push_back( centralitybins );
      }
      Double_t normalize_stop ;
      ParamFile >> normalize_stop ;
      mNormalize_stop.push_back( normalize_stop );
      mCentrality_bins[mNCentrality].push_back( 5000 );
      //cout << "Data line = " << input_counter << ", Start_runId = " << Start_runId[input_counter] << ", Stop_runId = " << Stop_runId[input_counter] << endl;
      const UInt_t id = mStart_runId.size()-1;
      cout << "StRefMultCorr::read  Index = " << id << endl;
      cout << "StRefMultCorr::read  Start_runId = " << mStart_runId[id] << ", Stop_runId = " << mStop_runId[id] << endl;
      cout << "StRefMultCorr::read  Start_zvertex = " << mStart_zvertex[id] << ", Stop_zvertex = " << mStop_zvertex[id] << endl;
      cout << "StRefMultCorr::read  Normalize_stop = " << mNormalize_stop[id] << endl;
      for(Int_t i=0;i<mNCentrality;i++){
        cout << Form("StRefMultCorr::read  Centrality %3d-%3d %%, refmult > %4d", 75-5*i, 80-5*i, mCentrality_bins[i][id]) << endl;
      }
      cout << endl;
    }
  }
  else
  {
    cout << "StRefMultCorr::read  Input file is not correct! Wrong structure." << endl;
    return;
  }
  ParamFile.close();
}

