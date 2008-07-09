// -*- mode: c++;-*-
// $Id: StJetBEMCEnergyCut.h,v 1.1 2008/07/09 10:24:33 tai Exp $
#ifndef STJETBEMCENERGYCUT_H
#define STJETBEMCENERGYCUT_H

#include "TowerEnergyDeposit.h"

namespace StSpinJet {

class StJetBEMCEnergyCut {

public:
  StJetBEMCEnergyCut()
    : mUse2003Cuts(false), mUse2005Cuts(false) { }
  virtual ~StJetBEMCEnergyCut() { }
  
  TowerEnergyDepositList Apply(const TowerEnergyDepositList& energyList);

  void setUse2003Cuts(bool v) { mUse2003Cuts = v; }
  void setUse2005Cuts(bool v) { mUse2005Cuts = v; }

private:

  bool shouldKeep(const TowerEnergyDeposit& energyDeposit);
  bool accept2003Tower(int id);

  bool mUse2003Cuts;
  bool mUse2005Cuts;

};

}

#endif // STJETBEMCENERGYCUT_H