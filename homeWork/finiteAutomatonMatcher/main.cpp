# include <stdio.h>
# include <iostream>
# include <string.h>
# include <vector>
# include <algorithm>

# define SEARCH 's'
# define PRINT 'u'
# define EXIT 'e'
# define MAX_ASCII_CHAR 255

void printVector(std::vector<char> v);
//std::vector<char> alphabetExtract(char *pattern);

int wordState(char *pattern, int state, char letter);
void computeTransitionFunction(char *pattern, char *text, std::vector<char> alphabet, int table[][MAX_ASCII_CHAR]);
void finiteAutomatonMatcher(char *text, char *pattern, std::vector<char> alphabet, int table[][MAX_ASCII_CHAR]);

void putThingsOnTable(int table[][MAX_ASCII_CHAR], std::vector<char> alphabet, char *pattern);
void printTable(int table[][MAX_ASCII_CHAR],std::vector<char> alphabet, char *pattern);

int main(){
	int textLength;
	scanf("%d", &textLength);
	
	char pattern[textLength], text[textLength];
	char choice = 'a';

	scanf(" %[^\n]s", text);
	getchar();
	scanf(" %[^\n]s", pattern);
	getchar();

	std::vector<char> alphabet = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','.',',',' '};

	//printVector(alphabet);


	int states = strlen(pattern)+1;
	int table[states][MAX_ASCII_CHAR];
	putThingsOnTable(table, alphabet, pattern);

	computeTransitionFunction(pattern,text,alphabet,table);

	while(choice != EXIT){
		scanf("%c", &choice);
		getchar();
		printf("A operação escolhida foi: ");

		switch(choice){
			case SEARCH:
				printf("BUSCAR PADRÃO\n");
				finiteAutomatonMatcher(text,pattern,alphabet,table);
			break;

			case PRINT:
				printf("IMPRIMIR TABELA\n");
				printTable(table, alphabet, pattern);
			break;

			case EXIT:
				printf("SAIR DO PROGRAMA\n");
			break;

			default:
				printf("ENTRADA ERRADA\n");
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

void printVector(std::vector<char> v){
	for (int i = 0; i < v.size(); ++i){
		printf("%c ", v[i]);
	}
	printf("|\n");
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

void computeTransitionFunction(char *pattern, char *text, std::vector<char> alphabet, int table[][MAX_ASCII_CHAR]){
	int alphabetSize = alphabet.size();
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

void finiteAutomatonMatcher(char *text, char *pattern, std::vector<char> alphabet, int table[][MAX_ASCII_CHAR]){
	int textLength = strlen(text);
	int patternLength = strlen(pattern);

	for(int i = 0, state = 0,letterPosition = 0; i < textLength;i++){
		for(letterPosition = 0; text[i] != alphabet[letterPosition] ;letterPosition++);
		state = table[state][letterPosition];
		if(state == patternLength){
			printf("%d\n", i-patternLength+2);
		}
	}
}

void printTable(int table[][MAX_ASCII_CHAR], std::vector<char> alphabet, char *pattern){
	int patternSize = strlen(pattern) + 1;
	int alphabetSize = alphabet.size();
	printf("Tabela Delta:\n");
	for(int i = 0;i < patternSize;i++){
		for(int j = 0; j < alphabetSize;j++){
			if (alphabet[j] != ' '){
				printf("[%d,%c]: %d\n", i, alphabet[j], table[i][j]);
			} else{
				printf("[%d,'%c']: %d\n", i, alphabet[j], table[i][j]);
			}
		}
	}
}

void putThingsOnTable(int table[][MAX_ASCII_CHAR], std::vector<char> alphabet, char *pattern){
	int patternSize = strlen(pattern) + 1;
	int alphabetSize = alphabet.size();
	for(int i = 0;i < patternSize;i++){
		for(int j = 0; j < alphabetSize;j++){
			table[i][j] = 0;
		}
	}
}