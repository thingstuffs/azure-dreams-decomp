#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern u8 D_A0700000[];

void func_808B2E74(void)
{
    register s32 i ASM_REG("$5") = 1;
    register s32 one ASM_REG("$8") = 1;
    register s16 *p ASM_REG("$7") = (s16 *)(D_A0700000 + 0xF26);
    register s32 index ASM_REG("$6");

    do {
        register s32 value ASM_REG("$4");
        register s32 n ASM_REG("$3");
        register u8 *q ASM_REG("$2");
        register u8 *bitmap_base;

        value = *p;
        index = i << 1;
        n = value;
        if (value < 0)
            n = value + 31;
        bitmap_base = (u8 *)0xA0700000;
        ASM_KEEP(bitmap_base);
        q = *(u8 **)(bitmap_base + 0xF40);
        ASM_KEEP(q);
        n >>= 5;
        q += n;
        n = value - (n << 5);
        n = one << n;
        *q &= ~n;
    {
        register s32 value2 ASM_REG("$3");
        register s32 n2 ASM_REG("$2");
        register u8 *q2 ASM_REG("$4");
        register u8 *bitmap_base2;
        value2 = FIELD((u32)D_A0700000 + index, s16, 0xF1C);
        n2 = value2;
        if (value2 < 0)
            n2 = value2 + 31;
        p = (s16 *)((u8 *)p + 2);
        i += 1;
        bitmap_base2 = (u8 *)0xA0700000;
        ASM_KEEP(bitmap_base2);
        q2 = *(u8 **)(bitmap_base2 + 0xF40);
        ASM_KEEP(q2);
        n2 >>= 5;
        q2 += n2;
        n2 = value2 - (n2 << 5);
        n2 = one << n2;
        *q2 &= ~n2;
    }
    } while (i < 4);
}
