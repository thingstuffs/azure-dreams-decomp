#include "common.h"

typedef s32 M2C_UNK;

extern void func_80033CD8();
extern void func_80045340();
extern M2C_UNK D_800A833C;
extern s32 D_800D0E44;
extern M2C_UNK D_800F8A70;

/* Initialize the object state, shared counter, context resource, and callback. */
void func_800A82F0(void *object, M2C_UNK unused, void *context) {
    void *resource_base;

    *(M2C_UNK **) ((s8 *) object - 0x10) = &D_800A833C;
    D_800D0E44 = 0x14;
    resource_base = &D_800F8A70;
    *(void **) ((s8 *) context + 8) = (void *) ((s8 *) resource_base + 0xF0);
    func_80033CD8(object, func_80045340);
}
