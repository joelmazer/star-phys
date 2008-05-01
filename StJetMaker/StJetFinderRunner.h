// -*- mode: c++;-*-
// $Id: StJetFinderRunner.h,v 1.2 2008/05/01 21:28:37 tai Exp $
#ifndef STJETFINDERRUNNER_HH
#define STJETFINDERRUNNER_HH

#include "StppAnaPars.h"

#include "StJetFinder/StProtoJet.h"

#include <list>

class StJetPars;
class StJetFinder;

namespace StSpinJet {

class StJetFinderRunner {

public:

  typedef std::list<StProtoJet> ProtoJetList;

  StJetFinderRunner(const StppAnaPars* ap, StJetPars* jp, ProtoJetList& protoJets);

  virtual ~StJetFinderRunner();

  void Init();

  void findJets();

private:

  void applyCutsOnJets();

  bool shouldNotKeep(StProtoJet &pj);
    
  StJetFinder* _jetFinder;

  ProtoJetList& _protoJetList;

  StppAnaPars _anaPar;

};

}

#endif // STJETFINDERRUNNER_HH

