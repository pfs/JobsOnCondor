#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

//include user defined histograms and auxiliary macros
#include "Auxiliary.cpp"
#include "Histodef.cpp"

using namespace std;

#define MAX_ARRAY_SIZE 128
#define GEN_MAX_ARRAY_SIZE 1024


//void Electron_Analysis(string inputFile, string ofile);
//int main(int argc, char** argv){
//
//    string inputFile = argv[1];
//    string outputFile = argv[2];
//    Electron_Analysis(inputFile, outputFile);
//}
//
void Electron_Analysis(string inputFile, string ofile){

    TFile *fin = TFile::Open(inputFile.c_str());
    TTree *tin = static_cast<TTree*>(fin->Get("Events"));

    // Set all branches to 0
    tin->SetBranchStatus("*", 0);
    // get the pt
    Float_t Muon_pt[MAX_ARRAY_SIZE], Electron_pt[MAX_ARRAY_SIZE], Jet_pt[MAX_ARRAY_SIZE];
    tin->SetBranchStatus("Electron_pt", 1);
    tin->SetBranchAddress("Electron_pt", &Electron_pt);
    tin->SetBranchStatus("Muon_pt", 1);
    tin->SetBranchAddress("Muon_pt", &Muon_pt);
    tin->SetBranchStatus("Jet_pt", 1);
    tin->SetBranchAddress("Jet_pt", &Jet_pt);
    // get the number of muons, electrons
    UInt_t nMuon, nElectron;
    tin->SetBranchStatus("nElectron", 1);
    tin->SetBranchAddress("nElectron", &nElectron);
    tin->SetBranchStatus("nMuon", 1);
    tin->SetBranchAddress("nMuon", &nMuon);
    // get the eta
    Float_t Muon_eta[MAX_ARRAY_SIZE], Electron_eta[MAX_ARRAY_SIZE], Jet_eta[MAX_ARRAY_SIZE];
    tin->SetBranchStatus("Electron_eta", 1);
    tin->SetBranchAddress("Electron_eta", &Electron_eta);
    tin->SetBranchStatus("Muon_eta", 1);
    tin->SetBranchAddress("Muon_eta", &Muon_eta);
    tin->SetBranchStatus("Jet_eta", 1);
    tin->SetBranchAddress("Jet_eta", &Jet_eta);
    // get the phi
    Float_t Muon_phi[MAX_ARRAY_SIZE], Electron_phi[MAX_ARRAY_SIZE], Jet_phi[MAX_ARRAY_SIZE];
    tin->SetBranchStatus("Electron_phi", 1);
    tin->SetBranchAddress("Electron_phi", &Electron_phi);
    tin->SetBranchStatus("Muon_phi", 1);
    tin->SetBranchAddress("Muon_phi", &Muon_phi);
    tin->SetBranchStatus("Jet_phi", 1);
    tin->SetBranchAddress("Jet_phi", &Jet_phi);
    // get the mass
    Float_t Muon_mass[MAX_ARRAY_SIZE], Electron_mass[MAX_ARRAY_SIZE], Jet_mass[MAX_ARRAY_SIZE];
    tin->SetBranchStatus("Electron_mass", 1);
    tin->SetBranchAddress("Electron_mass", &Electron_mass);
    tin->SetBranchStatus("Muon_mass", 1);
    tin->SetBranchAddress("Muon_mass", &Muon_mass);
    tin->SetBranchStatus("Jet_mass", 1);
    tin->SetBranchAddress("Jet_mass", &Jet_mass);

    // get gen quantities
    Int_t Muon_genPartIdx[MAX_ARRAY_SIZE], Electron_genPartIdx[MAX_ARRAY_SIZE];
    Int_t GenPart_pdgId[GEN_MAX_ARRAY_SIZE], GenPart_genPartIdxMother[GEN_MAX_ARRAY_SIZE]; //These last guys are actually huge, better be careful!
    UChar_t Muon_genPartFlav[MAX_ARRAY_SIZE], Electron_genPartFlav[MAX_ARRAY_SIZE];
    UInt_t nGenPart;
    tin->SetBranchStatus("Electron_genPartIdx", 1);
    tin->SetBranchStatus("Electron_genPartFlav", 1);
    tin->SetBranchStatus("Muon_genPartIdx", 1);
    tin->SetBranchStatus("Muon_genPartFlav", 1);
    tin->SetBranchStatus("GenPart_pdgId", 1);
    tin->SetBranchStatus("GenPart_genPartIdxMother",1);
    tin->SetBranchStatus("nGenPart", 1);
    tin->SetBranchAddress("nGenPart", &nGenPart);
    tin->SetBranchAddress("Electron_genPartIdx", &Electron_genPartIdx);
    tin->SetBranchAddress("Electron_genPartFlav", &Electron_genPartFlav);
    tin->SetBranchAddress("Muon_genPartIdx", &Muon_genPartIdx);
    tin->SetBranchAddress("Muon_genPartFlav", &Muon_genPartFlav);
    tin->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
    tin->SetBranchAddress("GenPart_genPartIdxMother",&GenPart_genPartIdxMother);

    // collect the trigger information
    Bool_t HLT_IsoMu27, HLT_Ele35_WPTight_Gsf; 
    tin->SetBranchStatus("HLT_IsoMu27", 1);
    tin->SetBranchStatus("HLT_Ele35_WPTight_Gsf", 1);
    tin->SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
    tin->SetBranchAddress("HLT_Ele35_WPTight_Gsf", &HLT_Ele35_WPTight_Gsf);

    // collect the triggger Ids
    Int_t Muon_charge[MAX_ARRAY_SIZE], Electron_charge[MAX_ARRAY_SIZE];
    Bool_t Electron_mvaFall17V2Iso_WP90[MAX_ARRAY_SIZE],Muon_triggerIdLoose[MAX_ARRAY_SIZE],Muon_tightId[MAX_ARRAY_SIZE];
    Float_t Muon_pfRelIso04_all[MAX_ARRAY_SIZE];
    tin->SetBranchStatus("Muon_tightId", 1);
    tin->SetBranchStatus("Muon_charge", 1);
    tin->SetBranchStatus("Muon_triggerIdLoose", 1);
    tin->SetBranchStatus("Muon_pfRelIso04_all", 1);
    tin->SetBranchStatus("Electron_charge", 1);
    tin->SetBranchStatus("Electron_mvaFall17V2Iso_WP90", 1);
    tin->SetBranchAddress("Electron_mvaFall17V2Iso_WP90", &Electron_mvaFall17V2Iso_WP90);
    tin->SetBranchAddress("Muon_tightId", &Muon_tightId);
    tin->SetBranchAddress("Muon_charge", &Muon_charge);
    tin->SetBranchAddress("Muon_triggerIdLoose", &Muon_triggerIdLoose);
    tin->SetBranchAddress("Muon_pfRelIso04_all", &Muon_pfRelIso04_all);
    tin->SetBranchAddress("Electron_charge", &Electron_charge);

    // Jet tagging , FlavB is the recomennded one, DeepB was used by Anup
    Float_t Jet_btagDeepFlavB[MAX_ARRAY_SIZE], Jet_btagDeepB[MAX_ARRAY_SIZE];
    UInt_t nJet;
    tin->SetBranchStatus("Jet_btagDeepB", 1);
    tin->SetBranchStatus("Jet_btagDeepFlavB", 1);
    tin->SetBranchStatus("nJet", 1);
    tin->SetBranchAddress("nJet", &nJet);
    tin->SetBranchAddress("Jet_btagDeepFlavB", &Jet_btagDeepFlavB);
    tin->SetBranchAddress("Jet_btagDeepB", &Jet_btagDeepB);


    // define hist for electron number
    TH1F *h_nElectron = new TH1F("h_nElectron", "h_nElectron", 10, -1, 9);

    int trigger = 0;
    const auto nEv = tin->GetEntries();
    vector <TLorentzVector*> Muon_p4(20, nullptr), Electron_p4(20, nullptr);
    for (UInt_t i = 0; i < nEv; i++){
        tin->GetEntry(i);
        if (i % 100000 == 0) cout << "Processing entry " << i << " of " << nEv << endl;
        // apply triggers

        if (!(HLT_IsoMu27 || HLT_Ele35_WPTight_Gsf)){
            trigger++;
            continue;
        };
        
        // rquire to have two electrons with pt > 30 and abs(eta) < 2.4 and tightId and to be isolated
        bool electron_selection = (Electron_pt[0]>37 && abs(Electron_eta[0])<2.4 && Electron_mvaFall17V2Iso_WP90[0]);
        electron_selection = electron_selection && (Electron_pt[1]>37. && abs(Electron_eta[1])<2.4 && Electron_mvaFall17V2Iso_WP90[1]); 
        // TODO: Electron isolation comparison with ANUP
        // check if muons are of opposite charge
        
        if(nElectron < 2) {
            h_nElectron->Fill(-1);
            continue;
        };
        bool selection = electron_selection && (Electron_charge[0] * Electron_charge[1]) < 0;
        // the tight working point is 0.71, medium 0.2783, loose 0.0490
        //Float_t jet_btag_deepFlav_wp = 0.71;
        // the wp are: (0.1355, 0.4506, 0.7738)
        Float_t jet_btag_deep_wp = 0.4506;
        // cycle through btags and check if one passes the tagging WP
        bool one_Bjet = false;
        for (size_t j = 0; j < nJet; j++){
            if (Jet_btagDeepB[j] > jet_btag_deep_wp){
                one_Bjet = true;
                break;
            }
        }
        selection = selection && (one_Bjet);
        if (!selection) continue;

        // continue if the selection is not passed

        size_t nElectron_p4 = 0;
        for (UInt_t j = 0; j < nElectron; j++)
        {
            // match the muon to the PID of the W boson (PID=24)
            // printMCTree(nGenPart, GenPart_pdgId,GenPart_genPartIdxMother, Muon_genPartIdx[j]);
            if (isFromW(nGenPart, GenPart_pdgId, GenPart_genPartIdxMother, Electron_genPartIdx[j]))
            {
                if (Electron_p4[nElectron_p4] == nullptr)
                {
                    Electron_p4[nElectron_p4] = new TLorentzVector();
                }
                // nElectron_p4++ increments by one and returns the previuos value
                // std::cout << "Electron " << nElectron_p4 << std::endl;
                Electron_p4[nElectron_p4++]->SetPtEtaPhiM(Electron_pt[j], Electron_eta[j], Electron_phi[j], Electron_mass[j]);
                h_Electron_pt->Fill(Electron_pt[j]);
                h_Electron_eta->Fill(Electron_eta[j]);
            }
        }
        h_nElectron->Fill(nElectron_p4);
        if (nElectron_p4 == 2){
            // calculate the invariant mass of the two muons
            float_t lepton_invariant_mass = (*(Electron_p4[0]) + *(Electron_p4[1])).M();
            // fill the invariant mass histogram
            h_Electron_Electron_invariant_mass->Fill(lepton_invariant_mass);
        }
    }
    //save the histograms in a new File
    TFile *fout =new TFile(ofile.c_str(),"RECREATE");
    // Write the histograms to the file
    h_Electron_pt->Write(); 
    h_Electron_eta->Write(); 
    h_nElectron->Write();
    h_Electron_Electron_invariant_mass->Write();

    fout->Write();
    fout->Close();
    
}
