//----------------------------------------------------------------------------------------------------
// $Id$
// $Log$
// Revision 1.2  2012/05/08 03:19:36  hmasui
// Move parameters to Centrality_def_refmult.txt
//
// Revision 1.1  2012/04/23 21:32:12  hmasui
// Interface for future extention of centrality correction maker to other centrality measures, like refmult2
//
//
//----------------------------------------------------------------------------------------------------

#include "StRefMultCorr.h"
#include "CentralityMaker.h"

ClassImp(CentralityMaker)

  CentralityMaker* CentralityMaker::fInstance = 0 ;

//____________________________________________________________________________________________________
CentralityMaker::CentralityMaker()
{
  // Create instance for centrality classes
  fRefMultCorr  = new StRefMultCorr("refmult") ;
  fRefMult2Corr = new StRefMultCorr("refmult2") ;
}

//____________________________________________________________________________________________________
CentralityMaker::~CentralityMaker()
{ }

//____________________________________________________________________________________________________
CentralityMaker* CentralityMaker::instance()
{
  if ( !fInstance ) {
    // Initialize StRefMultCorr only once
    fInstance = new CentralityMaker() ;
  }

  return fInstance ;
}

//____________________________________________________________________________________________________
StRefMultCorr* CentralityMaker::getRefMultCorr()
{
  return fRefMultCorr ;
}

//____________________________________________________________________________________________________
StRefMultCorr* CentralityMaker::getRefMult2Corr()
{
  return fRefMult2Corr ;
}


