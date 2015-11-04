#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TChain.h"

#include "Math/QuantFuncMathCore.h"
#include "TMath.h"
#include "SusyAnaTools/Tools/NTupleReader.h"
#include "SusyAnaTools/Tools/baselineDef.h"

#include "LLBinFunction.h"

//############################begin to defin class AccRecoIsoEffs###################
static BaselineVessel *myBaselineVessel;
void mypassBaselineFunc(NTupleReader& tr)
{
  (*myBaselineVessel)(tr);
}

class BaseHistgram;

class AccRecoIsoEffs
{
 public:
  void printOverview();
  void printAccRecoIsoEffs();
  void printNormalizeFlowNumber();
  void printEffsHeader();

  //here we define the overall information for ttbar sample
  int nevents_tot = 0;
  int nevents_sel_base = 0;
  int nevents_sel_mus = 0;
  int nevents_sel_els = 0;
  int nevents_cs_mus = 0;

  //define acceptance, reco eff and iso eff to be calculated
  double mus_acc[NJETS_BINS] = {0}, els_acc[NJETS_BINS] = {0};
  double mus_acc_err[NJETS_BINS] = {0}, els_acc_err[NJETS_BINS] = {0};

  double mus_recoeff[PT_BINS][AC_BINS] = {{0}}, els_recoeff[PT_BINS][AC_BINS] = {{0}};
  double mus_isoeff[PT_BINS][AC_BINS] = {{0}}, els_isoeff[PT_BINS][AC_BINS] = {{0}};
  double mus_isoeff_allreco[PT_BINS][AC_BINS] = {{0}}, els_isoeff_allreco[PT_BINS][AC_BINS] = {{0}};
 
  double mus_recoeff_err[PT_BINS][AC_BINS] = {{0}}, els_recoeff_err[PT_BINS][AC_BINS] = {{0}};
  double mus_isoeff_err[PT_BINS][AC_BINS] = {{0}}, els_isoeff_err[PT_BINS][AC_BINS] = {{0}};
  double mus_isoeff_err_allreco[PT_BINS][AC_BINS] = {{0}}, els_isoeff_err_allreco[PT_BINS][AC_BINS] = {{0}};

  double mtwcorrfactor[PT_BINS] = {0}, mtwcorrfactor_err[PT_BINS] = {0};
 
  //here we define the muon/electron number we need to count in the loop
  double nmus_MC[NJETS_BINS] = {0}, nmus_acc_MC[NJETS_BINS] = {0}, nels_MC[NJETS_BINS] = {0}, nels_acc_MC[NJETS_BINS] = {0};
  double nmus_acc_bin_MC[PT_BINS][AC_BINS] = {{0}}, nels_acc_bin_MC[PT_BINS][AC_BINS] = {{0}};
  double nmus_reco_MC[PT_BINS][AC_BINS] = {{0}}, nels_reco_MC[PT_BINS][AC_BINS] = {{0}};
  double nmus_iso_MC[PT_BINS][AC_BINS] = {{0}}, nels_iso_MC[PT_BINS][AC_BINS] = {{0}};

  double nmus_reco_MC_allreco[PT_BINS][AC_BINS] = {{0}}, nels_reco_MC_allreco[PT_BINS][AC_BINS] = {{0}};
  double nmus_iso_MC_allreco[PT_BINS][AC_BINS] = {{0}}, nels_iso_MC_allreco[PT_BINS][AC_BINS] = {{0}};

  double mtwall_MC[PT_BINS] = {0}, mtw100_MC[PT_BINS] = {0};

  double nmus[NJETS_BINS] = {0}, nmus_acc[NJETS_BINS] = {0}, nels[NJETS_BINS] = {0}, nels_acc[NJETS_BINS] = {0};
  double nmus_acc_bin[PT_BINS][AC_BINS] = {{0}}, nels_acc_bin[PT_BINS][AC_BINS] = {{0}};
  double nmus_reco[PT_BINS][AC_BINS] = {{0}}, nels_reco[PT_BINS][AC_BINS] = {{0}};
  double nmus_iso[PT_BINS][AC_BINS] = {{0}}, nels_iso[PT_BINS][AC_BINS] = {{0}};

  double nmus_reco_allreco[PT_BINS][AC_BINS] = {{0}}, nels_reco_allreco[PT_BINS][AC_BINS] = {{0}};
  double nmus_iso_allreco[PT_BINS][AC_BINS] = {{0}}, nels_iso_allreco[PT_BINS][AC_BINS] = {{0}};

  double mtwall[PT_BINS] = {0}, mtw100[PT_BINS] = {0};

