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

# define MAXNAME 20
# define EMPTY -1

int MAXREGISTER = 11;

typedef struct Register{
  int key;
  char name[MAXNAME];
  int age;
}Register;


void save(int );

void listAll();

void createRegister();
void search(int input);

int main() {
  char choice = 's';
  int input;

  createRegister();
  while(choice != EXIT){
    printf("Enter:\n");
    scanf("%c", &choice);

    switch(choice){
      case INSERT:
        printf("Insert\n");
        printf("\n");
      break;

      case SEARCH:
        printf("Search\n");
        scanf("%d", &input);
        search(input);
        printf("\n");
      break;

      case REMOVE:
        printf("Remove\n");
        printf("\n");
      break;

      case LISTALL:
        printf("Print\n");
        listAll();
        printf("\n");
      break;

      case ACCESS:
        printf("Access\n");
        printf("\n");
      break;

      default:
        printf("Entrada Inválida\n");
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

  newREG.key = -1;
  newREG.age = -1;
  bzero(newREG.name, MAXNAME*(sizeof(char)));

  for(i = 0; i < MAXREGISTER ;i++){
    if(fwrite(&newREG,sizeof(newREG),1,fp) != 1)
      printf("Erro na escrita do arquivo");
  }
  fclose(fp); 
}

void save(int value){
  FILE *fp;
  int hashing, hashingOne, hashingTwo, walker, i = 0;

  if((fp = fopen(DIR, "r+")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  hashingOne = value % MAXREGISTER;
  hashingTwo = value/MAXREGISTER;
  printf("\tInserindo valor %d -> hash: %d \n", value, hashingOne);

  fseek(fp,(hashingOne)*sizeof(int),SEEK_SET);
  fread(&walker,sizeof(int),1,fp);
  printf("Encontrei: %d\n", walker);
  
  while(walker != EMPTY){
    i++;

    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;
    
    printf("Hashing is: %d, i: %d\n",hashing,i);

    fseek(fp,(hashing)*sizeof(int),SEEK_SET);
    fread(&walker,sizeof(int), 1,fp);
    printf("Encontrei: %d\n", walker);
  }

  fseek(fp,-sizeof(int),SEEK_CUR);
  if(fwrite(&value,sizeof(int),1,fp) != 1)
    printf("Erro na escrita do arquivo"); 
  else
    printf("Registro salvo com sucesso\n");

  fclose(fp);     
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

  fseek(fp,(hashingOne)*sizeof(int),SEEK_SET);
  fread(&walker,sizeof(int),1,fp);

  for(i = 1; walker.key != EMPTY && walker.key != input && i < MAXREGISTER; i++){
    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;

    fseek(fp,(hashing)*sizeof(Register),SEEK_SET);
    fread(&walker,sizeof(Register), 1,fp);
  }

  if(walker.key != EMPTY && i < MAXREGISTER){
    printf("chave: %d\n", walker.key);
    printf("%s\n", walker.name);
    printf("%d\n", walker.age);
  }else{
    printf("chave nao encontrada: %d\n",input);
  }

}