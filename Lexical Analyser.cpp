#include<bits/stdc++.h>
using namespace std;
int isKeyword(char buffer[]){
 char keywords[35][10] = {"auto", "break", "case", "char", "const", "continue", "default",
 "do", "double", "else", "enum", "extern", "float", "for", "goto",
 "if", "int", "long", "register", "return", "short", "signed",
 "sizeof", "static", "struct", "switch", "typedef", "union",
 "unsigned", "void", "volatile", "while", "printf", "scanf", "main"};

 int i, flag = 0;

 for (i = 0; i < 35; ++i){
 if (strcmp(keywords[i], buffer) == 0){
 flag = 1;
 break;
 }
 }
 return flag;
}
int main(){
 char ch;
 char buffer[15], operators[] = "&+-*/%=", delimiters[] = "{(,;)}";
 string temp = "";
 bool flag = false;
 FILE *fp;
 int i, j = 0, k, count = 0, keyCount = 0, litCount = 0, deCount = 0, idCount = 0, opCount = 0;
 fp = fopen("program.txt", "r");
 if (fp == NULL){
 cout<<"Can not open the file\n";
 exit(0);
 }
 while ((ch = fgetc(fp)) != EOF){
 for (i = 0; i < 7; ++i)
 if (ch == operators[i] && !flag){
 cout<<"Operator: "<<ch<<"\n";
 opCount++;
 count++;
 }
 for (k = 0; k < 6; ++k)
 if (ch == delimiters[k] && !flag){
 cout<<"Delimiter: "<<ch<<"\n";
 deCount++;
 count++;
 }
 if ((ch >= '0' && ch <= '9') ||(ch >= 'a' && ch <= 'z') ||(ch >= 'A' && ch <= 'Z'))
 buffer[j++] = ch;
 else if ((ch == ' ' || ch == '\n') && (j != 0)){
 buffer[j] = '\0';
 if(j == 1){
 if(buffer[0] >= '0' && buffer[0] <= '9')
 cout<<"Literal: "<<buffer[0]<<"\n";
 count++;
 litCount++;
 }
 else if (isKeyword(buffer) == 1 && !flag){
 cout<<"Keyword: "<<buffer<<"\n";
 count++;
 keyCount++;
 }
 else if (!flag){
 cout<<"Identifier: "<<buffer<<"\n";
 count++;
 idCount++;
 }
 j = 0;
 }

 if(flag == true)
 temp += ch;
 if(flag == false && ch == '"'){
 flag = true;
 temp += ch;
 }
 else if(flag == true && ch == '"'){
 flag = false;
 cout<<"Literal: "<<temp<<"\n";
 temp = "";
 litCount++;
 count++;
 }
 }
 cout<<"\nNumber of tokens: "<<count;
 cout<<"\n\nNumber of keywords: "<<keyCount;
 cout<<"\nNumber of identifiers: "<<idCount;
 cout<<"\nNumber of literals: "<<litCount;
 cout<<"\nNumber of operators: "<<opCount;
 cout<<"\nNumber of delimiters: "<<deCount;
 fclose(fp);
 return 0;
}
