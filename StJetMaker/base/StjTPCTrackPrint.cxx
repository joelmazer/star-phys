// $Id: StjTPCTrackPrint.cxx,v 1.2 2008/08/02 19:22:48 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#include "StjTPCTrackPrint.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace StSpinJet {

void StjTPCTrackPrint::operator()(const StjTrackList& trackList)
{
  for(StjTrackList::const_iterator it = trackList.begin(); it != trackList.end(); ++it) {
    print(*it);
  }
}

void StjTPCTrackPrint::print(const StjTrack& track) const
{
  static ofstream ofs("./tpctracks.txt");

  ofs 
    << track.runNumber	      << " "
    << track.eventId	      << " "
    << track.detectorId       << " "
    << track.pt               << " "
    << track.eta              << " "
    << track.phi              << " "
    << track.flag	      << " "
    << track.nHits	      << " "
    << track.charge	      << " "
    << track.nHitsPoss	      << " "
    << track.nHitsDedx	      << " "
    << track.nHitsFit	      << " "
    << track.nSigmaPion       << " "
    << track.Tdca             << " "
    << track.dcaZ             << " "
    << track.dcaD             << " "
    << track.BField	      << " "
    << track.bemcRadius	      << " "
    << track.vertexZ	      << " "
    << track.exitDetectorId   << " "
    << track.exitTowerId      << " "
    << track.exitEta         << " "
    << track.exitPhi        << " "
    << track.dEdx	   << " "
    << track.trackIndex   << " "
    << track.id          << " "
    << endl;

}



}