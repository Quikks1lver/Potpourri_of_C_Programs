// Adam Fernandes
// March 2020
// Utilizes euclidean algorithm to find the gcd of two numbers.

#include <stdio.h>
#define BAR "====="

void swap(int *a, int *b)
{
   int temp = *a;
   *a = *b;
   *b = temp;
}

int euclidean_algorithm(int a, int b)
{
   if (!b)
   {
      printf("%s\n%d\n%s\n", BAR, a, BAR);
      return a;
   }

   if (b > a)
      swap(&a, &b);

   printf("%.2d = %.2d * %.2d + %.2d\n", a, a / b, b, a % b);
   return euclidean_algorithm(b, a % b);
}

int main(int argc, char **argv)
{
   int a, b;
   printf("Input two numbers (space in between) for euclidean algorithm GCD: ");
   scanf("%d %d", &a, &b);
   euclidean_algorithm(a, b);

   return 0;
}