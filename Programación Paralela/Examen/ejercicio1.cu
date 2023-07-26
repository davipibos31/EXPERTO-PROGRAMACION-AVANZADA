#include <omp.h>

int main() {
   double a[1000], b[1000], c[1000];

   #pragma omp parallel for
   for(int i = 0; i < 1000; i++) {
      a[i] = b[i] + c[i];
   }

   return 0;
}
