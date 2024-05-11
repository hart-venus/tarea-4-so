// alloc.h
#define ALLOCSIZE 10000 // tamaño del espacio disponible (cambiar para verificar funcionamiento)

static char allocbuf[ALLOCSIZE]; // almacenamiento para alloc
static char *allocp1 = allocbuf; // siguiente posición libre para el área 1
static char *allocp2 = allocbuf + ALLOCSIZE; // siguiente posición libre para el área 2

char *alloc(int n, int i) { // regresa un puntero a n caracteres
  if (i == 1) { // Top-down
    if (allocp2 - allocp1 >= n) {
      allocp1 += n;
      return allocp1 - n;
    } else {
      return 0;
    }
  } else if (i == 2) { // Bottom-up
    if (allocp2 - allocp1 >= n) {
      allocp2 -= n;
      return allocp2;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

void afree(char *p) { // libera la memoria apuntada por p
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE) {
    if (p < allocp1) {
      allocp1 = p;
    } else if (p >= allocp2) {
      allocp2 = p + (allocp2 - p);
    }
  }
}

#include <stdio.h>

int main() {
  char *p1 = alloc(100, 1);
  char *p2 = alloc(200, 2);
  char *p3 = alloc(300, 1);
  char *p4 = alloc(400, 2);

  printf("p1: %p\n", p1);
  printf("p2: %p\n", p2);
  printf("p3: %p\n", p3);
  printf("p4: %p\n", p4);

  afree(p1);
  afree(p2);

  char *p5 = alloc(500, 1);
  char *p6 = alloc(600, 2);

  printf("p5: %p\n", p5);
  printf("p6: %p\n", p6);

  return 0;
}
