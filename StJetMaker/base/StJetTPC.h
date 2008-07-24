// -*- mode: c++;-*-
// $Id: StJetTPC.h,v 1.1 2008/07/21 17:24:50 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJETTPC_H
#define STJETTPC_H

#include "TrackList.h"

namespace StSpinJet {

class StJetTPC {

public:
  StJetTPC() { }
  virtual ~StJetTPC() { }

  virtual void Init() { }

  virtual TrackList getTrackList() = 0;
};


class StJetTPCNull : public StJetTPC {

public:
  StJetTPCNull() { }
  virtual ~StJetTPCNull() { }

  void Init() { }

  TrackList getTrackList() { return TrackList(); }
};

}

#endif // STJETTPC_H