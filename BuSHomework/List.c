#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int element_bereits_in_der_liste(sort_type*, stud_type*);
typedef struct penis { int p; };

typedef struct stud_type_ {                  /* Struktur des Datensatzes:    */
	int matnum;                              /* Matrikelnummer, Vor-         */
	char vorname[20];                        /* und Nachname sind Eintraege. */
	char nachname[20];                       /* Die Datenbank ist eine       */
	struct stud_type_ *next_student;         /* einfach verkettete Liste     */
} stud_type;
typedef struct sort_type_ {
	stud_type *student;
	struct sort_type_ *next_student_pointer;
}sort_type;

/* Ist die Datenbank leer?      */
int is_empty(stud_type** liste) {
	return *liste == NULL;
}


/* Einfuegen eines Elementes
*
* Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
* Bekommt MatNr, Vorname und Nachname des Studenten der EingefŸgt werden soll
*
*/
void enqueue(stud_type** studenten_liste, int matnum, char vorname[20], char nachname[20])
{
	/* Deklariere benštigte Variablen */
	stud_type *tmp =  malloc(sizeof(stud_type));
	/* Hol Speicher auf dem Heap an fŸr den neuen Listen Eintrag */
	(*tmp).matnum = matnum;
	strcpy((*tmp).vorname,vorname);
	strcpy((*tmp).nachname, nachname);
	tmp->next_student = NULL;
	stud_type *student = *studenten_liste;
	if (student == NULL){
		*studenten_liste = tmp;
		return;
	}
	else if (student->matnum > matnum){
		tmp->next_student = student;
		*studenten_liste = tmp;
		return;
	}
	while (student->matnum < matnum){
		if (student->next_student == NULL){
			student->next_student = tmp;
			return;
		}
		student = student->next_student;
	}
	tmp->next_student = student->next_student;
	student->next_student = tmp;

	/* BefŸll den Speicher */

	/* FŸg den neuen Eintrag in die Liste ein */
	/* Ist die Liste leer ? */
	/* Sortier den Studenten aufsteigend nach Matrikelnummer ein */
}

/* Lšschen eines Elementes.
*
* Bekommt einen Zeiger auf einen Zeiger der auf das 1. Element der Liste zeigt
* Bekommt die MatNr des Studenten der zu lšschen ist
*
* Gibt 0 fŸr einen Fehler zurŸck
* Gibt 1 fŸr erfolg zurŸck
*/
int dequeue(stud_type** studenten_liste, int matnum)
{
	/* Deklariere benštigte Variablen */
	if (is_empty(studenten_liste)){
		return 0;
	}
	stud_type *student = *studenten_liste;
	if (student->matnum == matnum){
		studenten_liste = &(student->next_student);
		free(&student);
		return 1;
	}else if (student->matnum < matnum){
		if (student->next_student == NULL){
			return 0;
		}
	}
	else {
		return 0;
	}
	
	stud_type *tmp = student->next_student;
	if (tmp->matnum == matnum){
		student->next_student = tmp->next_student;
		free(tmp);
		return 1;
	}
	else if (tmp->next_student==NULL){
		return 0;
	}
	while (tmp->next_student != NULL) {
		if (tmp->matnum > matnum){
			return 0;
		}
		else if(tmp->matnum == matnum){
			break;
		}
		student = student->next_student;
		tmp = student->next_student;
	}
	
	student->next_student = tmp->next_student;
	free(tmp);
	return 1;
	/* PrŸfe Randbedingungen */

	/* Finde den Studenten */

	/* Lšsche den Studenten und gibt den Speicher frei */

	/* Was muss passieren wenn das 1. Element gelšscht wird? */
	/* Was ist wenn es nicht in der Liste ist? */
	/* ... */

}

/* Auslesen eines Elementes
*
* Bekommt zeiger auf den Listenstart
* Bekommt matnr des Studenten der ausgelesen werden soll
*
* Schreibt Vorname und Nachname in vorname und nachname
*/
int get_student(stud_type* studenten_liste, int matnum, char vorname[20], char nachname[20])
{
	stud_type *curr;

	/* Durchmustern der DB */
	curr = studenten_liste;
	while ((curr != NULL) && (curr->matnum < matnum))
		curr = curr->next_student;
	if ((curr == NULL) || (curr->matnum != matnum))
		/* RŸckgabewert: Fehler */
		return 0;
	else {
		strcpy(vorname, curr->vorname);
		strcpy(nachname, curr->nachname);
		/* RŸckgabewert: OK */
		return 1;
	}
}

