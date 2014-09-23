//
//  mobcalc.C
//  
//
//  Created by Lana Beck.
//
//

using namespace std;
#include <TGraph.h>

void mobcalc(){
    
    double t   = 0.028; // in m or 0.048m
    double E_value;

    TH1D *mob_0 = new TH1D("h1","h1", 10, 0., 0.5);
    TH1D *mob_m20 = new TH1D("h2","h2", 10, 0., 0.5);
    TH1D *ratio = new TH1D("h3","h3", 10, 0., 0.5);

    TH1D *drift_0 = new TH1D("h4", "h4", 10, 0., 0.5);
    TH1D *drift_m20 = new TH1D("h5", "h5", 10, 0., 0.5);
    TH1D *drift_ratio = new TH1D("h6", "h6", 10, 0., 0.5);

    
    for (double y=0; y<t; y+=(t/100.)){
        E_value = field(y, t);

        mob_0->Fill(mobility(273, E_value));
        mob_m20->Fill(mobility(253, E_value) );
        ratio->Fill( ( mobility(273, E_value) / mobility(253, E_value) ) );

        drift_0->Fill(driftVelocity(273, E_value));
        drift_m20->Fill(driftVelocity(253, E_value));
        drift_ratio->Fill( (driftVelocity(273, E_value) / driftVelocity(253, E_value) ) );
        
    }
    

    TCanvas *c1 = new TCanvas("c1","c1", 600, 600); //c1->cd();

    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();


    TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.25);
    pad2->Draw();
 
    mob_0->GetYaxis()->SetLabelFont(63); //font in pixels
    mob_0->GetYaxis()->SetLabelSize(16); //in pixels
    mob_0->GetYaxis()->SetTitle("mobility");
    mob_0->SetTitle("");
    mob_0->SetMinimum(0.);
    mob_0->SetMaximum(100.);
    mob_0->GetYaxis()->SetTitleSize(0.07);
    mob_0->GetYaxis()->SetTitleOffset(0.65);
    
    mob_m20->SetLineColor(kRed);

    pad1->cd();
    
    mob_0->Draw();
    mob_m20->Draw("SAME");
    
    TLegend* leg = new TLegend(0.75, 0.73, .85, .85);
    leg->SetFillColor(0);
    leg->AddEntry(mob_m20, " -20C", "l");
    leg->AddEntry(mob_0, "  0C", "l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.07);
    
    leg->Draw();
    
    pad2->cd();

    ratio->SetStats(0.);
    ratio->SetTitle("");
    //ratio->GetXaxis()->SetLabelFont(63);
    ratio->GetXaxis()->SetLabelSize(0.1); //in pixels
    ratio->GetYaxis()->SetLabelSize(0.1); //in pixels
    
    ratio->GetXaxis()->SetTitle("E-field (V/#mu m)");
    ratio->GetXaxis()->SetTitleSize(0.1);
    ratio->GetXaxis()->SetTitleOffset(0.9);
    ratio->GetYaxis()->SetTitle("0C / -20C");
    ratio->GetYaxis()->SetTitleSize(0.11);
    ratio->GetYaxis()->SetTitleOffset(0.45);
    ratio->Draw();

    c1->cd();
    c1->SaveAs("mobilityt.png");
    ////////////////////new canvas/////////////////////////
    TCanvas *c2 = new TCanvas("c2","c2", 600, 600); //c2->cd();

    TPad *pad3 = new TPad("pad3","pad3",0,0.3,1,1);
    pad3->SetBottomMargin(0);
    pad3->Draw();


    TPad *pad4 = new TPad("pad4","pad4",0,0.05,1,0.3);
    pad4->SetTopMargin(0);
    pad4->SetBottomMargin(0.25);
    pad4->Draw();
 
    drift_0->GetYaxis()->SetLabelFont(63); //font in pixels
    drift_0->GetYaxis()->SetLabelSize(16); //in pixels
    drift_0->GetYaxis()->SetTitle("drift velocity");
    drift_0->SetTitle("");
    drift_0->SetMinimum(0.);
    drift_0->SetMaximum(0.01);
    drift_0->GetYaxis()->SetTitleSize(0.07);
    drift_0->GetYaxis()->SetTitleOffset(0.65);
    
    drift_m20->SetLineColor(kRed);

    pad3->cd();
    
    drift_0->Draw();
    drift_m20->Draw("SAME");
    
    TLegend* leg = new TLegend(0.75, 0.73, .85, .85);
    leg->SetFillColor(0);
    leg->AddEntry(drift_m20, " -20C", "l");
    leg->AddEntry(drift_0, "  0C", "l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.07);
    
    leg->Draw();
    
    pad4->cd();

    drift_ratio->SetStats(0.);
    drift_ratio->SetTitle("");
    //drift_ratio->GetXaxis()->SetLabelFont(63);
    drift_ratio->GetXaxis()->SetLabelSize(0.1); //in pixels
    drift_ratio->GetYaxis()->SetLabelSize(0.1); //in pixels
    
    drift_ratio->GetXaxis()->SetTitle("E-field (V/#mu m)");
    drift_ratio->GetXaxis()->SetTitleSize(0.1);
    drift_ratio->GetXaxis()->SetTitleOffset(0.9);
    drift_ratio->GetYaxis()->SetTitle("0C / -20C");
    drift_ratio->GetYaxis()->SetTitleSize(0.11);
    drift_ratio->GetYaxis()->SetTitleOffset(0.45);
    drift_ratio->Draw();

    c2->cd();
    c2->SaveAs("driftt.png");
    
}


double driftVelocity(double T, double E ) {
    double v_d;
    
    /*   Jacoboni et al.
     *   Solid-State Electronics, 1977, Vol. 20, pp. 7749.
     *   Pergamon Press.
     *   Printed in Great Britain
     */
    double v_m;
    double E_c;
    double beta;
    int sign = 1; //for holes
    double mobility;
    
    if (sign==-1) {
        v_m = 15300 * pow(T,-.87);     // in um/ns
        E_c = 1.01E-04 * pow(T,1.55);  // in V/um
        beta = 2.57E-2 * pow(T,0.66);  // pure number
    } else {
        v_m = 1620 * pow(T,-.52);      // in um/ns
        E_c = 1.24E-04 * pow(T,1.68);  // in V/um
        beta = 0.46 * pow(T,0.17);     // pure number
    }
    v_d = v_m;
    v_d*=(E/E_c);
    v_d/=pow((1+pow((E/E_c),beta)),1/beta);
    
    // (v_d = mobility * E;) 
    
    return v_d;
}

double mobility(double drift_v, double E){
    double mob = 10 * drift_v/E; //multiply by 10 to get into cm^2/Vs
    return mob;
}

// @param V applied voltage
// @param Vfd full depletion voltage
// @param t thickness of the silicon
// @param y position in the silicon (y=0 on backplane)
// @return the electric field value
double field(double y, double t) {
    double E;
    double V   = 300.; // in V
    double Vfd = 170.; // in V
    if (V<Vfd) {
        double d = t * sqrt(V / Vfd);
        if (y<(t-d)) E=0;
        else E=2*Vfd/t/t*(y-(t-d));
    } else {
        E = (V-Vfd)/t + 2 * Vfd /t/t * y;
    }
    return E; //V/m
}
