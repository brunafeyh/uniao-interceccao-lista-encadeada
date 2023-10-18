#include <stdio.h>
#include <stdlib.h>

typedef int TipoItem;

typedef struct No {
    TipoItem info;
    struct No *prox;
} Lista;

int estaVazia(Lista *l) {
    return (l == NULL);
}

void limparLista(Lista *l) {
    if (!estaVazia(l)) {
        Lista *aux = l->prox;
        free(l);
        limparLista(aux);
    }
}

void imprimir(Lista *l) {
    if (!estaVazia(l)) {
        printf("%d ", l->info);
        imprimir(l->prox);
    } else {
        printf("\n");
    }
}

Lista *inserir(Lista *l, TipoItem info) {
    if (estaVazia(l)) {
        l = (Lista *)malloc(sizeof(Lista));
        l->info = info;
        l->prox = NULL;
        return l;
    }
    if (l->info != info) {
        l->prox = inserir(l->prox, info);
    }
    return l;
}

int pertence(Lista *l, int x) {
    if (!estaVazia(l)) {
        if (l->info == x) {
            return 1;
        } else {
            return pertence(l->prox, x);
        }
    }
    return 0;
}

Lista *concatenar(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!estaVazia(l1)) {
        aux = inserir(aux, l1->info);
        aux->prox = concatenar(l1->prox, l2);
    }

    if (estaVazia(l1) && !estaVazia(l2)) {
        aux = inserir(aux, l2->info);
        aux->prox = concatenar(l1, l2->prox);
    }

    return aux;
}

Lista *uniao(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!estaVazia(l1)) {
        if (!pertence(l2, l1->info)) {
            aux = inserir(aux, l1->info);
            aux->prox = uniao(l1->prox, l2);
        } else {
            aux = uniao(l1->prox, l2);
        }
    }

    if (estaVazia(l1) && !estaVazia(l2)) {
        aux = inserir(aux, l2->info);
        aux->prox = uniao(l1, l2->prox);
    }

    return aux;
}

Lista *intersecao(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!estaVazia(l1)) {
        if (pertence(l2, l1->info)) {
            aux = inserir(aux, l1->info);
            aux->prox = intersecao(l1->prox, l2);
        } else {
            aux = intersecao(l1->prox, l2);
        }
    }

    return aux;
}

Lista *diferenca(Lista *l1, Lista *l2) {
    Lista *aux = NULL;

    if (!estaVazia(l1)) {
        if (!pertence(l2, l1->info)) {
            aux = inserir(aux, l1->info);
            aux->prox = diferenca(l1->prox, l2);
        } else {
            aux = diferenca(l1->prox, l2);
        }
    }

    return aux;
}

int estaContido(Lista *l1, Lista *l2) {
    if (estaVazia(l2)) {
        return 1;
    }

    if (!estaVazia(l2) && pertence(l1, l2->info)) {
        return 1 * estaContido(l1, l2->prox);
    }

    return 0;
}

int main() {
    Lista *lista1 = NULL;
    Lista *lista2 = NULL;
    Lista *uniaoLista = NULL;
    Lista *intersecaoLista = NULL;
    Lista *diferencaLista = NULL;
    Lista *lista3 = NULL;
    Lista *lista4 = NULL;
    Lista *lista5 = NULL;

    lista1 = inserir(lista1, 10);
    lista1 = inserir(lista1, 20);
    lista1 = inserir(lista1, 30);
    lista1 = inserir(lista1, 40);

    lista2 = inserir(lista2, 20);
    lista2 = inserir(lista2, 30);
    lista2 = inserir(lista2, 50);
    lista2 = inserir(lista2, 60);

    printf("Lista 1: ");
    imprimir(lista1);
    printf("Lista 2: ");
    imprimir(lista2);

    printf("O elemento 30 pertence ao conjunto lista 1? %d\n", pertence(lista1, 30));
    printf("O elemento 70 pertence ao conjunto lista 1? %d\n", pertence(lista1, 70));
    printf("O elemento 50 pertence ao conjunto lista 2? %d\n", pertence(lista2, 50));

    uniaoLista = uniao(lista1, lista2);
    printf("União de Lista 1 e Lista 2: ");
    imprimir(uniaoLista);

    intersecaoLista = intersecao(lista1, lista2);
    printf("Interseção de Lista 1 e Lista 2: ");
    imprimir(intersecaoLista);

    diferencaLista = diferenca(lista1, lista2);
    printf("Diferença entre Lista 1 e Lista 2: ");
    imprimir(diferencaLista);

    lista3 = inserir(lista3, 100);
    lista3 = inserir(lista3, 200);
    lista3 = inserir(lista3, 300);

    lista4 = inserir(lista4, 200);
    lista4 = inserir(lista4, 300);
    lista4 = inserir(lista4, 400);

    printf("Lista 3: ");
    imprimir(lista3);
    printf("Lista 4: ");
    imprimir(lista4);

    printf("Lista 4 está contida na Lista 3? %d\n", estaContido(lista3, lista4));

    limparLista(lista1);
    limparLista(lista2);
    limparLista(uniaoLista);
    limparLista(intersecaoLista);
return 0;
}
