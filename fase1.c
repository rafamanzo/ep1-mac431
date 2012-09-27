#include <stdio.h>

static long num_steps = 1000000;
double step;

void main (){
  int i; double x, pi, sum = 0.0;
  step = 1.0/(double) num_steps;

  #pragma omp parallel for reduction(+:sum) private(x)
  for (i=0;i < num_steps; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }

  pi = step * sum;
  printf("Pi = %g\n", pi);
}