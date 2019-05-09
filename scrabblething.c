#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addWord(char gameBoard[21][21],char word[20],char dir,int length,int row,int col){
	int i;
	
	if(dir == 'd'){	
				
		for (i=0;i < length;i++){
			
		gameBoard[row+i][col] = word[i];		
		}
	} 
	if (dir == 'a'){
		for (i=0;i<length;i++){
			
				gameBoard[row][col+i] = word[i];
		}		
		
	} 
}

//if word is valid, returns 0. If not valid, returns 1
int checkWord(char gameBoard[21][21],char word[20],char dir,int length,int row,int col)
{
	int valid = 0;
	int i;
	
	if(dir == 'd'){
		for(i = 0;i < length;i++){
			if(gameBoard[row+i][col] == '.'){
				continue;
			} else if(gameBoard[row+i][col] == word[i]){
				continue;
			} else {
				valid++;
			}			
		}
		return valid;
	}
	if(dir == 'a'){
		for(i = 0;i < length;i++){
			if(gameBoard[row][col+i] == '.'){
				continue;
			} else if(gameBoard[row][col+i] == word[i]){
				continue;
			} else {
				valid++;
			}				
		}
		return valid;
	}	
}

int dictionaryCheck(char word[20], char *dictionary, int dictionaryLength, int *offsets){
			
			int match = 0;
			
			for(int wordIndex = 0; wordIndex < dictionaryLength; wordIndex++){

				if (strcmp(word, (char *)(dictionary + offsets[wordIndex])) == 0){
					match = 1;
					break;
				}	
			}
			return match;
}

int scoreWord(char word[20], int length){
	int letterValues[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10}; 
	int x,total;
	
	for(int i = 0;i<length;i++){
		x = (int)word[i] - 97;
		total = total + letterValues[x];
	}
	return total;
}

void printScrabble(char board[21][21]){
	printf("   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21\n");
	for (int i=0;i < 21;i++){
		printf("%2d", i+1); 
		for (int j=0;j < 21;j++){
			
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}		
}

int main(int argc, char * argv[]){

	int row,col,i,j,wordLength,playerCount,points,N;
	int x = 1;
	char scrabbleBoard[21][21];
	char direction;
	char word[20];
	int playerScore[20] = {0};
	
		
	char line[100];
	
	char *wordListData; 
	int *wordListOffsets;
	int dictionaryWordCount = 0;
	int wordListLength = 1000;	 
	int dataSize = 1024;	
	int wordIndex = 0;
	int byteCount = 0;
	
	wordListData = malloc(dataSize); 
	wordListOffsets = malloc(wordListLength * sizeof(int));
	
	
	FILE *wordList;
	wordList = fopen("GameWordList","r");
	
	if (wordList == NULL){
		printf("Dictionary file does not exist!\n");
		printf("Now exiting program.\n");
	 	exit(0);
	}
	
	while(! feof(wordList)){	
		fgets(line,100,wordList);
		
		sscanf(line, "%50s", word);
		
		if (wordIndex >= wordListLength){
			wordListLength = wordListLength * 2;
			wordListOffsets = realloc(wordListOffsets, wordListLength * sizeof(int));
		}
	
		wordListOffsets[wordIndex] = byteCount;
		
		byteCount = byteCount + strlen(word) + 1;
		
		if (byteCount > dataSize){ 
			dataSize = dataSize * 2;
			wordListData = realloc(wordListData, dataSize);
		}
		
		strcpy(wordListData + wordListOffsets[wordIndex], word); 
		
		wordIndex++;
	}	
	
	dictionaryWordCount = wordIndex;
	fclose(wordList);
	

	for (i=0;i < 21;i++){
		for (j=0;j < 21;j++){
			scrabbleBoard[i][j] = '.';
		}	
	}
	
	

	word[0] = '\0';


	printf("How many players? ");
	scanf("%d", &playerCount);
	
	system("clear");
	printScrabble(scrabbleBoard);
	x = playerCount;

 while(1){
	
	points = 0;
	N = x % playerCount + 1;

	printf("Currently Player %d's turn.\n", N);	
	printf("Enter row: ");
	scanf("%d", &row);
	row--; 
	printf("Enter column: ");
	scanf("%d", &col);
	col--;
	printf("Enter (d)own or (a)cross: ");
	scanf(" %c", &direction);
	
	if (direction != 'd' && direction != 'a'){
		printf("Direction not valid! Try again.\n");
		continue;
	}

	printf("Enter word: ");
	scanf("%s", word);
	wordLength = strlen(word);

	if(checkWord(scrabbleBoard,word,direction,wordLength,row,col) == 0 &&
	   dictionaryCheck(word, wordListData, dictionaryWordCount, wordListOffsets) == 1){
		system("clear");
		addWord(scrabbleBoard,word,direction,wordLength,row,col);
		points = scoreWord(word,wordLength);
		printScrabble(scrabbleBoard);
	} else {
		system("clear");
		printScrabble(scrabbleBoard);
		printf("Not a valid word! Try again.\n");
	}		
		
	if(points > 0){	
		
		playerScore[N] = playerScore[N] + points;
	
		printf("Your word scored %d points!\n====================\nCurrent Score\n", points);
		for(int z = 1;z <= playerCount;z++){
			printf("Player %d: %d points\n", z, playerScore[z]);
	
		}
		printf("====================\n");
		x++;
	
	
	}
 }
}
