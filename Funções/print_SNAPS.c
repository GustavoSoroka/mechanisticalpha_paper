void print_SNAPS(FILE *snaps,int i, int snap[20][20], int N, int t, int T1, int *disparo){


if(P_SNAPS==yes){

int ii, jj;

//INICIALIZAÇÃO (ṔRIMEIRA VEZ)
if(t==-1){
snaps=fopen("Dados/snap.dat", "w");  
for(ii=0;ii<20;ii++)
  for(jj=0;jj<20;jj++){
    snap[ii][jj]=0;
    fprintf(snaps, "%i\t%i\t%i\n", ii, jj, snap[ii][jj]);
  }

fclose(snaps);
}



//REINICIALIZAÇÃO (EM CADA CICLO TEMPORAL)
if(i==N){
snaps=fopen("Dados/snap.dat", "w");
for(ii=0;ii<20;ii++)
  for(jj=0;jj<20;jj++){
    snap[ii][jj]=0;
    fprintf(snaps, "%i\t%i\t%i\n", ii, jj, snap[ii][jj]);
  }
  fclose(snaps);
}




//DISPAROS=>1
if(t==T1 && i>0){
    snap[(i-1)/20][(i-1)%20]=*disparo;     //auxiliar1= (i-1)/20;//linha
                                              //auxiliar2= (i-1)%20;//coluna
}


//ATUALIZAÇÃO
  if(i==(N-1)){
    snaps=fopen("Dados/snap.dat", "w");
    for(ii=0;ii<20;ii++)
      for(jj=0;jj<20;jj++){
        if(jj>9){fprintf(snaps, "%i\t%i\t%i\t%i\n", ii, jj, snap[ii][jj],1);}
        else{fprintf(snaps, "%i\t%i\t%i\t%i\n", ii, jj, snap[ii][jj], 2);}
      }
        fclose(snaps);

  }
}
}
