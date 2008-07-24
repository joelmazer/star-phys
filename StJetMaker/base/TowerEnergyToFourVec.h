// -*- mode: c++;-*-
// $Id: TowerEnergyToFourVec.h,v 1.1 2008/07/21 17:24:57 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef TOWERENERGYTOFOURVEC_H
#define TOWERENERGYTOFOURVEC_H

#include "FourVecList.h"

#include "TowerEnergyToTLorentzVector.h"

namespace StSpinJet {

class TowerEnergy;

class TowerEnergyToFourVec {
public:
  TowerEnergyToFourVec(double mass = 0 /* photon mass as default */)
    : _towerenergy2tlorentzvector(*(new TowerEnergyToTLorentzVector(mass))) { }
  virtual ~TowerEnergyToFourVec() { delete &_towerenergy2tlorentzvector; }
  FourVec operator()(const TowerEnergy& towerEnergy);

private:
  TowerEnergyToTLorentzVector& _towerenergy2tlorentzvector;
};

}

#endif // TOWERENERGYTOFOURVEC_H