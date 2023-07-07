
double neuron( double V, double *V_adp, double *V_theta, double *V_psp, double I_inf, double *I_psp, double I_adp, double I_theta, double I_alpha, double V_limiar, double V_rest, double *tau, int *disparo, int *reftime, int i){

 float dt = 0.01;




 if(i>=401){

    V = V + dt/(tau[mI])*(V_rest - V + *I_psp);

  }


else{

    V = V + dt/tau[mE]*(V_rest - V + I_inf + I_theta + I_alpha + I_adp + *I_psp);

    *V_adp   = *V_adp   + dt/tau[mE]*(V_rest  - *V_adp  + I_adp);   //ADP     |integração da membrana integrando separadamente
    *V_psp   = *V_psp   + dt/(tau[mE])*(V_rest  - *V_psp  + *I_psp);   //psp  |as correntes, observando os fenomenos da mesma
    *V_theta = *V_theta + dt/tau[mE]*(V_rest  - *V_theta + I_theta);//theta   |forma como demonstrado analiticamente no TCC
  }





//tempo de refraçao + limiar de disparo
 *reftime+=1;

 if (*reftime ==1){
	V= -75;
	*V_adp=-70;
  if(i>400){
    V=-70;I_psp=0;};
	}
 if ( V > V_limiar && *reftime >400)
   {
   V = V_rest;
   *disparo = 1;
   *reftime = 0;
   }
 else
   {
   *disparo = 0;
   }
 return V;
}