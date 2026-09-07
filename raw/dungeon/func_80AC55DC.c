#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_80045340;
extern u8 D_800DEC70[];
extern u8 D_80170A84[];

void func_80AC55DC(
    void *arg0, s16 arg1, s32 arg2, s16 arg3,
    s32 arg4, s32 arg5, s32 arg6)
{
    void *node;
    void *work;
    void *sprite;
    void *source;
    u16 third;
    u16 flags;
    s32 size;
    register void *data ASM_REG("$5");
    register s32 div_raw ASM_REG("$2");
    register s32 numerator ASM_REG("$2");
    register s32 divisor ASM_REG("$4");
    register s32 adjusted ASM_REG("$3");
    register s32 step_x ASM_REG("$6");
    register s32 step_y ASM_REG("$5");
    register s32 step_z ASM_REG("$3");

    node = func_8003FC64(0x212);
    if (node != 0) {
        FIELD(node, void *, 0x10) = D_80170A84;

        FIELD(FIELD(node, void *, 8), s16, 2) =
            FIELD(FIELD(arg0, void *, 8), u16, 2) + arg4;
        FIELD(FIELD(node, void *, 8), s16, 6) =
            FIELD(FIELD(arg0, void *, 8), u16, 6) + arg5;
        FIELD(FIELD(node, void *, 8), s16, 0xA) =
            FIELD(FIELD(arg0, void *, 8), u16, 0xA) + arg6 - 0x14;

        work = (u8 *)node + 0x20;
        FIELD(work, u16, 0x36) = FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(work, u16, 0x38) = FIELD(FIELD(arg0, void *, 8), u16, 6);
        ASM_SCHED_BARRIER();
        div_raw = arg3 << 16;
        source = FIELD(arg0, void *, 8);
        ASM_SCHED_BARRIER();
        divisor = div_raw >> 16;
        ASM_KEEP(div_raw);
        third = FIELD(source, u16, 0xA);
        adjusted = divisor;
        FIELD(work, u16, 0x3A) = third;
        ASM_SCHED_BARRIER();
        numerator = arg4 << 16;
        numerator = -numerator;
        if (divisor < 0) {
            adjusted = divisor + 7;
        }
        ASM_KEEP(divisor);
        adjusted >>= 3;

        step_x = numerator / adjusted;
        ASM_KEEP(numerator);
        FIELD(work, volatile s32, 0x40) = step_x / 2;
        ASM_SCHED_BARRIER();
        numerator = arg5 << 16;
        numerator = -numerator;
        step_y = numerator / adjusted;
        ASM_KEEP(numerator);
        FIELD(work, volatile s32, 0x44) = step_y / 2;
        ASM_KEEP(adjusted);
        step_z = -(arg6 << 16) / adjusted;
        FIELD(work, volatile s32, 0x48) = step_z / 2;
        ASM_SCHED_BARRIER();

        FIELD(work, s32, 0x4C) = step_x / 4;
        ASM_KEEP(step_x);
        FIELD(work, s32, 0x50) = step_y / 4;
        ASM_KEEP(step_y);
        ASM_KEEP(step_z);
        FIELD(work, s32, 0x54) = step_z / 4;

        FIELD(work, s16, 0x14) = arg1;
        FIELD(work, s16, 0x32) = arg3;
        FIELD(work, s16, 0x34) = arg3;
        func_8004491C(node, &D_80045340);

        data = D_800DEC70;
        ASM_KEEP(data);
        sprite = FIELD(node, void *, 0xC);
        size = 0x20;
        flags = FIELD(sprite, u16, 0x14);
        ASM_SCHED_BARRIER();
        FIELD(sprite, s16, 0x10) = size;
        FIELD(sprite, s16, 0x1E) = 0x1000;
        FIELD(sprite, s16, 0x1C) = 0x1000;
        FIELD(sprite, u8, 0xE) = 0;
        FIELD(sprite, u8, 0xD) = 0;
        FIELD(sprite, u8, 0xC) = 0;
        FIELD(sprite, u16, 0x14) = flags | 0xC;
        FIELD(node, s32, 0x20) = arg2;
        FIELD(work, s32, 8) = arg2;
        func_8003DB94(sprite, data, 0);
    }
}

/* MECHANISM: The seven live arguments naturally produce the retail 0x38 frame and saved-register order.
   Split pinned $v0 numerators from $a2/$a1/$v1 quotients; narrow barriers preserve each mflo/round/store seam.
   A one-read flags RMW plus held $a1 data pointer fixes the final li/lhu/zero-argument schedule. */
