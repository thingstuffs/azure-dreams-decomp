#include "common.h"

#include "common.h"

typedef struct S_8004FA2C {
    void (*f0)(void *self);   /* 0x00 - callback, compared to func_8004F9AC */
    u8 pad04[0x20 - 0x4];
    s32 f20;                  /* 0x20 */
    s32 f24;                  /* 0x24 */
    u8 pad28[0x2C - 0x28];
    s32 f2C;                  /* 0x2C */
    s32 f30;                  /* 0x30 */
    s32 f34;                  /* 0x34 */
} S_8004FA2C;

extern void func_8004F9AC(void *a0);
extern void func_8004F95C(void *a0);
extern int func_80049DE8(int a0, int a1, int a2);

/* Resets f2C; if the object's callback is still func_8004F9AC, sets f20 to
 * 0x20 and invokes it. Installs func_8004F95C as the new callback and
 * advances f30 (saving the previous value into f34) via func_80049DE8. */
void func_8004FA2C(S_8004FA2C *a0, int a1)
{
    a0->f2C = 0;
    if (a0->f0 == func_8004F9AC) {
        a0->f20 = 0x20;
        func_8004F9AC(a0);
    }
    a0->f34 = a0->f30;
    a0->f0 = func_8004F95C;
    a0->f30 = func_80049DE8(a0->f30, a1, a0->f24);
}
