// $Id: StJetScratch.cxx,v 1.5 2008/08/02 03:57:36 tai Exp $
#include "StJetScratch.h"

#include "StjTPCMuDst.h"
#include "StjBEMCMuDst.h"
#include "StjEEMCMuDst.h"

#include <StMuDSTMaker/COMMON/StMuDstMaker.h>
#include <StMuDSTMaker/COMMON/StMuDst.h>
#include <StMuDSTMaker/COMMON/StMuEvent.h>

#include <TFile.h>
#include <TTree.h>

#include <iostream>

using namespace std;
using namespace StSpinJet;

ClassImp(StJetScratch)
  

StJetScratch::StJetScratch(const Char_t *name, TDirectory* file, StMuDstMaker* uDstMaker)
  : StMaker(name)
  , _file(file)
  , _uDstMaker(uDstMaker)
{ }

Int_t StJetScratch::Init()
{
  return kStOk;
}

Int_t StJetScratch::Make()
{
  return kStOk;
}

Int_t StJetScratch::Finish()
{
  return kStOk;
}
