# include <stdio.h>
# include <string.h>
# include <stdlib.h>

//caminho onde estará salvo o arquivo binario
# define DIR "doubleHashing.bin"

//Alias para as escolhas do menu
# define INSERT 'i'
# define SEARCH 'c'
# define REMOVE 'r'
# define LISTALL 'p'
# define ACCESS 'm'
# define EXIT 'e'

//Tamanho maximo da variavel de nome
# define MAXNAME 21

//Valor para variavel vazia
# define EMPTY -1

//TAMANHO_ARQUIVO
# define TAMANHO_ARQUIVO 11

//Caso a divisão da hash 2 dê zero
# define ZERO 0
# define TRUE 1
# define FALSE 0

//Registro que será usado
typedef struct Register{
  int key;
  char name[MAXNAME];
  int age;
}Register;

//declaração das funcções que serão usadas
void insertReg();
void startFileRead();
void save(int key, char name[MAXNAME], int age);

void listAll();
void counterAccess();

void createRegister();
void search(int input);
int keyExistent(int key);

void removeRegister(int input);

int main(){
  char choice = 's';
  int input;

  startFileRead();
  while(choice != EXIT){
    scanf("%c", &choice);

    switch(choice){
      case INSERT:
        insertReg();
      break;

      case SEARCH:
        scanf("%d", &input);
        search(input);
      break;

      case REMOVE:
        scanf("%d", &input);
        removeRegister(input);
      break;

      case LISTALL:
        listAll();
      break;

      case ACCESS:
        counterAccess();
      break;

      case EXIT:
      break;

      default:
        printf("Entrada Inválida\n");
      break;
    }
    getchar();
  }

  return 0;
}

