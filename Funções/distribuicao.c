

int *distribuicao(){
 double drand48(), n1, n2, nn1, nn2;
 int nn3, nn4;
 static int r[200]={};
 int i=0, G, k=1, z1, z2;
 int bin[200]={};

  FILE *dados;
  dados = fopen("Dados/normal.dat", "w");
  srand48(time(NULL));
  do{

    n1 = drand48();
    n2 = drand48();

   //printf("%i\n", i);
   // nn1=n1/1;
   // nn2=n2/2;

   //printf("%f\t%f\n", n1, n2);
    nn1 = 30+1*sqrt(-2*log(n1))*(cos(2*3.141592*n2));

    nn2 = 30+1*sqrt(-2*log(n1))*(sin(2*3.141592*n2));

   nn3=nn1/1;
   nn4=nn2/1;

   r[i]=nn3;
   r[i+1]=nn4;




    //printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%i\t%i\n", n1, n2, log(n1), sqrt(-2*log(n1)), cos(2*3.141592*n2), sin(2*3.141592*n2), nn1, nn2, nn3, nn4 );
    //fprintf(dados, "%f\t%f\n", n1, n2);


    G=200;
    do{
       if(nn3 == G){
             bin[G]=bin[G]+1;
             G= -1;}

       else{
            G= G-1;}

    }while(G>-0);

    G=200;
    do{
       if(nn4  == G){
            bin[G]=bin[G]+1;
             G= -1;}

       else{
           G= G-1;}

   }while(G>0);

    i=i+2;


  }while(i<200);

 do{
  fprintf(dados, "%i\t%i\n", bin[k], k);
   k=k+1;

  }while(k<200);



  fclose(dados);

return r;
}
