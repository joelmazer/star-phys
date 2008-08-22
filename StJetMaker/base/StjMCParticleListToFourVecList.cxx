// $Id: StjMCParticleListToFourVecList.cxx,v 1.1 2008/08/22 18:36:19 tai Exp $
#include "StjMCParticleListToFourVecList.h"

#include "StjMCParticleToFourVec.h"

ClassImp(StjMCParticleListToFourVecList)

StjFourVecList StjMCParticleListToFourVecList::operator()(const StjMCParticleList& mcparticleList)
{
  StjFourVecList ret;

  StjMCParticleToFourVec mcparticle2four;

  int fourvecId(1);
  for(StjMCParticleList::const_iterator mcparticle = mcparticleList.begin(); mcparticle != mcparticleList.end(); ++mcparticle) {
    StjFourVec four = mcparticle2four(*mcparticle);
    four.fourvecId = fourvecId++;
    ret.push_back(four);
  }


  return ret;
}
