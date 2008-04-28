// -*- mode: c++;-*-
// $Id: StConeJetFinder.h,v 1.20 2008/04/28 21:59:07 tai Exp $
#ifndef StConeJetFinder_HH
#define StConeJetFinder_HH

#include "TObject.h"


//std
#include <utility>
#include <map>
#include <vector>
#include <cmath>
using std::map;
using std::vector;
using std::pair;

//StJetFinder
#include "StJetFinder.h"
#include "Functors.h"
#include "StJetEtCell.h"

class StJetSpliterMerger;
class StConeJetFinder;

#include "StConePars.h"

class StJetEtCellFactory {

public:
  virtual StJetEtCell* create(double etaMin, double etaMax, double phiMin, double phiMax)
  { return new StJetEtCell(etaMin, etaMax, phiMin, phiMax); }
};


class StJetEtCellGrid {

public:

  typedef map<StEtGridKey, StJetEtCell*> CellMap;
  typedef CellMap::value_type CellMapValType;
  typedef StJetEtCell::CellList CellList;
  typedef list<StJetEtCell> ValueCellList;

  StJetEtCellGrid(StConePars& pars) : _pars(pars) { }

  void buildGrid(CellList& cellList, CellMap& cellMap, StJetEtCellFactory* cellFactory);

private:

  StEtGridKey findKey(double eta, double phi) const;
  int findEtaKey(double eta) const;
  int findPhiKey(double phi) const;


  StConePars& _pars;

};

/*!
  \class StConeJetFinder
  \author M.L. Miller (Yale Software)
  Implementation of the cone algorithm, circa Tevatron RunII Jet Physics working group specification.
*/
class StConeJetFinder : public StJetFinder {

public:
	
    ///useful typdefs
    typedef map<StEtGridKey, StJetEtCell*> CellMap;
    typedef CellMap::value_type CellMapValType;
    typedef StJetEtCell::CellList CellList;
    typedef list<StJetEtCell> ValueCellList;
	
    ///cstr-dstr
    StConeJetFinder(const StConePars& pars);
    virtual ~StConeJetFinder();
	
  virtual void Init();

    ///simple access to the parameters
    StConePars pars() const; 
	
    ///inherited interface
    virtual void findJets(JetList& protojets);     
    virtual void clear();
    virtual void print();
	
protected:
		
    ///needs access to the grid
    friend struct PreJetInitializer; 
	
    ///Only available for derived classes
    StConeJetFinder();

    ///make a polymorphic cell
    virtual StJetEtCell* makeCell(double etaMin, double etaMax, double phiMin, double phiMax);
    ///build the grid at construction time
    virtual void buildGrid();

  virtual StJetEtCellFactory* makeCellFactory();

	
    ///put 'em in the grid
    virtual void fillGrid(JetList& protoJets); 
	
    void clearAndDestroy();

    void initializeWorkCell(const StJetEtCell* other);

    void addToPrejets(StJetEtCell* cell);
	
    StJetEtCell* findCellByKey(const StEtGridKey& key);
	
    enum SearchResult {kTooManyTries=0, kLeftVolume=1, kConverged=2, kContinueSearch=3};	
    SearchResult doSearch();
	
    void doMinimization();
	
    void addSeedsAtMidpoint();
	
    StJetEtCell* defineMidpoint(const StJetEtCell& pj1, const StJetEtCell& pj2) ;
	
  virtual bool acceptSeed(const StJetEtCell* cell);
    virtual bool acceptPair(const StJetEtCell* center, const StJetEtCell* assoc) const;
	
    const StProtoJet& collectCell(StJetEtCell* seed);
	
    ///action
    int findPhiKey(double phi) const;
    int findEtaKey(double eta) const;
	
    ///is this point in the detector volume?
    bool inVolume(double eta, double phi);
	
    ///find a key.  If out of bounds, it aborts program flow.  otherwise, nasty run-time errors!
    StEtGridKey findKey(double eta, double phi) const;
	
    ///find iterators into grid
    CellMap::iterator findIterator(double eta, double phi);
    ///find iterators into grid
    CellMap::iterator findIterator(const StEtGridKey&);
	
protected:

  StConePars mPars; ///run-time pars
	
  CellMap _EtCellMap; ///the map references the objects in the vector
  CellList _EtCellList; ///the vector holds the actual objects
  CellList::iterator mTheEnd;
	
  StJetEtCell mWorkCell;
  int mSearchCounter;
	
  StJetSpliterMerger* mMerger;
  ValueCellList mPreJets;
	
  typedef std::pair<ValueCellList::iterator, ValueCellList::iterator> ValueCellListItPair;
  typedef vector<ValueCellListItPair> VCLItPairVec;
  VCLItPairVec mMidpointVec;

  StJetEtCellGrid _cellGrid;
	
private:

  virtual void findJets_sub1();
  virtual void findJets_sub2();

};

inline StConePars StConeJetFinder::pars() const
{
    return mPars;
}

//non-members

struct PreJetLazyUpdater //assume proto-jet updated
{
    PreJetLazyUpdater() : sumEt(0.) {};
    double sumEt;
	
    void operator()(StJetEtCell& cell);
    void operator()(StJetEtCell* cell);
};

struct PostMergeUpdater
{
    void operator()(StJetEtCell& cell);
};

struct PreJetInitializer
{
  PreJetInitializer(StConeJetFinder& j) : mConeFinder(j) {};
  StConeJetFinder& mConeFinder;
	
  void operator()(StJetEtCell& cell);
};

#endif

