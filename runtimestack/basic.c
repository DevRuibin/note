#include <stdio.h>
#include <stdlib.h>

int func(int a) {
  int b=10;
  return a+b;
}

void main() {
  int result;
  result=func(5);
  printf("The result is %d\n",result);
}
