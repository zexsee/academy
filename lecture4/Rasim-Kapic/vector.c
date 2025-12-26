#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MIN_CAP 16

typedef struct {
    int *data;
    int size;
    int cap;
} Vector;

int next2(int n) {
    if (n < MIN_CAP) return MIN_CAP;
    int x = MIN_CAP;
    while (x < n) x *= 2;
    return x;
}

Vector* make_vector(int init) {
    Vector *v = malloc(sizeof(Vector));
    if (!v) { printf("Nema memorije\n"); exit(1); }
    v->cap = next2(init);
    v->size = 0;
    v->data = malloc(sizeof(int) * v->cap);
    if (!v->data) { free(v); printf("Nema memorije\n"); exit(1); }
    return v;
}

void free_vector(Vector *v) {
    free(v->data);
    free(v);
}

void resize(Vector *v, int newcap) {
    if (newcap < MIN_CAP) newcap = MIN_CAP;
    int *tmp = malloc(sizeof(int) * newcap);
    for (int i = 0; i < v->size; i++) tmp[i] = v->data[i];
    free(v->data);
    v->data = tmp;
    v->cap = newcap;
}

void push(Vector *v, int x) {
    if (v->size == v->cap) resize(v, v->cap*2);
    v->data[v->size++] = x;
}

void insert(Vector *v, int pos, int x) {
    if (pos < 0 || pos > v->size) { printf("Greska index\n"); return; }
    if (v->size == v->cap) resize(v, v->cap*2);
    for (int i = v->size; i > pos; i--) v->data[i] = v->data[i-1];
    v->data[pos] = x;
    v->size++;
}

void prepend(Vector *v, int x) {
    insert(v, 0, x);
}

int pop(Vector *v) {
    if (v->size == 0) { printf("Prazan vector\n"); return -1; }
    int val = v->data[v->size-1];
    v->size--;
    if (v->size > 0 && v->size <= v->cap/4) resize(v, v->cap/2);
    return val;
}

void delete(Vector *v, int pos) {
    if (pos < 0 || pos >= v->size) { printf("Greska index\n"); return; }
    for (int i = pos; i < v->size-1; i++) v->data[i] = v->data[i+1];
    v->size--;
    if (v->size > 0 && v->size <= v->cap/4) resize(v, v->cap/2);
}

void remove_item(Vector *v, int x) {
    int i = 0;
    while (i < v->size) {
        if (v->data[i] == x) delete(v, i);
        else i++;
    }
}

int find(Vector *v, int x) {
    for (int i = 0; i < v->size; i++) if (v->data[i] == x) return i;
    return -1;
}

void print_vector(Vector *v) {
    for (int i = 0; i < v->size; i++) printf("%d ", v->data[i]);
    printf("\n");
}

int main() {
    Vector *v = make_vector(0);
    int n;

    printf("Unesi brojeve (0 za kraj):\n");
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        push(v, n);
    }

    printf("Trenutni vector: ");
    print_vector(v);

    printf("Unesi index za dohvatanje: ");
    scanf("%d", &n);
    if (n >= 0 && n < v->size)
        printf("Na indexu %d je %d\n", n, v->data[n]);
    else
        printf("Greska index\n");

    printf("Unesi broj za ukloniti: ");
    scanf("%d", &n);
    remove_item(v, n);

    printf("Vector nakon uklanjanja: ");
    print_vector(v);

    free_vector(v);
    return 0;
}
