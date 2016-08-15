# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXREGISTER 11
static const int LAMBIDA = -1;
static const char DIR[30] = "files/quadraticProbing.bin";

void save(int );
void list();
void createRegister();

int main() {
  int i, input;

  createRegister();

  while(scanf("%d", &input) > 0){
    save(input);
    list();
  }

  list();

  return 0;
}


void save(int value){
  FILE *fp;
  int hashing, h2, walker, i = 0;

  if((fp = fopen(DIR, "r+")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  hashing = value % MAXREGISTER;
  printf("\tInserindo valor %d -> hash: %d \n", value, hashing);

  fseek(fp,(hashing)*sizeof(int),SEEK_SET);
  fread(&walker,sizeof(int),1,fp);
  printf("Encontrei: %d\n", walker);
  
  while(walker != LAMBIDA){
    i++;
    h2 = (hashing + (i + (i*i)));
    h2 = h2 % MAXREGISTER;
    printf("h2 is: %d, i: %d\n",h2,i );

    fseek(fp,(h2)*sizeof(int),SEEK_SET);
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
  int i;

  if((fp = fopen(DIR, "w")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  rewind(fp);

  for(i = 0; i < MAXREGISTER ;i++){
    if(fwrite(&LAMBIDA,sizeof(int),1,fp) != 1)
      printf("Erro na escrita do arquivo");
  }
  fclose(fp); 
}