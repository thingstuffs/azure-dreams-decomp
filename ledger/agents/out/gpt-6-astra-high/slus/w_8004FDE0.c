#include "common.h"

/* Sub-object embedded at offset 0x20 of the allocated object. It matches the
 * prefix layout of Struct_8004FC68 (already-matched func_8004FC68), with
 * additional fields this function itself writes. */
typedef struct S_8004FDE0_sub {
    void (*cb)(void *self);   /* 0x00 - set to func_8004F9AC on success */
    u8 pad04[0xC];             /* 0x04 */
    u8 unk10[0x14];            /* 0x10 - sub-object used by func_80021448 */
    s32 unk24;                 /* 0x24 - result of func_80021448 */
    u8 pad28[0x8];             /* 0x28 */
    s32 unk30;                 /* 0x30 - result of func_8004FD78 */
} S_8004FDE0_sub;

typedef struct S_8004FDE0_obj {
    u8 pad0[0x10];              /* 0x00 */
    void (*vtable)(void *self); /* 0x10 - set to func_8004FC2C on success */
    u8 pad14[0xC];              /* 0x14 */
    S_8004FDE0_sub sub;         /* 0x20 */
} S_8004FDE0_obj;

extern void *func_8003FC64(s32 a0);
extern void func_8004FC68(void *a0);
extern void func_8004FC2C(void *a0);
extern s32 func_8004FD78(void *a0, void *a1);
extern s32 func_8004FC98(void *a0);
extern void func_8004FE78(void *a0);
extern void func_8004F9AC(void *a0);

/* Allocates and initializes an object, installs its callbacks, or returns NULL on failure. */
void *func_8004FDE0(void *init_data)
{
    S_8004FDE0_obj *obj;
    S_8004FDE0_sub *sub;

    obj = func_8003FC64(0);
    if (obj != 0) {
        sub = &obj->sub;
        func_8004FC68(sub);
        sub->unk30 = func_8004FD78(sub, init_data);
        if (func_8004FC98(sub) == 0) {
            func_8004FE78(obj);
            obj = 0;
        } else {
            obj->vtable = func_8004FC2C;
            sub->cb = func_8004F9AC;
        }
    }
    return obj;
}
