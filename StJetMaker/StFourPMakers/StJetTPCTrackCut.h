// -*- mode: c++;-*-
// $Id: StJetTPCTrackCut.h,v 1.1 2008/07/08 04:56:12 tai Exp $
#ifndef STJETTPCTRACKCUT_H
#define STJETTPCTRACKCUT_H

#include <vector>

namespace StSpinJet {

class StMuTrackEmu;

class StJetTPCTrackCut {

public:

  StJetTPCTrackCut() : _use2006Cuts(false) { }
  virtual ~StJetTPCTrackCut() { }

  typedef std::vector<StMuTrackEmu*> TrackList;

  void setUse2006Cuts(bool v) { _use2006Cuts = v; }

  TrackList operator()(const TrackList& trackList);

private:

  bool shoudNotPass(const StMuTrackEmu& track) const;

  bool _use2006Cuts;
};

}

#endif // STJETTPCTRACKCUT_H