# include <stdio.h>
# include <iostream>
# include <string>

# define SEARCH 's'
# define PRINT 'u'
# define EXIT 'e'

int main(){
	int textLength;
	scanf("%d", &textLength);
	
	char pattern[textLength], text[textLength];
	char choice = 'a';

	scanf(" %[^\n]s", text);
	getchar();
	scanf(" %[^\n]s", pattern);
	getchar();

	printf("Texto: %s\n", text);
	printf("Padrão: %s\n", pattern);

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