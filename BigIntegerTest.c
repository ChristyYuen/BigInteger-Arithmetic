//test testing 
#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h" 

int main(int argc, char* argv[]){

  FILE *in, *out;

  char* test = "123456789"; 
  char* test2 = "-987654321";
  char* test3 = "8594275484";

  BigInteger A = stringToBigInteger(test);
  BigInteger B = stringToBigInteger(test2);
  BigInteger C = stringToBigInteger(test3);

  //A
  printf("BigInteger A:\n");
  printBigInteger(out, A);
  printf("\n");

  //B 
  printf("BigInteger B:\n");
  printBigInteger(out, B);
  printf("\n");

  //C 
  printf("BigInteger C:\n");
  printBigInteger(out, C);
  printf("\n");

  freeBigInteger(&A);
  freeBigInteger(&B);
  freeBigInteger(&C);
    

  return EXIT_SUCCESS;
}