//
//  MobilityCalc.C
//  
//
//  Created by Lana Beck on 16/09/2014.
//
//

using namespace std;
#include <TGraph.h>

void mob_v(){
    
    std::vector<double> E_values, vec_0, vec_m20, vec_300K, vec_ratio, vec_vd0, vec_vdm20, vec_vdratio;
    
    for (double i=0.01; i<100.0; i+=0.01){
        E_values.push_back(i);
        vec_0.push_back(mobility((driftVelocity(273, i)), i)); //0 degrees
        vec_m20.push_back( mobility((driftVelocity(253, i)), i)); //minus 20 degrees
        vec_300K.push_back( mobility((driftVelocity(300, i)), i)); //300K
        vec_ratio.push_back( mobility((driftVelocity(273, i)), i) / mobility((driftVelocity(253, i)), i) );

        vec_vd0.push_back(driftVelocity(273, i));
        vec_vdm20.push_back( driftVelocity(253, i));
        vec_vdratio.push_back( driftVelocity(273, i) / driftVelocity(253, i) );

        cout<<i<<"  v_d: "<<driftVelocity(273, i)<<"  mob: "<<mobility((driftVelocity(273, i)), i)<<endl;
        
    }

  /*  double module_thickness = 0.028; //or 0.048m

    for (double i=0; i<module_thickness; i+=(module_thickness/20.)){
        E_values.push_back(field(i, module_thickness));
        vec_0.push_back(mobility((driftVelocity(273, field(i, module_thickness))), field(i, module_thickness)));
        vec_m20.push_back( mobility((driftVelocity(253, field(i, module_thickness))), field(i, module_thickness)));
        vec_ratio.push_back( mobility((driftVelocity(273, field(i, module_thickness))), field(i, module_thickness)) / mobility((driftVelocity(253, field(i, module_thickness))), field(i, module_thickness)) );

        vec_vd0.push_back(driftVelocity(273, field(i, module_thickness)));
        vec_vdm20.push_back( driftVelocity(253, field(i, module_thickness)));
        vec_vdratio.push_back( driftVelocity(273, field(i, module_thickness)) / driftVelocity(253, field(i, module_thickness)) );     

        cout<<i<<"  E-field:  "<<field(i, module_thickness)<<"  v_d: "<<driftVelocity(273, i)<< "  mob: "<<mobility((driftVelocity(273, field(i, module_thickness))), field(i, module_thickness))<<endl;
    }*/
    
    //mobility plots
    TGraph *mob_0;
    TGraph *mob_m20;
    TGraph *mob_300K;
    TGraph *ratio;

    
    TCanvas *c1 = new TCanvas("c1","c1", 600, 600);
    
    mob_0 = new TGraph(E_values.size(), &(E_values[0]), &(vec_0[0]));
    mob_m20 = new TGraph(E_values.size(), &(E_values[0]), &(vec_m20[0]));
    mob_300K = new TGraph(E_values.size(), &(E_values[0]), &(vec_300K[0]));
    

    mob_0->GetYaxis()->SetLabelFont(63); //font in pixels
    mob_0->GetYaxis()->SetLabelSize(16); //in pixels
    mob_0->GetYaxis()->SetTitle("mobility");
    mob_0->SetTitle("");
    mob_0->SetMinimum(0.);
    mob_0->SetMaximum(1000.);
    mob_0->GetYaxis()->SetTitleSize(0.07);
    mob_0->GetYaxis()->SetTitleOffset(0.65);

    mob_m20->SetLineColor(kRed);
    mob_300K->SetLineColor(kGreen);

    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    
    mob_0->Draw();
    mob_m20->Draw("SAME");
    mob_300K->Draw("SAME");
 
    pad1->SetLogx();
    TLegend* leg = new TLegend(0.75, 0.73, .85, .85);
    leg->SetFillColor(0);
    leg->AddEntry(mob_m20, " -20C", "l");
    leg->AddEntry(mob_0, "  0C", "l");
    leg->AddEntry(mob_300K, "  300K", "l");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.07);

    leg->Draw();
 
    c1->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.25);

    pad2->Draw();
    pad2->cd();

    pad2->SetLogx();
    
    ratio = new TGraph(E_values.size(), &(E_values[0]), &(vec_ratio[0]));
    ratio->SetTitle("");
    ratio->GetXaxis()->SetLabelSize(0.1); //in pixels
    ratio->GetYaxis()->SetLabelSize(0.1); //in pixels

    ratio->GetXaxis()->SetTitle("E-field (V/#mu m)");
    ratio->GetXaxis()->SetTitleSize(0.1);
    ratio->GetXaxis()->SetTitleOffset(0.9);
    ratio->GetYaxis()->SetTitle("0C / -20C");
    ratio->GetYaxis()->SetTitleSize(0.11);
    ratio->GetYaxis()->SetTitleOffset(0.45);
    ratio->Draw();
    
    c1->SaveAs("mobility.png");
    
    ////////////////*************/////////////////
    ///drift velocity plots
    TGraph *vd_0;
    TGraph *vd_m20;
    TGraph *vd_ratio;
    TCanvas *c2 = new TCanvas("c2","c2", 600, 600);
    
    vd_0 = new TGraph(E_values.size(), &(E_values[0]), &(vec_vd0[0]));
    vd_m20 = new TGraph(E_values.size(), &(E_values[0]), &(vec_vdm20[0]));
    

    vd_0->GetYaxis()->SetLabelFont(63); //font in pixels
    vd_0->GetYaxis()->SetLabelSize(16); //in pixels
    vd_0->GetYaxis()->SetTitle("v_drift (um/ns)");
    vd_0->SetTitle("");
    vd_0->SetMinimum(pow(10,5));
    vd_0->SetMaximum(pow(10,8));
    vd_0->GetYaxis()->SetTitleSize(0.07);
    vd_0->GetYaxis()->SetTitleOffset(0.65);

    vd_m20->SetLineColor(kRed);

    TPad *pad3 = new TPad("pad3","pad3",0,0.3,1,1);
    pad3->SetBottomMargin(0);
    pad3->Draw();
    pad3->cd();
    
    vd_0->Draw();
    vd_m20->Draw("SAME");

    pad3->SetLogy();
    pad3->SetLogx();
 
    TLegend* leg2 = new TLegend(0.75, 0.13, .85, .25);
    leg2->SetFillColor(0);
    leg2->AddEntry(vd_m20, " -20C", "l");
    leg2->AddEntry(vd_0, "  0C", "l");
    leg2->SetBorderSize(0);
    leg2->SetTextSize(0.07);

    leg2->Draw();
 
    c2->cd();
    TPad *pad4 = new TPad("pad4","pad4",0,0.05,1,0.3);
    pad4->SetTopMargin(0);
    pad4->SetBottomMargin(0.25);

    pad4->Draw();
    pad4->cd();
    pad4->SetLogx();
    
    vd_ratio = new TGraph(E_values.size(), &(E_values[0]), &(vec_vdratio[0]));
    vd_ratio->SetTitle("");
    vd_ratio->GetXaxis()->SetLabelSize(0.1); //in pixels
    vd_ratio->GetYaxis()->SetLabelSize(0.1); //in pixels

    vd_ratio->GetXaxis()->SetTitle("E-field (V/#mu m)");
    vd_ratio->GetXaxis()->SetTitleSize(0.1);
    vd_ratio->GetXaxis()->SetTitleOffset(0.9);
    vd_ratio->GetYaxis()->SetTitle("0C / -20C");
    vd_ratio->GetYaxis()->SetTitleSize(0.11);
    vd_ratio->GetYaxis()->SetTitleOffset(0.45);
    vd_ratio->Draw();
    c2->SaveAs("drift_v.png");


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
    
    return v_d*pow(10,5); // *by 10^5 to get into cm/s
}

double mobility(double drift_v, double E){
    double mob = drift_v/(E); 
    mob/= pow(10,4); //multiply by 10^4 to get into cm^2/Vs
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
    E *= pow(10, -6); //to go from V/m to v/um
    return E; //V/um
}

