// -*- mode: c++;-*-
// $Id: StjJetListWriter.h,v 1.3 2008/08/02 22:43:40 tai Exp $
#ifndef STJJETLISTWRITER_H
#define STJJETLISTWRITER_H

#include "StjFourVecList.h"
#include "StjJetList.h"

#include <Rtypes.h>

class TDirectory;
class TTree;


class StjJetListWriter {

public:

  StjJetListWriter(const char* jetTreeName, const char* jetFourVecTreeName, TDirectory* file);
  virtual ~StjJetListWriter() { }

  void Fill(const StSpinJet::StjJetList& jetList, const StSpinJet::StjFourVecList& fourVecList);
  void Finish();

private:

  void fillJetTree(const StSpinJet::StjJetList& jetList);
  void fillFourVecTree(const StSpinJet::StjJetList& jetList, const StSpinJet::StjFourVecList& fourVecList);

  Int_t findJetId(const StSpinJet::StjFourVec& four, const StSpinJet::StjJetList& jetList);

  TDirectory* _file;
  TTree* _jetTree;
  TTree* _jetFourVecTree;

  Int_t    _jet_runNumber;
  Int_t    _jet_eventId;
  Int_t    _jet_nJets;
  Int_t    _jet_jetId[128];
  Double_t _jet_pt[128];
  Double_t _jet_eta[128];
  Double_t _jet_phi[128];
  Double_t _jet_m[128];
  Double_t _jet_vertexZ;
  Double_t _jet_detectorEta[128];

  Int_t    _four_runNumber;
  Int_t    _four_eventId;
  Int_t    _four_nFourVecs;
  Int_t    _four_fourvecId[4096];
  Int_t    _four_jetId[4096];
  Int_t    _four_type[4096];
  Int_t    _four_detectorId[4096];
  Short_t  _four_trackId[4096];
  Int_t    _four_towerId[4096];
  Double_t _four_pt[4096];
  Double_t _four_eta[4096];
  Double_t _four_phi[4096];
  Double_t _four_m[4096];
};

#endif // STJJETLISTWRITER_H