#include<stdio.h>
#include<stdlib.h>
#include <string.h> // for strlength
#include "BigInteger.h"
#include <stdbool.h>
#define POWER 9
#define BASE 1000000000

// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj
{
	List val; //all the values
	int sign; 
}BigIntegerObj; 

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger()
{
	BigInteger BI = malloc(sizeof(BigIntegerObj));
	BI->val = newList();
	BI->sign = 0; 
	return BI; 
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN)
{
	if(pN != NULL && *pN != NULL)
   {
      makeZero(*pN);
      freeList(&(*pN)->val); //free the list
      free(*pN); //free pN
      *pN = NULL;
   }
}

// Access functions -----------------------------------------------------------
// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
	return (N->sign); 
}
// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
  if(sign(A) < sign(B))
  {
    return -1;
  }
  if(sign(A) > sign(B))
  {
    return 1;
  }
  if (length(A->val) > length(B->val)) //check sign
  {
    return 1;
  }
  if(length(A->val) < length(B->val))
  {
    return -1;
  }
  //loop through and count matches to return 0, A=B
  moveFront(A->val);
  moveFront(B->val);
  bool equals = (get(A->val) == get(B->val));
  while(index(A->val) != -1 && equals)
  {
      equals = (get(A->val) == get(B->val));
      moveNext(A->val);
      moveNext(B->val);
  }
  if (!equals)//checks the 2 nodes to see which is equal
  {
    if (get(A->val) > get(B->val))
      return 1;
    if (get(A->val) < get(B->val))
      return -1;
  }
  return 0; 
}
// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
  bool equal = (get(A->val) == get(B->val));
	if (sign(A) == sign(B))
  {
  
    if (length(A->val) == length(B->val))
    {
      moveFront(A->val);
      moveFront(B->val);
      while(index(A->val) != -1 && equal)
      {
        equal = (get(A->val) == get(B->val));
        moveNext(A->val);
        moveNext(B->val);
      }
      if(equal)
        return 1;
    }
  }
  return 0;
  
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
  clear(N->val);
  N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the zero state.
void negate(BigInteger N)
{
  if(sign(N) == -1)
  {
    N->sign = 1;
  }
  if(sign(N) == 1)
  {
    N->sign = -1;
  }
}

//normalize the list 
int normalize(List L)
{
  int sign = 0; 
  long q, r, u;
  long carryIn, carryOut, thisCol = 0; 

  moveFront(L);
  while(index(L) >=0)
  {
    carryIn = carryOut; 
    thisCol = get(L);
    thisCol += carryIn; 
    q = (thisCol) / BASE;
    r = (thisCol) % BASE;
    u = (r>0)?1:0; 

    thisCol = r + u*BASE;
    carryOut = q-u;
    set(L,thisCol);

    if(index(L) == (length(L)-1)) 
    {
      if(carryOut>0)
      {
        append(L,0);
      }
      else if(carryOut<0)
      {
        append(L, carryOut);
        break;
      }
      moveNext(L);
    }
  }
  while(length(L) != 0 && back(L) ==0)
  {
    deleteBack(L); 
  }
  if(length(L) != 0)
  {
    if(back(L)==0)
    {
      sign = 1; 
    }
    else if(back(L)>0)
    {
      sign = -1;
      //negateList(L);
      normalize(L); 
    }
  }
  return sign; 
  /*
  int carry = 0; 
  long tl; //tempLong
  BigInteger temp = newBigInteger();
  moveBack(B->val);
  while(index(B->val) != -1)
  {
    tl = get(B->val);
    if(tl > BASE)
    {
      if(carry == 1)
      {
        tl += carry; 
      }
      tl = tl - BASE;
      carry = 1; 
      prepend(temp->val, tl);
      movePrev(B->val);  
    }
    if(tl<0) //tl is negative
    {
      if(carry == -1)
      {
        tl = tl - carry;
      }
      tl = tl + BASE;
      carry = -1;
      prepend(temp->val, tl);
      movePrev(B->val);
    }
  }
  if(index(B->val) == -1 && (carry == 1 || carry == -1) ) 
  {
    prepend(temp->val, carry);
  } 
  //if the front is negative
  if(front(temp->val) < 0)
  {
    long neg = -1;
    moveBack(temp->val);
    while(index(temp->val) != -1)//loop to flip sign
    {
      tl = get(temp->val);
      //set temp->data to tl*-1, thus making the list flip sign 
      tl = tl*neg;  
      set(temp->val, tl);
      movePrev(temp->val);
    }
    moveBack(temp->val);
    while(index(temp->val) != -1)
    {
      tl = get(temp->val);
      if(tl<0) //tl is negative
      {
        if(carry == -1)
        {
          tl = tl - carry;
        }
      tl = tl + BASE;
      carry = -1;
      set(temp->val, tl);
      movePrev(temp->val);
      }
    }
    temp->sign = -1;
  }
  return temp; 
  */
}

