//StProtoJet.h
//M.L. Miller (Yale Software)
//4/02

#ifndef StProtoJet_HH
#define StProtoJet_HH

#include <iostream.h>
#include <math.h>

#include <list>
using std::list;

#include <vector>
using std::vector;

#include <algorithm>
using std::copy;

#include <iterator>
using std::ostream_iterator;

#include "FourVec.h"

class StProtoJet : public StFourVec
{
public:
    typedef vector<AbstractFourVec*> FourVecList;
	
    StProtoJet();
    StProtoJet(AbstractFourVec*);
    virtual ~StProtoJet();
	
    //access
	
    ///Number of particles in this protojet
    unsigned int numberOfParticles() const {return size();}
    unsigned int size() const {return mList.size();}
    FourVecList& list() {return mList;}
	
    ///The d=et^2 of the protojet
    double d() const {return eT()*eT();}
	
    ///Add a protojet to this one and calculate new parameters.  
    void merge(const StProtoJet&);
	
    ///Add a protojet to this one w/o calculating the new parameters
    void add(const StProtoJet&);
	void remove(StProtoJet&);

	
    ///update the parameters of this protojet (in case some have been added via add())
    void update();
	
    ///clear
    void clear();
	
    friend ostream& operator<<(ostream& os, const StProtoJet& j);
	
private:
    FourVecList mList;
};

inline void StProtoJet::clear()
{
    mList.clear();
    mPx=mPy=mPz=mE=0.;
}

inline ostream& operator<<(ostream& os, const StProtoJet& j)
{
    os <<"et: "<<j.eT()<<"\tphi: "<<j.phi()<<"\teta: "<<j.eta()
       <<"\tmass: "<<j.mass()<<"\tcharge: "<<j.charge()<<"\tParticles"<<endl;
    for (StProtoJet::FourVecList::const_iterator it=j.mList.begin(); it!=j.mList.end(); ++it) {
	os << **it <<endl;
    }
    return os;
}

#endif

