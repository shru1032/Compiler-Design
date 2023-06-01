#include <stdio.h>
#include <conio.h>
#include <string.h>
int main() {
 char input[100], left[50], right[50], temp[10], tempprod[20], productions[25][50];
 int i=0, j=0, flag=0, consumed=0;

 printf("Enter the productions: ");
 scanf("%1s->%s",left,right);
 printf("%s",right);

 while(sscanf(right+consumed, "%[^|]s", temp) == 1 && consumed <= strlen(right)) {
 if(temp[0] == left[0]) {
 flag = 1;
 sprintf(productions[i++], "%s->%s%s", left, temp+1, left);
 }
 else
 sprintf(productions[i++], "%s->%s%s", left, temp, left);
 consumed += strlen(temp)+1;
 }
 if(flag == 1) {
 sprintf(productions[i++], "%s->Epsilon", left);
 printf("The productions after eliminating Left Recursion are:\n");
 for(j=0; j<i; j++)
 printf("%s\n", productions[j]);
 }
 else
 printf("The Given Grammar has no Left Recursion");
 return 0;
}
