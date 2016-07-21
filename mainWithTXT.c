# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXNAME 30
static const char DIRBANDA[MAXNAME] = "files/bandas.txt";

unsigned int bandasGlobalID;
unsigned int albunsGlobalID;
unsigned int integrantesGlobalID;

struct Integrantes{
  int id;
  char nome[MAXNAME];
  char funcao;

  Integrantes *prox;
  Integrantes *ant;
};

struct Albuns{
  int id;
  char nome[MAXNAME];
  int anoLancamento;
  int tempo;
  Albuns *prox;
  Albuns *ant;
};

struct Bandas{
  int id;
  char nome[MAXNAME];

  Integrantes *integrantes;
  Albuns *albuns;

  Bandas *ant;
  Bandas *prox; 
};

void inputBandas(Bandas **);
void listarBandas(Bandas *);
Bandas* criarBanda(char nome[MAXNAME]);
void salvarBanda(Bandas **, Bandas *);
Bandas* buscarBandaNome(Bandas *, char nome[MAXNAME]);
void alterarNomeBanda(Bandas *, char nome[MAXNAME]);
void alterarBandas(Bandas *);


void salvarArquivoBandas(Bandas *);
void carregarArquivoBandas(Bandas **);

int main() {
  Bandas *ptrBandas = NULL;
  int opcao = 9;

  carregarArquivoBandas(&ptrBandas);

  while(opcao != 0){
    printf("1- Adicionar uma Banda\n2- Listar todas as Bandas\n0- Para sair do sistema\nDigite uma opção:\n");
    scanf("%d",&opcao);
    switch(opcao){ 
      case 0:
        salvarArquivoBandas(ptrBandas);
        printf("Saindo do sistema\n");
      break;
    
      case 1:  
        inputBandas(&ptrBandas);
      break;  

      case 2:  
        listarBandas(ptrBandas);
      break;  

      case 3:  
        alterarBandas(ptrBandas);
      break;

      default:
        printf("Opção não encontrada\n");
      break;
    }
  }  
  return 0;
}

Bandas* buscarBandaNome(Bandas *ptrBandas, char nome[MAXNAME]){
  while((ptrBandas != NULL) && (strcasecmp(ptrBandas->nome,nome) != 0)){
    ptrBandas = ptrBandas->prox;
  }

  return ptrBandas;
}

void alterarNomeBanda(Bandas *banda, char nome[MAXNAME]){
  Bandas *tmp;
  FILE *arquivo;
  int id;
  /*
  arquivo = fopen(DIRBANDA, "r");
  if(arquivo != NULL){
    while(fscanf(arquivo, "'%d',' %[^']\n';\n", &id,nome) != EOF){
      printf("%d %s\n", id, nome);
      banda = criarBanda(nome);      
    }
    fclose(arquivo);
  } else {
    printf("Erro ao tentar carregar o arquivo de Bandas!\n");
  }
  */
  strcpy(banda->nome,nome);
}  

void alterarBandas(Bandas *ptrBandas){
  Bandas *banda;
  char nome[MAXNAME]; 

  printf("Digite o nome da banda que deseja procurar:\n");
  scanf(" %[^\n]s", nome);

  banda = buscarBandaNome(ptrBandas,nome);

  if(banda == NULL){
    printf("Banda '%s' não encontrada\n", nome);
    return;
  }
  printf("Deseja trocar o nome de %s por? \n", banda->nome);
  scanf(" %[^\n]s", nome);

  alterarNomeBanda(banda,nome);
}  

Bandas* criarBanda(char nome[MAXNAME]){
  Bandas *banda;
  
  banda = (Bandas*)malloc(sizeof(Bandas));

  strcpy(banda->nome,nome);
  
  banda->integrantes = NULL;
  banda->albuns = NULL;
  banda->ant = NULL;
  banda->prox = NULL; 

  return banda;
}

void salvarBanda(Bandas **ptrBandas, Bandas *banda){
  Bandas *tmp;

  if(*ptrBandas == NULL){
    *ptrBandas = banda;  
  }else{
    tmp = *ptrBandas;
    while(tmp->prox != NULL)
      tmp = tmp->prox;

    tmp->prox = banda;
    banda->ant = tmp;

    bandasGlobalID++;
    banda->id = bandasGlobalID;
  }  
}

void inputBandas(Bandas **ptrBandas){
  char nome[MAXNAME];

  printf("Digite o nome da banda: ");
  scanf(" %[^\n]s", nome);
  printf("\n");

  salvarBanda(ptrBandas, criarBanda(nome));
  printf("***Banda %s Salva com Sucesso\n", nome);
}

void listarBandas(Bandas *ptrBandas){
  if(ptrBandas == NULL){
    printf("Nenhuma banda registrada\n");
  }else{
    printf("Lista de Bandas\n");
    while(ptrBandas != NULL ){
      printf("---------------\n");
      printf("id: %d\n", ptrBandas->id);
      printf("Nome: %s\n", ptrBandas->nome);

      ptrBandas = ptrBandas->prox;
    }
    printf("---------------\n");
  }
}

void salvarArquivoBandas(Bandas *ptrBandas){
  FILE *arquivo;
  arquivo = fopen(DIRBANDA, "w");
  while(ptrBandas != NULL){
    fprintf(arquivo, "'%d','%s';\n", ptrBandas->id,ptrBandas->nome);



    ptrBandas = ptrBandas->prox;
  }
  fclose(arquivo);
}

void carregarArquivoBandas(Bandas **ptrBandas){
  Bandas *banda, *tmp;
  FILE *arquivo;
  int id;
  char nome[MAXNAME]; 

  arquivo = fopen(DIRBANDA, "r");
  if(arquivo != NULL){
    while(fscanf(arquivo, "'%d',' %[^']\n';\n", &id,nome) != EOF){
      banda = criarBanda(nome);

      if(*ptrBandas == NULL){
        *ptrBandas = banda;  
      }else{
        tmp = *ptrBandas;
        while(tmp->prox != NULL)
          tmp = tmp->prox;

        tmp->prox = banda;
        banda->ant = tmp;

        banda->id = id;
        if(bandasGlobalID < id){
          bandasGlobalID = id;
        }  
      }  
    }
    fclose(arquivo);
  } else {
    printf("Erro ao tentar carregar o arquivo de Bandas!\n");
  }
}