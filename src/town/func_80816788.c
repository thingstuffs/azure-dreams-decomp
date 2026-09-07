#include "common.h"

typedef struct S_80020788_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80020788_0;   /* object in func_80020788 */



typedef struct {
    s32 words[10];
} Record;

extern void *func_8003FD64();
extern void func_8004491C();
extern s32 D_80053A88;
extern u8 D_80083498[];

void func_80020788(s32 arg0, void *arg1) {
    void *object;

    object = func_8003FD64(1, D_80083498);
    if (object != 0) {
        *(Record *)(object + 0x20) = *(Record *)arg1;
        ((S_80020788_0 *)object)->unk_10 = arg0;
        func_8004491C(object, &D_80053A88);
    }
}

/* MECHANISM: The 40-byte Record assignment emits retail's four-word copy loop and two-word tail.
   CDK keeps the allocator return in t0; live args naturally occupy s1/s0 and produce the 0x20 frame.
   Inlining object+0x20 into the aggregate lvalue selects a3 directly and removes the extra v0 move. */
