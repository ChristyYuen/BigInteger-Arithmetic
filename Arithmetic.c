#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[])
{
	FILE *in, *out;
    if( argc != 3 )
    {
    	printf("Usage: %s <input file> <output file>\n", argv[0]);
     	exit(1);
    }

    // open files for reading and writing 
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL )
    {
     	printf("Unable to open file %s for reading\n", argv[1]);
     	exit(1);
    }
    if( out==NULL )
    {
    	printf("Unable to open file %s for writing\n", argv[2]);
    	exit(1);
    }

    int numA, numB;
    char* sA; 
    char* sB; 

    fscanf (in, "%d", &numA);
    fscanf (in, "%s", sA);
    fscanf (in, "%d", &numB);
    fscanf (in, "%s", sB);

    BigInteger A = stringToBigInteger(sA);
    BigInteger B = stringToBigInteger(sB);

    BigInteger C, D, E, F, G, H, I, J, temp1, temp2;

    //𝐴, 𝐵, 𝐴 + 𝐵, 𝐴 − 𝐵, 𝐴 − 𝐴, 3𝐴 − 2𝐵, 𝐴𝐵, 𝐴^2, B^2, 9A^4 + 16B^5 

    //A
 	  printf("BigInteger A:\n");
    printBigInteger(out, A);
    printf("\n");

    //B 
    printf("BigInteger B:\n");
    printBigInteger(out, B);
    printf("\n");

    //A+B 
    printf("A+B:\n");
    C = sum(A,B);
    printBigInteger(out, C);
    printf("\n");

    //A-B 
    printf("A+B:\n");
    D = diff(A,B);
    printBigInteger(out, D);
    printf("\n");

    //A-A 
    printf("A-A:\n");
    E = diff(A,A);
    printBigInteger(out, E);
    printf("\n");

    //3A-2B
    printf("3A-2B:\n"); 
    F = diff(sum(A,sum(A,A)), sum(B,B));
    printBigInteger(out, F);
    printf("\n");

    //AB
    printf("AB:\n");
    G = prod(A,B);
    printBigInteger(out, G);
    printf("\n");

    //A^2
    printf("A^2:\n");
    H = prod(A,A);
    printBigInteger(out, H);
    printf("\n");

    //B^2
    printf("B^2:\n");
    I = prod(B,B);
    printBigInteger(out, I);
    printf("\n");

    //9A^4 + 16B^5
    printf("9A^4 + 16B^5:\n");
    temp1 = prod(A,prod(A,prod(A,A))); //A^4
    //temp1 = temp1*((long)9); 
    printBigInteger(out, J);
    printf("\n");

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&I);
    freeBigInteger(&J);
    

    return EXIT_SUCCESS;
}
