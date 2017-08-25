#include "SampleAnalyzer/User/Analyzer/JC_ll.h"
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool JC_ll::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
    INFO << "        <><><><><><><><><><><><><><><><><><><><><><><><><><><>" << endmsg;
    INFO << "        <>   Analysis:  CMS-EXO-16-022,                     <>" << endmsg;
    INFO << "        <>             (Long lived particles)               <>" << endmsg;
    INFO << "        <>   Recasted by: J.Chang, D.Kang, P.Wu and S.Yang  <>" << endmsg;
    INFO << "        <>   Contact: lovejesus99wwjd@gmail.com             <>" << endmsg;
    INFO << "        <>            dayou17@gmail.com                     <>" << endmsg;
    INFO << "        <>            peiwen.wu123@gmail.com                <>" << endmsg;
    INFO << "        <>            slowmoyang@gmail.com                  <>" << endmsg;
    INFO << "        <>   Based on MadAnalysis 5 v1.6.25                 <>" << endmsg;
    INFO << "        <>   For more information, see                      <>" << endmsg;
    INFO << "        <>  http://madanalysis.irmp.ucl.ac.be/wiki/PhysicsAnalysisDatabase" << endmsg;
    INFO << "        <><><><><><><><><><><><><><><><><><><><><><><><>" << endmsg;
    

    // Declaration of the signal regions
    Manager()->AddRegionSelection("SR1");
    Manager()->AddRegionSelection("SR2");
    Manager()->AddRegionSelection("SR3");
    
    // Declaration of the preselection cuts
