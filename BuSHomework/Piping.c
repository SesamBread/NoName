#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

struct summanden_ {
	int a;
	int b;
};
void get_user_iput(struct summanden_ *summanden){
	char* a; 
	printf("Gif me a numbaaah!");

	fgets(a, 10, stdin);
	summanden->a = atoi(a);
	printf("Gif me one moaaaah!");
	fgets(a, 10, stdin);
	summanden->b = atoi(a);
}
int sum(int *sum, struct summanden_ *summanden){
	if (summanden->a + summanden->b == 0){
		sum = 0;
		return -1;
	}
	else{
		sum = summanden->a + summanden->b;
		return 0;
	}
}
int child(int *vomrechner, int *zumrechner){
	struct summanden_ *summanden;
	read(*zumrechner, summanden, sizeof(struct summanden_));
	int summe;
	if (sum(summe, summanden) != 0){
		//close this shit
	}
	else{
		write(*vomrechner, &summe, sizeof(summe));
	}
	/* Hier Code */
}
int father(int *vomrechner, int *zumrechner, int pid, int endID, int status){
	struct summanden_ summanden;
	get_user_input(&summanden);
	write(*zumrechner, &summanden, sizeof(struct summanden_));
	int *summe;
	read(*vomrechner, summe, sizeof(int));
	printf("Das Ergebnis ist %i", *summe);

	endID = waitpid(pid, &status, WNOHANG | WUNTRACED);
	if (endID == -1) {            /* error calling waitpid       */
		perror("waitpid error");
		return -1;
	}
	else if (endID == 0) {        /* child still running         */

	}
	else if (endID == pid) {  /* child ended                 */
		if (WIFEXITED(status))
			printf("Child ended normally.n");
		else if (WIFSIGNALED(status))
			printf("Child ended because of an uncaught signal.n");
		else if (WIFSTOPPED(status))
			printf("Child process has stopped.n");
		printf("Vater fertig");
		return 0;
	}
}
int main(void) {
	int vomrechner[2], zumrechner[2];
	int pid, endID, status;
	char buf[20];
	struct summanden_ summanden;
	int summe;
	int nbytes;

	if ((pipe(vomrechner) != 0) || (pipe(zumrechner) != 0)) {
		printf("pipe(): %d %s\n", errno, strerror(errno));
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		printf("fork(): %d %s\n", errno, strerror(errno));
		exit(1);
	}
	else if (pid == 0) { // Kind
		close(vomrechner[0]);
		close(zumrechner[1]);
		child(vomrechner[1], zumrechner[0]);//Mit und oder ohne?!
	}
	else { // Vater
		close(vomrechner[1]);
		close(zumrechner[0]);
		if (father(vomrechner[0], zumrechner[1], pid, endID, status)!=0)
		return EXIT_FAILURE;
		return EXIT_SUCCESS;
}