  //here we define the event weight we are going to use in the second loop ( muon/electron CS and prediction plots)
  double mus_EventWeight_iso[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}}, mus_EventWeight_reco[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}}, mus_EventWeight_acc[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}};
  double els_EventWeight_iso[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}}, els_EventWeight_reco[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}}, els_EventWeight_acc[NJETS_BINS][PT_BINS][AC_BINS] = {{{0}}};

  //here we define the search bin variables
  double nevents_mus_CS_SB_MC[NSEARCH_BINS] = {0}, nevents_mus_CS_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_mus_pred_SB_MC[NSEARCH_BINS] = {0}, nevents_mus_pred_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_mus_pred_SB_MC_err[NSEARCH_BINS] = {0};
  double nevents_mus_exp_SB_MC[NSEARCH_BINS] = {0}, nevents_mus_exp_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_els_pred_SB_MC[NSEARCH_BINS] = {0}, nevents_els_pred_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_els_exp_SB_MC[NSEARCH_BINS] = {0}, nevents_els_exp_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_lept_pred_SB_MC[NSEARCH_BINS] = {0}, nevents_lept_pred_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_lept_exp_SB_MC[NSEARCH_BINS] = {0}, nevents_lept_exp_SB_Normalized[NSEARCH_BINS] = {0};
  double nevents_lept_exp_SB_MC_isotrk[NSEARCH_BINS] = {0}, nevents_lept_exp_SB_Normalized_isotrk[NSEARCH_BINS] = {0};

  //di-lepton correction
  double nevents_single_mus = 0, nevents_di_mus = 0;
  double nevents_single_els = 0, nevents_di_els = 0;
  
  //flow number table
  double nevents_exp_all_mus = 0, nevents_exp_all_els = 0;
  double nevents_exp_acc_mus = 0, nevents_exp_acc_els = 0;
  double nevents_exp_id_mus = 0, nevents_exp_id_els = 0;
  double nevents_exp_iso_mus = 0, nevents_exp_iso_els = 0;
  double nevents_exp_all_mus_err = 0, nevents_exp_all_els_err = 0;
  double nevents_exp_acc_mus_err = 0, nevents_exp_acc_els_err = 0;
  double nevents_exp_id_mus_err = 0, nevents_exp_id_els_err = 0;
  double nevents_exp_iso_mus_err = 0, nevents_exp_iso_els_err = 0;

  double nevents_pred_all_mus = 0, nevents_pred_all_els = 0;
  double nevents_pred_acc_mus = 0, nevents_pred_acc_els = 0;
  double nevents_pred_id_mus = 0, nevents_pred_id_els = 0;
  double nevents_pred_iso_mus = 0, nevents_pred_iso_els = 0;
  double nevents_pred_all_mus_err = 0, nevents_pred_all_els_err = 0;
  double nevents_pred_acc_mus_err = 0, nevents_pred_acc_els_err = 0;
  double nevents_pred_id_mus_err = 0, nevents_pred_id_els_err = 0;
  double nevents_pred_iso_mus_err = 0, nevents_pred_iso_els_err = 0;

  //di lepton correction factor
  double corrfactor_di_mus = 0;
  double corrfactor_di_els = 0;
  double corrfactor_di_mus_err = 0;
  double corrfactor_di_els_err = 0;

  TFile *Effs2dPlots = new TFile("Effs2dPlots.root", "recreate");
  //double ptbins[9]={5.0,10.0,20.0,30.0,40.0,50.0,70.0,100.0,120.0};
  //double acbins[9]={0.0,5.0,10.0,20.0,40.0,60.0,80.0,100.0,120.0};
  //TH2D *mus_recoeffs2d  = new TH2D("mus_recoeffs","Muon RecoEffs",8,ptbins,8,acbins);
  //TH2D *mus_isoeffs2d  = new TH2D("mus_isoeffs","Muon IsoEffs",8,ptbins,8,acbins);
  //TH2D *els_recoeffs2d  = new TH2D("els_recoeffs","Electron RecoEffs",8,ptbins,8,acbins);
  //TH2D *els_isoeffs2d  = new TH2D("els_isoeffs","Electron IsoEffs",8,ptbins,8,acbins);

  TH2D *mus_recoeffs2d  = new TH2D("mus_recoeffs","Muon RecoEffs",PT_BINS,0,PT_BINS,AC_BINS,0,AC_BINS);
  TH2D *mus_isoeffs2d  = new TH2D("mus_isoeffs","Muon IsoEffs",PT_BINS,0,PT_BINS,AC_BINS,0,AC_BINS);
  TH2D *els_recoeffs2d  = new TH2D("els_recoeffs","Electron RecoEffs",PT_BINS,0,PT_BINS,AC_BINS,0,AC_BINS);
  TH2D *els_isoeffs2d  = new TH2D("els_isoeffs","Electron IsoEffs",PT_BINS,0,PT_BINS,AC_BINS,0,AC_BINS);

  void NumberstoEffs();
  void EffsPlotsGen();
  void EffstoWeights();
  void GetDiLeptonFactor();
  void NormalizeFlowNumber();
  void printSearchBin(BaseHistgram& myBaseHistgram);

 private:
  //define the variables we needed for normalization
  //double Nevents = 25446993;
  //double XSec = 806.1;
  //double Lumi = 10000;
  //double scale = XSec*Lumi/Nevents;
  double scale = 1;  

  double get_stat_Error(
                        double a,
                        double an
                       );
  
  double get_sys_Error(
                       double r,
                       double p
                      );
};


double AccRecoIsoEffs::get_stat_Error(
                                      double a,
                                      double an
                                     )
{
  double n;
  n = an - a;

  double err;
  err = 1000;

  double alpha;
  alpha = 1-0.6827;

  if( a>=0 && n>=0 )
  {
    err = std::sqrt(n/(a+n)/(a+n)*n/(a+n)/(a+n)*ROOT::Math::gamma_quantile_c(alpha/2,a+1,1)+a/(a+n)/(a+n)*a/(a+n)/(a+n)*ROOT::Math::gamma_quantile_c(alpha/2,n+1,1));
    return err;
  }
  else
  {
    return -1;
  }
}

