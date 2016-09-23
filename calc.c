#include <stdio.h>
#include <stdlib.h>
typedef struct Node * link;
struct Node{
    int nro;
    link next;
};
typedef struct Pilha{
    link top;
} * pilha;

pilha criaPilha(){
    pilha p;
    p = malloc(sizeof(pilha));
    p->top = NULL;
    return p;
}

void push(pilha t, int n){
    link temp;
    temp = malloc(sizeof(link));
    if(t->top == NULL){
        temp->nro = n;
        temp->next = NULL;
        t->top = temp;
    }
    else{
        temp->nro = n;
        temp->next = t->top;
        t->top = temp;
    }
}

void pop(pilha t){
    link temp = t;
    if(t->top != NULL)
        t->top = t->top->next;
    else
        puts("pilha vazia");
}

int imprime(pilha f){
    link temp = f->top;
    while(temp != NULL){
        printf("%d\n", temp->nro);
        temp = temp->next;
    }
}

int bemEncaixado(char* s){
    pilha verifica = criaPilha();
    int i, r = 1;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '(')
            push(verifica, 1);
        else if (s[i] == ')')
            verifica->top == NULL ? r = 0 : pop(verifica);
    }
    if(verifica->top != NULL)
        r = 0;
    return r;
}


int main(){
    char infixo[255] ;
    char posfixo[255];
    printf("Sou uma calculadora de inteiros implementado com pilha!\n");
    printf("Digite quit para sair !\n");
    printf ("> ");
    while(fgets(infixo, 255, stdin) != NULL) {
        if(strcmp(infixo, "quit\n") == 0)  {
            printf ("morri !\n");
            return 0;
        }
        if(bemEncaixado(infixo)){
            printf("%s", infixo);
        }
        else
            puts("Parenteses mal formado");
    }
    return 0;
}