// BigInteger Arithmetic operations -----------------------------------------------
// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
  int p = POWER;
  BigInteger temp = newBigInteger();
  long x; 
  int n; //length of s 
  char* buff; 
  int i;

  if(s[0] == '-')
  {
    temp->sign = -1;
    s++;
    n--;
  }
  else
  {
    temp->sign = 1;
    s++;
    n--;
  }

  if(n==0)
  {
    fprintf(stderr, "Error");
    exit(1);
  }
  buff = calloc(p+1, sizeof(char));
  for(i=n-p; i>=0; i-=p)
  {
    strncpy(buff, &s[i], p);
    if(sscanf(buff,"%ld",&x) != 1)
    {
      fprintf(stderr, "Error");
      exit(1);
    }
    append(temp->val, x);
  }
  if(i+p>0)
  {
    strncpy(buff, s, p);
    buff[i+p]='\0';
    if(sscanf(buff,"%ld",&x) != 1)
    {
      fprintf(stderr, "Error");
      exit(1);
    }
  }
  append(temp->val, x);
  free(buff);
  temp->sign = normalize(temp->val);
  return temp; 
  /*long mult = 1; 
  long value = 0; 
	if(s != NULL) //&& *s != NULL)
  {
    //if has sign, temp->sign == smth
    for(int i = 1; i < strlen(s); i++)
    {
      value += (strlen(s)-1) * mult;  
      mult *= 10;
      if (POWER%i == 0)
      {
        append(temp->val, value);
        mult = 1;
        value = 0; 
      }
    }
    return temp;
  }*/

  /*
  if(s == NULL)
  {
    printf("BigInteger Error: calling stringToBigInteger() on NULL string reference\n");
    exit(1);
  }

  BigInteger temp = newBigInteger();
  int remain = strlen(s) % POWER; 

  if(s[0] == '+')
  {
    temp->sign = 1;
  }
  if(s[0] == '-')
  {
    temp->sign = -1;
  }

  char* tempC = malloc(sizeOf(s) * POWER); 
  //loop for a new string w/o sign
  for(int i = 0; i<strlen(s); i++)
  {
    if(s[i] != '+' || s[i] != '-')
    {
      tempC[i] = s[i]; 
    }
  } //tempC should have just numbers
  printf("%s\n", tempC); 

  for(int i = 0; i<strlen(tempC); i++)
  {
    for(int j = 0; j<POWER; j++)
    {
      tempC[j] = s[i];  
      //remain needed
    }
    prepend(temp->val, atol(tempC));
  }

  //memset

  return temp; 
  */

}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
  BigInteger temp = newBigInteger();
  List L = N->val;
  List tL = temp->val; 
  moveBack(L);
  while(index(L) != -1)
  {
    append(tL, get(L)); 
    moveNext(L);
  }
  return temp; 
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its current state: S = A + B
//S == A || S == B shouldn't matter 
//A < B length is off
//A > B length is off
//A == B (value or memory location) hmmmm
//A == 0 || B == 0 return the other 
//A < 0 && B < 0 
//A < 0 && B > 0
//A > 0 && B < 0
//A > 0 && B > 0
void add(BigInteger S, BigInteger A, BigInteger B)
{
  makeZero(S);
  S = sum(A,B); //this is too simple. Don't I need a loop? 
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
//A < B length is off
//A > B length is off
//A == B (value or memory location) hmmmm
//A == 0 || B == 0 return the other 
//A < 0 && B < 0 
//A < 0 && B > 0
//A > 0 && B < 0
//A > 0 && B > 0
BigInteger sum(BigInteger A, BigInteger B)
{
  BigInteger temp = newBigInteger();
  long num;
  if(sign(A) == 1 && sign(B) == 1)
  {
    if(length(A->val) > length(B->val))
    {
      //move back both and add until B runs out
      moveBack(A->val);
      moveBack(B->val);
      while(index(B->val) != -1)
      {
        num = (get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(A->val) != -1)
      {
        num = get(A->val);
        prepend(temp->val, num);
        movePrev(A->val);
      }
      //normalize
      normalize(temp->val); 

    }
    if(length(A->val) < length(B->val))
    {
      //move back both and add until A runs out
      moveBack(A->val);
      moveBack(B->val);
      while(index(A->val) != -1) //shortest one
      {
        num = (get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(B->val) != -1) //rest of it
      {
        num = get(B->val);
        prepend(temp->val, num);
        movePrev(B->val);
      }
      //normalize
      normalize(temp->val);
    }
    if(length(A->val) == length(B->val))
    {
      //add without worry
      while(index(A->val) != -1) //doesnt matter which one
      {
        num = (get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      //normalize
      normalize(temp->val);
    }
  }
  if( (sign(A) == -1 && sign(B) == 1) || (sign(B) == -1 && sign(A) == 1) ) 
  {
    temp = diff(A, B);
    return temp;
  }
  if(sign(A) == 0 || sign(B) == 0)
  {
    if(length(B->val) > length(A->val))
    {
      //A is zero
      return B;
    }
    if(length(A->val) > length(B->val))
    {
      //B is zero
      return A;
    }
    if(length(A->val) == length(B->val))
    {
      //doesn't matter so A will do 
      //same length and sign 
      return A;
    }
  }
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
  makeZero(D);
  D = diff(A, B);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
  BigInteger temp = newBigInteger();
  long num;
  if(sign(A) == -1 && sign(B) == 1)
  {
    //-A-B= A+B and sign change
    temp = sum(A, B);
    negate(temp);
    return temp;
  }
  if(sign(A) == -1 && sign(B) == -1)
  {
     //-A--B = -A+B
    if(length(B->val) > length(A->val)) //B is bigger
    {
      while(index(A->val) != -1) 
      {
        num = (-1*get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(B->val) != -1) 
      {
        num = (get(B->val)); 
        prepend(temp->val, num);
        movePrev(B->val);
      }
      //normalize
      normalize(temp);
    }
    if(length(A->val) > length(B->val)) //-A--B = -A+B, A is bigger
    {
      while(index(B->val) != -1) 
      {
        num = (-1*get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(A->val) != -1) 
      {
        num = (get(A->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
      }
      //normalize
      normalize(temp->val);
    }
    if(length(A->val) == length(B->val))
    {
      while(index(B->val) != -1) //doesnt matter
      {
        num = (-1*get(A->val)) + (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      //normalize
      normalize(temp->val);
    }
  }
  if(sign(A) == 1 && sign(B) == -1)
  {
    //A--B = A+B = sum
    temp = sum(A,B);
    return temp;
  }
  if(sign(A) == 1 && sign(B) == 1)
  {
    //A-B= A-B 
    if(length(B->val) > length(A->val))//B is bigger
    {
      while(index(A->val) != -1) 
      {
        num = (get(A->val)) - (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(B->val) != -1) 
      {
        num = (get(B->val)); 
        prepend(temp->val, num);
        movePrev(B->val);
      }
      //normalize
      normalize(temp->val);
    }
    if(length(A->val) > length(B->val)) //A is bigger
    {
      while(index(B->val) != -1) 
      {
        num = (get(A->val)) - (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      while(index(A->val) != -1) 
      {
        num = (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
      }
      //normalize
      normalize(temp->val);
    }
    if(length(A->val) == length(B->val))
    {
      while(index(B->val) != -1) 
      {
        num = (get(A->val)) - (get(B->val)); 
        prepend(temp->val, num);
        movePrev(A->val);
        movePrev(B->val);
      }
      //normalize
      normalize(temp->val);
    }
  }
  if(sign(A) == 0 && (sign(B) == 1 || sign(B) == -1) )
  {
    //0 - - B = +B
    if(sign(B) == -1)
    {
      temp = B;
      negate(temp);
      return temp;
    }
    else//0 - B = -B
    {
      return temp; 
    }
  }
  if(sign(B) == 0 && (sign(A) == 1 || sign(A) == -1) )
  {
    //-A - 0 = -A 
    //A - 0 = A 
    //length doesn't matter 
    return A; 
    
  }
}

//-----Helper Function for prod---------
long mult(long A, long B) 
{
  long result; 
  while(B!=0)
  {
    if(B%2 == 0)
    {
      result = result + A;
    }
    A = 2*A;
    B = B/2; 
  }
  return result; 
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
  BigInteger temp = newBigInteger();
  if( (sign(A) == 0 && (sign(B) == -1 || sign(B) == 1 )) || (sign(B) == 0 && (sign(A) == -1 || sign(A) == 1 )) ) 
  {
    //if either is zero
    makeZero(temp);
  }

  if( (sign(A) == -1 && sign(B) == 1) || (sign(A) == 1 && sign(B) == -1) ) //if either is negative
  {
    //while loop
    int k = 0; 
    int i;
    List BL = B->val; 
    List AL = A->val;
    moveBack(BL);
    moveBack(AL);
    while(index(BL) != -1)
    {
      int s = 0;
      int c = 0; 
      while(index(AL) != -1)
      {
        s = (get(AL)*get(BL) + c) % 10;
        c = (get(AL)*get(BL) + c) / 10;
        prepend(temp->val, s);
        movePrev(AL);
      }
    if(c != 0)
    {
      prepend(temp->val, c);
    }
    for(int i = 0; i < k; i++)
    {
      append(P->val, 0); 

    }
    //add smth
    add(temp, temp, P);
    k++;
    movePrev(BL); 
    }
    temp->sign = -1;
  }
  if(sign(A) == sign(B)) //sign doeesn't matter
  {
    temp->sign = 1; 
  }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
  BigInteger temp = newBigInteger();
  multiply(temp,A,B);
  return temp;
}


// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
   List L = N->val;
   moveBack(L); 
   while(L != NULL)
   {
     printf("%lu ", get(L));
     movePrev(L);
   }
}