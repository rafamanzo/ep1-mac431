#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t sum_mutex = PTHREAD_MUTEX_INITIALIZER;
double sum;
double step;
int num_threads;
long num_steps, steps_per_thread;

void *calc_partial_sum(void *id){
  long beginning, end, i;
  int thread_num = *((int *) id);
  double x, partial_sum = 0.0;

  beginning = (thread_num*steps_per_thread);
  end = beginning + steps_per_thread;

  for(i = beginning; i < end; i++){
    x = (i+0.5)*step;
    partial_sum += 4.0/(1+x*x);
  }

  pthread_mutex_lock(&sum_mutex);
  sum += partial_sum;
  pthread_mutex_unlock(&sum_mutex);
}

void main(int argc, char *argv[]){
  long i;
  int *thread_id;
  pthread_t *threads;

  num_threads = sysconf( _SC_NPROCESSORS_ONLN )*sysconf( _SC_NPROCESSORS_ONLN );

  num_steps = atoi(argv[1]);
  steps_per_thread = num_steps/num_threads;
  step = 1.0/(double) num_steps;

  threads = malloc(num_threads*sizeof(pthread_t));
  thread_id = malloc(num_threads*sizeof(int));
  sum = 0.0;

  for(i = 0; i < num_threads; i++){
    thread_id[i] = i;
    pthread_create(&(threads[i]), NULL, calc_partial_sum, (void *) (&(thread_id[i])));
  }

  for(i = 0; i < num_threads; i++)
    pthread_join(threads[i], NULL);

  free(threads);
  free(thread_id);

  printf("Pi = %g\n", step * sum);
}