double AccRecoIsoEffs::get_sys_Error(
                                     double r,
                                     double p
                                    )
{
  double err;
  err = 1000;

  err = r - (1-(1-r)*(1+p));

  if(err < 0)
  {
    return -1;
  }
  return err;
}

//############finish the definition of class AccRecoEffs######################

class BaseHistgram
{
 public:
  void BookHistgram(const char *);

  TFile *oFile;
  TH1D *h_b_all_MET;
  TH1D *h_b_baseline_nMuons, *h_b_baseline_njets, *h_b_baseline_nbjetsCSVM, *h_b_baseline_MET, *h_b_baseline_jetpt2, *h_b_baseline_jetpt4, *h_b_baseline_jet1_met_phi_diff, *h_b_baseline_jet2_met_phi_diff, *h_b_baseline_jet3_met_phi_diff;
  TH1D *h_b_acc_njets, *h_b_acc_nbjetsCSVM, *h_b_acc_MET, *h_b_acc_jetpt2, *h_b_acc_jetpt4, *h_b_acc_jet1_met_phi_diff, *h_b_acc_jet2_met_phi_diff, *h_b_acc_jet3_met_phi_diff;
  TH1D *h_b_reco_nMuons, *h_b_reco_njets, *h_b_reco_nbjetsCSVM, *h_b_reco_MET, *h_b_reco_jetpt2, *h_b_reco_jetpt4, *h_b_reco_jet1_met_phi_diff, *h_b_reco_jet2_met_phi_diff, *h_b_reco_jet3_met_phi_diff;
  TH1D *h_b_deltaR_mus, *h_b_deltaR_els;
  TH1D *h_b_activity_mus, *h_b_activity_els;
  TH1D *h_b_njets_mus, *h_b_njets_els;
  TH1D *h_b_jet_pt;

  TH1D *h_b_deltaR_genup_mus, *h_b_deltaR_genup_els;
  TH2D *h_b_deltaR_pt_mus, *h_b_deltaR_pt_els;
  TH2D *h_b_njets30_pt_mus, *h_b_njets30_pt_els, *h_b_njets30_eta_mus, *h_b_njets30_eta_els;
  TH1D *h_b_njets30_4_pt_mus, *h_b_njets30_5_pt_mus, *h_b_njets30_6_pt_mus, *h_b_njets30_7_pt_mus, *h_b_njets30_8_pt_mus, *h_b_njets30_9_pt_mus;
  TH1D *h_b_njets30_4_eta_mus, *h_b_njets30_5_eta_mus, *h_b_njets30_6_eta_mus, *h_b_njets30_7_eta_mus, *h_b_njets30_8_eta_mus, *h_b_njets30_9_eta_mus;
  TH1D *h_b_njets30_4_pt_els, *h_b_njets30_5_pt_els, *h_b_njets30_6_pt_els, *h_b_njets30_7_pt_els, *h_b_njets30_8_pt_els, *h_b_njets30_9_pt_els;
  TH1D *h_b_njets30_4_eta_els, *h_b_njets30_5_eta_els, *h_b_njets30_6_eta_els, *h_b_njets30_7_eta_els, *h_b_njets30_8_eta_els, *h_b_njets30_9_eta_els;
  TH1D *h_b_njets30_4_ht_mus, *h_b_njets30_5_ht_mus, *h_b_njets30_6_ht_mus, *h_b_njets30_7_ht_mus, *h_b_njets30_8_ht_mus, *h_b_njets30_9_ht_mus;

  TH1D *h_mtw_mus;

  //closure plots definition
  TH1D *h_pred_mu_iso_met, *h_pred_mu_iso_njets, *h_pred_mu_iso_mt2, *h_pred_mu_iso_ht, *h_pred_mu_iso_mht, *h_pred_mu_iso_ntopjets;
  TH1D *h_pred_mu_id_met, *h_pred_mu_id_njets, *h_pred_mu_id_mt2, *h_pred_mu_id_ht, *h_pred_mu_id_mht, *h_pred_mu_id_ntopjets;
  TH1D *h_pred_mu_acc_met, *h_pred_mu_acc_njets, *h_pred_mu_acc_mt2, *h_pred_mu_acc_ht, *h_pred_mu_acc_mht, *h_pred_mu_acc_ntopjets;
  TH1D *h_pred_mu_all_met, *h_pred_mu_all_njets, *h_pred_mu_all_mt2, *h_pred_mu_all_ht, *h_pred_mu_all_mht, *h_pred_mu_all_ntopjets;

  TH1D *h_exp_mu_iso_met, *h_exp_mu_iso_njets, *h_exp_mu_iso_mt2, *h_exp_mu_iso_ht, *h_exp_mu_iso_mht, *h_exp_mu_iso_ntopjets;
  TH1D *h_exp_mu_id_met, *h_exp_mu_id_njets, *h_exp_mu_id_mt2, *h_exp_mu_id_ht, *h_exp_mu_id_mht, *h_exp_mu_id_ntopjets;
  TH1D *h_exp_mu_acc_met, *h_exp_mu_acc_njets, *h_exp_mu_acc_mt2, *h_exp_mu_acc_ht, *h_exp_mu_acc_mht, *h_exp_mu_acc_ntopjets;
  TH1D *h_exp_mu_all_met, *h_exp_mu_all_njets, *h_exp_mu_all_mt2, *h_exp_mu_all_ht, *h_exp_mu_all_mht, *h_exp_mu_all_ntopjets;

