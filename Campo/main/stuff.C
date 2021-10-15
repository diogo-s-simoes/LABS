TGraph2D G3Db; G3Db.SetTitle(""); G3Db.SetLineColor(kGreen); G3Db.SetMarkerStyle(8); G3Db.SetMarkerColor(kGreen); G3Db.SetMarkerSize(.5);
int numpnts = 25;
for(int j = 0; j<numpnts; ++j){
    for(int l=0; l<numpnts; ++l){
        G3Db.SetPoint(l+numpnts*j,0.12/numpnts*j,-0.04+0.08/numpnts*l,ftotb->Eval(0.12/numpnts*j,-0.04+0.08/numpnts*l));
    }
}
I=1;
Gtotb.Draw("P");
G3Db.Draw("P TRIW SAME");
c1->SetPhi(330.);
c1->SaveAs("3Db.png");
c1->Clear();