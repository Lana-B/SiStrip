////////*************Code for plotting the charge spread including stack plots for different module thicknesses*******////////

void PlotFieldOff(){
    gSystem->Load("libFWCoreFWLite");
    AutoLibraryLoader::enable();
    gSystem->Load("libDataFormatsFWLite.so");
    gSystem->Load("libAnalysisDataFormatsSUSYBSMObjects.so");
    gSystem->Load("libDataFormatsVertexReco.so");
    gSystem->Load("libDataFormatsCommon.so");
    gSystem->Load("libDataFormatsHepMCCandidate.so");
    gSystem->Load("libPhysicsToolsUtilities.so");
    gStyle->SetOptStat(0);
    cout << "Loaded stuff" << endl;
    
    TFile *f0 = TFile::Open("SecondProduction/ZeroDegrees/StripVars.root");
    TFile *fMin20 = TFile::Open("SecondProduction/Minus20Degrees/StripVars.root");
    TFile *f0_FieldOff = TFile::Open("FieldOff/StripVars.root");
    //TFile *fMin20 = TFile::Open("Minus20Degrees/StripVars.root");
    
    cout<< "got files" <<endl;
    
    TTree *t0 = (TTree *)f0->Get("EventVars");
    TTree *tMin20 = (TTree *)fMin20->Get("EventVars");
    TTree *t0_FieldOff = (TTree *)f0_FieldOff->Get("EventVars");
    //TTree *tMin20 = (TTree *)fMin20->Get("EventVars");
    
    TCanvas *c2 = new TCanvas();
    TH1F* H11 = new TH1F("H11","H11",100,0,0.7e-03);
    TH1F* H22 = new TH1F("H22","H22",100,0,0.7e-03);
    TH1F* H33 = new TH1F("H33","H33",100,0,0.7e-03);
    
    t0->Project("H11","sigmaCS");
    tMin20->Project("H22","sigmaCS");
    t0_FieldOff->Project("H33","sigmaCS");
    
    H11->SetTitle("Charge Spread");
    H11->Draw();
    H22->SetLineColor(kRed);
    H22->Scale(H11->Integral()/H22->Integral());
    H22->Draw("SAME");
    H33->SetLineColor(kGreen-3);
    H33->Scale(H11->Integral()/H22->Integral());
    H33->Draw("SAME");
    
    c2->SetLogy();
    
    TLegend* leg2 = new TLegend(0.6, 0.63, .78, .80);
    leg2->SetFillColor(0);
    leg2->AddEntry(H11, "0C field on", "l");
    leg2->AddEntry(H22, "-20C", "l");
    leg2->AddEntry(H33, "0C field off", "l");
    
    leg2->Draw();
    
    c2->SaveAs("ChargeSpreadOnOff.png");
    
    ////////*********************Stack plot for the charge spread for different module thicknesses********************///////////
    
    TH1F * hMod28 = new TH1F("hMod28", "hMod28", 100, 0, 0.7e-03);
    TH1F * hMod48 = new TH1F("hMod48", "hMod28", 100, 0, 0.7e-03);
    double dSCS0, dModT0;
    t0->SetBranchAddress("sigmaCS", &dSCS0);
    t0->SetBranchAddress("modThick", &dModT0);
    hMod28->SetFillColor(kBlue-9);
    hMod48->SetFillColor(kBlue+3);
    int nEntries0 = t0->GetEntries();
    for (int i = 0; i<nEntries0; i++){
        t0->GetEntry(i);
        if(dModT0 <0.03){
            hMod28->Fill(dSCS0);
        }
        else{
            hMod48->Fill(dSCS0);
        }
    }
    hMod48->GetXaxis()->SetTitle("Charge Spread");
    
    THStack *stackmod = new THStack("stackmod", "Zero degrees");
    stackmod->Add(hMod48);
    stackmod->Add(hMod28);
    TCanvas* cStack = new TCanvas();
    TLegend* legS = new TLegend(0.6, 0.63, .86, .80);
    legS->SetFillColor(0);
    legS->AddEntry(hMod28, "modThick = 0.028" , "f");
    legS->AddEntry(hMod48, "modThick = 0.048" , "f");
    
    legS->SetTextSize(.03);
    stackmod->Draw();
    stackmod->GetHistogram()->GetXaxis()->SetTitle("Charge Spread");
    
    legS->Draw();
    cStack->SaveAs("sigmaStack.png");
    ///////Minus 20/////Stack///////
    TH1F * hMod28M20 = new TH1F("hMod28M20", "hMod28M20", 100, 0, 0.7e-03);
    TH1F * hMod48M20 = new TH1F("hMod48M20", "hMod28M20", 100, 0, 0.7e-03);
    double dSCSM20, dModTM20;
    tMin20->SetBranchAddress("sigmaCS", &dSCSM20);
    tMin20->SetBranchAddress("modThick", &dModTM20);
    hMod28M20->SetFillColor(kBlue-9);
    hMod48M20->SetFillColor(kBlue+3);
    int nEntriesMin20 = tMin20->GetEntries();
    for (int i = 0; i<nEntriesMin20; i++){
        tMin20->GetEntry(i);
        if(dModTM20 <0.03){
            hMod28M20->Fill(dSCSM20);
        }
        else{
            hMod48M20->Fill(dSCSM20);
        }
    }
    hMod48M20->GetXaxis()->SetTitle("Charge Spread");
    
    THStack *stackmodM20 = new THStack("stackmodM20", "Minus 20 degrees");
    stackmodM20->Add(hMod48M20);
    stackmodM20->Add(hMod28M20);
    TCanvas* cStackM20 = new TCanvas();
    TLegend* legSM20 = new TLegend(0.6, 0.63, .86, .80);
    legSM20->SetFillColor(0);
    legSM20->AddEntry(hMod28M20, "modThick = 0.028" , "f");
    legSM20->AddEntry(hMod48M20, "modThick = 0.048" , "f");
    
    legSM20->SetTextSize(.03);
    stackmodM20->Draw();
    stackmodM20->GetHistogram()->GetXaxis()->SetTitle("Charge Spread");
    
    legSM20->Draw();
    cStackM20->SaveAs("sigmaStackMinus20.png");
    
    cout<<"END"<<endl;
}