  TH1D *h_exp_musingle_all_met, *h_exp_musingle_all_njets, *h_exp_musingle_all_mt2, *h_exp_musingle_all_ht, *h_exp_musingle_all_mht, *h_exp_musingle_all_ntopjets;

  TH1D *h_pred_el_iso_met, *h_pred_el_iso_njets, *h_pred_el_iso_mt2, *h_pred_el_iso_ht, *h_pred_el_iso_mht, *h_pred_el_iso_ntopjets;
  TH1D *h_pred_el_id_met, *h_pred_el_id_njets, *h_pred_el_id_mt2, *h_pred_el_id_ht, *h_pred_el_id_mht, *h_pred_el_id_ntopjets;
  TH1D *h_pred_el_acc_met, *h_pred_el_acc_njets, *h_pred_el_acc_mt2, *h_pred_el_acc_ht, *h_pred_el_acc_mht, *h_pred_el_acc_ntopjets;
  TH1D *h_pred_el_all_met, *h_pred_el_all_njets, *h_pred_el_all_mt2, *h_pred_el_all_ht, *h_pred_el_all_mht, *h_pred_el_all_ntopjets;

  TH1D *h_exp_el_iso_met, *h_exp_el_iso_njets, *h_exp_el_iso_mt2, *h_exp_el_iso_ht, *h_exp_el_iso_mht, *h_exp_el_iso_ntopjets;
  TH1D *h_exp_el_id_met, *h_exp_el_id_njets, *h_exp_el_id_mt2, *h_exp_el_id_ht, *h_exp_el_id_mht, *h_exp_el_id_ntopjets;
  TH1D *h_exp_el_acc_met, *h_exp_el_acc_njets, *h_exp_el_acc_mt2, *h_exp_el_acc_ht, *h_exp_el_acc_mht, *h_exp_el_acc_ntopjets;
  TH1D *h_exp_el_all_met, *h_exp_el_all_njets, *h_exp_el_all_mt2, *h_exp_el_all_ht, *h_exp_el_all_mht, *h_exp_el_all_ntopjets;

  TH1D *h_pred_lept_all_met, *h_pred_lept_all_njets, *h_pred_lept_all_mt2, *h_pred_lept_all_ht, *h_pred_lept_all_mht, *h_pred_lept_all_ntopjets;
  TH1D *h_exp_lept_all_met, *h_exp_lept_all_njets, *h_exp_lept_all_mt2, *h_exp_lept_all_ht, *h_exp_lept_all_mht, *h_exp_lept_all_ntopjets;

  TH1D *h_exp_elsingle_all_met, *h_exp_elsingle_all_njets, *h_exp_elsingle_all_mt2, *h_exp_elsingle_all_ht, *h_exp_elsingle_all_mht, *h_exp_elsingle_all_ntopjets;

  //closure for search bin
  TH1D *h_exp_mu_sb, *h_pred_mu_sb, *h_exp_el_sb, *h_pred_el_sb, *h_exp_lept_sb, *h_pred_lept_sb, *h_exp_lept_sb_isotrk, *h_pred_lept_sb_isotrk;
};