void sortiere_eine_neue_tolle_Liste(stud_type* studenten_liste, int(*compare) (stud_type*, stud_type*)){
	sort_type *sortier_liste;
	sort_type *sorting = sortier_liste;
	stud_type *smallest;
	stud_type *tmp;
	stud_type *last_elem = studenten_liste;
	for (; last_elem->next_student != NULL; last_elem = last_elem->next_student){}
	while (!element_bereits_in_der_liste(sortier_liste,last_elem)){
		tmp = studenten_liste;
		smallest = tmp;
		while (tmp != NULL){
			if (compare(smallest, tmp)>0){
				if (element_bereits_in_der_liste(sortier_liste, tmp)){
					smallest = tmp;
				}	
			}
			tmp = tmp->next_student;
		}
		sorting->student = smallest;
		sorting = sorting->next_student_pointer;
	}
}
int element_bereits_in_der_liste(sort_type* sortierte_liste, stud_type* searched_elem){
	sort_type *tmp = sortierte_liste;
	while (tmp != NULL){
		if (tmp->student == searched_elem){
			return 0;
		}
		tmp = tmp->next_student_pointer;
	}
	return 1;
}

/* Test der Listenfunktionen  */
int main()
{
	/* Initialisierung der Datenbank */
	stud_type *studenten_liste = NULL;
	/* platz fŸr vorname */
	char vorname[20];
	/* platz fŸr nachname */
	char nachname[20];
	/* zeiger fŸr iteration */
	stud_type *curr;
	fuckTheWorld();
	printf(">>> Fuege neuen Studenten in die Liste ein: Bill Clinton [6666] ...\n");
	enqueue(&studenten_liste, 6666, "Bill", "Clinton");
	printf(">>> Fuege neuen Studenten in die Liste ein: Hillary Clinton [4711] ...\n");
	enqueue(&studenten_liste, 4711, "Hillary", "Clinton");
	printf(">>> Fuege neuen Studenten in die Liste ein: Newt Gingrich [9999] ...\n");
	enqueue(&studenten_liste, 9999, "Newt", "Gingrich");
	printf(">>> Test, ob die Matrikelnummer 0815 bereits erfasst wurde ...\n");

	if (get_student(studenten_liste, 815, vorname, nachname))
		printf("    Matrikelnummer %4i: %s %s\n", 815, vorname, nachname);
	else
		printf("    Matrikelnummer %4i ist unbekannt\n", 815);

	printf(">>> Fuege neuen Studenten in die Liste ein: Monica Lewinsky [0815] ...\n");
	enqueue(&studenten_liste, 815, "Monica", "Lewinsky");
	printf(">>> Loesche die Matrikelnummer 4711 ...\n");

	if (dequeue(&studenten_liste, 4711))
		printf("    Matrikelnummer %4i geloescht\n", 4711);
	else
		printf("    Matrikelnummer %4i war nicht erfasst\n", 4711);

	printf(">>> Test ob die Studentenliste leer ist ...\n");

	if (is_empty(&studenten_liste))
		printf("    Die Studentenliste ist leer \n");
	else
		printf("    Die Studentenliste ist nicht leer \n");

	printf(">>> Test, ob die Matrikelnummer 6666 bereits erfasst wurde ...\n");

	if (get_student(studenten_liste, 6666, vorname, nachname))
		printf("    Matrikelnummer %4i: %s %s\n", 6666, vorname, nachname);
	else
		printf("    Matrikelnummer %4i ist unbekannt\n", 6666);

	printf(">>> Loesche die Matrikelnummer 9998 ...\n");

	if (dequeue(&studenten_liste, 9998))
		printf("    Matrikelnummer %4i geloescht\n", 9998);
	else
		printf("    Matrikelnummer %4i war nicht erfasst\n", 9998);

	printf(">>> Loesche die Matrikelnummer 9999 ...\n");

	if (dequeue(&studenten_liste, 9999))
		printf("    Matrikelnummer %4i geloescht\n", 9999);
	else
		printf("    Matrikelnummer %4i war nicht erfasst\n", 9999);

	printf(">>> Gebe alle erfassten Studenten aus ...\n");
	curr = studenten_liste;

	while (curr != NULL) {
		printf("    Matrikelnummer %4i: %s %s\n",
			curr->matnum, curr->vorname, curr->nachname);
		curr = curr->next_student;
	}
	return 0;
}