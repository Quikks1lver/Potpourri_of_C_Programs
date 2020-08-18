// Adam Fernandes
// August 2020
// This program converts infix expressions into postfix.

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 256
#define STACK_ERROR 0

typedef struct node {
   int data;
   struct node *next;
} node;

typedef struct stack {
   int capacity;
   int size;
   node *head;
} stack;

node *createNode(int data) {
   node *res = malloc(sizeof(node));
   res->data = data;
   res->next = NULL;
   return res;
}

stack *createStack(int capacity) {
   stack *res = malloc(sizeof(stack));
   res->capacity = capacity;
   res->size = 0;
   res->head = NULL;
   return res;
}

int isEmpty(stack *s) {
   return (s == NULL || s->size == 0);   
}

int isFull(stack *s) {
   return (s == NULL || s->size >= s->capacity);
}

int push(stack *s, int data) {
   node *temp;
   
   if (isFull(s))
      return STACK_ERROR;
   
   temp = s->head;
   s->head = createNode(data);
   s->head->next = temp;
   s->size++;

   return 1;
}

int pop(stack *s) {
   int data;
   node *temp;
   
   if (isEmpty(s))
      return STACK_ERROR;
   
   data = s->head->data;
   temp = s->head;
   s->head = s->head->next;
   s->size--;
   free(temp);

   return data;
}

void printPop(stack *s) {
   if (isEmpty(s))
      return;
   printf("%c ", pop(s));
   fflush(stdout);
}

void printStack(stack *s) {
   node *temp;
   
   if (s == NULL || s->size <= 0) {
      printf("(Empty stack)\n");
      return;
   }

   printf("Size %d | ", s->size);
   temp = s->head;
   while (temp != NULL) {
      printf("%c%s", temp->data, (temp->next == NULL) ? "\n" : " -> ");
      temp = temp->next;
   }
}

stack *freeStack(stack *s) {
   node *temp, *temp1;
   
   if (s == NULL)
      return NULL;
   
   temp = s->head;
   while (temp != NULL) {
      temp1 = temp;
      temp = temp->next;
      free(temp1);
   }
   free(s);
   
   return NULL;
}

int peek(stack *s) {
   if (isEmpty(s) || s->head == NULL)
      return STACK_ERROR;
   
   return s->head->data;
}

int isOperator(char c) {
   return (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')');
}

int keepGoing(char curOp, char peekedOp) {
   if (peekedOp == '(')
      return 0;
   // + and -
   else if (curOp == '+' || curOp == '-') {
      return 1;
   }
   // * and /
   else {
      if (peekedOp == '*' || peekedOp == '/')
         return 1;
      else
         return 0;
   }
}

void infixToPostfix(char *input, int len) {
   int i = 0, j;
   char temp[MAX_STR_LEN] = "\0";
   char c;
   stack *s = createStack(len);

   if (input == NULL)
      return;
   
   while (i < len) {
      c = input[i];
      if (isspace(c)) {
         i++;
         continue;
      }
      else if (isdigit(c)) {
         j = 0;
         while (i < len && isdigit(c)) {
            temp[j++] = c;
            i++;
            c = input[i];
         }
         temp[j] = '\0';
         printf("%s ", temp);
         // fflush(stdout);
         temp[0] = '\0';
         i--;
      }
      else if (isalnum(c)) {
         printf("%c ", c);
         // fflush(stdout);
      }
      else if (isOperator(c)) {
         if (c == '(')
            push(s, c);
         else if (c == ')') {
            while (!isEmpty(s) && peek(s) != '(')
               printPop(s);
            pop(s);
         }
         else {
            while (!isEmpty(s) && keepGoing(c, peek(s)))
               printPop(s);
            push(s, c);
         }
      }
      i++;
   }

   while (!isEmpty(s))
      printPop(s);
   
   printf("\n");
   freeStack(s);
}

int main(void) {
   char buffer[MAX_STR_LEN];
   int a, len;
   

   printf("Input a string of infix to be converted into postfix.\n");
   printf("~~~DO NOT COPY PASTE AS CHARACTERS ARE SOMETIMES DIFFERENT~~~\n");
   fgets(buffer, MAX_STR_LEN, stdin);
   len = strlen(buffer);

   infixToPostfix(buffer, len);

   return 0;
}