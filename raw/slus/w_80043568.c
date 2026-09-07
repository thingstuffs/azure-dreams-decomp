#include "common.h"

#include "common.h"

void func_80043568(void) {
    register s32 i ASM_REG("$5");
    register u32 page ASM_REG("$9");
    volatile u8 *p;
    register u32 v ASM_REG("$2");
    s32 c13;
    s32 c39;
    register s32 c2 ASM_REG("$6");
    u32 idx;

    i = 0x3F;
    page = 0x80010000;
    c13 = 0x13;
    c39 = 0x39;
    c2 = 2;
    p = (volatile u8 *)(page | 0xFC);
    do {
        if (p[0x981] == c13 && p[0x980] == c39) {
            v = p[0x983];
            p[0x980] = c2;
            idx = v & 0x3F;
            ((u8 *)page)[idx * 0x54 + 0xA93] = c2;
        }
        i -= 1;
        p -= 4;
    } while (i >= 0);

    i = 0x13;
    page = 0x80010000;
    c13 = i;
    c39 = 0x39;
    c2 = 2;
    p = (volatile u8 *)(page | 0x4C);
    do {
        if (p[0x249] == c13 && p[0x248] == c39) {
            p[0x248] = c2;
        }
        if (p[0x21E9] == c13 && p[0x21E8] == c39) {
            v = p[0x21EB];
            p[0x21E8] = c2;
            idx = v & 0x1F;
            ((u8 *)page)[idx * 0x8C + 0x2273] = c2;
        }
        i -= 1;
        p -= 4;
    } while (i >= 0);
}
