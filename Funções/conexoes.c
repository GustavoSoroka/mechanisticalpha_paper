
void conexoes(int N, double W[N][N] ,double P[N][N], double f_entre_ensemble, double f_inib ){


  int i, j, a, b;
  float valor2 = 4.5;//
  float valor = 1.0*3.0;
  float f_inib2 = f_inib*2.5;//inibição modular

  



   // inibição global (I---> ALL E)
   for(i=1;i<401;i++){
     for(j=401;j<501;j++){
        W[i][j] = (f_inib2/4)*rand()*1.0/RAND_MAX;
     }
   }

  // excitação global dos interneuronios (E ---> ALL I)
   for(i=401;i<501;i++){
     for(j=1;j<401;j++){
         W[i][j] = (valor2*0.25)*rand()*1.0/RAND_MAX;
     }
   }



/////Excitação modular//////
//Modulo 1
 for (i=1;i<100;i++){
    for (j=1;j<100;j++){                 
      W[j][i]= valor*rand()*1.0/RAND_MAX; // E(m1) --> E(m1)
    }
    for (j=1+400;j<25+400;j++){
      W[j][i]= valor2*rand()*1.0/RAND_MAX; //E(m1) --> I(m1)
    }
  }

//Modulo 2
  for (i=100;i<200;i++){
    for (j=100;j<200;j++){
      W[j][i]= valor*rand()*1.0/RAND_MAX;
    }
    for (j=25+400;j<50+400;j++){
      W[j][i]= valor2*rand()*1.0/RAND_MAX;    
    }
  }

//Modulo 3
  for (i=200;i<300;i++){
    for (j=200;j<300;j++){
      W[j][i]= valor*rand()*1.0/RAND_MAX;
    }
    for (j=50+400;j<75+400;j++){
      W[j][i]= valor2*rand()*1.0/RAND_MAX;    
    }
  }

//Modulo 4
  for (i=300;i<400;i++){
    for (j=300;j<400;j++){
      W[j][i]= valor*rand()*1.0/RAND_MAX;
    }
    for (j=75+400;j<100+400;j++){
      W[j][i]= valor2*rand()*1.0/RAND_MAX;
    }
  }





////Inibição Modular////

  //modulo 1
  for (i=1;i<100;i++){
    for (j=1+400;j<25+400;j++){              
      W[i][j]= f_inib2*rand()*1.0/RAND_MAX;  //I(m1)--> E(m1)
    }
  }

 // modulo 2
 for (i=100;i<200;i++){
   for (j=25+400;j<50+400;j++){
     W[i][j]= (f_inib2)*rand()*1.0/RAND_MAX;
    }
  }

  // modulo 3
  for (i=200;i<300;i++){
    for (j=50+400;j<75+400;j++){        
      W[i][j]= f_inib2*rand()*1.0/RAND_MAX;
    }
  }

  //modulo 4
  for (i=300;i<400;i++){
   for (j=75+400;j<100+400;j++){        
      W[i][j]= f_inib2*rand()*1.0/RAND_MAX;
    }
  }




}