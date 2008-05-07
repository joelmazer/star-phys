// $Id: StCdfChargedConeJetFinder.cxx,v 1.24 2008/05/07 22:43:08 tai Exp $
#include "StCdfChargedConeJetFinder.h"

#include "StJetEtCell.h"
#include "StJetSpliterMerger.h"
#include "StProtoJet.h"
#include "StCdfChargedJetEtCell.h"

StCdfChargedConeJetFinder::StCdfChargedConeJetFinder(const StCdfChargedConePars& pars) 
  : StConeJetFinderBase(pars)
{

}

StCdfChargedConeJetFinder::~StCdfChargedConeJetFinder()
{
}

StJetEtCellFactory* StCdfChargedConeJetFinder::makeCellFactory()
{
  return new StCdfChargedJetEtCellFactory;
}

void StCdfChargedConeJetFinder::findJets(JetList& protoJetList)
{
  clearPreviousResult();

  CellList orderedList = generateLeadingPtOrderedList(protoJetList);

  CellList toSearchList = generateToSearchListFrom(orderedList);

  findProtoJets(toSearchList);

  storeTheResultIn(protoJetList);

}

StEtaPhiCell::CellList StCdfChargedConeJetFinder::generateLeadingPtOrderedList(JetList& protoJetList)
{
  _cellGrid.fillGridWith(protoJetList);
  return _cellGrid.EtSortedCellList();
}

void StCdfChargedConeJetFinder::findJetAroundThis(StEtaPhiCell* cell)
{
  initializeWorkCell(cell);
  
  formCone();
  addToPrejets(*mWorkCell);
}

bool StCdfChargedConeJetFinder::shouldNotSearchForJetAroundThis(const StEtaPhiCell* cell) const
{
  if (cell->nTimesUsed()) return true;

  if (cell->empty()) return true;

  return false;
}

bool StCdfChargedConeJetFinder::shouldNotAddToTheCell(const StEtaPhiCell& theCell, const StEtaPhiCell& otherCell) const
{
  if (otherCell.nTimesUsed()) return true;
  if (otherCell.empty()) return true;
  if (otherCell.eT() <= mPars.assocEtMin()) return true; 
  return false;
}

