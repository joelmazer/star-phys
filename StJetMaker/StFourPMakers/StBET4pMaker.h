// -*- mode: c++;-*-
// $Id: StBET4pMaker.h,v 1.42 2008/07/14 23:38:36 tai Exp $
#ifndef STBET4PMAKER_HH
#define STBET4PMAKER_HH

#include "StFourPMaker.h"

class StMuDstMaker;
class StJetTreeEntryMaker;
class StBET4pMakerImp;

namespace StSpinJet {

class BemcEnergySumCalculator;

class StJetTPCTrackCut;
class StJetBEMCEnergyCut;
class TrackListToFourList;
class EnergyListToFourList;

}

class StBET4pMaker : public StFourPMaker {

public:
    
  StBET4pMaker(const char* name, StMuDstMaker* maker, bool doTowerSwapFix = true);
  StBET4pMaker(const char* name, StJetTreeEntryMaker* maker);
    
  virtual ~StBET4pMaker() {};
    
  Int_t Init();    
  Int_t Make();
    
  void Clear(Option_t* opt = "");

  FourList &getTracks();

  void setUseTPC(bool v = true)      { _useTPC      = v; }
  void setUseBEMC(bool v = true)     { _useBEMC     = v; }
  void setUseEndcap(bool v = true)   { _useEEMC   = v; }
  void setUse2003Cuts(bool v = true) { _use2003Cuts = v; }
  void setUse2005Cuts(bool v = true) { _use2005Cuts = v; }
  void setUse2006Cuts(bool v = true) { _use2006Cuts = v; }
  void setUseBEMCEnergySum(bool v = true) { _useBEMCEnergySum = v; }

  int nDylanPoints() const;
  double sumEmcEt() const;

  bool bemcCorrupt() const { return isBemcCorrupted(); }

  StBET4pMakerImp* GetImp() { return _imp; }

  bool useTree() const { return _useTree; }

  const char* GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StBET4pMaker.h,v 1.42 2008/07/14 23:38:36 tai Exp $ built "__DATE__" "__TIME__; return cvs;}

private:

  StJetTreeEntryMaker* _entryMaker;

  StMuDstMaker* _uDstMaker;
  bool _doTowerSwapFix;

  bool _useTPC;
  bool _useBEMC;
  bool _useEEMC;
  bool _use2003Cuts;
  bool _use2005Cuts;
  bool _use2006Cuts;
  bool _useBEMCEnergySum;

  bool _useTree;

  StBET4pMakerImp* _imp;

  StSpinJet::BemcEnergySumCalculator* _bemcEnergySumCalculator;

  StSpinJet::TrackListToFourList& _track2four;
  StSpinJet::EnergyListToFourList& _energy2four;
  FourList _tracks;

  bool isBemcCorrupted() const;

  ClassDef(StBET4pMaker,1)
};

#endif // STBET4PMAKER_HH
