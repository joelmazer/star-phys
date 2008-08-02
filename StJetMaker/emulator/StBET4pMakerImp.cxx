// $Id: StBET4pMakerImp.cxx,v 1.3 2008/08/02 19:23:05 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#include "StBET4pMakerImp.h"

#include "StjTPC.h"
#include "StjBEMC.h"
#include "StjEEMC.h"

#include "StjTrackListCut.h"
#include "StjTowerEnergyListCut.h"

#include "StjTowerEnergyCorrectionForTracks.h"

#include <iostream>

using namespace std;
using namespace StSpinJet;


StBET4pMakerImp::StBET4pMakerImp(StjTPC* tpc, StjTrackListCut* tpcCut,
				 StjBEMC* bemc, StjTowerEnergyListCut* bemcCut,
				 StjTowerEnergyCorrectionForTracks* correctTowerEnergyForTracks,
				 StjEEMC* eemc)
  : _tpc(tpc), _bemc(bemc), _eemc(eemc)
  , _tpcCut(tpcCut), _bemcCut(bemcCut)
  , _correctTowerEnergyForTracks(correctTowerEnergyForTracks)
{

}

void StBET4pMakerImp::Init()
{
  _tpc->Init();
  _bemc->Init();
  _eemc->Init();
}

std::pair<StjTrackList, StjTowerEnergyList> StBET4pMakerImp::getTrackAndEnergyList()
{
  StjTrackList trackList = _tpc->getTrackList();
  StjTowerEnergyList bemcEnergyList = _bemc->getEnergyList();
  StjTowerEnergyList eemcEnergyList = _eemc->getEnergyList();

  trackList = (*_tpcCut)(trackList);
  bemcEnergyList = (*_bemcCut)(bemcEnergyList);

  bemcEnergyList = (*_correctTowerEnergyForTracks)(bemcEnergyList, trackList);

  StjTowerEnergyList energyList;
  copy(bemcEnergyList.begin(), bemcEnergyList.end(), back_inserter(energyList));
  copy(eemcEnergyList.begin(), eemcEnergyList.end(), back_inserter(energyList));

  return pair<StjTrackList, StjTowerEnergyList>(trackList, energyList);
}
