#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern u8 D_80016000[12];

void func_8065C05C(void *arg0) {
    register void *base;
    s32 count;
    register s32 index;
    register s32 tag ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register u8 *page ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *base_copy ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 end;
    register void *out ASM_REG("$16");   /* MATCH pin: retail callee-saved set / frame layout depends on it */

    base = arg0;
    count = 0;
    index = 0;
    page = (u8 *)0x80010000;
    tag = 0x17;
    out = base;
    do {
        if (FIELD(FIELD(FIELD(page, void **, 0x6000), void **, 0x20), s32 (**)(s32), 0x70)(index) != 0) {
            FIELD(out, s8 *, 0) = index;
            FIELD(out, s8 *, 1) = tag;
            FIELD(out, s8 *, 3) = 0;
            FIELD(out, s8 *, 2) = 0;
            out += 4;
            count += 1;
        }
        index += 1;
    } while (index < 0x43);

    base_copy = base;
    end = count;
    end <<= 2;
    end += (u32)base_copy;
    FIELD((void *)end, s8 *, 1) = 0;
    FIELD((void *)end, s8 *, 0) = 0;
    ASM_USE2(base_copy, end);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
}
