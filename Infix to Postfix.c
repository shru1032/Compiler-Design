#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAX 50
void push(char[],char);
int pop();
int prec(char);
int top = 0;
void main() {
 int op_count=0;
 char stack[MAX], exps[MAX], symbols[MAX];
 int i=0, j=0, len, check;
 printf("Enter the infix expression:\n");
 while((symbols[i]=getchar())!='\n') {
 if(symbols[i]!=' ' || symbols[i]!='\t') {
 if(symbols[i]=='+' || symbols[i]=='-' || symbols[i]=='/' || symbols[i]=='*' || symbols[i]=='^')
 op_count++;
 i++;
 }
 }
 symbols[i]='#';
 symbols[++i]='\0';
 len = strlen(symbols);
 stack[top] = '#';
 for(i=0; i<=len; i++) {
 if(symbols[i]>='a' && symbols[i]<='z') {
 exps[j]=symbols[i];
 j++;
 }
 switch(symbols[i]) {
 case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
 exps[j]=symbols[i];
 j++;
 break;
 case '+': case '-': case '*': case '/': case '^':
 exps[j++] = ' ';
 while(prec(symbols[i]) <= prec(stack[top])) {
 exps[j] = stack[top];
 pop();
 j++;
 }
 if(prec(symbols[i]) > prec(stack[top])) {
 push(stack, symbols[i]);
 }
 break;
 case '(':
 push(stack,symbols[i]);
 break;
 case ')':
 while(stack[top]!='(') {
 exps[j] = stack[top];
 pop();
 j++;
 }
 pop();
 break;
 case '#':
 exps[j++] = ' ';
 while(stack[top]!='#') {
 exps[j] = stack[top];
 pop();
 j++;
 }
 pop();
 break;
 }
 }
 exps[j]='\0';
 printf("Postfix: %s", exps);
}
int prec(char a) {
 if(a=='^')
 return 3;
 else if(a=='*' || a=='/' || a=='%')
 return 2;
 else if(a=='+' || a=='-')
 return 1;
 else if(a=='(')
 return 0;
 else
 return -1;
}
void push(char stack[], char ele) {
 if(top>=MAX) {
 printf("\nStack Overflow");
 exit(1);
 }
 stack[++top] = ele;
}
int pop() {
 if(top<0) {
 printf("\nStack Underflow");
 exit(1);
 }
 top = top - 1;
 return top;
}
