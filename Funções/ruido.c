double ruido(int t, double var_ruido,double *V_limiar){

  double n1, n2, RUIDO;

  if(t%100==0){
    n1=rand()*1.0/RAND_MAX ;
    n2=rand()*1.0/RAND_MAX ;
    RUIDO= var_ruido*sqrt(-2*log(n1))*sin(2*3.141596*n2);
    //printf("%i\n", t);
    //if (t == 30000){printf("%i\t%lf\n", t,RUIDO);}

    *V_limiar=-50+RUIDO;
  }

  return RUIDO;


}
