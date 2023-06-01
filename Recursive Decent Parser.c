// This code implements a recursive descent parser for a simple arithmetic expression language
// that supports addition and multiplication operators, parentheses for grouping, and single-letter
// variables represented by the letter "i". The grammar for the language is:
// E -> T | T + E
// T -> F | F * T
// F -> ( E ) | i
#include<iostream>
#include<string>
#include<deque>
using namespace std;
int n,n1,n2;
int getPosition(string arr[], string q, int size)
{
 for(int i=0;i<size;i++)
 {
 if(q == arr[i])
 return i;
 }
 return -1;
}
void E(string);
void T(string);
void F(string);
string input;
int index = 0;
int main()
{
 cout<<"Enter the input string: ";
 getline(cin, input);
 n1 = input.size();
 input.push_back('$');
 E(input);
 if(index == n1 && input[index] == '$')
 cout<<"String Accepted"<<endl;
 else
 cout<<"String Rejected"<<endl;
 return 0;
}
void E(string str)
{
 cout<<"E"<<endl;
 T(str);
 if(str[index] == '+')
 {
 index++;
 E(str);
 }
}
void T(string str)
{
 cout<<"T"<<endl;
 F(str);
 if(str[index] == '*')
 {
 index++;
 T(str);
 }
}
void F(string str)
{
 cout<<"F"<<endl;
 if(str[index] == '(')
 {
 index++;
 E(str);
 if(str[index] == ')')
 index++;
 else
 cout<<"String Rejected"<<endl;
 }
 else if(str[index] == 'i')
 {
 index++;
 }
 else
 {
 cout<<"String Rejected"<<endl;
 }
}
