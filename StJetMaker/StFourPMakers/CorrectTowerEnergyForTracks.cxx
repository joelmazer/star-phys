// $Id: CorrectTowerEnergyForTracks.cxx,v 1.6 2008/07/14 23:07:29 tai Exp $
#include "CorrectTowerEnergyForTracks.h"

#include "StEmcUtil/geometry/StEmcGeom.h"

namespace StSpinJet {

const int CorrectTowerEnergyForTracks::mNOfBemcTowers;

CorrectTowerEnergyForTracks::CorrectTowerEnergyForTracks()
{

}

TowerEnergyList CorrectTowerEnergyForTracks::Do(const TowerEnergyList &energyDepositList, const TrackList& trackList)
{
  for (int i = 1; i <= mNOfBemcTowers; ++i) {
    mNtracksOnTower[i] = 0;
  }

  for(TrackList::const_iterator track = trackList.begin(); track != trackList.end(); ++track) {
    countTracksOnBemcTower(*track);
  }

  TowerEnergyList ret;

  for(TowerEnergyList::const_iterator it = energyDepositList.begin(); it != energyDepositList.end(); ++it) {

    TowerEnergy energyDeposit(*it);

    energyDeposit.energy = correctBemcTowerEnergyForTracks_(energyDeposit.energy, energyDeposit.towerId, energyDeposit.towerEta, energyDeposit.towerPhi);

    energyDeposit.energy = (energyDeposit.energy <= 0) ? 0 : energyDeposit.energy;

    ret.push_back(energyDeposit);
  }

  return ret;
}

void CorrectTowerEnergyForTracks::countTracksOnBemcTower(const Track& track)
{
  int id = 0;

  if(StEmcGeom::instance("bemc")->getId(track.phiext, track.etaext, id) == 0)
    mNtracksOnTower[id]++;
}

double CorrectTowerEnergyForTracks::correctBemcTowerEnergyForTracks_(double energy, int bemcTowerId, float eta, float phi)
{
    float theta=2.*atan(exp(-eta));

    //do a quick correction for hadronic MIP eneryg deposition:
    double MipE = 0.261*(1.+0.056*eta*eta)/sin(theta); //GeV

    return energy - mNtracksOnTower[bemcTowerId]*MipE;
}


}
