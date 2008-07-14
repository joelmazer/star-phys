// $Id: StBET4pMaker.cxx,v 1.64 2008/07/14 23:38:35 tai Exp $
#include "StBET4pMaker.h"
#include "StBET4pMakerImp.h"
#include "StBET4pMakerImpBuilder.h"

#include "TrackListToFourList.h"
#include "EnergyListToFourList.h"

#include "BemcEnergySumCalculator.h"
#include "BemcEnergySumCalculatorBuilder.h"

#include "StEmcADCtoEMaker/StEmcADCtoEMaker.h"
#include "StEEmcDbMaker/StEEmcDbMaker.h"

#include <iostream>

using namespace std;
using namespace StSpinJet;

ClassImp(StBET4pMaker)
    
StBET4pMaker::StBET4pMaker(const char* name, StMuDstMaker* uDstMaker, bool doTowerSwapFix)
  : StFourPMaker(name)
  , _entryMaker(0)
  , _uDstMaker(uDstMaker), _doTowerSwapFix(doTowerSwapFix)
  , _useTPC(true), _useBEMC(true), _useEEMC(false)
  , _use2003Cuts(false), _use2005Cuts(false), _use2006Cuts(false)
  , _useBEMCEnergySum(true)
  , _useTree(false)
  , _imp(0)
  , _bemcEnergySumCalculator(0)
  , _track2four(*(new TrackListToFourList))
  , _energy2four(*(new EnergyListToFourList))
{ }

StBET4pMaker::StBET4pMaker(const char* name, StJetTreeEntryMaker* maker)
  : StFourPMaker(name)
  , _entryMaker(maker)
  , _uDstMaker(0), _doTowerSwapFix(true)
  , _useTPC(true), _useBEMC(true), _useEEMC(false)
  , _use2003Cuts(false), _use2005Cuts(false), _use2006Cuts(false)
  , _useBEMCEnergySum(false)
  , _useTree(true)
  , _imp(0)
  , _bemcEnergySumCalculator(0)
  , _track2four(*(new TrackListToFourList))
  , _energy2four(*(new EnergyListToFourList))
{ }


Int_t StBET4pMaker::Init()
{
  StBET4pMakerImpBuilder impBuilder;
  if(_useTree) {
    _imp = impBuilder.build(_useTPC, _useBEMC, _useEEMC, _use2003Cuts, _use2005Cuts, _use2006Cuts, _entryMaker);
  } else {
    _imp = impBuilder.build(_useTPC, _useBEMC, _useEEMC, _use2003Cuts, _use2005Cuts, _use2006Cuts, _uDstMaker, _doTowerSwapFix);
  }
  _imp->Init();

  BemcEnergySumCalculatorBuilder bemcEnergySumCalculatorBuilder;
  if(_useTree) _useBEMCEnergySum = false;
  _bemcEnergySumCalculator = bemcEnergySumCalculatorBuilder.build(_useBEMCEnergySum && _useBEMC, _use2003Cuts, _use2005Cuts, _uDstMaker, _doTowerSwapFix);
  _bemcEnergySumCalculator->Init();

  return StMaker::Init();
}


void StBET4pMaker::Clear(Option_t* opt)
{
  for (FourList::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    delete (*it);
    (*it) = 0;
  }
  _tracks.clear();

  _bemcEnergySumCalculator->Clear();

  return StMaker::Clear(opt);
}

Int_t StBET4pMaker::Make()
{
  if(isBemcCorrupted()) return kStOk;

  _bemcEnergySumCalculator->Make();

  if (_bemcEnergySumCalculator->sumEmcEt() > 200.) return kStOk;

  //  _imp->Make();

  pair<TrackList, TowerEnergyList> trackAndEnergyList = _imp->getTrackAndEnergyList();

  FourList tpc4pList = _track2four(trackAndEnergyList.first);
  _tracks.insert(_tracks.end(), tpc4pList.begin(), tpc4pList.end());

  FourList energy4pList = _energy2four(trackAndEnergyList.second);
  _tracks.insert(_tracks.end(), energy4pList.begin(), energy4pList.end());

  return StMaker::Make();
}

FourList &StBET4pMaker::getTracks()
{
  return _tracks;
  //  return _imp->getTracks();
}

bool StBET4pMaker::isBemcCorrupted() const
{
  if(StEmcADCtoEMaker* adc2e = dynamic_cast<StEmcADCtoEMaker*>(const_cast<StBET4pMaker*>(this)->GetMaker("Eread")))
    return adc2e->isCorrupted();
    
  return false;
}

int StBET4pMaker::nDylanPoints() const
{ 
  return _bemcEnergySumCalculator->nDylanPoints();
}

double StBET4pMaker::sumEmcEt() const 
{ 
  return _bemcEnergySumCalculator->sumEmcEt();
}
