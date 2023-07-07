void condicoes_iniciais(int N, double *V, double *V_adp, double *V_theta, double *V_psp, int *reftime, int *t0, int *disparo, double *V_limiar, double *P_inter){

  int i;

  for(i=0;i<N;i++){
     V[i] = -60;
     V_adp[i]=-60;
     V_theta[i]=-60;
     V_psp[i]=-60;
     reftime[i]=1001;
     t0[i]=-500000;
     disparo[i]=0;
     V_limiar[i]=-50;
  }
  *P_inter=0;

}
