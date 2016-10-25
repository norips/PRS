#define _GNU_SOURCE

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define NCOMMANDES 4

#define SIG_CURRENT SIGCHLD
struct etat
{
  pid_t pid;
  char commande[10];
  char arg[10];
  int etat;
};

typedef struct etat* etat;


etat etat_tableau[NCOMMANDES];


char *commandes[NCOMMANDES][10]={
  {"sleep","0",NULL}, 
  {"sleep","3",NULL}, 
  {"sleep","4",NULL}, 
  {"sleep","5", NULL} 
};

void afficher_etat()
{
  int i;
  
  for ( i=0;i<NCOMMANDES;i++)
    {
      switch(etat_tableau[i]->etat)
	{
	case 3:
	  printf("%d : Stoppé %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 2:
	  printf("%d : Continué %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;

	case 1:
	  printf("%d : En cours %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;
	  
	case 0:
	  printf("%d : Terminé %s(%s)\n",etat_tableau[i]->pid,etat_tableau[i]->commande,etat_tableau[i]->arg);
	  break;
	  
	}
    }
  printf("\n");
}

int reste_commande()
{
  int i;
  
  for (i=0;i<NCOMMANDES;i++)
    {
      if(etat_tableau[i]->etat)
	return 1;
    }
  return 0;
}

void timer()
{
 struct itimerval time;
  time.it_interval.tv_sec=0;
  time.it_interval.tv_usec=500000;
  time.it_value.tv_sec=0;
  time.it_value.tv_usec=500000;
  setitimer(ITIMER_REAL,&time,NULL);
}
void routine(int signo){
    if(signo == SIG_CURRENT){
        afficher_etat();
    }
}

int
main(int argc, char *argv[])
{
  pid_t cpid, w;
  int status;
  
  int i;
  /* Lancement */
  struct sigaction s;
  s.sa_handler = routine;
  s.sa_flags = 0;
  sigemptyset(&s.sa_mask);
  //Receive SIGALRM
  sigaction(SIG_CURRENT,&s,NULL);
  
#if SIG_CURRENT == SIGALRM
  sigset_t mask, old_mask;
  sigemptyset(&mask);
  sigaddset(&mask,SIG_CURRENT);
  //Block SIGALRM
  sigprocmask(SIG_BLOCK,&mask,&old_mask);
  timer();
#endif
  for(i=0; i < NCOMMANDES; i++)
    {
      cpid = fork();
      if (cpid == -1) {
	perror("fork");
	exit(EXIT_FAILURE);
	
      }
      
      if (cpid == 0) {  
	execvp(commandes[i][0],commandes[i]);
	perror("execvp");
	abort();
      } 
      
      etat_tableau[i]=malloc(sizeof(struct etat));
      etat_tableau[i]->pid=cpid;
      strcpy(etat_tableau[i]->commande,commandes[i][0]);
      strcpy(etat_tableau[i]->arg,commandes[i][1]);
      etat_tableau[i]->etat=1; /* en cours */
    }
  
  /* Analyse */
  while(reste_commande())
    {
#if SIG_CURRENT == SIGALRM
      sigsuspend(&old_mask);
#endif
      w = waitpid(0, &status, WUNTRACED | WCONTINUED);
      fprintf(stderr,"wait : %d\n",w);
      perror("wait");

      if (w > 0) {
	for(i=0; i < NCOMMANDES ; i++)
	  if(etat_tableau[i]->pid == w) 
	    break;
     
	if (WIFEXITED(status)) {
	etat_tableau[i]->etat=0; 
	} else if (WIFSIGNALED(status)) {
	  etat_tableau[i]->etat=0; 
	} else if (WIFSTOPPED(status)) {
	  etat_tableau[i]->etat=3; 
	} else if (WIFCONTINUED(status)) {
	  etat_tableau[i]->etat=2; 
	}
      }
    }
  afficher_etat();
  printf("Tous les processus se sont terminés !\n");
  
  exit(EXIT_SUCCESS);
}
