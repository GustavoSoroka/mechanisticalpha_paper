void print_ONE(FILE *ONE ,double t, int disparo, double V, double I_theta, double V_adp, double V_psp, double I_inf, double tau, double f_inib){


  if(P_ONE == yes)
  fprintf(ONE, "%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n", t*0.01,V*(1-disparo)+ disparo*40.0, I_theta, V_adp,V_psp, I_inf, tau, f_inib);

}
