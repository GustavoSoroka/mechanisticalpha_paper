
double ensembles(int N, int *r1, int *r2, int *r3, int* r4){

  *r1= 100 ;//((N-1))/10;
  *r2= 200   ;//*r1+ (N-1)/10;
  *r3= 300  ;//*r1 + 2*(N-1)/10;
  *r4= 400   ;//*r1 + 3*(N-1)/10;
}



//basicamente divide metade do numero total de neuronios em 5 ensembles
//fiz uma função separada pois pensei que poderia usar em algum outro processo