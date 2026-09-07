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

/* Allocates an object via func_8003FC64, initializes its embedded sub-object
 * (func_8004FC68), computes and stores an index/value via func_8004FD78,
 * then validates the result via func_8004FC98. On success, installs the
 * object's vtable/callback function pointers; on failure, tears the object
 * down via func_8004FE78 and returns NULL. */
void *func_8004FDE0(void *a0)
{
    S_8004FDE0_obj *s1;
    S_8004FDE0_sub *s0;

    s1 = func_8003FC64(0);
    if (s1 != 0) {
        s0 = &s1->sub;
        func_8004FC68(s0);
        s0->unk30 = func_8004FD78(s0, a0);
        if (func_8004FC98(s0) == 0) {
            func_8004FE78(s1);
            s1 = 0;
        } else {
            s1->vtable = func_8004FC2C;
            s0->cb = func_8004F9AC;
        }
    }
    return s1;
}
