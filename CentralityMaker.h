//----------------------------------------------------------------------------------------------------
// $Id$
// $Log$
// Revision 1.1  2012/04/23 21:32:16  hmasui
// Interface for future extention of centrality correction maker to other centrality measures, like refmult2
//
//----------------------------------------------------------------------------------------------------
//  * Interface of StRefMultCorr for possible extention of StRefMultCorr class to the other 
//    centrality measure, such as refmult2.
//  * This interface is also useful when StRefMultCorr needs to be called from two or more different 
//    makers in order to have exactly the same corrected refmult and centrality bins among different makers.
//
//  There is only one change you have to make
//    Replace
//      StRefMultCorr* refmultCorr = new StRefMultCorr();
//    to
//      StRefMultCorr* refmultCorr = CentralityMaker::instance()->getStRefMultCorr();
//
//  authors: Hiroshi Masui
//----------------------------------------------------------------------------------------------------

#ifndef __CentralityMaker_h__
#define __CentralityMaker_h__

class StRefMultCorr ;
#include "Rtypes.h"

//____________________________________________________________________________________________________
class CentralityMaker {
  public:
    static CentralityMaker* instance(); // Use this function to access StRefMultCorr
    virtual ~CentralityMaker(); /// Default destructor

    // Interface
    StRefMultCorr* getRefMultCorr() ;

  private:
    CentralityMaker() ; // Constructor is private
    static CentralityMaker* fInstance ; // Static pointer of CentralityMaker

    // Centrality correction classes
    StRefMultCorr* fRefMultCorr ; // refmult based centrality

    ClassDef(CentralityMaker, 0)
};
#endif

