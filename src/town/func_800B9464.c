#include "common.h"

/* Canonical global flags word shared by several sibling functions across
 * the codebase (code9.c, code10.c, code11.c, code5.c, w_8004FE78.c, ...).
 * Declared as a plain `extern int` so the address is recomputed separately
 * for the load and the store, matching this function's tail. */
extern int D_800814A0;

extern void func_8004B248(u16 **a0);
extern void func_800B6B10(s32 arg0);
extern void func_800B6F54(void *arg0);

typedef struct S_800B9464_sub {
    u8 pad00[0x98];
    s32 unk98;
} S_800B9464_sub;

typedef struct S_800B9464_a0 {
    u8 pad00[0x1E];
    u16 field_1E;          /* 0x1E */
    S_800B9464_sub sub;    /* 0x20 */
    u16 *arr_bc[1];        /* 0xBC, NULL-terminated pointer array */
} S_800B9464_a0;

/* Process an object's pointer array and embedded state, then set its and the global 0x8000 flags. */
void func_800B6BC4(S_800B9464_a0 *object)
{
    S_800B9464_sub *objectState;

    if (object != 0) {
        objectState = &object->sub;
        func_8004B248(object->arr_bc);
        func_800B6B10(objectState->unk98);
        func_800B6F54(objectState);
        object->field_1E |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
