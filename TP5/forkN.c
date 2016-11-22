#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>


int main (int argc, char *argv[])
{  
  int pid, n, nbth;

  n = atoi(argv[1]);
  for(int i = 0 ; i < n ; i++) {
    
    // cr�ation d'un nouveau processus fils...
    if( (pid = fork()) == 0) {      
      // le processus fils continue ici
      printf("fork du processus fils %d (pid = %d)\n",i, getpid());
      char param1[256];
      char param2[256];
      sprintf(param1,"%d",n);
      sprintf(param2,"%d",i);
      execl("/net/cremi/rdruon/prs/PRS/TP5/bin/nreines_partiel","nreines_partiel",param1,param2,NULL);
      perror("exec");
      return EXIT_SUCCESS; // fin du processus fils
    }
    
  }
  
  // le p�re attend tout ces fils
  for(int i = 0 ; i < n ; i++) {
    wait(NULL); // j'attend la fin de une de mes fils...
  }
  int file = open("/tmp/nreine",O_RDONLY);
  ssize_t lu = 0;
  int cpt = 0;
  int i = 0;
  while((lu = read(file,&i,sizeof(int))) > 0){
      cpt+=i;
  }
  printf("Resultat : %d\n",cpt);
  printf("fin du processus principal %d\n",getpid());
  
  return EXIT_SUCCESS;
}
