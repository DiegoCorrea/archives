# include <stdio.h>
# include <iostream>
# include <string.h>
# include <vector>
# include <algorithm>

# define SEARCH 's'
# define PRINT 'u'
# define EXIT 'e'

void printVector(std::vector<char> v);
std::vector<char> alphabetExtract(char *pattern);

int * computeTransitionFunction(char *pattern, char *text, std::vector<char> alphabet);
void finiteAutomatonMatcher(int textLength, char *text, char *pattern);

void printTable(int *table,std::vector<char> alphabet, char *pattern);

int main(){
	int textLength;
	scanf("%d", &textLength);
	
	char pattern[textLength], text[textLength];
	char choice = 'a';

	scanf(" %[^\n]s", text);
	getchar();
	scanf(" %[^\n]s", pattern);
	getchar();

	std::vector<char> alphabet = alphabetExtract(pattern);

	printf("Texto: %s\n", text);
	printf("Padrão: %s\n", pattern);
	printf("Alfabeto: ");
	printVector(alphabet);


	int *table = computeTransitionFunction(pattern,text,alphabet);
	finiteAutomatonMatcher(textLength,text,pattern);
	while(choice != EXIT){
		scanf("%c", &choice);
		getchar();
		printf("A operação escolhida foi: ");

		switch(choice){
			case SEARCH:
				printf("BUSCAR PADRÃO\n");
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

int *computeTransitionFunction(char *pattern, char *text, std::vector<char> alphabet){

}

void finiteAutomatonMatcher(int textLength, char *text, char *pattern){

	for(int i = 0; i < textLength;i++){

	}
}

void printTable(int *table, std::vector<char> alphabet, char *pattern){
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