void createRegister(){
  FILE *fp;
  Register newREG;
  int i;

  if((fp = fopen(DIR, "w+")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  rewind(fp);

  newREG.key = EMPTY;
  newREG.age = EMPTY;
  bzero(newREG.name, MAXNAME*(sizeof(char)));

  for(i = 0; i < TAMANHO_ARQUIVO ;i++){
    if(fwrite(&newREG,sizeof(newREG),1,fp) != 1)
      printf("Erro na escrita do arquivo");
  }
  fclose(fp); 
}

void startFileRead(){
  FILE *fp;
  if((fp = fopen(DIR, "r")) == NULL){
    createRegister();
  }else
    fclose(fp);
}

void save(int key, char name[MAXNAME], int age){
  FILE *fp;
  Register walker, newREG;
  int hashing, hashingOne, hashingTwo, i = 0;

  if((fp = fopen(DIR, "r+")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  newREG.key = key;
  newREG.age = age;
  strcpy(newREG.name,name);

  hashingOne = key % TAMANHO_ARQUIVO;
  hashingTwo = key/TAMANHO_ARQUIVO;
  hashingTwo = hashingTwo % TAMANHO_ARQUIVO;

  if(hashingTwo == ZERO){
    hashingTwo = 1;
  }  

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);
  
  for(i = 0;walker.key != EMPTY && newREG.key != walker.key && i < TAMANHO_ARQUIVO; i++){
    hashing = (hashingOne + (i*hashingTwo)) % TAMANHO_ARQUIVO;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);
  }

  if(newREG.key == walker.key){
    printf("chave ja existente: %d\n", key);
  }else if(walker.key == EMPTY){
    fseek(fp,-sizeof(Register),SEEK_CUR);
    if(fwrite(&newREG,sizeof(Register),1,fp) != 1)
      printf("Erro na escrita do arquivo");    
  }
  fclose(fp);     
}

void insertReg(){
  int key, age;
  char nameInput[MAXNAME];

  scanf("%d", &key);
  scanf(" %[^\n]s", nameInput);
  scanf("%d", &age);

  if(keyExistent(key) == FALSE)
    save(key, nameInput, age);
  else
    printf("chave ja existente: %d\n", key);
}

void listAll(){
  FILE *fp;
  Register walker;
  int i;

  if((fp = fopen(DIR, "r")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  rewind(fp);

  for(i = 0; i < TAMANHO_ARQUIVO ;i++){
    if(fread(&walker,sizeof(Register),1,fp) == 1){
      if(walker.key != EMPTY)
        printf("%d: %d %s %d\n", i, walker.key, walker.name, walker.age);
      else
        printf("%d: vazio\n", i);
    }else{
      printf("Erro! Sequência não pode ser impressa");
    }
  }
  fclose(fp);
}

void search(int input){
  FILE *fp;
  Register walker;
  int i, hashing, hashingOne, hashingTwo;

  if((fp = fopen(DIR, "r")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  hashingOne = input % TAMANHO_ARQUIVO;
  hashingTwo = input/TAMANHO_ARQUIVO;
  hashingTwo = hashingTwo % TAMANHO_ARQUIVO;

  if(hashingTwo == ZERO){
    hashingTwo = 1;
  }

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);

  for(i = 1;walker.key != input && i < TAMANHO_ARQUIVO; i++){
    hashing = (hashingOne + (i*hashingTwo)) % TAMANHO_ARQUIVO;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);
  }

  if(walker.key == input){
    printf("chave: %d\n", walker.key);
    printf("%s\n", walker.name);
    printf("%d\n", walker.age);
  }else{
    printf("chave nao encontrada: %d\n",input);
  }
  fclose(fp);
}

void counterAccess(){
  FILE *fp;
  Register walker, toCountSearch;
  int i, countAccess = 0, countRegister = 0, totalAccess = 0, hashing, hashingOne, hashingTwo;
  float media;

  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  rewind(fp);

  for(i = 0; i < TAMANHO_ARQUIVO ;i++, countAccess = 0, fseek(fp,(i)*sizeof(Register),SEEK_SET)){
    if(fread(&toCountSearch,sizeof(Register),1,fp) == 1){
      if(toCountSearch.key != EMPTY){

        countAccess = 1;
        countRegister++;

        hashingOne = toCountSearch.key % TAMANHO_ARQUIVO;
        hashingTwo = toCountSearch.key/TAMANHO_ARQUIVO;
        hashingTwo = hashingTwo % TAMANHO_ARQUIVO;

        if(hashingTwo == ZERO){
          hashingTwo = 1;
        }

        fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
        fread(&walker,sizeof(Register),1,fp);

        while(walker.key != toCountSearch.key){
          hashing = (hashingOne + (countAccess*hashingTwo)) % TAMANHO_ARQUIVO;

          fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
          fread(&walker,sizeof(Register), 1,fp);

          countAccess++;
        }
        totalAccess = totalAccess + countAccess;
      }
    } else {
      printf("Erro! Contador não pode ser impresso");
    }
  }
  if(totalAccess != ZERO){
    media = ((float)totalAccess/countRegister);
  }else{
    media = 0.0;
  }

  printf("%.1f\n", media);

  fclose(fp);
}

void removeRegister(int input){
  FILE *fp;
  Register walker;
  int i, hashing, hashingOne, hashingTwo;

  if((fp = fopen(DIR, "r+")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  hashingOne = input % TAMANHO_ARQUIVO;
  hashingTwo = input/TAMANHO_ARQUIVO;
  hashingTwo = hashingTwo % TAMANHO_ARQUIVO;

  if(hashingTwo == ZERO){
    hashingTwo = 1;
  }

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);

  for(i = 0;walker.key != input && i < TAMANHO_ARQUIVO; i++){
    hashing = (hashingOne + (i*hashingTwo)) % TAMANHO_ARQUIVO;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);
  }

  if(walker.key == input){
    walker.key = EMPTY;
    walker.age = EMPTY;
    bzero(walker.name, MAXNAME*(sizeof(char)));

    fseek(fp,-sizeof(Register),SEEK_CUR);
    if(fwrite(&walker,sizeof(Register),1,fp) != 1)
      printf("Erro na escrita do arquivo"); 
  }else{
    printf("chave nao encontrada: %d\n",input);
  }
  fclose(fp);
}

int keyExistent(int input){
  FILE *fp;
  Register walker;
  int i, hashing, hashingOne, hashingTwo;

  if((fp = fopen(DIR, "r")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  hashingOne = input % TAMANHO_ARQUIVO;
  hashingTwo = input/TAMANHO_ARQUIVO;
  hashingTwo = hashingTwo % TAMANHO_ARQUIVO;

  if(hashingTwo == ZERO){
    hashingTwo = 1;
  }

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);

  for(i = 0;walker.key != input && i < TAMANHO_ARQUIVO; i++){
    hashing = (hashingOne + (i*hashingTwo)) % TAMANHO_ARQUIVO;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);
  }

  fclose(fp);
  if(walker.key == input){
    return TRUE;
  }else{
    return FALSE;
  }
}