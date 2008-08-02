// $Id: StjMCMuDst.cxx,v 1.2 2008/08/02 19:23:20 tai Exp $

#include <StjMCMuDst.h>

#include <StMaker.h>

#include <StMuDSTMaker/COMMON/StMuEvent.h>
#include <StMuDSTMaker/COMMON/StMuDst.h>
#include <StMuDSTMaker/COMMON/StMuDstMaker.h>

#include <TDataSet.h>
#include <TDataSetIter.h>

#include <tables/St_particle_Table.h>

#include <TLorentzVector.h>

namespace StSpinJet {

StjMCParticleList StjMCMuDst::getMCPartilceList()
{

  TDataSet *Event = _maker->GetDataSet("geant");

  TDataSetIter geantDstI(Event);
  const St_particle* particleTabPtr = (St_particle*)geantDstI("particle");
  const particle_st* particleTable = particleTabPtr->GetTable();

  StjMCParticleList theList;

  StMuDstMaker *uDstMaker = dynamic_cast<StMuDstMaker*>(_maker->GetMaker("MuDst"));

  StjMCParticle particle;
  particle.runNumber = uDstMaker->muDst()->event()->runId();
  particle.eventId = uDstMaker->muDst()->event()->eventId();
  particle.vertexZ = uDstMaker->muDst()->event()->primaryVertexPosition().z();

  for (int i = 0; i < particleTabPtr->GetNRows(); ++i) {
		
    particle.status          = particleTable[i].isthep;
    particle.mcparticleId    = i + 1;
    particle.pdg             = particleTable[i].idhep;
    particle.firstMotherId   = particleTable[i].jmohep[0];
    particle.lastMotherId    = particleTable[i].jmohep[1];
    particle.firstDaughterId = particleTable[i].jdahep[0];
    particle.lastDaughterId  = particleTable[i].jdahep[1];

    TLorentzVector p4(particleTable[i].phep[0], particleTable[i].phep[1], particleTable[i].phep[2], particleTable[i].phep[3]);
    particle.pt  = p4.Pt();
    particle.eta = p4.Eta();
    particle.phi = p4.Phi();
    particle.m   = p4.M();
    particle.e   = p4.E();

    theList.push_back(particle);
  }

  return theList;
}

}
