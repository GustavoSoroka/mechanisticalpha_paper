//BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
//~~~~~~


//FUNÇÔES
#include "Funções/constantes.c"             //fora o PI (3.14...), são constantes que ajudam a tornar o código mais legível, substituindo valores por letras
#include "Funções/config.c"                 //por enquanto, configura quais impressões serão feitas (ou ignoradas) no programa (SNAPS, ONE, PESOS)
#include "Funções/ensembles.c"              //divide a REDE EXCITATÓRIA em 5 ensembles iguais
#include "Funções/adp.c"                    //função do fenômeno de despolarização pós disparo (afterdepolarization)
#include "Funções/iinfo.c"                  //função que estímula os neurônios com corrente informacional
#include "Funções/neuron.c"                 //função da integração dos neurônios e tempo de refração
#include "Funções/OSC.c"                    //função de corrente oscilatória (THETA)
#include "Funções/conexoes.c"               //função que gera as conexões entre os neurônios
#include "Funções/distribuicao.c"           //gera uma distribuição que vai ser usada para as conexões (nesse caso é linear, mas pdoeria ser normal, uniforme,etc)
#include "Funções/psp.c"                    //função que gera um incremento de corrente (e seu decaimento) quando um neurônio excita o outro
#include "Funções/condicoesgerais.c"        //determina condições globais da rede e simulação
#include "Funções/condicoesiniciais.c"      //determina condições iniciais da rede e simulação
#include "Funções/sumpsp.c"                 //soma as correntes geradas pelo estímulo de todos neurônios em um específico
#include "Funções/ruido.c"                  //ruido do sistema (nesse caso, é uma variação no limiar de disparo)
#include "Funções/print_ONE.c"              //imprime vários parâmetros de um único neurônio
#include "Funções/print_PESOS.c"            //imprime as conexões


