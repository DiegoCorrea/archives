# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define DIR "doubleHashing.bin"

# define INSERT 'i'
# define SEARCH 'c'
# define REMOVE 'r'
# define LISTALL 'p'
# define ACCESS 'm'
# define EXIT 'e'

# define MAXNAME 21
# define EMPTY -1

//TAMANHO_ARQUIVO
# define MAXREGISTER 11

typedef struct Register{
  int key;
  char name[MAXNAME];
  int age;
}Register;


void insertReg();
void save(int key, char name[MAXNAME], int age);

void listAll();
void counterAccess();

void createRegister();
void search(int input);

void removeRegister(int input);

int main() {
  char choice = 's';
  int input;

  createRegister();
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

  if((fp = fopen(DIR, "w")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  rewind(fp);

  newREG.key = EMPTY;
  newREG.age = EMPTY;
  bzero(newREG.name, MAXNAME*(sizeof(char)));

  for(i = 0; i < MAXREGISTER ;i++){
    if(fwrite(&newREG,sizeof(newREG),1,fp) != 1)
      printf("Erro na escrita do arquivo");
  }
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

  hashingOne = key % MAXREGISTER;
  hashingTwo = key/MAXREGISTER;

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);
  
  for(i = 0; walker.key != EMPTY; i++){
    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);

    if(newREG.key == walker.key){
      printf("chave ja existente: %d\n", key);
      return;
    }
  }

  fseek(fp,-sizeof(Register),SEEK_CUR);
  if(fwrite(&newREG,sizeof(Register),1,fp) != 1)
    printf("Erro na escrita do arquivo"); 

  fclose(fp);     
}

void insertReg(){
  int key, age;
  char nameInput[MAXNAME];

  scanf("%d", &key);
  scanf(" %[^\n]s", nameInput);
  scanf("%d", &age);

  save(key, nameInput, age);
}

void listAll(){
  FILE *fp;
  Register walker;
  int i;

  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  rewind(fp);

  for(i = 0; i < MAXREGISTER ;i++){
    if(fread(&walker,sizeof(Register),1,fp) == 1) {
      if(walker.key != EMPTY)
        printf("%d: %d %s %d\n", i, walker.key, walker.name, walker.age);
      else
        printf("%d: vazio\n", i);
    } else {
      printf("Erro! Sequência não pode ser impressa");
    }
  }
  fclose(fp);
}

void search(int input){
  FILE *fp;
  Register walker;
  int i, hashing, hashingOne, hashingTwo;

  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  hashingOne = input % MAXREGISTER;
  hashingTwo = input/MAXREGISTER;

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);

  for(i = 1; walker.key != EMPTY && walker.key != input && i < MAXREGISTER; i++){
    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;

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

  for(i = 0; i < MAXREGISTER ;i++){
    fseek(fp,(i)*sizeof(Register),SEEK_SET);
    if(fread(&toCountSearch,sizeof(Register),1,fp) == 1) {
      if(toCountSearch.key != EMPTY){

        countAccess = 1;
        countRegister++;

        hashingOne = toCountSearch.key % MAXREGISTER;
        hashingTwo = toCountSearch.key/MAXREGISTER;

        fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
        fread(&walker,sizeof(Register),1,fp);

        while(walker.key != toCountSearch.key){
          hashing = (hashingOne + (countAccess*hashingTwo)) % MAXREGISTER;

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
  media = ((float)totalAccess/countRegister);
  printf("%.1f\n", media);

  fclose(fp);
}

void removeRegister(int input){
  FILE *fp;
  Register walker;
  int i, hashing, hashingOne, hashingTwo;

  if((fp = fopen(DIR, "r+")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  hashingOne = input % MAXREGISTER;
  hashingTwo = input/MAXREGISTER;

  fseek(fp,(hashingOne)*sizeof(Register),SEEK_SET);
  fread(&walker,sizeof(Register),1,fp);

  for(i = 1; walker.key != EMPTY && walker.key != input && i < MAXREGISTER; i++){
    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;

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