void BaseHistgram::BookHistgram(const char *outFileName)
{
  oFile = new TFile(outFileName, "recreate");

  h_b_all_MET = new TH1D("h_b_all_MET","",1000,0,1000);

  h_b_baseline_nMuons = new TH1D("h_b_baseline_nMuons","",10,0,10);
  h_b_baseline_njets = new TH1D("h_b_baseline_njets","",10,0,10);
  h_b_baseline_nbjetsCSVM = new TH1D("h_b_baseline_nbjetsCSVM","",10,0,10);
  h_b_baseline_MET = new TH1D("h_b_baseline_MET","",1000,0,1000);
  h_b_baseline_jetpt4 = new TH1D("h_b_baseline_jetpt4","",1000,0,1000);
  h_b_baseline_jetpt2 = new TH1D("h_b_baseline_jetpt2","",1000,0,1000);
  h_b_baseline_jet1_met_phi_diff = new TH1D("h_b_baseline_jet1_met_phi_diff","",1000,-5,5);
  h_b_baseline_jet2_met_phi_diff = new TH1D("h_b_baseline_jet2_met_phi_diff","",1000,-5,5);
  h_b_baseline_jet3_met_phi_diff = new TH1D("h_b_baseline_jet3_met_phi_diff","",1000,-5,5);

  h_b_acc_njets = new TH1D("h_b_acc_njets","",10,0,10);
  h_b_acc_nbjetsCSVM = new TH1D("h_b_acc_nbjetsCSVM","",10,0,10);
  h_b_acc_MET = new TH1D("h_b_acc_MET","",1000,0,1000);
  h_b_acc_jetpt4 = new TH1D("h_b_acc_jetpt4","",1000,0,1000);
  h_b_acc_jetpt2 = new TH1D("h_b_acc_jetpt2","",1000,0,1000);
  h_b_acc_jet1_met_phi_diff = new TH1D("h_b_acc_jet1_met_phi_diff","",1000,-5,5);
  h_b_acc_jet2_met_phi_diff = new TH1D("h_b_acc_jet2_met_phi_diff","",1000,-5,5);
  h_b_acc_jet3_met_phi_diff = new TH1D("h_b_acc_jet3_met_phi_diff","",1000,-5,5);

  h_b_reco_nMuons = new TH1D("h_b_reco_nMuons","",10,0,10);
  h_b_reco_njets = new TH1D("h_b_reco_njets","",10,0,10);
  h_b_reco_nbjetsCSVM = new TH1D("h_b_reco_nbjetsCSVM","",10,0,10);
  h_b_reco_MET = new TH1D("h_b_reco_MET","",1000,0,1000);
  h_b_reco_jetpt4 = new TH1D("h_b_reco_jetpt4","",1000,0,1000);
  h_b_reco_jetpt2 = new TH1D("h_b_reco_jetpt2","",1000,0,1000);
  h_b_reco_jet1_met_phi_diff = new TH1D("h_b_reco_jet1_met_phi_diff","",1000,-5,5);
  h_b_reco_jet2_met_phi_diff = new TH1D("h_b_reco_jet2_met_phi_diff","",1000,-5,5);
  h_b_reco_jet3_met_phi_diff = new TH1D("h_b_reco_jet3_met_phi_diff","",1000,-5,5);

  h_b_deltaR_mus = new TH1D("h_b_deltaR_mus","",1000,0,0.5);
  h_b_deltaR_els = new TH1D("h_b_deltaR_els","",1000,0,0.5);
  
  h_b_deltaR_genup_mus = new TH1D("h_b_deltaR_genup_mus","",50,0,5);
  h_b_deltaR_genup_els = new TH1D("h_b_deltaR_genup_els","",50,0,5);

  h_b_deltaR_pt_mus = new TH2D("h_b_deltaR_pt_mus","",100,0,1,100,0,500);
  h_b_deltaR_pt_els = new TH2D("h_b_deltaR_pt_els","",100,0,1,100,0,500);

  h_b_njets30_pt_mus = new TH2D("h_b_njets30_pt_mus","",15,0,15,20,0,200);
  h_b_njets30_pt_els = new TH2D("h_b_njets30_pt_els","",15,0,15,20,0,200);
  h_b_njets30_eta_mus = new TH2D("h_b_njets30_eta_mus","",15,0,15,12,-3,3);
  h_b_njets30_eta_els = new TH2D("h_b_njets30_eta_els","",15,0,15,12,-3,3);

  h_b_njets30_4_pt_mus = new TH1D("h_b_njets30_4_pt_mus","",200,0,200);
  h_b_njets30_5_pt_mus = new TH1D("h_b_njets30_5_pt_mus","",200,0,200);
  h_b_njets30_6_pt_mus = new TH1D("h_b_njets30_6_pt_mus","",200,0,200);
  h_b_njets30_7_pt_mus = new TH1D("h_b_njets30_7_pt_mus","",200,0,200);
  h_b_njets30_8_pt_mus = new TH1D("h_b_njets30_8_pt_mus","",200,0,200);
  h_b_njets30_9_pt_mus = new TH1D("h_b_njets30_9_pt_mus","",200,0,200);

  h_b_njets30_4_ht_mus = new TH1D("h_b_njets30_4_ht_mus","",200,0,2000);
  h_b_njets30_5_ht_mus = new TH1D("h_b_njets30_5_ht_mus","",200,0,2000);
  h_b_njets30_6_ht_mus = new TH1D("h_b_njets30_6_ht_mus","",200,0,2000);
  h_b_njets30_7_ht_mus = new TH1D("h_b_njets30_7_ht_mus","",200,0,2000);
  h_b_njets30_8_ht_mus = new TH1D("h_b_njets30_8_ht_mus","",200,0,2000);
  h_b_njets30_9_ht_mus = new TH1D("h_b_njets30_9_ht_mus","",200,0,2000);

  h_b_njets30_4_eta_mus = new TH1D("h_b_njets30_4_eta_mus","",60,-3,3);
  h_b_njets30_5_eta_mus = new TH1D("h_b_njets30_5_eta_mus","",60,-3,3);
  h_b_njets30_6_eta_mus = new TH1D("h_b_njets30_6_eta_mus","",60,-3,3);
  h_b_njets30_7_eta_mus = new TH1D("h_b_njets30_7_eta_mus","",60,-3,3);
  h_b_njets30_8_eta_mus = new TH1D("h_b_njets30_8_eta_mus","",60,-3,3);
  h_b_njets30_9_eta_mus = new TH1D("h_b_njets30_9_eta_mus","",60,-3,3);

  h_b_njets30_4_pt_els = new TH1D("h_b_njets30_4_pt_els","",200,0,200);
  h_b_njets30_5_pt_els = new TH1D("h_b_njets30_5_pt_els","",200,0,200);
  h_b_njets30_6_pt_els = new TH1D("h_b_njets30_6_pt_els","",200,0,200);
  h_b_njets30_7_pt_els = new TH1D("h_b_njets30_7_pt_els","",200,0,200);
  h_b_njets30_8_pt_els = new TH1D("h_b_njets30_8_pt_els","",200,0,200);
  h_b_njets30_9_pt_els = new TH1D("h_b_njets30_9_pt_els","",200,0,200);

  h_b_njets30_4_eta_els = new TH1D("h_b_njets30_4_eta_els","",60,-3,3);
  h_b_njets30_5_eta_els = new TH1D("h_b_njets30_5_eta_els","",60,-3,3);
  h_b_njets30_6_eta_els = new TH1D("h_b_njets30_6_eta_els","",60,-3,3);
  h_b_njets30_7_eta_els = new TH1D("h_b_njets30_7_eta_els","",60,-3,3);
  h_b_njets30_8_eta_els = new TH1D("h_b_njets30_8_eta_els","",60,-3,3);
  h_b_njets30_9_eta_els = new TH1D("h_b_njets30_9_eta_els","",60,-3,3);

  h_mtw_mus = new TH1D("h_mtw_mus","",200,0,200);

  h_b_activity_mus = new TH1D("h_b_activity_mus","",1000,0,200);
  h_b_activity_els = new TH1D("h_b_activity_els","",1000,0,200);

  h_b_njets_mus = new TH1D("h_b_njets_mus","",40,0,40);
  h_b_njets_els = new TH1D("h_b_njets_els","",40,0,40);

  h_b_jet_pt = new TH1D("h_b_jet_pt","",1000,0,200);

  //start closure plots
  h_pred_mu_iso_met = new TH1D("h_pred_mu_iso_met","",100,0,1000);
  h_pred_mu_iso_njets = new TH1D("h_pred_mu_iso_njets","",20,0,20);
  h_pred_mu_iso_mt2 = new TH1D("h_pred_mu_iso_mt2","",100,0,1000);
  h_pred_mu_iso_ht = new TH1D("h_pred_mu_iso_ht","",300,0,3000);
  h_pred_mu_iso_mht = new TH1D("h_pred_mu_iso_mht","",100,0,1000);
  h_pred_mu_iso_ntopjets = new TH1D("h_pred_mu_iso_ntopjets","",20,0,20);

  h_pred_mu_id_met = new TH1D("h_pred_mu_id_met","",100,0,1000);
  h_pred_mu_id_njets = new TH1D("h_pred_mu_id_njets","",20,0,20);
  h_pred_mu_id_mt2 = new TH1D("h_pred_mu_id_mt2","",100,0,1000);
  h_pred_mu_id_ht = new TH1D("h_pred_mu_id_ht","",300,0,3000);
  h_pred_mu_id_mht = new TH1D("h_pred_mu_id_mht","",100,0,1000);
  h_pred_mu_id_ntopjets = new TH1D("h_pred_mu_id_ntopjets","",20,0,20);

  h_pred_mu_acc_met = new TH1D("h_pred_mu_acc_met","",100,0,1000);
  h_pred_mu_acc_njets = new TH1D("h_pred_mu_acc_njets","",20,0,20);
  h_pred_mu_acc_mt2 = new TH1D("h_pred_mu_acc_mt2","",100,0,1000);
  h_pred_mu_acc_ht = new TH1D("h_pred_mu_acc_ht","",300,0,3000);
  h_pred_mu_acc_mht = new TH1D("h_pred_mu_acc_mht","",100,0,1000);
  h_pred_mu_acc_ntopjets = new TH1D("h_pred_mu_acc_ntopjets","",20,0,20);

  h_pred_mu_all_met = new TH1D("h_pred_mu_all_met","",100,0,1000);
  h_pred_mu_all_njets = new TH1D("h_pred_mu_all_njets","",20,0,20);
  h_pred_mu_all_mt2 = new TH1D("h_pred_mu_all_mt2","",100,0,1000);
  h_pred_mu_all_ht = new TH1D("h_pred_mu_all_ht","",300,0,3000);
  h_pred_mu_all_mht = new TH1D("h_pred_mu_all_mht","",100,0,1000);
  h_pred_mu_all_ntopjets = new TH1D("h_pred_mu_all_ntopjets","",20,0,20);

  h_exp_mu_iso_met = new TH1D("h_exp_mu_iso_met","",100,0,1000);
  h_exp_mu_iso_njets = new TH1D("h_exp_mu_iso_njets","",20,0,20);
  h_exp_mu_iso_mt2 = new TH1D("h_exp_mu_iso_mt2","",100,0,1000);
  h_exp_mu_iso_ht = new TH1D("h_exp_mu_iso_ht","",300,0,3000);
  h_exp_mu_iso_mht = new TH1D("h_exp_mu_iso_mht","",100,0,1000);
  h_exp_mu_iso_ntopjets = new TH1D("h_exp_mu_iso_ntopjets","",20,0,20);

  h_exp_mu_id_met = new TH1D("h_exp_mu_id_met","",100,0,1000);
  h_exp_mu_id_njets = new TH1D("h_exp_mu_id_njets","",20,0,20);
  h_exp_mu_id_mt2 = new TH1D("h_exp_mu_id_mt2","",100,0,1000);
  h_exp_mu_id_ht = new TH1D("h_exp_mu_id_ht","",300,0,3000);
  h_exp_mu_id_mht = new TH1D("h_exp_mu_id_mht","",100,0,1000);
  h_exp_mu_id_ntopjets = new TH1D("h_exp_mu_id_ntopjets","",20,0,20);

  h_exp_mu_acc_met = new TH1D("h_exp_mu_acc_met","",100,0,1000);
  h_exp_mu_acc_njets = new TH1D("h_exp_mu_acc_njets","",20,0,20);
  h_exp_mu_acc_mt2 = new TH1D("h_exp_mu_acc_mt2","",100,0,1000);
  h_exp_mu_acc_ht = new TH1D("h_exp_mu_acc_ht","",300,0,3000);
  h_exp_mu_acc_mht = new TH1D("h_exp_mu_acc_mht","",100,0,1000);
  h_exp_mu_acc_ntopjets = new TH1D("h_exp_mu_acc_ntopjets","",20,0,20);

  h_exp_mu_all_met = new TH1D("h_exp_mu_all_met","",100,0,1000);
  h_exp_mu_all_njets = new TH1D("h_exp_mu_all_njets","",20,0,20);
  h_exp_mu_all_mt2 = new TH1D("h_exp_mu_all_mt2","",100,0,1000);
  h_exp_mu_all_ht = new TH1D("h_exp_mu_all_ht","",300,0,3000);
  h_exp_mu_all_mht = new TH1D("h_exp_mu_all_mht","",100,0,1000);
  h_exp_mu_all_ntopjets = new TH1D("h_exp_mu_all_ntopjets","",20,0,20);

  h_exp_lept_all_met = new TH1D("h_exp_lept_all_met","",100,0,1000);
  h_exp_lept_all_njets = new TH1D("h_exp_lept_all_njets","",20,0,20);
  h_exp_lept_all_mt2 = new TH1D("h_exp_lept_all_mt2","",100,0,1000);
  h_exp_lept_all_ht = new TH1D("h_exp_lept_all_ht","",300,0,3000);
  h_exp_lept_all_mht = new TH1D("h_exp_lept_all_mht","",100,0,1000);
  h_exp_lept_all_ntopjets = new TH1D("h_exp_lept_all_ntopjets","",20,0,20);

  h_exp_musingle_all_met = new TH1D("h_exp_musingle_all_met","",100,0,1000);
  h_exp_musingle_all_njets = new TH1D("h_exp_musingle_all_njets","",20,0,20);
  h_exp_musingle_all_mt2 = new TH1D("h_exp_musingle_all_mt2","",100,0,1000);
  h_exp_musingle_all_ht = new TH1D("h_exp_musingle_all_ht","",300,0,3000);
  h_exp_musingle_all_mht = new TH1D("h_exp_musingle_all_mht","",100,0,1000);
  h_exp_musingle_all_ntopjets = new TH1D("h_exp_musingle_all_ntopjets","",20,0,20);

  h_pred_el_iso_met = new TH1D("h_pred_el_iso_met","",100,0,1000);
  h_pred_el_iso_njets = new TH1D("h_pred_el_iso_njets","",20,0,20);
  h_pred_el_iso_mt2 = new TH1D("h_pred_el_iso_mt2","",100,0,1000);
  h_pred_el_iso_ht = new TH1D("h_pred_el_iso_ht","",300,0,3000);
  h_pred_el_iso_mht = new TH1D("h_pred_el_iso_mht","",100,0,1000);
  h_pred_el_iso_ntopjets = new TH1D("h_pred_el_iso_ntopjets","",20,0,20);

  h_pred_el_id_met = new TH1D("h_pred_el_id_met","",100,0,1000);
  h_pred_el_id_njets = new TH1D("h_pred_el_id_njets","",20,0,20);
  h_pred_el_id_mt2 = new TH1D("h_pred_el_id_mt2","",100,0,1000);
  h_pred_el_id_ht = new TH1D("h_pred_el_id_ht","",300,0,3000);
  h_pred_el_id_mht = new TH1D("h_pred_el_id_mht","",100,0,1000);
  h_pred_el_id_ntopjets = new TH1D("h_pred_el_id_ntopjets","",20,0,20);

  h_pred_el_acc_met = new TH1D("h_pred_el_acc_met","",100,0,1000);
  h_pred_el_acc_njets = new TH1D("h_pred_el_acc_njets","",20,0,20);
  h_pred_el_acc_mt2 = new TH1D("h_pred_el_acc_mt2","",100,0,1000);
  h_pred_el_acc_ht = new TH1D("h_pred_el_acc_ht","",300,0,3000);
  h_pred_el_acc_mht = new TH1D("h_pred_el_acc_mht","",100,0,1000);
  h_pred_el_acc_ntopjets = new TH1D("h_pred_el_acc_ntopjets","",20,0,20);

  h_pred_el_all_met = new TH1D("h_pred_el_all_met","",100,0,1000);
  h_pred_el_all_njets = new TH1D("h_pred_el_all_njets","",20,0,20);
  h_pred_el_all_mt2 = new TH1D("h_pred_el_all_mt2","",100,0,1000);
  h_pred_el_all_ht = new TH1D("h_pred_el_all_ht","",300,0,3000);
  h_pred_el_all_mht = new TH1D("h_pred_el_all_mht","",100,0,1000);
  h_pred_el_all_ntopjets = new TH1D("h_pred_el_all_ntopjets","",20,0,20);

  h_pred_lept_all_met = new TH1D("h_pred_lept_all_met","",100,0,1000);
  h_pred_lept_all_njets = new TH1D("h_pred_lept_all_njets","",20,0,20);
  h_pred_lept_all_mt2 = new TH1D("h_pred_lept_all_mt2","",100,0,1000);
  h_pred_lept_all_ht = new TH1D("h_pred_lept_all_ht","",300,0,3000);
  h_pred_lept_all_mht = new TH1D("h_pred_lept_all_mht","",100,0,1000);
  h_pred_lept_all_ntopjets = new TH1D("h_pred_lept_all_ntopjets","",20,0,20);

  h_exp_el_iso_met = new TH1D("h_exp_el_iso_met","",100,0,1000);
  h_exp_el_iso_njets = new TH1D("h_exp_el_iso_njets","",20,0,20);
  h_exp_el_iso_mt2 = new TH1D("h_exp_el_iso_mt2","",100,0,1000);
  h_exp_el_iso_ht = new TH1D("h_exp_el_iso_ht","",300,0,3000);
  h_exp_el_iso_mht = new TH1D("h_exp_el_iso_mht","",100,0,1000);
  h_exp_el_iso_ntopjets = new TH1D("h_exp_el_iso_ntopjets","",20,0,20);

  h_exp_el_id_met = new TH1D("h_exp_el_id_met","",100,0,1000);
  h_exp_el_id_njets = new TH1D("h_exp_el_id_njets","",20,0,20);
  h_exp_el_id_mt2 = new TH1D("h_exp_el_id_mt2","",100,0,1000);
  h_exp_el_id_ht = new TH1D("h_exp_el_id_ht","",300,0,3000);
  h_exp_el_id_mht = new TH1D("h_exp_el_id_mht","",100,0,1000);
  h_exp_el_id_ntopjets = new TH1D("h_exp_el_id_ntopjets","",20,0,20);

  h_exp_el_acc_met = new TH1D("h_exp_el_acc_met","",100,0,1000);
  h_exp_el_acc_njets = new TH1D("h_exp_el_acc_njets","",20,0,20);
  h_exp_el_acc_mt2 = new TH1D("h_exp_el_acc_mt2","",100,0,1000);
  h_exp_el_acc_ht = new TH1D("h_exp_el_acc_ht","",300,0,3000);
  h_exp_el_acc_mht = new TH1D("h_exp_el_acc_mht","",100,0,1000);
  h_exp_el_acc_ntopjets = new TH1D("h_exp_el_acc_ntopjets","",20,0,20);

  h_exp_el_all_met = new TH1D("h_exp_el_all_met","",100,0,1000);
  h_exp_el_all_njets = new TH1D("h_exp_el_all_njets","",20,0,20);
  h_exp_el_all_mt2 = new TH1D("h_exp_el_all_mt2","",100,0,1000);
  h_exp_el_all_ht = new TH1D("h_exp_el_all_ht","",300,0,3000);
  h_exp_el_all_mht = new TH1D("h_exp_el_all_mht","",100,0,1000);
  h_exp_el_all_ntopjets = new TH1D("h_exp_el_all_ntopjets","",20,0,20);

  h_exp_elsingle_all_met = new TH1D("h_exp_elsingle_all_met","",100,0,1000);
  h_exp_elsingle_all_njets = new TH1D("h_exp_elsingle_all_njets","",20,0,20);
  h_exp_elsingle_all_mt2 = new TH1D("h_exp_elsingle_all_mt2","",100,0,1000);
  h_exp_elsingle_all_ht = new TH1D("h_exp_elsingle_all_ht","",300,0,3000);
  h_exp_elsingle_all_mht = new TH1D("h_exp_elsingle_all_mht","",100,0,1000);
  h_exp_elsingle_all_ntopjets = new TH1D("h_exp_elsingle_all_ntopjets","",20,0,20);

  //closure for search bin
  h_exp_mu_sb = new TH1D("h_exp_mu_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_mu_sb = new TH1D("h_pred_mu_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_exp_el_sb = new TH1D("h_exp_el_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_el_sb = new TH1D("h_pred_el_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_exp_lept_sb = new TH1D("h_exp_lept_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_exp_lept_sb_isotrk = new TH1D("h_exp_lept_isotrk","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_lept_sb = new TH1D("h_pred_lept_sb","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
  h_pred_lept_sb_isotrk = new TH1D("h_pred_lept_isotrk","",NSEARCH_BINS+1,0,NSEARCH_BINS+1);
}

//##########functions to calculate Delta_R and Delta Phi###############
double DeltaPhi(double phi1, double phi2) 
{
  double result = phi1 - phi2;
  while (result > M_PI)    result -= 2 * M_PI;
  while (result <= -M_PI)  result += 2 * M_PI;
  return result;
}

double DeltaR(double eta1, double phi1, double eta2, double phi2) 
{
  double deta = eta1 - eta2;
  double dphi = DeltaPhi(phi1, phi2);
  return std::sqrt(deta*deta + dphi*dphi);
}
