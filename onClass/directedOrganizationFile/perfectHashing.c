# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define MAXREGISTER 9
static const char DIR[30] = "files/perfectHashing.bin";
static const int LAMBIDA = -1;

struct Table{
  int many;
  int min;
  int max;
}table[MAXREGISTER];

int when[MAXREGISTER], input[MAXREGISTER][2], length, smaller, larger, prime, top, bottom;

void list();
void createRegister();

int main() {
  top = 42;
  bottom = 3;
  prime = 101;

  smaller = 99999;
  larger = 0;
  length = 0;

  while(scanf("%d", &input[length][0]) > 0){ 
    if(larger < input[length][0])
      larger = input[length][0];
    if(smaller > input[length][0])
      smaller = input[length][0];

    table[length].many = 0;
    table[length].min = 0;
    table[length].max = 0;
    when[length] = 0;
    length++;
  }

  createRegister();

  list();

  return 0;
}

void list(){
  int i;
  printf("Smaller: %d | Larger %d\n", smaller, larger);
  for(i = 0; i < MAXREGISTER;i++){
    printf("P[%d]: How much: %d | Inf lim: %d | Sup lim: %d\n", i, table[i].many, table[i].min, table[i].max);
  }
}

void createRegister(){
  FILE *fp;
  int i, hashing;

  for(i = 0; i < length;i++){
    input[i][1] = ((bottom*input[i][0] + top) % prime) % MAXREGISTER;
    table[input[i][1]].many++;
  }

  if((fp = fopen(DIR, "w")) == NULL) {
    printf("Erro na abertura do arquivo");
    exit(1);
  }

  for(i = 0; i < MAXREGISTER ;i++){
    if(fwrite(&table[i], sizeof(struct Table), 1,fp) != 1)
      printf("Erro na escrita do arquivo");
  }

  fclose(fp); 
}