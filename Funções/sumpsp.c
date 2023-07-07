
void sum_PSP(int N, int i, double W[N][N], double P[N][N], double tau[3], int disparo[N], double *I_psp){

  int j;

  for(j=0;j<N;j++){
      if (W[i][j] != 0 ){

           P[i][j] = pospotential(P[i][j], tau, disparo[j],j);
           *I_psp += W[i][j]*P[i][j];
  }
 }
}
