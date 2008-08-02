// $Id: StjBEMCMuDst.cxx,v 1.2 2008/08/02 19:23:19 tai Exp $
#include "StjBEMCMuDst.h"

#include <StMuDSTMaker/COMMON/StMuDstMaker.h>
#include <StMuDSTMaker/COMMON/StMuDst.h>
#include <StMuDSTMaker/COMMON/StMuEvent.h>

#include <StEvent/StEmcRawHit.h>
#include <StEvent/StEmcCollection.h>
#include <StEvent/StEmcModule.h>
#include <StEvent/StEmcDetector.h>

#include <StEmcUtil/geometry/StEmcGeom.h>

#include <StEmcRawMaker/defines.h>
#include <StEmcRawMaker/StBemcTables.h>

#include <TVector3.h>

#include <iostream>

using namespace std;

namespace StSpinJet {


StjBEMCMuDst::StjBEMCMuDst(StMuDstMaker* uDstMaker, bool doTowerSwapFix)
  : _uDstMaker(uDstMaker)
  , _bemcTables(new StBemcTables(doTowerSwapFix))
 {

 }


StjTowerEnergyList StjBEMCMuDst::getEnergyList()
{
  _bemcTables->loadTables((StMaker*)_uDstMaker);

  StjTowerEnergyList ret;

  StEmcDetector* detector = _uDstMaker->muDst()->emcCollection()->detector(kBarrelEmcTowerId);

  static const int nBemcModules = 120;

  for(int m = 1; m <= nBemcModules; ++m) {

    StSPtrVecEmcRawHit& rawHits = detector->module(m)->hits();

    for(UInt_t k = 0; k < rawHits.size(); ++k) {
  	    
      ret.push_back(readTowerHit(*rawHits[k]));
    }
  }

  return ret;
}

StjTowerEnergy StjBEMCMuDst::readTowerHit(const StEmcRawHit& hit)
{
  StjTowerEnergy ret;

  ret.runNumber = _uDstMaker->muDst()->event()->runId();
  ret.eventId = _uDstMaker->muDst()->event()->eventId();

  ret.detectorId = 9;

  int towerId;
  StEmcGeom::instance("bemc")->getId(hit.module(), hit.eta(), abs(hit.sub()), towerId);

  ret.towerId = towerId;

  float towerX, towerY, towerZ;
  StEmcGeom::instance("bemc")->getXYZ(towerId, towerX, towerY, towerZ);
  TVector3 tower(towerX, towerY, towerZ);

  ret.towerR   = tower.Perp();
  ret.towerEta = tower.Eta();
  ret.towerPhi = tower.Phi();

  StThreeVectorF vertex = _uDstMaker->muDst()->event()->primaryVertexPosition();

  ret.vertexX = vertex.x();
  ret.vertexY = vertex.y();
  ret.vertexZ = vertex.z(); 

  ret.energy = hit.energy();
  ret.adc    = hit.adc();

  float pedestal, rms;
  int CAP(0);
  _bemcTables->getPedestal(BTOW, towerId, CAP, pedestal, rms);
  ret.pedestal = pedestal;
  ret.rms = rms;

  int status;
  _bemcTables->getStatus(BTOW, towerId, status);
  ret.status = status;

  return ret;
}


}
