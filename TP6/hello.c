#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
{
   #pragma omp critical
   {
   printf("Bonjour ! %d\n",omp_get_thread_num());
   printf("Au revoir !%d\n",omp_get_thread_num());
   }
}

  return 0;
}
