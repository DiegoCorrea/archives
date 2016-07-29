# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXREGISTER 11
static const char DIR[30] = "files/primaryKeySearch.bin";
static const int LAMBIDA = -1;
int r = MAXREGISTER - 1;

struct Unity{
  int value;
  int pointer;
}unity;

void save(int );
void list();
void createRegister();

int main() {
  int i, input;

 createRegister();

  //while(scanf("%d", &input) > 0){
  //  save(input);
  //}

  list();

  return 0;
}

void save(int input){
  FILE *fp;
  int hashing;
  Unity walker;

  if((fp = fopen(DIR, "w")) == NULL){
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  unity.pointer = LAMBIDA;
  unity.value = input;

  hashing = input % MAXREGISTER;
  fseek(fp,hashing*sizeof(struct Unity),SEEK_SET);

  if(fread(&walker, sizeof(struct Unity), 1,fp) != 1){
    if(fwrite(&unity, sizeof(struct Unity), 1,fp) != 1)
      printf("Erro na escrita do arquivo"); 
    else
      printf("Registro salvo com sucesso\n");
  } else{
    while(walker.pointer >= 0){
      fseek(fp,walker.pointer*sizeof(struct Unity),SEEK_SET);
      fread(&walker, sizeof(struct Unity), 1,fp);
    }

    walker.pointer = r;
    if(fwrite(&walker, sizeof(struct Unity), 1,fp) != 1)
      printf("Erro na escrita do arquivo");
    else
      printf("Ponteiro do Registro salvo com sucesso\n");

    fseek(fp,r*sizeof(struct Unity),SEEK_SET);
    if(fwrite(&unity, sizeof(struct Unity), 1,fp) != 1)
      printf("Erro na escrita do arquivo");
    else
      printf("Registro salvo com sucesso com alteração no R\n");

    do{
      r--;
      fseek(fp,r*sizeof(struct Unity),SEEK_SET);
    }while((r >= 0) && (fread(&walker, sizeof(struct Unity), 1,fp) == 1));
  }
  
  fclose(fp);     
}

void list(){
  FILE *fp;
  int i;

  printf("\t\tListando todos registros***\n");
  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }
  
  rewind(fp); 

  for(i = 0; i < MAXREGISTER ;i++){
    if(fread(&unity, sizeof(struct Unity), 1,fp) == 1) {
      printf("Valor: %d Ponteiro: %d\n", unity.value,unity.pointer);
    } else {
      printf("----------------------\n");
      printf("Valor: %d Ponteiro: %d\n", unity.value,unity.pointer);  
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
  //unity.value = LAMBIDA;
  //unity.pointer = LAMBIDA;

  //for(i = 0; i < MAXREGISTER ;i++){
    //if(fwrite(&unity, sizeof(struct Unity), 1,fp) != 1)
      //printf("Erro na escrita do arquivo");
  //}
  fclose(fp); 
}