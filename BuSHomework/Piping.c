#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

struct summanden_ {
	int a;
	int b;
};
void get_user_input(struct summanden_ *summanden){
	char a[20];
	printf("Gif me a numbaaah!\n");
	fgets(a, 20, stdin);
	summanden->a = atoi(a);
	printf("Gif me one moaaaah!\n");
	fgets(a, 20, stdin);
	summanden->b = atoi(a);
	printf("a = %i\n", summanden->a);
	printf("b = %i\n", summanden->b);
}
int sum(int *sum, struct summanden_ *summanden){
	if ((int)(summanden->a) == 0 && (int)(summanden->b) == 0){
		sum = 0;
		return -1;
	}
	else{
		*sum = (int)(summanden->a) + (int)(summanden->b);
		return 0;
	}
}
int child(int *vomrechner, int *zumrechner){
	struct summanden_ summanden;
	int summe;
	while(1){
		read(*zumrechner, &summanden, sizeof(struct summanden_));
		if (sum(&summe, &summanden) != 0){
			break;
		}
		else{
			write(*vomrechner, &summe, sizeof(summe));
		}
	}
	printf("Child closing!\n");
	return EXIT_SUCCESS;
}
int analyze_child_status(int process_id){
	int endID, status;
	endID = waitpid(process_id, &status, WNOHANG | WUNTRACED);
	if (endID == -1) {           
		perror("waitpid error");
		return -1;
	}
	else if (endID == 0) {        // child is running
		return 0;
	}
	else if (endID == process_id) {  // child isn't running
		if (WIFEXITED(status)){
			printf("Child ended normally.\n");
			return -1;
	    }
		else if (WIFSIGNALED(status)){
			printf("Child ended because of an uncaught signal.\n");
			return -1;
		}
		else if (WIFSTOPPED(status)){
			printf("Child process has stopped.\n");
			return -1;
		}
	}
	return -1;
}
int father(int *vomrechner, int *zumrechner, int pid){
	struct summanden_ summanden;
	int summe = 0;
	while (1){
		get_user_input(&summanden);
		write(*zumrechner, &summanden, sizeof(struct summanden_));
		read(*vomrechner, &summe, sizeof(int));
		usleep(100);
		if (analyze_child_status(pid) == 0){
			printf("the solution is: %i \n", summe);
		}
		else{
			printf("Vater finished!\n");
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
int main(void) {
	int vomrechner[2], zumrechner[2];
	int pid;
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
		return child(&vomrechner[1], &zumrechner[0]);
	}
	else { // Vater
		close(vomrechner[1]);
		close(zumrechner[0]);
			return father(&vomrechner[0], &zumrechner[1], pid);
	}
	return 0;
}