#include "common.h"

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
            register s8 *page ASM_REG("$2");
            register void *ptr ASM_REG("$3");

            func_8001A554(0x949);
            page = (s8 *)0x80010000;
            ASM_KEEP(page);
            ptr = *(void **)(page + 0x6000);
            ASM_KEEP(ptr);
            page = (s8 *)0x80020000;
            ASM_KEEP(page);
            ptr = *(void **)((s8 *)ptr + 0x1C);
            ASM_KEEP(ptr);
            page -= 0x2950;
            ASM_KEEP(page);
            *(void **)((s8 *)ptr + 0x40) = page;
        } else {
            register s8 *page ASM_REG("$2");
            register void *ptr ASM_REG("$3");

            func_8001A554(0x949);
            page = (s8 *)0x80010000;
            ASM_KEEP(page);
            ptr = *(void **)(page + 0x6000);
            ASM_KEEP(ptr);
            page = (s8 *)0x80020000;
            ASM_KEEP(page);
            ptr = *(void **)((s8 *)ptr + 0x1C);
            ASM_KEEP(ptr);
            page -= 0x2860;
            ASM_KEEP(page);
            *(void **)((s8 *)ptr + 0x40) = page;
        }
        goto dispatch;
    }

    func_80019988();
    if (func_8001991C(arg0, arg1) != 0) {
        return 1;
    }

dispatch:
    {
        register void *ptr ASM_REG("$2");
        register s32 first_arg ASM_REG("$4");

        ptr = (void *)0x80010000;
        ASM_KEEP(ptr);
        ptr = *(void **)((s8 *)ptr + 0x6000);
        ASM_KEEP(ptr);
        ptr = *(void **)((s8 *)ptr + 0x20);
        ASM_KEEP(ptr);
        first_arg = 0xF;
        ASM_KEEP(first_arg);
        ptr = *(void **)((s8 *)ptr + 0x2F8);
        ASM_KEEP(ptr);
        ((Callback)ptr)(first_arg, 0x200);
    }
    return 0;
}

/* MECHANISM: Recovering 800183C4/800183EC as local joins removed phantom calls
   and the s2 hold, yielding the retail 0x20/s0-s1-ra prologue. Guarded v0 page
   and v1 pointer lifetimes preserve lui/lw/addiu; pinned a0 fills the tail gap. */
