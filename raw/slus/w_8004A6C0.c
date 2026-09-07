#include "common.h"

struct Entry { short a; short b; };
extern struct Entry D_80013564[];
int func_8004A6C0(int a0, int a1) {
    int i = 0;
    struct Entry *p = D_80013564;
    for (; i < 20; i++, p++) {
        if (p->a == a0 && p->b == a1) break;
    }
    return i;
}
