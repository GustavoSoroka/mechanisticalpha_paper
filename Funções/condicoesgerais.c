void condicoes_gerais(double *A_adp, double *A_theta, double *f, double *tau, double *V_rest){

  *A_adp   = 6.0;//7.0; //mV
  *A_theta = 7.0; //mV
  *f	= 8.0; //Hz

  tau[mE]	=  15;// decaimento da corrente na membrana dos neuronios excitatorios    = 10 ms
  tau[mI]	=  2;  // decaimento da corrente na membrana dos neuronios inibitorios     = 1 ms
  tau[psp_E]=  1;   // decaimento da corrente pelo neuronio pos sinaptico excitatórios 	= 4 ms
  tau[psp_I]=  10;   // decaimento da corrente pelo neuronio pos sinaptico inibitorio   = 10  ms
  tau[adp]	= 140; // decaimento da corrente ADP			      					    = 130 ms

  *V_rest   =  -60;	 //potencial de repouso



}
