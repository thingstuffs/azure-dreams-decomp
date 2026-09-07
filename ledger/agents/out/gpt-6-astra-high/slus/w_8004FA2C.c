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

/* Resets the object's transition state, switches callbacks, and advances its saved value. */
void func_8004FA2C(S_8004FA2C *object, int target)
{
    object->f2C = 0;
    if (object->f0 == func_8004F9AC) {
        object->f20 = 0x20;
        func_8004F9AC(object);
    }
    object->f34 = object->f30;
    object->f0 = func_8004F95C;
    object->f30 = func_80049DE8(object->f30, target, object->f24);
}
