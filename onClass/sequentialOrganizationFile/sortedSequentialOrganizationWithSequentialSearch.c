# include <stdio.h>
# include <stdlib.h>

static const char DIR[30] = "files/sSOWSS.bin";
int tam;

void input();
void list();
void remove();

int main() {

  scanf("%d", &tam);
  
  input();

  list();

  remove();

  list();
  
  remove();

  list();

  return 0;
}

void input(){
  FILE *fp;
  int input, i;

  if((fp = fopen(DIR, "w")) == NULL) {
    printf("Erro na abertura do arquivo\n");
    exit(1);
  }

  for(i = 0; i < tam; i++){
    scanf("%d", &input);
    fwrite(&input, sizeof(int), 1,fp);
  }

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

  for(i = 0; i < tam; i++){
    fread(&value, sizeof(int), 1,fp);
    printf("Valor: %d\n", value);
  }
  fclose(fp);
}

void remove(){
  FILE *fp;
  int i, value, rmv, tmp;

  printf("\t\tRemovendo registro***\n");
  if((fp = fopen(DIR, "r+")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }
  
  rewind(fp);

  scanf("%d", &rmv);

  for(i = 0; i < tam && value != rmv; i++, fread(&value, sizeof(int), 1,fp));

  if(value == rmv){
    fseek(fp,sizeof(int),SEEK_END);
    fread(&tmp, sizeof(int), 1,fp);

    rewind(fp);

    fseek(fp,sizeof(int)*(i-1),SEEK_SET);
    fwrite(&tmp,sizeof(int),1,fp);

    tam--;
  }
  fclose(fp);
}