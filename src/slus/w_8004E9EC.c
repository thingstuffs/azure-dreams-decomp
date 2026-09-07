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
    s32 n;
    u8 *p;
    s32 pos;
    s32 result;
    s32 len;

    n = arg1;
    result = 0;
    len = n << 1;
    pos = result;
    if (len >= 0) {
        p = arg0;
        p++;
        p--;
        do {
            if (*p == 0) {
                s32 limit = len;
                result = 1;
                if (pos < limit) {
                    do {
                        if (pos & 1) {
                            *(Pattern3 *)p = *(Pattern3 *)&D_80080B70;
                        } else {
                            *(Pattern3 *)p = *(Pattern3 *)&D_80080B70;
                        }
                        pos += 2;
                        p += 2;
                    } while (pos < limit);
                    result = 1;
                }
            }
            pos++;
            len = n << 1;
            p++;
        } while (len >= pos);
    }
    return result;
}
