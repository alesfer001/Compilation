#include <stdio.h>
#include <stdlib.h>

struct test{
  int *a;
  int b;
};

void func(const struct test *my_test){
  *(my_test->a) = 0;
  //my_test->b = 5;
}

int main(){
  struct test my_test;
  my_test.a = malloc(sizeof(int));
  *(my_test.a) = 5;
  my_test.b = 0;
  printf("a : %d, b: %d\n", (*my_test.a), (my_test.b)); //5, 0
  func(&my_test);
  printf("a : %d, b: %d\n", (*my_test.a), (my_test.b)); //0, 0
}
