// -*- mode: c++;-*-
// $Id: StBET4pMakerImp.h,v 1.12 2008/06/06 20:13:13 tai Exp $
#ifndef STBET4PMAKERIMP_HH
#define STBET4PMAKERIMP_HH

#include <Rtypes.h>

#include "../StMuTrackFourVec.h"
#include "StJetFinder/AbstractFourVec.h"

#include "CollectChargedTracksFromTPC.h"

#include <map>

class StMuTrack;
class StEmcCollection;
class StMuTrackFourVec;
class StMuDstMaker;
class StEmcRawHit;
class EEmcGeomSimple;
class StBemcTables;
class StEEmcDbMaker;
class StEvent;

typedef std::vector<AbstractFourVec*> FourList;

class StBET4pMakerImp {

public:
    
  StBET4pMakerImp(const char* name, StMuDstMaker* uDstMaker, bool doTowerSwapFix = true);
    
  virtual ~StBET4pMakerImp() {};
    
  void Init(StEEmcDbMaker* eedb);
  void Make();
    
  void Clear(Option_t* opt);

  Int_t InitRun(Int_t runId, StBemcTables* tables);

  void setUseEndcap(bool v) { mUseEndcap = v; }
  void setUse2003Cuts(bool v) { mUse2003Cuts = v; }
  void setUse2005Cuts(bool v) { mUse2005Cuts = v; }
  void setUse2006Cuts(bool v);

  int nDylanPoints() const { return mDylanPoints; }
  double sumEmcEt() const { return mSumEmcEt; }

  FourList &getTracks() { return _tracks; };
  Int_t numTracks(void) { return _tracks.size(); };


private:

  typedef std::vector<std::pair<const StMuTrack*, int> > TrackList;

  void countTracksOnBemcTower(const StMuTrack& track);

  FourList constructFourMomentumListFrom(const TrackList& trackList);

  void collectEnergyFromBEMC();
  double correctBemcTowerEnergyForTracks(double energy, int bemcTowerId);

  void collectEnergyFromEEMC();

  void fillBemcTowerHits();
  double sumEnergyOverBemcTowers(double minE);
  int numberOfBemcTowersWithEnergyAbove(double minE);

  bool shouldKeepThisBemcHit(const StEmcRawHit* theRawHit, int bemcTowerID);

  bool accept2003Tower(int id);

  FourList _tracks;

  bool mUseEndcap;

  //these arrays are used to correlate tracks w/ towers
  static const int mNOfBemcTowers = 4800;

  int mNtracksOnTower[mNOfBemcTowers + 1]; // indexed form [1,4800] (number of tracks incident on this tower)

  typedef int BemcTowerID;
  std::map<BemcTowerID, const StEmcRawHit*> _bemcTowerHits;

  StMuDstMaker* mMuDstMaker;
  StBemcTables* mTables;

  bool mUse2003Cuts;
  bool mUse2005Cuts;
  bool mUse2006Cuts;
  int mDylanPoints;
  double mSumEmcEt;
        
  EEmcGeomSimple* mEeGeom;
  StEEmcDbMaker* mEeDb;

  StSpinJet::CollectChargedTracksFromTPC *_collectChargedTracksFromTPC;
  
};

#endif // STBET4PMAKERIMP_HH
