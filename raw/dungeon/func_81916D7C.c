#include "common.h"

extern s32 func_800478B8();
extern s32 D_800814A0[3];

void func_8002457C(void *arg0, void *unused, void *arg2)
{
    void *post_object;
    void *pre_object;

    pre_object = *(void **)arg0;
    *(u16 *)((u8 *)pre_object + 0x14) += 1;
    func_800478B8(arg2);
    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x6000) {
        u16 object_count;
        u16 object_flags;
        s32 global_flags;

        object_flags = *(u16 *)((u8 *)arg0 - 2);
        post_object = *(void **)arg0;
        *(u16 *)((u8 *)arg0 - 2) = object_flags | 0x8000;
        global_flags = D_800814A0[0];
        object_count = *(u16 *)((u8 *)post_object + 0x18);
        D_800814A0[0] = global_flags | 0x8000;
        *(u16 *)((u8 *)post_object + 0x18) = object_count + 1;
    }
}

/* MECHANISM: Cross-call arg0/arg2 lifetimes select s1/s0 and the 0x20 frame.
   Separate pre/post object locals color as retail v1/a1; explicit halfword
   and global temporaries overlap loads so cdk fills both delay slots. */
