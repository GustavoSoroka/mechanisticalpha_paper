double OSC(double A_osc, double t, double f, double fase){

 float dt=0.00001;
 return A_osc*sin(2*pi*f*t*dt+fase);
}
