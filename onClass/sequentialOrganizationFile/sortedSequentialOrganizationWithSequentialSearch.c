# include <stdio.h>
# include <stdlib.h>

static const char DIR[30] = "files/sSOWSS.bin";
int tam;

void input();
void list();
void remove();
void sequentialSearch();

int main() {

  scanf("%d", &tam);
  
  input();

  list();

  sequentialSearch();

  //remove();

  //list();
  
  //remove();

  //list();

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

  printf("\t\tList all the numbers***\n");
  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Error can't open the file");
    exit(1);
  }
  
  rewind(fp);

  for(i = 0; i < tam; i++){
    fread(&value, sizeof(int), 1,fp);
    printf("Value: %d\n", value);
  }
  fclose(fp);
}

void sequentialSearch(){
FILE *fp;
  int i, value, number;

  printf("\t\tSearch the number***\n");
  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Error can't open the file");
    exit(1);
  }
  
  rewind(fp);

  scanf("%d", &number);
  for(i = 0; i < tam && value != number; i++, fread(&value, sizeof(int), 1,fp));

  if(value == number)
    printf("Value: %d\n", value);
  else
    printf("Number not found!\n");
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