
double afterdepolarization(double A_adp, double *tau, int t, int t0, int i){


 float dt=0.01;

 t=t*dt;
 t0=t0*dt;


//apenas neuronios excitatórios possuem (são os que formam os ensembles)
 if(i<401)
 	return (A_adp/tau[adp])*(t-t0)*exp(-((t-t0)/tau[adp])+1);

 else
 	return 0;

}


//
//função analitica da corrente adp
//
//