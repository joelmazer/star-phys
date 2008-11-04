// -*- mode: c++;-*-
// $Id: StBET4pMaker.h,v 1.8 2008/11/04 05:54:35 tai Exp $
#ifndef STBET4PMAKER_H
#define STBET4PMAKER_H

#include "StFourPMaker.h"

#include <StjTowerEnergyListCut.h>

class StMuDstMaker;
class StjTreeEntryMaker;
class StBET4pMakerImp;

class StjeBemcEnergySumCalculator;

class StjTrackListCut;
class StjeTrackListToStMuTrackFourVecList;
class StjeTowerEnergyListToStMuTrackFourVecList;

class StBET4pMaker : public StFourPMaker {

public:
    
  StBET4pMaker(const char* name, StMuDstMaker* maker, bool doTowerSwapFix = true);
    
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

  const char* GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StBET4pMaker.h,v 1.8 2008/11/04 05:54:35 tai Exp $ built "__DATE__" "__TIME__; return cvs;}

private:

  StjTreeEntryMaker* _entryMaker;

  StMuDstMaker* _uDstMaker;
  bool _doTowerSwapFix;

  bool _useTPC;
  bool _useBEMC;
  bool _useEEMC;
  bool _use2003Cuts;
  bool _use2005Cuts;
  bool _use2006Cuts;
  bool _useBEMCEnergySum;

  StBET4pMakerImp* _imp;

  StjeBemcEnergySumCalculator* _bemcEnergySumCalculator;

  StjeTrackListToStMuTrackFourVecList& _track2four;
  StjeTowerEnergyListToStMuTrackFourVecList& _energy2four;
  FourList _tracks;

  bool isBemcCorrupted() const;

  ClassDef(StBET4pMaker,1)
};

#endif // STBET4PMAKER_H
