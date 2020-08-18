// Adam Fernandes
// March 2020
// Utilizes modular exponentiation to solve insane modular arithmetic problems.

#include <stdio.h>
#include <stdlib.h>

int *createArray(int capacity)
{
   return calloc(capacity, sizeof(int));
}

// Obtains number of elements in a binary string of base 10 parameter n.
int getCapacityNumber(int n)
{
   int count;

   if (n <= 1)
      return 1;
   
   for (count = 0; n > 0; count++)
      n /= 2;

   return count;
}

// Creates binary string where array[0] is 2^0 and array[length - 1] = 2^(length - 1).
int *createBitString(int n, int cap)
{
   int count, *arr = createArray(cap);

   for (count = 0; n > 0; count++, n /= 2)
      arr[count] = (n % 2) ? 1 : 0;

   return arr;
}

int calculateMod(int *binaryArr, int num, int mod, int capacity)
{
   int i, current = num, temp;
   unsigned long long int runningProduct = 1;

   for (i = 0; i < capacity; i++)
   {
      temp = current % mod;
      if (binaryArr[i])
         runningProduct *= temp;
      printf("%d to the power %d ^ %d = %d, running product = %llu\n", num, 2, i, temp, runningProduct);
      current = temp * temp;  
   }

   return runningProduct % mod;
}

int main(void)
{
   int a, b, c, *binaryArr, capacity;
   
   printf("Input 3 numbers (spaces in between) for modular exponentiation: a^b %% c\t");
   scanf("%d %d %d", &a, &b, &c);

   capacity = getCapacityNumber(b);
   binaryArr = createBitString(b, capacity);
   
   printf("\n%d ^ %d %% %d:\t%d\n", a, b, c, calculateMod(binaryArr, a, c, capacity));
}