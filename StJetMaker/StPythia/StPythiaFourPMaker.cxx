
//std
#include <iostream>
using namespace std;

//SCL
#include "StarClassLibrary/SystemOfUnits.h"
#include "StPhysicalHelixD.hh"
#include "StThreeVectorF.hh"
#include "StLorentzVectorF.hh"
#include "StThreeVectorD.hh"

//StMuDstMaker
#include "StMuDSTMaker/COMMON/StMuDst.h"
#include "StMuDSTMaker/COMMON/StMuTrack.h"
#include "StMuDSTMaker/COMMON/StMuEvent.h"
#include "StMuDSTMaker/COMMON/StMuDstMaker.h"
#include "StMuDSTMaker/COMMON/StMuEmcCollection.h"

//StEvent
#include "StDetectorId.h"

//McEvent
#include "StMcEventMaker/StMcEventMaker.h"
#include "StMcEventTypes.hh"
#include "StMcEvent.hh"

//Table stuff
#include "St_DataSet.h"
#include "St_DataSetIter.h"
#include "tables/St_g2t_event_Table.h"
#include "tables/St_particle_Table.h"
#include "tables/St_g2t_pythia_Table.h"

//StJetMaker
#include "StJetMaker/StJetSimuUtil/StJetSimuWeightMaker.h"
#include "StJetMaker/StMuTrackFourVec.h"
#include "StJetMaker/StPythia/StPythiaFourPMaker.h"
#include "StJetMaker/StPythia/StPythiaMuTrackFourVec.h"

ClassImp(StPythiaFourPMaker)
    
    StPythiaFourPMaker::StPythiaFourPMaker(const char* name, StJetSimuWeightMaker* sim,  StMcEventMaker* mc) 
	: StFourPMaker(name, 0), mSimuMaker(sim), mMcEventMaker(mc)
{
    cout <<"StPythiaFourPMaker::StPythiaFourPMaker()"<<endl;

}

void StPythiaFourPMaker::Clear(Option_t* opt)
{
    cout <<"void StPythiaFourPMaker::Clear(Option_t* opt)";
    for (Pythia4Vec::iterator it=mVec.begin(); it!=mVec.end(); ++it) {
	delete (*it);
	(*it) = 0;
    }
    mVec.clear();
    StFourPMaker::Clear(opt);
    cout <<"\tvec:\t"<<mVec.size()<<"\ttracks:\t"<<tracks.size()<<endl;
    return;
}

Int_t StPythiaFourPMaker::Make()
{

    cout <<"StPythiaFourPMaker::Make()"<<endl;
    assert(mSimuMaker);

    cout <<"Int_t StPythiaFourPMaker::Make()";
    cout <<"\tvec:\t"<<mVec.size()<<"\ttracks:\t"<<tracks.size()<<endl;


    //SubProcess ID from StMcEventMaker
    StMcEvent* mcEvent = dynamic_cast<StMcEvent*>( mMcEventMaker->currentMcEvent() );
    if(!mcEvent)  {
	cout <<"No McEvent!!!"<<endl;
	return kStErr;
    }
    

    //access the ptyhia particle table.  Should access via StMcEvent, but that's not yet updated for Maxim's newest additions
    St_particle* particleTabPtr = mSimuMaker->particleTabPtr;
    assert(particleTabPtr);
    particle_st* particleTable = particleTabPtr->GetTable();
    assert(particleTable);

    //look at outgoing parton:
    StThreeVectorF out1(mSimuMaker->parton1[1], mSimuMaker->parton1[2], mSimuMaker->parton1[3]);
    StThreeVectorF out2(mSimuMaker->parton2[1], mSimuMaker->parton2[2], mSimuMaker->parton2[3]);

    if (out1.perp()<3. || out2.perp()<3.) {
	cout <<"q2 too soft. "<<endl;
	return StMaker::Make();
    }


    //cout <<"Look at:\t"<<particleTabPtr->GetNRows()<<"\tparticles in event record"<<endl;
    //printf("row \t id \t pt \t phi \t eta \t status \n");
    for (int i=0; i<particleTabPtr->GetNRows();++i) {
	int status = particleTable[i].isthep;//status
	
	if (status==1) { //ok, showering is finished, but these particles could decay further (e.g., pi0 -> gamma gamma)
	    
	    //particleTable[i].idhep;// particle id
	    //particleTable[i].phep[4];//m
	    StThreeVectorF momentum(particleTable[i].phep[0],//px
				    particleTable[i].phep[1],//py
				    particleTable[i].phep[2]//pz
				    );
	    
	    double energy = particleTable[i].phep[3];//E
	    StLorentzVectorF p4( energy, momentum);
	    
	    if (fabs(p4.pseudoRapidity())<5.0) {
		
		StMuTrackFourVec* pmu = new StMuTrackFourVec();
		
		//void Init(StMuTrack* track, StLorentzVectorF P, Int_t i, StDetectorId detId);
		pmu->Init(0, p4, i, kUnknownId );
		
		mVec.push_back(pmu);
		tracks.push_back(pmu);
		//cout <<"Adding 4p:\t"<<(*pmu)<<endl;
		
		//printf("  %d \t %d \t %f \t %f \t %f \t %d,\n", i, particleTable[i].idhep, p4.perp(), p4.phi(), p4.pseudoRapidity(), status);
	    }
	}
    }
    cout <<StMaker::GetName()<<"::Make()\tAdded:\t"<<tracks.size()<<"\tparticles to track container"<<endl;

    cout <<"out1:\t"<<out1.perp()<<"\t"<<out1.phi()<<"\t"<<out1.pseudoRapidity()<<endl;
    cout <<"out2:\t"<<out2.perp()<<"\t"<<out2.phi()<<"\t"<<out2.pseudoRapidity()<<endl;
    
    return StMaker::Make();
}






