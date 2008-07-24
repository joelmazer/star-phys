// -*- mode: c++;-*-
// $Id: TowerEnergyToTLorentzVector.h,v 1.1 2008/07/21 17:24:58 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef TOWERENERGYTOTLORENTZVECTOR_H
#define TOWERENERGYTOTLORENTZVECTOR_H

#include <TLorentzVector.h>

namespace StSpinJet {

class TowerEnergy;

class TowerEnergyToTLorentzVector {

public:
  TowerEnergyToTLorentzVector(double mass = 0 /* photon mass as default */)
    : _mass(mass) { }
  TLorentzVector operator()(const TowerEnergy& deposit);

private:
  double _mass;
};

}

#endif // TOWERENERGYTOTLORENTZVECTOR_H