//    Manager()->AddCut("_electron", "e");
//    Manager()->AddCut("1_muon", "mu");
    Manager()->AddCut("1_electron");
    Manager()->AddCut("1_muon");
    Manager()->AddCut("dR_emu>0.5");
    string SR3Cut[] = {
        "SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>1000",SR3Cut);
    
    string SR2Cut[] = {
        "SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>500",SR2Cut);
    
    string SR1Cut[] = {
        "SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>200",SR1Cut);


    
    // Histogram declaration
    Manager()->AddHisto("# of SR1 electrons", 40,0,10);
    Manager()->AddHisto("# of SR2 electrons", 40,0,10);
    Manager()->AddHisto("# of SR3 electrons", 40,0,10);
    Manager()->AddHisto("# of SR1 muons", 40,0,10);
    Manager()->AddHisto("# of SR2 muons", 40,0,10);
    Manager()->AddHisto("# of SR3 muons", 40,0,10);

    Manager()->AddHisto("electron |d0| #mu m", 40,0,1000);
    Manager()->AddHisto("muon |d0| #mu m", 40,0,1000);
    Manager()->AddHisto("dR(e,mu) after preselection cut", 50,0,5);
    Manager()->AddHisto("eta(e) after preselection cut", 50,-5,5);
    Manager()->AddHisto("eta(mu) after preselection cut", 50,-5,5);
    Manager()->AddHisto("PT(e) after preselection cut", 50,0,200);
    Manager()->AddHisto("PT(mu) after preselection cut", 50,0,200);

  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void JC_ll::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool JC_ll::Execute(SampleFormat& sample, const EventFormat& event)
{

  double myWeight;
  if(Configuration().IsNoEventWeight()) myWeight=1.;
  else if(event.mc()->weight()!=0.) myWeight=event.mc()->weight();
  else
  {
    WARNING << "Found one event with a zero weight. Skipping..." << endmsg;
    return false;
  }
  Manager()->InitializeForNewEvent(myWeight);

  if (event.rec()!=0)
  {
      std::vector<const RecLeptonFormat*> SignalElectrons,SignalElectronsSR1, SignalElectronsSR2, SignalElectronsSR3;
      std::vector<const RecLeptonFormat*> SignalMuons, SignalMuonsSR1, SignalMuonsSR2, SignalMuonsSR3;


      for (MAuint32 i=0;i<event.rec()->electrons().size();i++)
    {
        for(unsigned int j=0; j<SignalElectrons[i]->isolCones().size(); j++)
        {
        const RecLeptonFormat *myElec = &(event.rec()->electrons()[i]);
        double eta = fabs(myElec->eta());
        double pt = myElec->pt();
        double elecd0 = fabs(myElec->d0());
        double iso_dr = fabs(SignalElectrons[i]->isolCones()[j].deltaR() - 0.3);
        double iso_pt = SignalElectrons[i]->isolCones()[j].sumPT();
        if( (eta > 1.44) and (eta<1.57) ) continue;
        if(eta > 2.4) continue;
        if(pt < 42) continue;

        if(eta < 1.44) {
        if( iso_dr > 0.001 &&
           iso_pt >.035*pt) continue;}
            
        if(eta < 1.57) {
        if( iso_dr > 0.001 &&
                   iso_pt >.065*pt) continue;}
            
                             SignalElectrons.push_back(myElec);
            if (elecd0>200 && elecd0<200)  SignalElectronsSR1.push_back(myElec);
            if (elecd0>500 && elecd0<1000)  SignalElectronsSR2.push_back(myElec);
            if (elecd0>1000)  SignalElectronsSR3.push_back(myElec);
        }}
      unsigned int ne=SignalElectrons.size(); // number of electrons
      unsigned int neSR1=SignalElectronsSR1.size(); // number of electrons
      unsigned int neSR2=SignalElectronsSR2.size(); // number of electrons
      unsigned int neSR3=SignalElectronsSR3.size(); // number of electrons
    // Looking through the reconstructed muon collection
      
    for (MAuint32 i=0;i<event.rec()->muons().size();i++)
    {
        for(unsigned int j=0; j<SignalMuons[i]->isolCones().size(); j++)
        {
        const RecLeptonFormat *myMuon = &(event.rec()->muons()[i]);
        double eta = fabs(myMuon->eta());
        double pt = myMuon->pt();
        double mud0 = fabs(myMuon->d0());
        double iso_dr = fabs(SignalMuons[i]->isolCones()[j].deltaR() - 0.4);
        double iso_pt = SignalMuons[i]->isolCones()[j].sumPT();
        if(eta > 2.4) continue;
        if(pt < 40) continue;
        
        if( iso_dr > 0.001 &&
           iso_pt >.15*pt) continue;
            
                       SignalMuons.push_back(myMuon);
        if (mud0>200 && mud0<500)  SignalMuonsSR1.push_back(myMuon);
        if (mud0>500 && mud0<1000)  SignalMuonsSR2.push_back(myMuon);
        if (mud0>1000)  SignalMuonsSR3.push_back(myMuon);
            
        }    }
    unsigned int nmu=SignalMuons.size(); // number of electrons
    unsigned int nmuSR1=SignalMuonsSR1.size(); // number of electrons
    unsigned int nmuSR2=SignalMuonsSR2.size(); // number of electrons
    unsigned int nmuSR3=SignalMuonsSR3.size(); // number of electrons
      
      Manager()->FillHisto("# of SR1 electrons", neSR1);
      Manager()->FillHisto("# of SR2 electrons", neSR2);
      Manager()->FillHisto("# of SR3 electrons", neSR3);

      Manager()->FillHisto("# of SR1 muons", nmuSR1);
      Manager()->FillHisto("# of SR2 muons", nmuSR2);
      Manager()->FillHisto("# of SR3 muns", nmuSR3);

      
      
      double charge=0.;
      double dR_emu=0.;
      double SR1_d0_e=0.;
      double SR2_d0_e=0.;
      double SR3_d0_e=0.;
      double SR1_d0_mu=0.;
      double SR2_d0_mu=0.;
      double SR3_d0_mu=0.;
      
      if(ne==1 || nmu==1) charge=SignalMuons[0]->charge()*SignalElectrons[0]->charge();
      if(!Manager()->ApplyCut( (ne==1) && (charge<0.),"1_electron")) return true;
      if(!Manager()->ApplyCut( (nmu==1) && (charge<0.),"1_muon")) return true;
       dR_emu=SignalMuons[0]->dr(SignalElectrons[0]);
      if(!Manager()->ApplyCut( dR_emu>0.5,"dR_emu>0.5")) return true;

      SR1_d0_e=SignalElectronsSR1[0]->d0();
      SR1_d0_mu=SignalMuonsSR1[0]->d0();
      if(!Manager()->ApplyCut( SR1_d0_e>200 && SR1_d0_mu>200 ,"|d0|>200")) return true;
      SR2_d0_e=SignalElectronsSR2[0]->d0();
      SR2_d0_mu=SignalMuonsSR2[0]->d0();
      if(!Manager()->ApplyCut( SR2_d0_e>200 && SR2_d0_mu>200,"|d0|>500")) return true;
      SR3_d0_e=SignalElectronsSR3[0]->d0();
      SR3_d0_mu=SignalMuonsSR3[0]->d0();
      if(!Manager()->ApplyCut( SR3_d0_e>200 && SR3_d0_mu>200,"|d0|>500")) return true;
  
  
  }
  
  return true;
}

