#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n) {
  //para filas
  for (int i = 0 ; i < 9 ; i++) {
    int fila[10] = {0};
    for (int j = 0 ; j < 9 ; j++) {
      int valor = n->sudo[i][j];
      if (valor == 0) continue;
      if (fila[valor] == 1) return 0;
      fila[valor] = 1;
    }
  }

  //para columnas
  for (int j = 0 ; j < 9 ; j++) {
    int columna[10] = {0};
    for (int i = 0 ; i < 9 ; i++) {
      int valor = n->sudo[i][j];
      if (valor == 0) continue;
      if (columna[valor] == 1) return 0;
      columna[valor] = 1;
    }
  }

  //para subcajas
  for (int k = 0 ; k < 9 ; k++) {
    int box[10] = {0};
    for (int p = 0 ; p < 9 ; p++) {
      int i = 3*(k/3) + (p/3) ;
      int j = 3*(k%3) + (p%3) ;
      int valor = n->sudo[i][j];
      if (valor == 0) continue;
      if (box[valor] == 1) return 0;
      box[valor] = 1;
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n) {
  List* list=createList();
  for (int i = 0 ; i < 9 ; i++) {
    for (int j = 0 ; j < 9 ; j++) {
      if (n->sudo[i][j] == 0) {
        for (int k = 1 ; k <= 9 ; k++) {
          Node *nuevo = copy(n); 
          nuevo->sudo[i][j] = k;
          if (is_valid(nuevo)) 
            pushBack(list, nuevo); 
          else
            free(nuevo);
        }
        return list;
      }
    }
  }    
  return list;
}


int is_final(Node* n) {
  for (int i = 0 ; i < 9 ; i++) {
    for (int j = 0 ; j < 9 ; j++) {
      int num = n->sudo[i][j];
      if (num == 0) {
        return 0; 
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont) {
  Stack *stack = createStack();
  push(stack, initial);
  free(initial);
  while (stack != NULL) {
    Node *n = top(stack);
    pop(stack);
    if (is_final(n)) return n;
    List *adj = get_adj_nodes(n);
    while (adj != NULL) {
      Node *n1 = first(adj);
      push(stack, n1);
      popFront(adj);
    }
    clean(adj);
    free(n);
    (*cont)++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/