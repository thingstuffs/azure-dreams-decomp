#include "common.h"

#include "common.h"

#ifndef NON_MATCHING
#undef ASM_KEEP
#define ASM_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

typedef struct {
    u8 pad0[0x10];
    u32 value;
    u8 pad14[0x2C];
    s32 remainder;
} S_80059814;

extern u32 D_800869A8[4];

void func_80059814(S_80059814 *p) {
    register u32 value ASM_REG("$2");
    register u32 high ASM_REG("$3");

    switch (D_800869A8[0]) {
    case 0x30:
        high = p->value;
        value = high * 10;
        p->value = value;
        value += p->remainder;
        p->value = value;
        ASM_KEEP(value);
        high = value;
        value &= 3;
        ASM_KEEP(value);
        high >>= 2;
        break;
    case 0x60:
        high = p->value;
        value = high * 5;
        p->value = value;
        value += p->remainder;
        p->value = value;
        ASM_KEEP(value);
        high = value;
        value &= 3;
        ASM_KEEP(value);
        high >>= 2;
        break;
    case 0xC0:
    case 0xF0:
        value = p->value;
        value += p->remainder;
        p->value = value;
        ASM_KEEP(value);
        high = value;
        value &= 1;
        ASM_KEEP(value);
        high >>= 1;
        break;
    case 0x120:
    case 0x168:
        p->value = p->value / 3;
        return;
    case 0x1E0:
    case 0x180:
        value = p->value;
        value += p->remainder;
        p->value = value;
        ASM_KEEP(value);
        high = value;
        value &= 3;
        ASM_KEEP(value);
        high >>= 2;
        break;
    case 0x300:
    case 0x3C0:
        value = p->value;
        value += p->remainder;
        p->value = value;
        ASM_KEEP(value);
        high = value;
        value &= 7;
        ASM_KEEP(value);
        high >>= 3;
        break;
    default:
        return;
    }

    p->remainder = value;
    p->value = high;
}
