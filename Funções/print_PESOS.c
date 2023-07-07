void print_PESOS(FILE *PESOS , int N, double W[N][N]){

	int i, j;

  for(i=1;i<N;i++){
   for(j=1;j<N;j++){
     fprintf(PESOS,"%i\t%i\t%f\n", i, j , W[i][j]);}}

}
