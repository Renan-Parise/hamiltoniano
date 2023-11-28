#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define V 4

struct Caminho {
  int path[V];
  int peso;
};

int calcularPeso(int path[], int size, int grafo[V][V]) {
  int peso = 0;
  for (int i = 0; i < size - 1; i++) {
    peso += grafo[path[i]][path[i + 1]];
  }
  peso += grafo[path[size - 1]][path[0]];
  return peso;
}

bool isSafe(int v, int pos, int path[], int grafo[V][V]) {
  if (grafo[path[pos - 1]][v] == 0)
    return false;

  for (int i = 0; i < pos; i++)
    if (path[i] == v)
      return false;

  return true;
}

bool cicloUtil(int grafo[V][V], int path[], int pos, struct Caminho *caminhos,
               int *contador) {
  if (pos == V) {
    if (grafo[path[pos - 1]][path[0]] != 0) {
      caminhos[*contador].peso = calcularPeso(path, V, grafo);
      for (int i = 0; i < V; i++) {
        caminhos[*contador].path[i] = path[i];
      }
      (*contador)++;
      return true;
    } else {
      return false;
    }
  }

  bool res = false;
  for (int v = 1; v < V; v++) {
    if (isSafe(v, pos, path, grafo)) {
      path[pos] = v;
      res = cicloUtil(grafo, path, pos + 1, caminhos, contador) || res;
      path[pos] = -1;
    }
  }

  return res;
}

int compararPaths(const void *a, const void *b) {
  return ((struct Caminho *)a)->peso - ((struct Caminho *)b)->peso;
}

void imprimePath(int path[], int size, int grafo[V][V]) {
  printf("Caminho: ");
  for (int i = 0; i < size; i++) {
    printf("%c ", 'A' + path[i]);
  }
  printf("%c", 'A' + path[0]);
  printf(" (%d)\n", calcularPeso(path, size, grafo));
}

void cicloHam(int grafo[V][V]) {
  int path[V];
  for (int i = 0; i < V; i++)
    path[i] = -1;

  path[0] = 0;

  struct Caminho caminhos[V * (V - 1)];
  int contador = 0;

  if (!cicloUtil(grafo, path, 1, caminhos, &contador)) {
    printf("Não existe ciclo Hamiltoniano no grafo.\n");
    return;
  }

  qsort(caminhos, contador, sizeof(struct Caminho), compararPaths);

  for (int i = 0; i < contador; i++)
    imprimePath(caminhos[i].path, V, grafo);
}

int main() {
  int grafo[V][V] = {{0, 4, 2, 1}, {4, 0, 13, 9}, {2, 13, 0, 8}, {1, 9, 8, 0}};

  cicloHam(grafo);

  return 0;
}
