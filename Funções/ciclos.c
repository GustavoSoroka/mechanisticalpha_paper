double def_ciclostheta(double A_theta, double f_theta, double *theta_cycle, double *theta_aux, double DELAY, int tmax ){

int i,j,tc,t;
double theta_current;

  i=0;
  j=1;
  tc=5000;
  for(t=0;t<tmax+30000; t=t+1){
  theta_current = (OSC(A_theta*1, t, f_theta, -DELAY) +
                  OSC(A_theta*1, t, f_theta, -2*DELAY)+
                  OSC(A_theta*1, t, f_theta, -3*DELAY)+
                  OSC(A_theta*1, t, f_theta, -4*DELAY)+
                  OSC(A_theta*1, t, f_theta, -5*DELAY))/5.0;


  if(theta_current<0.01 && theta_current > -0.01 && tc>5000){
  theta_aux[i]=t*0.01 - 35*DELAY - 2/DELAY;
  if((i)%2 == 0 && i>2){
  theta_cycle[j]=theta_aux[i];
  j++;}

  tc=0;
  i++;
  }
  tc++;
  }



}
