# include <stdio.h>
# include <stdlib.h>

static const char DIR[30] = "files/sSOWBS.bin";
int tam;

void input();
void list();
void remove();
void binarySearch();

int main() {

  scanf("%d", &tam);
  
  input();

  list();

  binarySearch();

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

void binarySearch(){
FILE *fp;
  int i, tmp, number, r = tam, l = 0;

  printf("\t\tSearch the number***\n");
  if((fp = fopen(DIR, "r")) == NULL) {
    printf("Error can't open the file");
    exit(1);
  }

  scanf("%d", &number);

  fseek(fp,sizeof(int)*((r+l)/2),SEEK_SET);
  fread(&tmp, sizeof(int), 1,fp);

  while(l != r && tmp != number){
    if(tmp > number){
      r = (r+l)/2;
    } else {
      l = (r+l)/2;
    }

    fseek(fp,sizeof(int)*((r+l)/2),SEEK_SET);
    fread(&tmp, sizeof(int), 1,fp);
  }

  if(tmp == number)
    printf("Value: %d\n", tmp);
  else
    printf("Number not found!\n");
  fclose(fp);
}


void remove(){
  FILE *fp;
  int i, rmv, tmp;

  printf("\t\tRemovendo registro***\n");
  if((fp = fopen(DIR, "r+")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }
  
  rewind(fp);

  scanf("%d", &rmv);

  for(i = 0; i < tam && tmp != rmv; i++, fread(&tmp, sizeof(int), 1,fp));

  rewind(fp);
  if(tmp == rmv){
    printf("We found the number: %d\n", tmp);
    fseek(fp,i*sizeof(int),SEEK_CUR);
    while(i < tam){
      fread(&tmp, sizeof(int), 1,fp);

      printf("Now I see: %d\n", tmp);

      fseek(fp,-(2*sizeof(int)),SEEK_CUR);

      fwrite(&tmp,sizeof(int),1,fp);

      i++;
    }
  }
  fclose(fp);
  tam--;
}