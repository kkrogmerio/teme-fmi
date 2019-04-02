#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define SWAP(a, b) { int aux = (a); (a) = (b); (b) = aux; }

Heap heap_nou(int capacitate) {
    Heap h;

    h.val = (int*)malloc(sizeof(int) * capacitate);
    h.n = 0;
    h.cap = capacitate;

    return h;
}

void heap_free(Heap* h) {
    free(h->val);
    h->val = NULL;
    h->n = h->cap = 0;
}

int heap_min(const Heap* h) {
    assert(h->n != 0 && "Heap-ul este gol!");

    return h->val[0];
}

void heap_afisare(const Heap* h) {
    for (int i = 0; i < h->n; ++i) {
        printf("%d ", h->val[i]);
    }
    printf("\n");
}

void heap_insert(Heap* h, int nr) {
    assert((h->n != h->cap) && "Heap plin");

    int idx = h->n++;
    h->val[idx] = nr;

    while (idx != 0) {
        int tata = (idx - 1) / 2;

        if (h->val[tata] > h->val[idx]) {
            SWAP(h->val[tata], h->val[idx]);
            idx = tata;
        } else {
            break;
        }
    }
}

static void heap_down(Heap* h, int idx) {
    int st = 2 * idx + 1, dr = 2 * idx + 2;

    int fiu = idx;

    if (st < h->n && h->val[st] < h->val[dr]) {
        fiu = st;
    }
    if (dr < h->n && h->val[st] > h->val[dr]) {
        fiu = dr;
    }

    if (idx != fiu) {
        SWAP(h->val[idx], h->val[fiu]);
        heap_down(h, fiu);
    }
}

int heap_pop(Heap* h) {
    assert((h->n != 0) && "Heap gol");

    int ret = h->val[0];

    // Cazul in care avem doar un nod
    if (h->n == 1) {
        h->n = 0;
        return ret;
    }

    --(h->n);

    SWAP(h->val[0], h->val[h->n]);

    heap_down(h, 0);

    return ret;
}
