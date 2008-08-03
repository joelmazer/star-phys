// -*- mode: c++;-*-
// $Id: StjTPCTree.h,v 1.4 2008/08/03 00:26:32 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STJTPCTREE_H
#define STJTPCTREE_H

#include "StjTPC.h"
#include <Rtypes.h>

class TTree;

class StjTrackListReader;

class StjTPCTree : public StjTPC {

public:
  StjTPCTree(TTree *tree,
	       const Int_t& indexMajor, const Int_t& indexMinor,
	       const char* indexMajorName = "runNumber",
	       const char* indexMinorName = "eventId"
	       );
  virtual ~StjTPCTree() { }

  StjTrackList getTrackList();

private:

  TTree* _tree;

  const Int_t& _indexMajor;
  const Int_t& _indexMinor;

  StjTrackListReader* _reader;

};

#endif // STJTPCTREE_H
