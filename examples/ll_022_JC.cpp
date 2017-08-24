#define PI 3.1415926535897932384626433832795028841971693993751


#include "SampleAnalyzer/User/Analyzer/ll_022.h"
using namespace MA5;
using namespace std;

// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool ll_022::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
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

    Manager()->AddRegionSelection("SR I, |d0|>200 #mu m");
    Manager()->AddRegionSelection("SR II, |d0|>500 #mu m");
    Manager()->AddRegionSelection("SR III, |d0|>1000 #mu m");
    
    
    Manager()->AddCut("mu isolation");
    Manager()->AddCut("e isolation");
    Manager()->AddCut("|eta_e,mu| < 2.4");
    Manager()->AddCut("PT mu > 40 GeV");
    Manager()->AddCut("PT e > 42 GeV");
    Manager()->AddCut("dR(e,mu) > 0.5");

    string SR3Cut[] = {"SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>1000 #mu m",SR3Cut);
    
    string SR2Cut[] = {"SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>1000 #mu m",SR2Cut);
    
    string SR1Cut[] = {"SR III, |d0|>1000 #mu m",
        "SR II, |d0|>500 #mu m",
        "SR I, |d0|>200 #mu m"};
    Manager()->AddCut("|d0|>1000 #mu m",SR1Cut);
    
    
   ]
    
    
    
    
    
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void ll_022::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  cout << "END   Finalization" << endl;
}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool ll_022::Execute(SampleFormat& sample, const EventFormat& event)
{
  // ***************************************************************************
  // Example of analysis with generated particles
  // Concerned samples : LHE/STDHEP/HEPMC
  // ***************************************************************************
  /*
  if (event.mc()!=0)
  {
    cout << "---------------NEW EVENT-------------------" << endl;

    // Initial state
    for (unsigned int i=0;i<event.mc()->particles().size();i++)
    {
      const MCParticleFormat& part = event.mc()->particles()[i];

      cout << "----------------------------------" << endl;
      cout << "MC particle" << endl;
      cout << "----------------------------------" << endl;

      // display index particle
      cout << "index=" << i+1;

      // display the status code
      cout << "Status Code=" << part.statuscode() << endl;
      if (PHYSICS->Id->IsInitialState(part)) cout << " (Initial state) ";
      else if (PHYSICS->Id->IsFinalState(part)) cout << " (Final state) ";
      else cout << " (Intermediate state) ";
      cout << endl;

      // pdgid
      cout << "pdg id=" << part.pdgid() << endl;
      if (PHYSICS->Id->IsInvisible(part)) cout << " (invisible particle) ";
      else cout << " (visible particle) ";
      cout << endl;

      // display kinematics information
      cout << "px=" << part.px()
                << " py=" << part.py()
                << " pz=" << part.pz()
                << " e="  << part.e()
                << " m="  << part.m() << endl;
      cout << "pt=" << part.pt() 
                << " eta=" << part.eta() 
                << " phi=" << part.phi() << endl;

      // display particle mother id
      if (part.mother1()==0) 
      {
        cout << "particle with no mother." << endl;
      }
      else if (part.mother2()==0 || part.mother1()==part.mother2())
      {
        const MCParticleFormat* mother = part.mother1();
        cout << "particle coming from the decay of " 
             << mother->pdgid() << "." << endl;
      }
      else
      {
        const MCParticleFormat* mother1 = part.mother1();
        const MCParticleFormat* mother2 = part.mother2();
        cout << "particle coming from interaction between "
             << mother1->pdgid() << " and " << mother2->pdgid()
             << "." << endl;
      }
    }

    // Transverse missing energy (MET)
    cout << "MET pt=" << event.mc()->MET().pt()
         << " phi=" << event.mc()->MET().phi() << endl;
    cout << endl;

    // Transverse missing hadronic energy (MHT)
    cout << "MHT pt=" << event.mc()->MHT().pt()
              << " phi=" << event.mc()->MHT().phi() << endl;
    cout << endl;

    // Total transverse energy (TET)
    cout << "TET=" << event.mc()->TET() << endl;
    cout << endl;

    // Total transverse hadronic energy (THT)
    cout << "THT=" << event.mc()->THT() << endl; 
   cout << endl;

  return true;
  }
  */


  // ***************************************************************************
  // Example of analysis with reconstructed objects
  // Concerned samples : 
  //   - LHCO samples
  //   - LHE/STDHEP/HEPMC samples after applying jet-clustering algorithm
  // ***************************************************************************
  /*
  if (event.rec()!=0)
  {
    cout << "---------------NEW EVENT-------------------" << endl;

    // Looking through the reconstructed electron collection
    for (unsigned int i=0;i<event.rec()->electrons().size();i++)
    {
      const RecLeptonFormat& elec = event.rec()->electrons()[i];
      cout << "----------------------------------" << endl;
      cout << "Electron" << endl;
      cout << "----------------------------------" << endl;
      cout << "index=" << i+1 
                << " charge=" << elec.charge() << endl;
      cout << "px=" << elec.px()
                << " py=" << elec.py()
                << " pz=" << elec.pz()
                << " e="  << elec.e()
                << " m="  << elec.m() << endl;
      cout << "pt=" << elec.pt() 
                << " eta=" << elec.eta() 
                << " phi=" << elec.phi() << endl;
      cout << "pointer address to the matching MC particle: " 
                << elec.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed muon collection
    for (unsigned int i=0;i<event.rec()->muons().size();i++)
    {
      const RecLeptonFormat& mu = event.rec()->muons()[i];
      cout << "----------------------------------" << endl;
      cout << "Muon" << endl;
      cout << "----------------------------------" << endl;
      cout << "index=" << i+1 
                << " charge=" << mu.charge() << endl;
      cout << "px=" << mu.px()
                << " py=" << mu.py()
                << " pz=" << mu.pz()
                << " e="  << mu.e()
                << " m="  << mu.m() << endl;
      cout << "pt=" << mu.pt() 
                << " eta=" << mu.eta() 
                << " phi=" << mu.phi() << endl;
      cout << "ET/PT isolation criterion =" << mu.ET_PT_isol() << endl;
      cout << "pointer address to the matching MC particle: " 
           << mu.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed hadronic tau collection
    for (unsigned int i=0;i<event.rec()->taus().size();i++)
    {
      const RecTauFormat& tau = event.rec()->taus()[i];
      cout << "----------------------------------" << endl;
      cout << "Tau" << endl;
      cout << "----------------------------------" << endl;
      cout << "tau: index=" << i+1 
                << " charge=" << tau.charge() << endl;
      cout << "px=" << tau.px()
                << " py=" << tau.py()
                << " pz=" << tau.pz()
                << " e="  << tau.e()
                << " m="  << tau.m() << endl;
      cout << "pt=" << tau.pt() 
                << " eta=" << tau.eta() 
                << " phi=" << tau.phi() << endl;
      cout << "pointer address to the matching MC particle: " 
           << tau.mc() << endl;
      cout << endl;
    }

    // Looking through the reconstructed jet collection
    for (unsigned int i=0;i<event.rec()->jets().size();i++)
    {
      const RecJetFormat& jet = event.rec()->jets()[i];
      cout << "----------------------------------" << endl;
      cout << "Jet" << endl;
      cout << "----------------------------------" << endl;
      cout << "jet: index=" << i+1 
           << " charge=" << jet.charge() << endl;
      cout << "px=" << jet.px()
           << " py=" << jet.py()
           << " pz=" << jet.pz()
           << " e="  << jet.e()
           << " m="  << jet.m() << endl;
      cout << "pt=" << jet.pt() 
           << " eta=" << jet.eta() 
           << " phi=" << jet.phi() << endl;
      cout << "b-tag=" << jet.btag()
           << " true b-tag (before eventual efficiency)=" 
           << jet.true_btag() << endl;
      cout << "EE/HE=" << jet.EEoverHE()
           << " ntracks=" << jet.ntracks() << endl;
      cout << endl;
    }

    // Transverse missing energy (MET)
    cout << "MET pt=" << event.rec()->MET().pt()
         << " phi=" << event.rec()->MET().phi() << endl;
    cout << endl;

    // Transverse missing hadronic energy (MHT)
    cout << "MHT pt=" << event.rec()->MHT().pt()
              << " phi=" << event.rec()->MHT().phi() << endl;
    cout << endl;

    // Total transverse energy (TET)
    cout << "TET=" << event.rec()->TET() << endl;
    cout << endl;

    // Total transverse hadronic energy (THT)
    cout << "THT=" << event.rec()->THT() << endl;
    cout << endl;
  }
  */
  return true;
}

