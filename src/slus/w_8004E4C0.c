#include "common.h"
char *func_8004E4C0(u32 value, s32 width, char *buf, s32 pad) {
    s32 count; u32 q; s32 limit;
    register u32 next ASM_REG("$2");   /* MATCH pin: slus-diff */
    count = 1;
    q = value / 10u;
    *buf = (char)((value - q * 10u) + '0');
    q = width & 0xFFFF;
    buf++;
    if (count < (s32)q) {
        limit = q;
        do {
        top:
            value = value / 10u;
            if (value == 0) break;
            count++;
            next = value / 10u;
            ASM_KEEP_NV(next);   /* MATCH pin: slus-diff */
            *buf++ = (char)((value - next * 10u) + '0');
        } while (count < limit);
        q = width & 0xFFFF;
        while (count < (s32)q) { *buf++ = (char)pad; count++; }
    }
    *buf = 0;
    return buf - (width & 0xFFFF);
}
