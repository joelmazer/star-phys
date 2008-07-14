// -*- mode: c++;-*-
// $Id: StJetMaker.h,v 1.45 2008/07/14 06:44:56 tai Exp $
#ifndef STJETMAKER_HH
#define STJETMAKER_HH

#include "StMaker.h"

#include "StJetMakerBackwordCompatibility.h"

#include <vector>

class TTree;

class StMuDstMaker;
class StFourPMaker;
class StJetPars;
class StppAnaPars;

namespace StSpinJet {
  class StParticleCollector;
  class StJetFinderRunner;
  class StJetCuts;
}

class StJetTreeWriter;

class StJetMaker : public StMaker {

public:

  StJetMaker(const Char_t *name, StMuDstMaker* uDstMaker, const char *outputFile);
  virtual ~StJetMaker();

  Int_t Init();
  Int_t Make();
  Int_t Finish();
    
  TTree* tree() const;
    
  void SetTreeWriter(StJetTreeWriter *treeWriter);

  void addAnalyzer(const StppAnaPars*, StJetPars*, StFourPMaker*, const char* anaName);
    
  typedef StSpinJet::StJetMakerBackwordCompatibility::jetBranchesMap jetBranchesMap;
  jetBranchesMap& getJets() const { return _backwordCompatibility->getJets(); }

  StJetTreeWriter* getTreeWriter() { return _treeWriter; }

  const char* GetCVS() const
  {static const char cvs[]="Tag $Name:  $ $Id: StJetMaker.h,v 1.45 2008/07/14 06:44:56 tai Exp $ built "__DATE__" "__TIME__; return cvs;}

private:

  std::vector<StSpinJet::StParticleCollector*> _particleCollectorList;

  std::vector<StSpinJet::StJetFinderRunner*> _jetFinderList;

  std::vector<StSpinJet::StJetCuts*> _jetCutsList;

  StJetTreeWriter *_defaultTreeWriter;
  StJetTreeWriter *_treeWriter;

  StSpinJet::StJetMakerBackwordCompatibility *_backwordCompatibility;

  ClassDef(StJetMaker, 0)

};

#endif // STJETMAKER_HH
