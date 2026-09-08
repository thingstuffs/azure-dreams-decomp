#include "common.h"

extern u8 D_800D1624[];
extern void func_800491F4(void *a0, void *a1, int a2);

/* Forwards the context and D_800D1624 to func_800491F4 with selector 4. */
void func_800B1938(void *context) {
    func_800491F4(context, D_800D1624, 4);
}
