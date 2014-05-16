/* thread1.c */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int i = 1;

static void *bullshit(void* val) {
	for (; i <= 50; i++){
		if (i <= 25){
			usleep(300);
		}
		else{
			usleep(rand() % 400 + 100);
		}
		printf("Child: %i", i);
	}
	return NULL;
}
void start_threading(){
	pthread_t thread;
	srand(time(NULL));
	for (; i <= 50; i++){
		if (i <= 25){
			if (i == 9){
				if (pthread_create(&thread, NULL, &bullshit, NULL) != 0){
					printf("Thread failed");
					printf(strerror(errno));
					return EXIT_FAILURE;
				}
			}
			usleep(300);
		}
		else{
			usleep(rand() % 400 + 100);
		}
		printf("Mother of threads: %i", i);
	}
	pthread_join(thread, NULL);
}
int main(void) {
	pthread_t thread1, thread2;
	int i, rc;

	// Ausgabe in eine Textdatei
	freopen("myoutput.txt", "w+", stdout);

	printf("Haupt-Thread main() wurde gestartet\n");
	// beide Arrays mit Werten initialisieren
	init_test_array(test_array1);
	init_test_array(test_array2);
	// Thread 1 erzeugen
	rc = pthread_create(&thread1, NULL, &bubble1, NULL);
	if (rc != 0) {
		printf("Konnte Thread 1 nicht erzeugen\n");
		return EXIT_FAILURE;
	}
	// Thread 2 erzeugen
	rc = pthread_create(&thread2, NULL, &bubble2, NULL);
	if (rc != 0) {
		printf("Konnte Thread 2 nicht erzeugen\n");
		return EXIT_FAILURE;
	}
	// Main-Thread wartet auf beide Threads.
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// das Ergebnis der Sortierung in die Datei
	// myoutput.txt schreiben
	for (i = 0; i < MAX; i++) {
		printf("[%d-%d]", test_array1[i], test_array2[i]);
	}
	printf("\nHaupt-Thread main() wurde beendet\n");
	return EXIT_SUCCESS;
}