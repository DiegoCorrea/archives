# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXREGISTER 11
static const char DIR[30] = "files/primaryKeySearch.bin";

int r = MAXREGISTER - 1;

struct Unity{
  int value;
  int pointer;
}unity;

void save(int );
void list();

int main() {
  int i, input;


  while(scanf("%d", &input) > 0){
    save(input);
  }

  list();

  return 0;
}

void save(int input){
  FILE *fp;
  int hashing;
  Unity walker;

  if((fp = fopen(DIR, "w")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);    
  }

  hashing = input % MAXREGISTER;
  fseek(fp,hashing*sizeof(struct Unity),SEEK_SET);
  while(fread(&walker, sizeof(struct Unity), 1,fp) == 1){
    fseek(fp,walker.pointer*sizeof(struct Unity),SEEK_SET);
  }

  unity.pointer = 0;
  unity.pointer--;
  unity.value = input;

  if(fwrite(&unity, sizeof(struct Unity), 1,fp) != 1)
    printf("Erro na escrita do arquivo");

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
    }
  }
  fclose(fp); 
}
