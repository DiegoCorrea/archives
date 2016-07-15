# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXNAME 30

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

void inputBandas(Bandas **ptrBandas);
void listarBandas(Bandas *ptrBandas);
Bandas* criarBanda();
void salvarBanda(Bandas **ptrBandas, Bandas *);

int main() {
  Bandas *ptrBandas;
  int opcao = 9;

  ptrBandas = NULL;
  bandasGlobalID = 0;
  albunsGlobalID = 0;
  integrantesGlobalID = 0;


  while(opcao != 0){
    printf("1- Adicionar uma Banda\n2- Listar todas as Bandas\n0- Para sair do sistema\nDigite uma opção:\n");
    scanf("%d",&opcao);
    switch(opcao){ 
      case 0:
        printf("Saindo do sistema\n");
      break;
    
      case 1:  
        inputBandas(&ptrBandas);
      break;  

      case 2:  
        listarBandas(ptrBandas);
      break;  

      default:
        printf("Opção não encontrada\n");
      break;
    }
  }  
  return 0;
}

Bandas* criarBanda(){
  Bandas *banda;
  char nome[MAXNAME];
  
  banda = (Bandas*)malloc(sizeof(Bandas));

  printf("Digite o nome da banda: ");
  scanf(" %[^\n]s", nome);
  printf("\n");
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
  }  

  bandasGlobalID++;
  banda->id = bandasGlobalID;
}

void inputBandas(Bandas **ptrBandas){
  Bandas *tmp;
  
  tmp = criarBanda();
  printf("%s \n", tmp->nome);
  salvarBanda(ptrBandas, tmp);
  printf("***Banda %s Salva com Sucesso\n", tmp->nome);
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