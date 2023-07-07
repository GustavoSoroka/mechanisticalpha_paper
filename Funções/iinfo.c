
double iinfo(double *I_inf,int t,int r1, int r2, int r3, int r4, double second_s, double sti_amp,double varrr){

 int i;
 double s_amp = 9.5;//6.5;
 int duration = 2000; //20ms

 int shift =000;

 int t1=27500 + shift;


 double peak1,peak2,peak3,peak4,gauss1,gauss2,gauss3,gauss4, var;

 var = varrr;

 peak1 = (t1 + duration/2); 
 peak2 = (t1 + duration/2 + second_s);
 peak3 = (t1 + duration/2 + 2*second_s); 
 peak4 = (t1 + duration/2 + 3*second_s);

 gauss1= exp(-0.5*(pow(((t-peak1)/var),2)));
 gauss2= exp(-0.5*(pow(((t-peak2)/var),2)));
 gauss3= exp(-0.5*(pow(((t-peak3)/var),2)));
 gauss4= exp(-0.5*(pow(((t-peak4)/var),2)));


/////MODULO 1
//item A
for(i=1;i<=25;i++)
	I_inf[i] = s_amp*sti_amp*gauss1;


//item B
for(i=26;i<=50;i++)
I_inf[i] = s_amp*sti_amp*gauss2;



//item 
for(i=51;i<=75;i++)
I_inf[i] = s_amp*sti_amp*gauss3;


//item D
for(i=75;i<=100;i++)
I_inf[i] = s_amp*sti_amp*gauss4;





/////MODULO 2
//item A
for(i=101;i<=125;i++)
I_inf[i] = s_amp*sti_amp*gauss1;


//item B
for(i=126;i<=150;i++)
I_inf[i] = s_amp*sti_amp*gauss2;



//item C
for(i=151;i<=175;i++)
I_inf[i] = s_amp*sti_amp*gauss3;


//item D
for(i=175;i<=200;i++)
I_inf[i] = s_amp*sti_amp*gauss4;



////MODULO 3
//item A
for(i=201;i<=225;i++)
I_inf[i] = s_amp*sti_amp*gauss1;

//item B
for(i=226;i<=250;i++)
I_inf[i] = s_amp*sti_amp*gauss2;



//item C
for(i=251;i<=275;i++)
I_inf[i] = s_amp*sti_amp*gauss3;


//item D
for(i=275;i<=300;i++)
I_inf[i] = s_amp*sti_amp*gauss4;



////MODULO 4
//item A
for(i=301;i<=325;i++)
I_inf[i] = s_amp*sti_amp*gauss1;


//item B
for(i=326;i<=350;i++)
I_inf[i] = s_amp*sti_amp*gauss2;



//item C
for(i=351;i<=375;i++)
I_inf[i] = s_amp*sti_amp*gauss3;


//item D
for(i=375;i<=400;i++)
I_inf[i] = s_amp*sti_amp*gauss4;




  return 0;

}