#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                int master_thread_id = omp_get_thread_num();
                printf("Master Thread ID: %d\n", master_thread_id);
            }

            #pragma omp section
            {
                int thread_id = omp_get_thread_num();
                printf("Thread ID: %d\n", thread_id);
            }
        }
    }

    return 0;
}