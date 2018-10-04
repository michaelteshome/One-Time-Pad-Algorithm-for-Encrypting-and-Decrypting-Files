/*
Michael Teshome, G-Number: 01028913
CS262 Project 1 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void createEncryption(FILE *finward, char *);
void decryption(char *, FILE *fd);
int main(int argc, char *argv[]){
	int i;
	//int j;// iteration variable 
	FILE *fin = NULL; //input file
	FILE *fout = NULL; //output file
	int keys = atoi(argv[1]);// converts key into an int so that seeding the random will successfully work.
	
	if(argc != 5){
		exit(1);
	}

	//this for loop iterates through all four command-line 
	for(i = 1 ; i < argc; i++){
		printf("Arguement %d contains: %s \n", i, argv[i]);
	}

	srandom(keys);
	//Encryption 
	if(strcmp("ENCRYPT", argv[2]) == 0 && argv[2][0] == 'E'){
		fin = fopen(argv[3], "r");
		if(fin == NULL){
			printf("Couldn't Find File");
			exit(1);
		}
		fputs(argv[1], fin);
		createEncryption(fin, argv[4]);	
		fclose(fin);
		
	}


	//Decryption
	else if(strcmp("DECRYPT", argv[2]) == 0){
		fout = fopen(argv[4], "w");
		if(fout == NULL){
			printf("Couldn't Find File");
			exit(1);
		}
		decryption(argv[3], fout);
		fclose(fout);
		//decryption(argv[3]);
	}
	
	else{
		printf("Invalid Argumnets for ENCRYPTR/DECRYPT"); 
		exit(1);//if there are no command-line arguments for ENCRYPT/DECRYPT mode, then we exit the program.
	}


}


void createEncryption(FILE *finward, char *arout){
	char p;
	char c;
	char r;// random iterator variable
	char p1;// counter varaible for plaintext
	char c1;// counter variable for ciphertext
	FILE *fileout;//declares a local FILE pointer to reference arguement 4 which is out.enc
	fileout = fopen(arout, "w");
	if(fileout == NULL){
		printf("Error couldn't find file");
		exit(1);
	}
	while(fscanf(finward,"%c",&p) != EOF){
		r = random() % 97;
		if(p == '\t'){
			p1 = 0;
		}
		else if(p == '\n'){
			p1 = 1;
		}
		else{
			p1 = p - 30;
		}
		c1 = (p1 + r) % 97;
		if(c1 == 0){
			c = '\t';
			fprintf(fileout, "%c", c);
		}
		else if(c1 == 1){
			c = '\n';
			fprintf(fileout, "%c", c);
		}
		else{
			c = c1 + 30;
			fprintf(fileout, "%c", c);
		}
		//fprintf(fileout, "%c", c);

	}
	fclose(fileout);

	

}


void decryption(char *df, FILE *fd){
	FILE *dout = NULL; //declares FILE pointer
	dout = fopen(df, "r");// opens the pass by reference input file
	char p;
	char c;
	char r;
	char p1;//used for the algorithm when evaluating plaintext characters.
	char c1;//used for the algorithm when evaluating ciphertext characters.
	if(dout == NULL){
		printf("Error finding file");
		exit(1);
	}

	while(fscanf(dout, "%c", &p) != EOF){
		r = random() % 97;
		if(p == '\t'){
			p1 = 0;
		}
		else if(p == '\n'){
			p1 = 1;
		}
		else{
			p1 = p - 30;
		}
		c1 = (p1 + 97 - r) % 97;
		if(c1 == 0){
			c = '\t';
			fprintf(fd, "%c", c);
		}
		else if(c1 == 1){
			c = '\n';
			fprintf(fd, "%c", c);
		}
		else {
			c = c1 + 30;
			fprintf(fd, "%c", c);
		}
	}
	fclose(dout);
	
	
}


