#define _CRT_SECURE_NO_DEPRECATE
/*#define _CRT_NONSTDC_NO_DEPRECATE*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#ifdef __unix__
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifndef _open
#define open _open
#endif
#ifndef _read
#define read _read
#endif
#elif __MSDOS__ || __WIN32__ || _MSC_VER
#include <io.h>
#include <sys\stat.h>
#endif
char decodeChar(char);
#include <fcntl.h>
#define BUFFER_SIZE 1
/*int main(int argc, char* argv[]){
	char buffer [BUFFER_SIZE];
	int file;
	int bytes_read = 1;
	if ((file = _open("obfuscated.txt", O_TEXT)) == -1) {
		printf("Error opening file : %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(bytes_read != 0){
		bytes_read = _read(file, buffer, BUFFER_SIZE);
		printf("%c", decodeChar(buffer[0]));
		if (bytes_read<0){
			printf("Error reading file : %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}
char decodeChar(char coded){
	int c = (int)coded;
	if (c > 64 && c < 91){
		c = ((c - 64 + 13) % 26) + 64;
	}
	else if (c > 96 && c < 123){
		c = ((c - 96 + 13) % 26) + 96;
	}
	return (char)c;
}*/
/*
FILE *file;
FILE *decodedFile;
char decodeChar(char);
int main(int argc, char* argv[]){
	file = fopen("obfuscated.txt", "rt");
	decodedFile = fopen("decoded.txt", "w");
	if (file == NULL) {
		fprintf(stderr, "Can't open coded file! Error: %d \n",errno);
		exit(1);
	}
	if (decodedFile == NULL) {
		fprintf(stderr, "Can't open decoded file! Error: %d \n",errno);
		exit(1);
	}
	char coded = getc(file);
	while (coded != EOF){
		fprintf(decodedFile, "%c", decodeChar(coded));//printf("%c", decodeChar(coded));
		coded = getc(file);
	}
	fclose(file);
	fclose(decodedFile);
	
}
*/