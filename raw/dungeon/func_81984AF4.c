#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void func_80026350(void) __attribute__((noreturn));
extern void func_800263B8(void) __attribute__((noreturn));

void func_81984AF4(void *arg0, s16 *arg1, s32 arg2, s32 arg3) {
    s16 step;
    s32 shifted;
    u32 flag;
    u32 next;
    u8 index;
    register void *obj ASM_REG("$8") = arg0;
    register s32 initialIndex ASM_REG("$3") = FIELD(obj, s8, 4);
    void *owner = FIELD(obj, void *, 8);

    ASM_KEEP(obj);
    ASM_KEEP(initialIndex);
    FIELD(obj, s32, 0) =
        FIELD(owner, s32, 0xC) + (initialIndex * 22);
    step = *arg1;
    if (step > 0) {
        next = FIELD(obj, volatile u8, 4) + 1;
        ASM_TAILSLOT_PIN_TIED(next);
        func_80026350();
    }
    if (step < 0) {
        FIELD(obj, volatile u8, 4) =
            FIELD(obj, volatile u8, 4) - 1;
    }
    index = (u8)FIELD(obj, s8, 4);
    shifted = index << 24;
    if ((s8)index < (s16)arg2) {
        flag = FIELD(obj, volatile u16, 0x14) | 0x4000;
        FIELD(obj, s8, 4) = arg2;
        ASM_TAILSLOT_PIN_TIED(flag);
        func_800263B8();
    }
    if ((s8)index > (s16)arg3) {
        flag = FIELD(obj, volatile u16, 0x14) | 0x4000;
        FIELD(obj, s8, 4) = arg3;
        ASM_TAILSLOT_PIN_TIED(flag);
        func_800263B8();
    }
    FIELD(obj, u16, 0x14) &= 0xBFFF;
}
