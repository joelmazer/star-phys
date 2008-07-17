// $Id: StJetTPCMuDst.cxx,v 1.6 2008/07/17 07:34:14 tai Exp $
#include "StJetTPCMuDst.h"

#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"

#include <StFourPMakers/StMuEmcPosition.h>
#include <StEmcUtil/geometry/StEmcGeom.h>

#include <TVector3.h>

namespace StSpinJet {

StJetTPCMuDst::StJetTPCMuDst(StMuDstMaker* uDstMaker)
  : _uDstMaker(uDstMaker)
{

}

TrackList StJetTPCMuDst::getTrackList()
{
  TrackList ret;

  StMuDst* uDst = _uDstMaker->muDst();

  long nTracks = uDst->numberOfPrimaryTracks();

  double magneticField = uDst->event()->magneticField()/10.0; // Tesla
  for(int i = 0; i < nTracks; ++i) {
    const StMuTrack* mutrack = uDst->primaryTracks(i);

    if(mutrack->flag() < 0) continue;

    if(mutrack->topologyMap().trackFtpcEast() || mutrack->topologyMap().trackFtpcWest()) continue;

    Track track = createTrack(mutrack, i, magneticField);

    ret.push_back(track);
  }

  return ret;
}

Track StJetTPCMuDst::createTrack(const StMuTrack* mutrack, int i, double magneticField)
{
  Track track;

  track.runNumber = _uDstMaker->muDst()->event()->runId();
  track.eventId = _uDstMaker->muDst()->event()->eventId();
  track.detectorId = 1;

  TVector3 p(mutrack->momentum().x(), mutrack->momentum().y(), mutrack->momentum().z());

  track.pt         = p.Pt();
  track.eta        = p.Eta();
  track.phi        = p.Phi();
  track.flag       = mutrack->flag();
  track.nHits      = mutrack->nHits(); 
  track.charge     = mutrack->charge();
  track.nHitsPoss  = mutrack->nHitsPoss();
  track.nHitsDedx  = mutrack->nHitsDedx();
  track.nHitsFit   = mutrack->nHitsFit();
  track.nSigmaPion = mutrack->nSigmaPion();
  track.Tdca       = mutrack->dcaGlobal().mag();
  track.dcaZ       = mutrack->dcaZ();
  track.dcaD       = mutrack->dcaD();

  track.BField      = magneticField;
  track.bemcRadius = StEmcGeom::instance("bemc")->Radius() + 5;

  StThreeVectorD momentumAt, positionAt;
  StMuEmcPosition EmcPosition;
  if (EmcPosition.trackOnEmc(&positionAt, &momentumAt, mutrack, track.BField, track.bemcRadius))
    {
      track.exitDetectorId = 9;
      int id(0);
      StEmcGeom::instance("bemc")->getId(track.exitPhi, track.exitEta, id);
      track.exitTowerId = id;
      track.exitEta = positionAt.pseudoRapidity();
      track.exitPhi = positionAt.phi();
    }
  else if(EmcPosition.trackOnEEmc(&positionAt, &momentumAt, mutrack))
    {
      track.exitDetectorId = 13;
      track.exitTowerId = 0; // todo 
      track.exitEta = positionAt.pseudoRapidity();
      track.exitPhi = positionAt.phi();
    }
  else
    {
      track.exitEta = -999;
      track.exitPhi = -999;
    }


  track.dEdx = mutrack->dEdx();

  track.trackIndex = i;

  track.id = mutrack->id();

  return track;
}

}
