// $Id: StjTowerEnergyListCut.cxx,v 1.4 2008/08/04 02:48:47 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#include "StjTowerEnergyListCut.h"

ClassImp(StjTowerEnergyListCut)

using namespace std;

StjTowerEnergyList StjTowerEnergyListCut::operator()(const StjTowerEnergyList &energyList)
{
  StjTowerEnergyList ret;

  for(StjTowerEnergyList::const_iterator it = energyList.begin(); it != energyList.end(); ++it) {

    if(shouldNotKeep(*it)) continue;

    ret.push_back(*it);

  }

  return ret;
}


bool StjTowerEnergyListCut::shouldNotKeep(const StjTowerEnergy& energyDeposit)
{
  for(CutList::iterator cut = _cutList.begin(); cut != _cutList.end(); ++cut){
    if((**cut)(energyDeposit)) return true;
  }

  return false;
}
