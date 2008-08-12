// $Id: StjJetListCut.cxx,v 1.5 2008/08/12 04:01:27 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#include "StjJetListCut.h"

ClassImp(StjJetListCut)

using namespace std;

StjJetList StjJetListCut::operator()(const StjJetList &jetList)
{
  StjJetList ret;

  for(StjJetList::const_iterator it = jetList.begin(); it != jetList.end(); ++it) {

    if(shouldNotKeep(*it)) continue;

    ret.push_back(*it);
  }

  return ret;
}


bool StjJetListCut::shouldNotKeep(const StjJet& p4)
{
  for(CutList::iterator cut = _cutList.begin(); cut != _cutList.end(); ++cut){
    if((**cut)(p4)) return true;
  }

  return false;
}
