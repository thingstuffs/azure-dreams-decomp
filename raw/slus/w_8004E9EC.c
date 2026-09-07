#include "common.h"

typedef struct PatternSource {
    s8 b0;
    s8 b1;
    s8 b2;
    s8 pad[13];
} PatternSource;

typedef struct Pattern3 {
    s8 b0;
    s8 b1;
    s8 b2;
} Pattern3;

extern PatternSource D_80080B70;

s32 func_8004E9EC(u8 *arg0, s32 arg1)
{
    register s32 n ASM_REG("$10");
    s32 pos;
    register s32 result ASM_REG("$5");
    s32 len;

    n = arg1;
    result = 0;
    len = n << 1;
    pos = result;
    if (len >= 0) {
        do {
            if (arg0[pos] == 0) {
                s32 limit = len;
                result = 1;
                if (pos < limit) {
                    do {
                        *(Pattern3 *)(arg0 + pos) = *(Pattern3 *)&D_80080B70;
                        pos += 2;
                    } while (pos < limit);
                    result = 1;
                }
            }
            pos++;
            len = n << 1;
        } while (len >= pos);
    }
    return result;
}
