// -*- mode: c++;-*-
// $Id: StMuTrackEmu.h,v 1.4 2008/05/09 03:10:22 tai Exp $
// Copyright (C) 2008 Tai Sakuma <sakuma@bnl.gov>
#ifndef STMUTRACKEMU_H
#define STMUTRACKEMU_H

#include <Rtypes.h>

namespace StSpinJet {

class StMuTrackEmu {

public:

  StMuTrackEmu() { }
  virtual ~StMuTrackEmu() { }

  short          flag()       const { return _flag; }
  unsigned short nHits()      const { return _nHits; }
  Short_t        charge()     const { return _charge; }
  unsigned short nHitsPoss()  const { return _nHitsPoss; }
  unsigned short nHitsDedx()  const { return _nHitsDedx; }
  unsigned short nHitsFit()   const { return _nHitsFit; }
  double         nSigmaPion() const { return _nSigmaPion; }
  double         Tdca()       const { return _Tdca; }
  Float_t        dcaZ()       const { return _dcaZ; }
  Float_t        dcaD()       const { return _dcaD; }
  double         etaext()     const { return _etaext; }
  double         phiext()     const { return _phiext; }

private:

  friend class StMuTrackEmuFactory;

  short          _flag;
  unsigned short _nHits;
  Short_t        _charge;
  unsigned short _nHitsPoss;
  unsigned short _nHitsDedx;
  unsigned short _nHitsFit;
  double         _nSigmaPion;
  double         _Tdca;
  Float_t        _dcaZ;
  Float_t        _dcaD;
  double         _etaext;
  double         _phiext;
};

}

#endif // STMUTRACKEMU_H