#include "common.h"
extern u8 D_8001D7A0[];
extern u8 D_8001D6B0[];
extern u8 D_80016000[];

typedef s32 (*Callback)(s32, s32);

extern void func_80016CC4(void);
extern s32 func_8001991C(s32, void *);
extern void func_80019988(void);
extern void func_8001A554(s32);
extern s32 func_8001A64C(s32);

s32 func_800182FC(s32 arg0, void *arg1)
{
    func_80016CC4();
    if (func_8001A64C(0x1068) != 0) {
        func_8001A554(0x94F);
        func_8001A554(0x93E);
        return 1;
    }

    if (func_8001A64C(0x949) == 0) {
        if (func_8001A64C(0x94A) != 0) {
            void *ptr;

            func_8001A554(0x949);
            ptr = *(void **)D_80016000;
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D6B0;
        } else {
            void *ptr;

            func_8001A554(0x949);
            ptr = *(void **)D_80016000;
            ptr = *(void **)((s8 *)ptr + 0x1C);
            *(void **)((s8 *)ptr + 0x40) = (s8 *)D_8001D7A0;
        }
        goto dispatch;
    }

    func_80019988();
    if (func_8001991C(arg0, arg1) != 0) {
        return 1;
    }

dispatch:
    {
        void *ptr;
        s32 first_arg;

        ptr = *(void **)D_80016000;
        ptr = *(void **)((s8 *)ptr + 0x20);
           /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        first_arg = 0xF;
        ptr = *(void **)((s8 *)ptr + 0x2F8);
        ((Callback)ptr)(first_arg, 0x200);
    }
    return 0;
}

/* MECHANISM: Recovering 800183C4/800183EC as local joins removed phantom calls
   and the s2 hold, yielding the retail 0x20/s0-s1-ra prologue. Guarded v0 page
   and v1 pointer lifetimes preserve lui/lw/addiu; pinned a0 fills the tail gap. */
