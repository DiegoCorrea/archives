# include <stdio.h>
# include <iostream>
# include <string.h>
# include <vector>
# include <algorithm>

# define SEARCH 's'
# define PRINT 'u'
# define EXIT 'e'
# define ALPHABETSIZE 29

void printVector(char*v);
//std::vector<char> alphabetExtract(char *pattern);

int wordState(char *pattern, int state, char letter);
void computeTransitionFunction(char *pattern, char *text, char *alphabet, int table[][ALPHABETSIZE]);
void finiteAutomatonMatcher(int textLength, char *text, char *pattern, char *alphabet, int table[][ALPHABETSIZE]);

void putThingsOnTable(int table[][ALPHABETSIZE], char *alphabet, char *pattern);
void printTable(int table[][ALPHABETSIZE], char *alphabet, char *pattern);

int main(){
	int textLength;
	scanf("%d", &textLength);
	getchar();
	//printf("%d\n", textLength);

	char pattern[textLength];
	char choice = 'a';
	char text[textLength];	

	scanf("%[^\n]", text);
	getchar();
	//printVector(text);
	scanf("%[^\n]", pattern);
	getchar();
	//printVector(pattern);

	char alphabet[ALPHABETSIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.',',',' '};

	int states = strlen(pattern)+1;
	int table[states][ALPHABETSIZE];
	putThingsOnTable(table, alphabet, pattern);

	//text[textLength+1] = '\0';
	computeTransitionFunction(pattern,text,alphabet,table);

	while(choice != EXIT){
		scanf("%c", &choice);
		getchar();
		//printf("A operação escolhida foi: ");

		switch(choice){
			case SEARCH:
				//printf("BUSCAR PADRÃO\n");
				finiteAutomatonMatcher(textLength,text,pattern,alphabet,table);
			break;

			case PRINT:
				//printf("IMPRIMIR TABELA\n");
				printTable(table, alphabet, pattern);
			break;

			case EXIT:
				//printf("SAIR DO PROGRAMA\n");
			break;

			default:
				//printf("ENTRADA ERRADA\n");
			break;
		}
	}
	return 0;
}

std::vector<char> alphabetExtract(char *pattern){
	int patternLength = strlen(pattern);
	std::vector<char> ordenedPattern;
	for (int i = 0; i < patternLength; ++i){
		ordenedPattern.push_back(pattern[i]);
	}
	sort(ordenedPattern.begin(),ordenedPattern.end());

	char walker = ordenedPattern[0];
	std::vector<char> alphabet;
	alphabet.push_back(walker);
	for(int i = 0; i < ordenedPattern.size();i++){
		if (walker != ordenedPattern[i]){
			walker = ordenedPattern[i];
			alphabet.push_back(walker);
		}
	}
	char space = ' ', dot = '.', comma = ',';

	std::vector<char> tmp;
	for(int i = 0; i < alphabet.size() && (alphabet[i] == space || alphabet[i] == dot || alphabet[i] == comma);i++){
		if(alphabet[i] == space || alphabet[i] == dot || alphabet[i] == comma){
			tmp.push_back(alphabet[i]);
			alphabet.erase(alphabet.begin() + i);
			i--;
		}
	}
	for(int i = tmp.size() - 1; i >= 0 ;i--){
		alphabet.push_back(tmp[i]);
	}
	return alphabet;
}

void putThingsOnTable(int table[][ALPHABETSIZE], char *alphabet, char *pattern){
	int patternSize = strlen(pattern) + 1;
	int alphabetSize = strlen(alphabet);
	for(int i = 0;i < patternSize;i++){
		for(int j = 0; j < alphabetSize;j++){
			table[i][j] = 0;
		}
	}
}

int wordState(char *pattern, int actualState, char letter){
	int patternSize = strlen(pattern);
	int i = 0;
	//printf("%c \n", letter);
	if (actualState < patternSize && letter == pattern[actualState]){
		//printf("%d ", actualState+1);
		return actualState+1;
	}
	for(int nextStageToGo = actualState; nextStageToGo > 0; nextStageToGo--){
		if(pattern[nextStageToGo - 1] == letter){
			for(i = 0; i < nextStageToGo-1; i++){
				if (pattern[i] != pattern[actualState - nextStageToGo + 1 + i])
					break;
			}
			if (i == nextStageToGo - 1){
				//printf("%d ", nextStageToGo);
				return nextStageToGo;
			}
		}
	}
	//printf("0 ");
	return 0;
}

void computeTransitionFunction(char *pattern, char *text, char *alphabet, int table[][ALPHABETSIZE]){
	int alphabetSize = strlen(alphabet);
	int patternSize = strlen(pattern);

	for(int state = 0; state <= patternSize;state++){
		//printf("Letter: \n");
		for(int letterOfAlphabet = 0; letterOfAlphabet < alphabetSize;letterOfAlphabet++){
			table[state][letterOfAlphabet] = wordState(pattern,state,alphabet[letterOfAlphabet]);
		}
		//printf("\n");
	}
	//printTable(table, alphabet, pattern);
}

void finiteAutomatonMatcher(int textLength, char *text, char *pattern, char *alphabet, int table[][ALPHABETSIZE]){
	int patternLength = strlen(pattern);

	for(int i = 0, state = 0,letterPosition = 0; i < textLength;i++){
		for(letterPosition = 0; text[i] != alphabet[letterPosition] ;letterPosition++);
		state = table[state][letterPosition];
		if(state == patternLength){
			printf("%d\n", (i+2) - (patternLength));
		}
	}
}

void printTable(int table[][ALPHABETSIZE], char *alphabet, char *pattern){
	int patternSize = strlen(pattern);
	int alphabetSize = strlen(alphabet);
	printf("Tabela Delta:\n");
	for(int state = 0;state <= patternSize;state++){
		for(int letter = 0; letter < alphabetSize;letter++){
			if (alphabet[letter] != ' '){
				printf("[%d,%c]: %d\n", state, alphabet[letter], table[state][letter]);
			} else{
				printf("[%d,'%c']: %d\n", state, alphabet[letter], table[state][letter]);
			}
		}
	}
}

void printVector(char *v){
	int a = strlen(v);
	printf("%d\n", a);
	for (int i = 0; i < strlen(v); ++i){
		printf("%c ", v[i]);
	}
	printf("|\n");
}
