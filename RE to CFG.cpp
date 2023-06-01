#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR 100
struct Rule {
 char left;
 union {
 char terminal;
 struct {
 struct Rule *next1;
 char op;
 struct Rule *next2;
 };
 };
 bool is_terminal;
};
int find_union_concat(char const *regexstr, int const start, int const end);
int find_kleene(char const *regexstr, int const start, int const end);
int find_open_parens(char const *regexstr, int const start, int const end);
int find_closed_parens(char const *regexstr, int const start, int const end);
struct Rule *form_rules(char const *regexstr, int start, int end);
void print_rules(struct Rule *symbol);
void free_rules(struct Rule *symbol);
int nt_count = -1;
int main(int argc, char **argv) {
 char const regexstr[] = "0.1 | 1.0 (1.1)*";
 struct Rule *start = form_rules(regexstr, 0, strnlen(regexstr, MAX_STR));
 printf("Regular Expression: %s\n", regexstr);
 printf("\nStart Symbol of Grammar: %c\nRules:", start->left);
 print_rules(start);
 free_rules(start);
 return 0;
}
int find_union_concat(char const *regexstr, int const start, int const end) {
 for ( int i = start; i < end; i++ ) {
 if ( regexstr[i] == '.' || regexstr[i] == '|' ) {
 return i;
 }
 }
 return -1;
}
int find_kleene(char const *regexstr, int const start, int const end) {
 for ( int i = start; i < end; i++ ) {
 if ( regexstr[i] == '*' ) {
 return i;
 }
 }
 return -1;
}
int find_open_parens(char const *regexstr, int const start, int const end) {
 for ( int i = start; i < end; i++ ) {
 if ( regexstr[i] == '(' ) {
 return i;
 }
 }
 return -1;
}
int find_closed_parens(char const *regexstr, int const start, int const end) {
 for ( int i = start; i < end; i++ ) {
 if ( regexstr[i] == ')' ) {
 return i;
 }
 }
 return -1;
}
struct Rule * form_rules(char const *regexstr, int start, int end) {
 nt_count++;

 struct Rule *n = ( struct Rule * ) malloc(sizeof(struct Rule));
 int union_concat_index = find_union_concat(regexstr, start, end);
 int kleene_index = find_kleene(regexstr, start, end);
 int open_paren_index = find_open_parens(regexstr, start, end);
 int closed_paren_index = find_closed_parens(regexstr, start, end);

 n->left = nt_count + 'A';

 if ( open_paren_index != -1 && open_paren_index == start ) {
 n->is_terminal = false;
 int union_concat_after_paren = find_union_concat(regexstr, closed_paren_index + 1, end);
 if ( union_concat_after_paren != -1 ) {
 n->op = regexstr[union_concat_after_paren];
 n->next1 = form_rules(regexstr, start, union_concat_after_paren);
 n->next2 = form_rules(regexstr, union_concat_after_paren + 1, end);
 }
 else {
 n->op = regexstr[closed_paren_index + 1];
 n->next1 = form_rules(regexstr, start + 1, closed_paren_index);
 if ( n->op != '*' ) {
 n->next2 = form_rules(regexstr, closed_paren_index + 2, end);
 }
 }
 }
 else if ( union_concat_index != -1 ) {
 n->is_terminal = false;
 n->op = regexstr[union_concat_index];
 n->next1 = form_rules(regexstr, start, union_concat_index);
 n->next2 = form_rules(regexstr, union_concat_index + 1, end);
 }
 else if ( kleene_index != -1 ) {
 n->is_terminal = false;
 n->op = regexstr[kleene_index];
 n->next1 = form_rules(regexstr, start, kleene_index);
 }
 else {
 n->is_terminal = true;
 n->terminal = regexstr[start];
 }
 return n;
}
void print_rules(struct Rule *symbol) {
 if ( symbol->is_terminal == false ) {
 if ( symbol->op != '*' ) {
 printf("\t%c->%c%c%c\n",
 symbol->left,
 (symbol->next1->is_terminal == true) ? symbol->next1->terminal
 : symbol->next1->left,
 (symbol->op == '|') ? '|' : '\0',
 (symbol->next2->is_terminal == true) ? symbol->next2->terminal
 : symbol->next2->left);
 if ( symbol->next1->is_terminal == false ) {
 print_rules(symbol->next1);
 }
 if ( symbol->next2->is_terminal == false ) {
 print_rules(symbol->next2);
 }
 } else {
 printf("\t%c->%c%c|e\n",
 symbol->left,
 (symbol->next1->is_terminal == true) ? symbol->next1->terminal
 : symbol->next1->left,
 symbol->left);
 if ( symbol->next1->is_terminal == false ) {
 print_rules(symbol->next1);
 }
 }
 } else {
 printf("\t%c->%c\n", symbol->left, symbol->terminal);
 }
}
void free_rules(struct Rule *symbol) {
 if ( symbol->is_terminal == false ) {
 free_rules(symbol->next1);
 if ( symbol->op != '*' ) {
 free_rules(symbol->next2);
 }
 }
 free(symbol);
}
