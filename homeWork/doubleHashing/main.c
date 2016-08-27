# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXNAME 20
# define DIR "doubleHashing.bin"

# define INSERT 'i'
# define SEARCH 'c'
# define REMOVE 'r'
# define PRINT 'p'
# define ACCESS 'm'
# define EXIT 'e'

static const int LAMBIDA = -1;

int MAXREGISTER = 11;

typedef struct Register{
  int key;
  char name[MAXNAME];
  int age;
}Register;


void save(int );
void list();

void createRegister();

int main() {
  char choice = 's';

  createRegister();
  while(choice != EXIT){
    scanf("%c", &choice);

    switch(choice){
      case INSERT:
      printf("Insert\n");
        printf("\n");
      break;

      case SEARCH:
        printf("Search\n");
        printf("\n");
      break;

      case REMOVE:
        printf("Remove\n");
        printf("\n");
      break;

      case PRINT:
        printf("Print\n");
        list();
        printf("\n");
      break;

      case ACCESS:
        printf("Access\n");
        printf("\n");
      break;

      default:
        printf("Entrada Inválida\n");
    }
  }

  return 0;
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
  
  while(walker != LAMBIDA){
    i++;

    hashing = (hashingOne + (i*hashingTwo)) % MAXREGISTER;;
    
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

void list(){
  FILE *fp;
  int i, value;

  printf("\t\tListando todos registros***\n");
  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }
  
  rewind(fp); 

  for(i = 0; i < MAXREGISTER ;i++){
    if(fread(&value,sizeof(int),1,fp) == 1) {
      printf("P[%d]: %d \n", i, value);
    } else {
      printf("Posição: %d vazia\n", i);
    }
  }
  fclose(fp); 
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
    if(fwrite(&newREG,sizeof(newREG),MAXREGISTER,fp) != 1)
      printf("Erro na escrita do arquivo");
  }
  fclose(fp); 
}
