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
// cria pilha
pilha criaPilha(){
    pilha p = malloc(sizeof(pilha));
    p->top = NULL;
    return p;
}
//empilha
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
// desempilha
int pop(pilha t){
    link temp = t->top;
    int valor = temp->nro;
    if(t->top != NULL)
        t->top = t->top->next;
    return valor;
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

int topo(pilha p){
	return p->top->nro;
}


/* Transforma a notação infixa para a notação posfixa */
int infixoParaPosfixo (char * entrada, char * saida, int n)
{
    pilha p = criaPilha();
    int i, k;
    int j = 0;
    char c;
    push(p, '(');
    for (i = 0; entrada[i] != '\0' &&  i < n; i++)
        {
            if((j-1 > 0) && (saida[j-1] != ' '))
                saida[j++]  = ' ';
            if(entrada[i] == '(') {
                push(p, entrada[i]);
            } else if(entrada[i] == ')'){
                while (1) {
                    c = pop(p);
                    if(c == '(') break;
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
            } else if((entrada[i] == '+') || (entrada[i] == '-')){
                while (1) {
                    c = topo(p);
                    if(c == '(') break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if((entrada[i] == '*') || (entrada[i] == '/')) {
                while (1) {
                    c = topo(p);
                    if(c == '(' || c == '+' || c == '-'  ) break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if (entrada[i] >= '0' && entrada[i] <= '9') {
                while (entrada[i] >= '0' && entrada[i] <= '9') {
                    saida[j++] = entrada[i];
                    i++;
                }
                saida[j++] = ' ';
                i--;
            }

        }
    while (1) {
        c = pop(p);
        if(c == '(') break;
        saida[j++] = c;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    return 0;
}

int calcula ( char * s ) {
    int i = 0;
    int d = 0,k;
    int numero = 0;
    pilha p = criaPilha();
    int resultado ;
    int a,b;
    while  (s[i] != '\0') {
        if(s[i] >= '0' && s[i] <= '9' ) {
            sscanf(&s[i], "%d", & numero);
            while(s[i] >= '0' && s[i] <= '9')
                i++;
            i--;
            push(p, numero);
        } else if (s[i] == '+') {
            b = pop(p);
            a = pop(p);
            push (p, a + b);
        } else if (s[i] == '-') {
            b = pop(p);
            a = pop(p);
            push (p, a - b);
        } else if (s[i] == '*') {
            b = pop(p);
            a = pop(p);
            push (p, a * b);
        } else if (s[i] == '/') {
            b = pop(p);
            a = pop(p);
            push (p, a/b);
        }
        i++;
    }

    resultado = topo(p);
    return resultado;
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
              infixoParaPosfixo(infixo, posfixo, 255);
              printf("%d\n", calcula(posfixo));
        }
        else
            puts("Parentesis mal formado");
    }
    return 0;
}