int main(){
int i,j;                     // neuron indexes, usually i pos-synaptic and j pre-synaptic
int N=501;                   // number of neurons //REDE 1[0-24] e REDE 2[25-49]
int r1,r2,r3,r4,r5;          // variaveis auxiliares pra divisao dos ensembles
int t=0;                     // temporal variable
int t0[N];	                 //tempo do ultimo disparo do neuronio N
int tmax;	                   //tempo de simulação

int disparo[N];              // spike activity of neurons
int reftime[N];	             //contator para o tempo de refração

double  W[N][N];             // synaptic strenght between two neurons
double  P[N][N];             // post synaptic potential between two neurons
double  P_inter;	           // potencial pos sinaptico dos interneuronios inibitorios

double  tau[5];              //constantes de tempo [mE,mI,ADP,psp_E,psp_I]

double I_adp[N];             //          /-ADP
double I_theta[N];		           //          /-oscilatoria da REDE 1
double I_psp[N];             //          /-psp
double I_inf[N];             //          /-informacional

//POTENCIAIS
double  V[N];                // 			     /-total
double V_adp[N];	           //           /-ADP
double V_psp[N];	           //potenciais /-psp
double V_theta[N];	         //			     /-theta
double V_limiar[N];	         //           /-limiar
double V_rest;               //           /-repouso

//THETA
double A_theta;              //amplitude da oscilaçao theta (o mínimo da oscilação)
double f_theta;		           //frequencia da oscilação theta
double fase_theta = 0;       //fase inicial da corrente theta


//ALPHA
double I_alpha[N];            //corrente oscilatória alpha
double A_alpha=0;            //amplitude alpha


double A_adp;		             //amplitude ADP

double var_ruido=0.0;      //variancia do ruido
time_t start, end, aux_start;//para o calculo do tempo da simulação
double tempo_simulacao;      //tempo de simulaçao

int NN1, NN2, NN3, NN4, NN5, NN6, NN7, NN8, NN9, NN10, NN11,NN12,NN13,NN14,NN15;                  //neuronio escolhido para a observação dos parametros (ONE.gp)
int *N_SYN_GABA;             //numero de sinapses que os neuronio inibitorios recebem dos excitatorios, no fim ela recebe a informação da distribuiçao()


double f_conex=0;

double DELAY=0;
double f_alfa = 10;
int REPP = 0;
int seed = 0;
double aux1 = 0;
double aux2 = 0;
double n1,n2;
//---EXPERIMENTO--//
double f_inib = 0.01;
double f_entre_ensemble = 0.12;
double second_s =0;
double sti_amp =0;
double varrr = 0;
double delay_i = 0;
double sstime = 0;
int PPi =0;
int PPj=0;
float MMM[9][13] = {

{0, 0, 0, 0, 0, 0, 0, 15.333333333333334, 18.0, 20.0, 22.0, 23.0, 24.0},
{0, 0, 0, 0, 0, 0, 15.0, 16.5, 19.0, 20.5, 22.5, 23.5, 24.5},
{0, 0, 0, 0, 0, 12.0, 15.5, 17.5, 19.5, 22.0, 23.0, 24.0, 25.0},
{0, 0, 0, 0, 10.5, 13.0, 16.0, 19.0, 20.0, 22.0, 23.0, 24.0, 25.0},
{0, 0, 0, 10.0, 12.0, 14.5, 16.5, 19.0, 21.0, 22.5, 24.0, 24.5, 25.0},
{0, 0, 0, 11.0, 13.0, 15.5, 18.0, 19.5, 22.0, 23.0, 24.0, 25.0, 25.5},
{0, 0, 8.5, 11.5, 14.5, 16.5, 18.5, 20.5, 22.5, 23.0, 24.5, 25.0, 26.5},
{0, 7.5, 9.5, 12.5, 14.5, 17.625, 19.0, 21.5, 23.0, 24.0, 25.5, 26.0, 27.0},
{0, 8.0, 11.5, 14.0, 16.142857142857142, 18.0, 19.88888888888889, 22.5, 23.5, 25.5, 25.5, 26.5, 0}


};
//-------------------


// -- // -- ARQUIVOS -- // -- // ----------------------------
char experimento[30];
sprintf(experimento, "data20reps_12demaio.dat");

FILE *ONE, *TWO, *THREE, *FOUR, *FIVE, *SIX, *SEVEN, *EIGHT, *NINE, *TEN,*PESOS, *RASTER;
FILE *IN_ONE, *IN_TWO, *IN_THREE, *IN_FOUR, *IN_FIVE;
FILE *OSCs;

//ONE=fopen("Dados/ONE.dat", "w");              //registro da dinamica de um neuronio
//TWO=fopen("Dados/TWO.dat", "w"); 
//THREE=fopen("Dados/THREE.dat", "w");
//FOUR=fopen("Dados/FOUR.dat", "w");  
//FIVE=fopen("Dados/FIVE.dat", "w");  
//SIX=fopen("Dados/SIX.dat", "w");  
//SEVEN=fopen("Dados/SEVEN.dat", "w");  
//EIGHT=fopen("Dados/EIGHT.dat", "w");  
//NINE=fopen("Dados/NINE.dat", "w");  
//TEN=fopen("Dados/TEN.dat", "w");  


//IN_ONE=fopen("Dados/IN_ONE.dat", "w");              //registro da dinamica de um neuronio
//IN_TWO=fopen("Dados/IN_TWO.dat", "w"); 
//IN_THREE=fopen("Dados/IN_THREE.dat", "w");
//IN_FOUR=fopen("Dados/IN_FOUR.dat", "w");  
//IN_FIVE=fopen("Dados/IN_FIVE.dat", "w");

//OSCs = fopen("Dados/osc.dat", "w");





//PESOS=fopen("Dados/pesos.dat", "w");          //conexões
RASTER=fopen(experimento, "w");    //rasterplot

//fprintf(ONE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(TWO, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(THREE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(FOUR, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(FIVE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(SIX, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(SEVEN, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(EIGHT, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(NINE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(TEN, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");

//fprintf(IN_ONE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(IN_TWO, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(IN_THREE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(IN_FOUR, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");
//fprintf(IN_FIVE, "t\tV\ttheta\tadp\tpsp\talfa\ttau\tf_inib\n");


//fprintf(OSCs, "t\tnada\tE1\tE2\tE3\tE4\tE5\tnada2\n");




fprintf(RASTER, "t\twho\ta\tdelay\ttau\n" );
//fprintf(PESOS, "n1\tn2\tpeso\n" );

fclose(RASTER);


//---- CONDIÇÕES GERAIS--------------------------------------

time(&start);                                                 // começa a contagem do tempo
NN1=15;
NN2 = 45;
NN3 = 75;
NN4 = 105;
NN5 = 135;
NN6 = 165;
NN7 = 195;
NN8 = 225;
NN9 = 255;
NN10 = 285;
NN11 = 310;
NN12 = 330;
NN13 = 350;
NN14 = 370;
NN15 = 390;



DELAY = 0.1;
var_ruido = 0.5;// 0.5;
f_inib = -0.8;//-2;
second_s = 0;
tau[mE]=8;
sti_amp = 1.8;
varrr = 400;



tmax = 65000;                                                // tempo máximo de simulação
ensembles(N, &r1, &r2, &r3, &r4);                        // definindo limites dos ensembles (0,40,80,120,160,200)                                    //
conexoes(N,W,P, f_entre_ensemble, f_inib);                                             // definindo conexões
condicoes_gerais(&A_adp, &A_theta, &f_theta, tau, &V_rest);   // condições gerais
//print_PESOS(PESOS, N, W);                                     // imprimindo as conexões
//fclose(PESOS);                                                //
//-----------------------------------------------------------


for (REPP = 1; REPP <50; REPP = REPP + 1){
for (PPi = 1; PPi <9 ; PPi++) { //9
  for(PPj = 1; PPj < 13; PPj++){ //13





    DELAY = PPj*0.1;
    delay_i = PPi*0.1;
    second_s = 100*MMM[PPi][PPj];
    printf("%i\t%lf\t%lf\t%lf\tCompleto:%i%c\n",REPP,PPi*0.1, PPj*0.1, second_s, (REPP-1)*2,'%');


    if(second_s != 0){


    
    

        seed = 10*second_s + delay_i+DELAY + PPi*PPj + REPP;
        srand(seed);
        conexoes(N,W,P, f_entre_ensemble, f_inib);                                              // definindo conexões

      
      condicoes_iniciais(N, V, V_adp, V_theta, V_psp, reftime, t0, disparo, V_limiar, &P_inter);


          

          for( t=25000;t<= tmax;t++){
              
                  RASTER=fopen(experimento, "a");
                  

                  iinfo(I_inf, t,r1,r2,r3,r4,second_s, sti_amp,varrr);


                    for(i=1;i<N;i++){

                      //LEMBRANDO QUE AQUI O I_THETA NÃO TEM INDICE DO NEURONIO, ENTÃO
                      //SÓ TA FUNCIONANDO PORQUE TA DENTRO DO LOOP QUE INTEGRA AS CORRENTES
                      //MELHOR COLOCAR OS INDICES TAMBÉM!!!

                      
                      if(i>0 && i< 101)
                      fase_theta= -0.1884- delay_i - 0*DELAY;
                      else if(i>100 && i<201)
                      fase_theta = -0.1884- delay_i - 1*DELAY;
                      else if(i>200 && i<301)
                      fase_theta = -0.1884-delay_i - 2*DELAY;
                      else if(i>300 && i<401)
                      fase_theta = -0.1884-delay_i - 3*DELAY;
                      else
                      fase_theta=0;
            
                      
                     

                      I_theta[i]=OSC(A_theta*1.0, t, f_theta+aux2, fase_theta);                  

                      I_alpha[i]=OSC(A_theta*0.0, t, f_alfa + aux1, fase_theta);

                      
                      if (t>1000000){
                          I_theta[i]=OSC(A_theta*0.5, t, f_theta+aux2, fase_theta);
                          I_alpha[i]=OSC(A_theta*0.5, t, f_alfa + aux1, fase_theta);
                  }






                      ruido(t, var_ruido, &V_limiar[i]);
                      I_psp[i]=0;
                      I_adp[i]= afterdepolarization(A_adp, tau, t, t0[i], i);//corrente ADP
                      sum_PSP(N, i, W, P, tau, disparo, &I_psp[i]);

                      //INTEGRAÇÃO DA MEMBRANA
                      V[i] = neuron( V[i], &(V_adp[i]), &(V_theta[i]), &(V_psp[i]), I_inf[i],  &I_psp[i], I_adp[i], I_theta[i], I_alpha[i], V_limiar[i], V_rest, tau, &(disparo[i]), &(reftime[i]), i);

                  

                      if(disparo[i]==1){
                        //fprintf(rpp2, "%lf\t%i\t%lf\t%lf\t%lf\n", t*0.01, i, f_alfa, var_ruido, DELAY);
                        fprintf(RASTER, "%lf\t%i\t%lf\t%lf\t%lf\t%i\n", t*0.01, i, delay_i,DELAY, second_s, REPP);
                        //fprintf(RASTER, "%f\t%i\n", t*0.01, i);
                        //printf("%lf\t%i\t%lf\t%lf\t%lf\n", t*0.01, i,ciclo, var_ruido, DELAY);
                        
                        for(j=1;j<(N-1)/2;j++){
                          P[i][j]=0;              //AQUI ZERANDO AS CORRENTES
                        }
                        t0[i]=t;
                      }

                      

                    }

              

              fclose(RASTER);



          } // LOOP TEMPORAL
          


      //} // LOOP REPETIÇÂO
  //} // LOOP TAU_m
//} //LOOP DELAY
}//loop conditional
} //LOOP PPi
} //LOOP ppj
}//loop REPP


//TIME is TIME
time(&end);
tempo_simulacao = difftime(end, start);


printf("\nInformações da Simulacao\n\n");
printf("Numero de neuronios\t %i \n", N);
printf("Tau da membrana dos Neuronios Excitatórios\t %.2f ms\n", tau[mE]);
printf("Tau da membrana dos Neuronios Inibitórios\t %.2f ms\n", tau[mI]);
printf("Tau da corrente ADP\t\t %.2f ms\n", tau[adp]);
printf("Tau PSP nos neurônios excitatórios\t\t %.2f ms\n", tau[psp_E]);
printf("Tau PSP nos neurônios inibitórios\t\t %.2f ms\n", tau[psp_I]);
printf("Potencial de Repouso\t %.2f mV\n", V_rest);
printf("Limiar de Disparo\t %.2f mV\n", V_limiar[0]);
printf("Amplitude Theta\t\t %.2f mV\n", A_theta);
printf("Frequência Theta\t %.2f Hz\n", f_theta);
printf("Amplitude Alpha\t\t %.2f mV\n", A_theta);
printf("Frequência Alpha\t %.2f Hz\n", f_theta);
printf("Amplitude ADP\t\t %.2f mV\n", A_adp);
printf("\nTempo de Simulacao\t~ %.0f segundos\n", tempo_simulacao);





return 0;
}

