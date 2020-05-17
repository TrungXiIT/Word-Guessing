#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 100

int countLine(FILE *sourc);		//dem so dong trong file
int ran(int numOfWord);			//random so le
void getSecret(char *secretWord); 	//them dau *
void reset(int* turn, int* flag, int* test, int* conti, int *count);		//reset game
char readchar();				// doc ki tu
void printSuggest(int len, char *suggest, char *secretWord);

int main(){
	
	int i, len, turn = 10, flag = 0, test = 0, conti = 1,count = 0 , random, numOfWord;
	char input ;
	
	FILE* sourc = NULL;
	
	numOfWord = countLine(sourc);
	
	while(conti != 0){
		printf("\
				=== WELCOME TO THE LETTERING GAME ===\n\n\n\n");
		printf("\
					1. New Game\n\n\
					2. Level\n\n\
					3. ADD Secret Word\n\n\n\n\n\n\
					0. Exit\n\n\n\n\
					Choose an option: ");
		scanf("%d", &conti);
		if(conti == 0) break;
		system("cls");
		char* secretWord;
		char secret[MAX];
		char suggest[200];
		
		if(turn == 0) break;
		
		srand(time(NULL));
		do {
			srand(time(NULL));	
			random = (rand() % numOfWord);
		}while(random % 2 != 1);
		//random = ran(numOfWord);
		
		printf("%d", random);
		
		sourc = fopen("SOURCE WORD.txt", "r");
	
		for(i = 1; i <= random; i++)
			fgets(secret, MAX, sourc);
			
		fgets(suggest, 200, sourc);
	
		len = strlen(secret);
		secret[len-1] = '\0';
		secretWord = strdup(secret);
		len = strlen(secretWord);
		
		getSecret(secretWord);
		printSuggest(len, suggest, secretWord);
			
		while(turn > 0){			//lap lai khi chua doan xong
			
			input = readchar();
			system("cls");
			for(i = 0; i < len; i++){
				if (secret[i] == input){
					secretWord[i] = input;
					flag ++;
				}
			}
			// kiem tra dung sai
			if(flag == 0){
				turn --;
				if(turn == 0){
					printf("\n\n\n\n\n\n\n\
					GAME OVER!!!\n\n\n\n\
					You guessed EXACTLY %d times, WRONG %d times\n\n\n\n\n\n\
					PRESS ANYKEY to CONTINE . . . ", count, turn);
					getch();
					reset(&turn, &flag, &test, &conti, &count);
					break;	
				}
				printSuggest(len, suggest, secretWord);
				
				printf("\
					Wrong character. Please try again!\n\n\
					You have %d guess.\n\n\n\n",turn);
			}
			else if(flag != 0){
				
				printSuggest(len, suggest, secretWord);
				printf("\
					Guess exactly %d character!\n\n\
					You have %d guess.\n\n\n\n", flag, turn);
				flag = 0;
				if(strcmp(secretWord, secret) == 0){
					system("cls");
					printf("\n\n\n\n\n\n\n\
					YOU WON!!!\n\n\
					You guessed EXACTLY %d time, WRONG %d times\n\n\n\n\n\
					PRESS ANYKEY to CONTINE . . . ", turn,count);
					getch();
					reset(&turn, &flag, &test, &conti, &count);
					break;	
				}
			}	
		}
		free(secretWord);
	}
	return 0;
}

	
int countLine(FILE *sourc){
	int numOfWord = 0;
	char testC;
	sourc = fopen("SOURCE WORD.txt", "r");
	
	do{
		testC = fgetc(sourc);
		if(testC == '\n')
			numOfWord ++;
	}while(testC != EOF);
		printf("%d", numOfWord);
		
	fclose(sourc);
	return numOfWord;
}

void getSecret(char *secretWord){
	int i, n = strlen(secretWord);
	
	for(i = 0; i < n; i++)		
			secretWord[i] = '*';
}

char readchar(){ 
	char ch;
	fflush(stdin);
	printf("\
					What is the Sercet Word: ");
	scanf("%c",&ch);
	fflush(stdin);
	
	ch = toupper(ch);
	return ch;
}
void printSuggest(int len, char *suggest, char *secretWord){
	printf("\n\n\n\n\
					Secret Word include %d characters.\n\n\
					SUGGESTIONE: %s\n\n\
					Secret Word: %s \n\n\n\n\n",len ,suggest,secretWord);
}
void reset(int* turn, int* flag, int* test, int* conti, int *count){
	*turn = 10;
	*flag = 0;
	*test = 0;
	*conti = 1;
	*count = 0;
	system("cls");
}
