
double pospotential( double P, double *tau, int disparo, int j){

 double dt = 0.01;
 if ( disparo == 1 ){
   P = P + 1;
   }
 if (j>400){P = P - dt/tau[psp_I]*P;}//corrente na membrana dos interneuronios
 else{P = P - dt/tau[psp_E]*P;}//corrente nas membranas dos neuronios 'normais'
 return P;
}