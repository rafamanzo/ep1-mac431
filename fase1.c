#include <stdlib.h>
#include <stdio.h>

static long num_steps = 1000000;
double step;

void main (){
  int i, j; double x, pi, sum = 0.0;
  step = 1.0/(double) num_steps;
  int iam, np, sum_j = 0;

  #pragma omp parallel for reduction(+:sum)
  for (i=0;i < num_steps; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }

  pi = step * sum;
  printf("Pi = %g\n", pi);

  /*#pragma omp parallel for reduction(+:sum_j)
  for (j=0;j < num_steps; j++){
    sum_j += j;
  }

  printf("S = %d\n", sum_j);

  #pragma omp parallel default(shared) private(iam, np)
  {
    #if defined (_OPENMP)
      np = omp_get_num_threads();
      iam = omp_get_thread_num();
    #endif
    printf("Hello from thread %d out of %d\n", iam, np);
  }*/
}