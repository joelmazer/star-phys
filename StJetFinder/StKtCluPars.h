// -*- mode: c++;-*-
// $Id: StKtCluPars.h,v 1.1 2008/04/21 16:22:35 tai Exp $
#ifndef STKTCLUPARS_H
#define STKTCLUPARS_H

#include "StJetPars.h"

class StKtCluPars : public StJetPars {

public:

    ///Set the distance measure, called d by Ellis/Soper
    void setR(double r) {mR=r;}
    double r() const {return mR;}

    ///Toggle the debug stream on/off
    void setDebug(bool v) {mDebug = v;}
    bool debug() const {return mDebug;}

private:
    double mR;
    bool mDebug;
    ClassDef(StKtCluPars,1)
};


#endif // STKTCLUPARS_H
