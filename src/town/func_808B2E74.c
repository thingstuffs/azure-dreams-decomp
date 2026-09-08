#include "common.h"

typedef struct S_808B2E74_0 {
    u8 pad_00[0xF1C];
    s16 unk_F1C;
} S_808B2E74_0;   /* (u32)D_A0700000 + index in func_808B2E74 */



extern u8 D_A0700000[];

void func_808B2E74(void)
{
    s32 i = 1;
    s32 one = 1;
    s16 *p = (s16 *)(D_A0700000 + 0xF26);
    register s32 index ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    do {
        s32 value;
        register s32 n ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *q ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        register u8 *bitmap_base;

        value = *p;
        index = i << 1;
        n = value;
        if (value < 0)
            n = value + 31;
        bitmap_base = (u8 *)0xA0700000;
        q = *(u8 **)(bitmap_base + 0xF40);
        n >>= 5;
        q += n;
        n = value - (n << 5);
        n = one << n;
        *q &= ~n;
    {
        s32 value2;
        register s32 n2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        u8 *q2;
        register u8 *bitmap_base2;
        value2 = ((S_808B2E74_0 *)((u32)D_A0700000 + index))->unk_F1C;
        n2 = value2;
        if (value2 < 0)
            n2 = value2 + 31;
        p = (s16 *)((u8 *)p + 2);
        i += 1;
        bitmap_base2 = (u8 *)0xA0700000;
        q2 = *(u8 **)(bitmap_base2 + 0xF40);
        n2 >>= 5;
        q2 += n2;
        n2 = value2 - (n2 << 5);
        n2 = one << n2;
        *q2 &= ~n2;
    }
    } while (i < 4);
}
