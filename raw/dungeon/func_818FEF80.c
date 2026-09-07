#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80024800() __attribute__((noreturn));
extern void func_80024954() __attribute__((noreturn));
extern void func_80024994() __attribute__((noreturn));
extern s16 D_80025E80;
extern s32 D_800814A0;

void func_818FEF80(void *arg0, void *arg1, void *arg2) {
    register void *object ASM_REG("$3");
    register void *linked ASM_REG("$8");
    s16 count;

    object = FIELD(arg0, void *, 0x30);
    D_80025E80 = 1;
    if ((u32)(FIELD(object, u8, 0x13) - 0x33) < 4U) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_80024994();
        return;
    }

    FIELD(arg0, u16, 2)--;
    if (FIELD(arg0, s16, 0xA) == 0) {
        FIELD(arg0, volatile s16, 0xA) = 1;
        (void)FIELD(arg1, volatile s32, 8);
        object = (void *)0xfffe0000;
        ASM_TAILSLOT_PIN(object);
        func_80024800();
        return;
    }

    FIELD(arg0, s16, 0xA) = 0;
    FIELD(arg1, s32, 8) += 0x20000;
    object = FIELD(arg0, void *, 0x30);
    linked = FIELD(object, void *, -0x14);
    FIELD(arg2, u16, 0x14) &= 0xFF7F;
    FIELD(linked, u16, 0x14) |= 0x80;

    count = FIELD(arg0, s16, 2);
    if (count < 0x3C) {
        register s32 tail_value ASM_REG("$2");

        FIELD(arg2, s8, 0xE) = (((0x3C - count) << 6) / 60) + 0x40;
        FIELD(arg2, s8, 0xD) = (((0x3C - FIELD(arg0, s16, 2)) << 6) / 60) + 0x40;
        tail_value = ((0x3C - FIELD(arg0, s16, 2)) << 6) / 60;
        ASM_TAILSLOT_PIN(tail_value);
        func_80024954();
        return;
    }

    __asm__ __volatile__("" ::: "memory");
    FIELD(arg2, s8, 0xE) = (((count - 0x3C) << 6) / 60) + 0x40;
    FIELD(arg2, s8, 0xD) = (((FIELD(arg0, s16, 2) - 0x3C) << 6) / 60) + 0x40;
    FIELD(arg2, s8, 0xC) = (((FIELD(arg0, s16, 2) - 0x3C) << 6) / 60) + 0x40;

    if (FIELD(arg0, s16, 2) <= 0) {
        u16 linked_value;

        FIELD(arg0, u16, -2) |= 0x8000;
        linked_value = FIELD(linked, u16, 0x14);
        D_800814A0 |= 0x8000;
        FIELD(linked, u16, 0x14) = linked_value & 0xFF7F;
    }
}
