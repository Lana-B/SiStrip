//
//  MobilityCalc.C
//  
//
//  Created by Lana Beck on 16/09/2014.
//
//

using namespace std;
#include <TGraph.h>

void MobilityCalc(){
    
    std::vector<double> E_values, vec_0, vec_m20, vec_ratio;
    
    
    for (double i=0.01.; i<0.5; i+=0.01){
        E_values.push_back(i);
        vec_0.push_back(driftVelocity(273, i));
        vec_m20.push_back( driftVelocity(253, i));
        vec_ratio.push_back( driftVelocity(273, i) / driftVelocity(253, i) );

        cout<<i<<"  v_d: "<<driftVelocity(273, i)<<endl;
        
    }
    
    TGraph *mob_0;
    TGraph *mob_m20;
    TGraph *ratio;
    
    TCanvas *c1 = new TCanvas("c1","c1", 600, 600);
    //c1->cd();
    
    mob_0 = new TGraph(E_values.size(), &(E_values[0]), &(vec_0[0]));
    mob_m20 = new TGraph(E_values.size(), &(E_values[0]), &(vec_m20[0]));
    

    mob_0->GetYaxis()->SetLabelFont(63); //font in pixels
    mob_0->GetYaxis()->SetLabelSize(16); //in pixels
    mob_0->GetYaxis()->SetTitle("mobility");
    mob_0->SetTitle("");
    mob_0->SetMinimum(250.);
    mob_0->SetMaximum(1000.);
    mob_0->GetYaxis()->SetTitleSize(0.07);
    mob_0->GetYaxis()->SetTitleOffset(0.65);

    mob_m20->SetLineColor(kRed);

    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();
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
 
    c1->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0.05,1,0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.25);

    pad2->Draw();
    pad2->cd();
    
    ratio = new TGraph(E_values.size(), &(E_values[0]), &(vec_ratio[0]));
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
    
    c1->SaveAs("mobility.png");
    
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
    cout<<"vd  "<<v_d<<endl;
    mobility = 10*v_d/E; //multiply by 10 to get into cm^2/Vs

    return mobility;
}
