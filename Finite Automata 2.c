//Finite automata for regular expression a+b*(c+d)+a*c+
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int transition(int state, char input){
 int nextst;
 switch(state){
 case 0:
 switch(input){
 case 'a':
 return 1;
 break;
 case 'b': case 'd':
 return -1;
 break;
 case 'c':
 return 4;
 break;
 }
 break;
 case 1:
 switch(input){
 case 'a':
 return 1;
 break;
 case 'b':
 return 2;
 break;
 case 'c':
 return 5;
 break;
 case 'd':
 return 3;
 break;
 }
 break;
 case 2:
 switch(input){
 case 'a':
 return -1;
 break;
 case 'b':
 return 2;
 break;
 case 'c': case 'd':
 return 3;
 break;
 }
 break;
 case 3:
 switch(input){
 case 'a': case 'b': case 'c': case 'd':
 return -1;
 break;
 }
 break;
 case 4: case 5:
 switch(input){
 case 'a': case 'b': case 'd':
 return -1;
 break;
 case 'c':
 return 4;
 break;
 }
 break;
 }
}
void checkValid(int state){
 if (state == 3 || state == 4 || state==5){
 printf("String Accepted\n");
 }
 else{
 printf("String Rejected\n");
 }
}
int main(){
 char re[50];
 printf("Enter the string: ");
 scanf("%s", re);
 int len = strlen(re);
 int newst=0;
 printf("0 -> ");
 for (int i =0; i<len; i++){
 newst = transition(newst, re[i]);
 printf("%d -> ", newst);
 }
 printf("\n");
 checkValid(newst);
}
