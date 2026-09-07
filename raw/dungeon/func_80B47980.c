#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
#define VFIELD(p, type, off) (*(volatile type *)((u8 *)(p) + (off)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern u8 D_80045340[];
extern u8 D_801749EC[];

void func_80175180(void *in_arg0, void *in_arg1)
{
    register void *arg0 ASM_REG("$17") = in_arg0;
    register void *arg1 ASM_REG("$18") = in_arg1;
    u16 flags;
    void *obj;
    void *part;
    void *pos;
    u8 *state;

    obj = func_8003FC64(0x12);
    ASM_KEEP(arg0);
    ASM_KEEP(arg1);
    state = (u8 *)obj + 0x20;
    if (obj != 0) {
        FIELD(state, s16, 8) = 0x4A;
        FIELD(state, u16, 0xA) = FIELD(arg0, u16, 0x96);
        FIELD(state, s16, 0xC) = 0;
        FIELD(obj, void *, 0x10) = D_801749EC;
        func_8004491C(obj, D_80045340);
        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        flags = VFIELD(part, u16, 0x14);
        flags |= 0xC;
        VFIELD(part, u16, 0x14) = flags;
        flags |= 0x80;
        VFIELD(part, u16, 0x14) = flags;
        pos = FIELD(obj, void *, 8);
        FIELD(pos, s32, 0) = FIELD(arg1, s32, 0);
        FIELD(pos, s32, 4) = FIELD(arg1, s32, 4);
        FIELD(pos, s32, 8) = FIELD(arg1, s32, 8) + 0xFFE80000;
        part = FIELD(obj, void *, 0xC);
        FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, s16, 0x1C) = 0x1000;
        FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, u8, 0xC) = 0x80;
        FIELD(part, u8, 0xD) = 0x80;
    }
}

/* MECHANISM: Pin arg0/arg1 to s1/s2 and keep them just after the allocator call,
   preserving the 0x20 frame/save order without blocking retail call setup.
   A volatile u16 RMW retains both flag stores; source order and u8 fields close the residue. */
