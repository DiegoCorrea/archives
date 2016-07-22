# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXNAME 30
static const char DIRBANDA[MAXNAME] = "files/bandas.bin";
static const char DIRGLOBAL[MAXNAME] = "files/global.bin";

unsigned int bandasGlobalID = 0;

struct Bandas{
  int id;
  char nome[MAXNAME];
};
Bandas banda;

void criarBanda(char nome[MAXNAME]);
void salvarBanda();
void inputBandas();

void listarBandas();

void buscarBandaNome(char nome[MAXNAME]);
void alterarNomeBanda(char nome[MAXNAME]);
void alterarBandas();

void salvarGlobalStatus();
void carregarGlobalStatus();

int main() {
  int opcao = 9;

  carregarGlobalStatus();

  while(opcao != 0){
    printf("1- Adicionar uma Banda\n2- Listar todas as Bandas\n0- Para sair do sistema\nDigite uma opção:\n");
    scanf("%d",&opcao);
    switch(opcao){ 
      case 0:
        printf("Saindo do sistema\n");
      break;
    
      case 1:  
        inputBandas();
      break;  

      case 2:  
        listarBandas();
      break;  

      case 3:  
        alterarBandas();
      break;

      default:
        printf("Opção não encontrada\n");
      break;
    }
  }  
  return 0;
}

void buscarBandaNome(char nome[MAXNAME]){

}

void alterarNomeBanda(char nome[MAXNAME]){
  FILE *arquivo;
  int id;

  strcpy(banda.nome,nome);
}  

void alterarBandas(){
  char nome[MAXNAME]; 

  printf("Digite o nome da banda que deseja procurar:\n");
  scanf(" %[^\n]s", nome);

  buscarBandaNome(nome);

  printf("Deseja trocar o nome de %s por? \n", banda.nome);
  scanf(" %[^\n]s", nome);

  alterarNomeBanda(nome);
}  

void criarBanda(char nome[MAXNAME]){
  strcpy(banda.nome,nome);
  banda.id = bandasGlobalID;  
  bandasGlobalID++;
}

void salvarBanda(){
  FILE *arquivo;

  if((arquivo = fopen(DIRBANDA, "a")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }
  if(fwrite(&banda, sizeof(struct Bandas), 1,arquivo) != 1)
    printf("Erro na escrita do arquivo");

  fclose(arquivo);     
}

void inputBandas(){
  char nome[MAXNAME];

  printf("Digite o nome da banda: ");
  scanf(" %[^\n]s", nome);
  printf("\n");

  criarBanda(nome);
  salvarBanda();
  salvarGlobalStatus();
  printf("***Banda %s Salva com Sucesso\n", nome);
}

void listarBandas(){
  FILE *arquivo;

  printf("\t\tListando todas as Banda***\n");
  if((arquivo = fopen(DIRBANDA, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }
  
  rewind(arquivo); 

  while(fread(&banda, sizeof(struct Bandas), 1,arquivo) == 1){
    printf("------======------\n");
    printf("ID: %d\nNome: %s\n", banda.id,banda.nome);
  }
  fclose(arquivo); 
}

void carregarGlobalStatus(){
  FILE *arquivo;

  if((arquivo = fopen(DIRGLOBAL, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    return;   
  }
  
  if(fread(&bandasGlobalID, sizeof(unsigned int), 1,arquivo) != 1)
    printf("Erro na abertura do arquivo\n");

  fclose(arquivo); 
}

void salvarGlobalStatus(){
  FILE *arquivo;

  if((arquivo = fopen(DIRGLOBAL, "w")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }
  if(fwrite(&bandasGlobalID, sizeof(unsigned int), 1,arquivo) != 1)
    printf("Erro na escrita do arquivo");

  fclose(arquivo);     
}
