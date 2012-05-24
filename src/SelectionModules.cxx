#include "../include/SelectionModules.h"


TriggerSelection::TriggerSelection(std::string triggername){
  m_name=triggername;
}

bool TriggerSelection::pass(BaseCycleContainer *bcc){

  for(unsigned int i=0; i<bcc->triggerNames_actualrun.size(); ++i){
    if(!bcc->triggerNames_actualrun.at(i).find(m_name)){
      return bcc->triggerResults->at(i);
    }
  }
  std::cout<< "WARNING: trigger not found: " << m_name <<"; reject this event." << std::endl;
  for(unsigned int i=0; i<bcc->triggerNames_actualrun.size(); ++i){
    std::cout << "   "  << bcc->triggerNames_actualrun.at(i) << std::endl;
  }
  return false;
}

std::string TriggerSelection::description(){
  return "Trigger: "+m_name;
}


NJetSelection::NJetSelection(int min_nparticle, double ptmin, double etamax){
  m_min_nparticle= min_nparticle;
  m_ptmin=ptmin;
  m_etamax=etamax;
}

bool NJetSelection::pass(BaseCycleContainer *bcc){
  int nparticle=0;
  for(unsigned int i=0;i<bcc->jets->size(); ++i){
    if(bcc->jets->at(i).pt()>m_ptmin && fabs(bcc->jets->at(i).eta())<m_etamax) nparticle++;
  }
  return nparticle>=m_min_nparticle;
}

std::string NJetSelection::description(){
  char s[100];
  sprintf(s, "%d jets with pt>%.1f GeV, abs(eta)<%.1f",m_min_nparticle,m_ptmin,m_etamax);

  return s;
}


NTopJetSelection::NTopJetSelection(int min_nparticle, double ptmin, double etamax){
  m_min_nparticle= min_nparticle;
  m_ptmin=ptmin;
  m_etamax=etamax;
}

bool NTopJetSelection::pass(BaseCycleContainer *bcc){
  int nparticle=0;
  for(unsigned int i=0;i<bcc->topjets->size(); ++i){
    if(bcc->topjets->at(i).pt()>m_ptmin && fabs(bcc->topjets->at(i).eta())<m_etamax) nparticle++;
  }
  return nparticle>=m_min_nparticle;
}

std::string NTopJetSelection::description(){
  char s[100];
  sprintf(s, "%d top-jets with pt>%.1f GeV, abs(eta)<%.1f",m_min_nparticle,m_ptmin,m_etamax);
  return s;
}


NTopTagSelection::NTopTagSelection(int min_ntoptag, int max_ntoptag){
  m_min_ntoptag=min_ntoptag;
  m_max_ntoptag=max_ntoptag;
}

bool NTopTagSelection::pass(BaseCycleContainer *bcc){

  int ntoptag=0;
  
  for(unsigned int i=0; i< bcc->topjets->size(); ++i){
    TopJet topjet =  bcc->topjets->at(i);
    double mmin=0;
    double mjet=0;
    int nsubjets=0;
    if(TopTag(topjet,mjet,nsubjets,mmin)) ntoptag++;
  }
  if(ntoptag<m_min_ntoptag) return false;
  if(ntoptag>m_max_ntoptag) return false;
  return true;

}

std::string NTopTagSelection::description(){
  char s[100];
  sprintf(s, "%d <= number of top-tags <= %d",m_min_ntoptag,m_max_ntoptag);
  return s;
}



/*


bool Selection::NTopTagSelection(int min_ntoptag){

  int ntoptag=0;
  
  for(unsigned int i=0; i< bcc->topjets->size(); ++i){
    
    TopJet topjet =  bcc->topjets->at(i);
    double mmin=0;
    double mjet=0;
    int nsubjets=0;
    if(TopTag(topjet,mjet,nsubjets,mmin)) ntoptag++;
  }

  if(ntoptag<min_ntoptag) return false;
  return true;

}

*/