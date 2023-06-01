//Finite automata for regular expression 0*1+ (0+1)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int transition(int state, char input){
 int nextst;
 switch(state){
 case 0:
 switch(input){
 case '0':
 return 0;
 break;
 case '1':
 return 1;
 break;
 }
 break;
 case 1:
 switch(input){
 case '0':
 return 3;
 break;
 case '1':
 return 2;
 break;
 }
 break;
 case 2:
 switch(input){
 case '0':
 return 3;
 break;
 case '1':
 return 2;
 break;
 }
 break;
 case 3:
 switch(input){
 case '0': case '1':
 return -1;
 break;
 }
 break;
 }
}
void checkValid(int state){
 int flag=0;
 if (state == 2 || state == 3){
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
