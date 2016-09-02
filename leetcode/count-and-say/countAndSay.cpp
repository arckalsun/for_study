#include<stdio.h>
#include"countAndSay.h"
Solution solu;

int main(void)
{
  int n = 2;
  char* str = solu.countAndSay(n);
  printf("count: %2d\tsay: %5s\n",n,str);
  return 0;
}


