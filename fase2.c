#include <stdlib.h>
#include <stdio.h>

double step;

void main (int argc, char *argv[]){
  double step, pi, x, sum, partial_sum;
  int num_threads, steps_per_thread, thread_num;
  long num_steps, beginning, end, i;

  num_threads = omp_get_num_procs()*omp_get_num_procs();
  omp_set_num_threads(num_threads);

  //partial_sum = malloc(num_threads*sizeof(double));

  num_steps = atoi(argv[1]);
  steps_per_thread = num_steps/num_threads;
  step = 1.0/(double) num_steps;

  sum = 0.0;
  #pragma omp parallel private(i, thread_num, x, partial_sum, beginning, end) reduction(+:sum)
  {
    thread_num = omp_get_thread_num();

    partial_sum = 0.0;
    beginning = (thread_num*steps_per_thread);
    end = beginning + steps_per_thread;

    for(i = beginning; i < end; i++){
      x = (i+0.5)*step;
      partial_sum += 4.0/(1+x*x);
    }

    sum += partial_sum;
  }

  printf("Pi = %g\n", step * sum);
}