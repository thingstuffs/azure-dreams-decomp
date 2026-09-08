#include "common.h"

u8 *func_800407C0(u8 *sp0, u8 *dp0)
{
    register u8 *dp ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *rowbase;
    u8 *rowend;
    u8 *end;
    register u8 *q ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 hdr ASM_REG("$6");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 stride;
    s32 size;
    s32 cnt;
    s32 phase;
    s32 sphase;
    s32 v;
    s32 vA;
    register s32 vst ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 t;
    s32 u;
    u32 b;
    u8 *sp;

    sp = sp0;
    ASM_KEEP_NV(sp);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    dp = dp0;
    phase = 0;
    rowbase = dp;
    hdr = *sp++;
    if (hdr & 1) {
        for (;;) {
            b = *sp++;
            if ((b & 0xF0) == 0) {
                cnt = (b & 0xFF) * 2;
                if ((b & 0xFF) == 0) {
                    goto ret_dp1;
                }
                sphase = 0;
                while (cnt > 0) {
                    if (sphase == 0) {
                        b = *sp++;
                    }
                    q = dp;
                    if (phase == 0) {
                        if (sphase != 0) {
                            *dp = b & 0xF;
                        } else {
                            *dp = b >> 4;
                        }
                    } else {
                        t = *dp;
                        dp++;
                        if (sphase != 0) {
                            vA = (b << 4) & 0xF0;
                        } else {
                            vA = b & 0xF0;
                        }
                        *q = t | vA;
                    }
                    sphase ^= 1;
                    cnt--;
                    phase ^= 1;
                }
            } else {
                cnt = b >> 4;
                v = b & 0xF;
                vst = v;
                while (cnt >= 0) {
                    if (phase == 0) {
                        *dp = vst;
                    } else {
                        *dp |= v << 4;
                        dp++;
                    }
                    cnt--;
                    phase ^= 1;
                }
            }
        }
    ret_dp1:
        return dp + 1;
    }
    if (hdr != 0) {
    stride = hdr >> 1;
    size = sp[0] + (sp[1] << 8);
    sp += 2;
    rowend = dp + stride;
    end = dp + size;
    do {
        b = *sp++;
        if ((b & 0xF0) == 0) {
            cnt = b * 2;
            sphase = 0;
            while (cnt > 0) {
                if (sphase == 0) {
                    b = *sp++;
                }
                if (phase == 0) {
                    v = b & 0xF;
                    if (sphase == 0) {
                        v = b >> 4;
                    }
                    *dp = v;
                } else {
                    u = *dp;
                    if (sphase != 0) {
                        v = (b << 4) & 0xF0;
                    } else {
                        v = b & 0xF0;
                    }
                    *dp = u | v;
                }
                dp += stride;
                sphase ^= 1;
                if (dp >= end) {
                    phase ^= 1;
                    if (phase == 0) {
                        rowbase++;
                        if (rowbase >= rowend) {
                            return end;
                        }
                    }
                    dp = rowbase;
                }
                cnt--;
            }
        } else {
            cnt = b >> 4;
            v = b & 0xF;
            vst = v;
            while (cnt >= 0) {
                if (phase == 0) {
                    *dp = vst;
                } else {
                    *dp |= v << 4;
                }
                dp += stride;
                if (dp >= end) {
                    phase ^= 1;
                    if (phase == 0) {
                        rowbase++;
                        if (rowbase >= rowend) {
                            return end;
                        }
                    }
                    dp = rowbase;
                }
                cnt--;
            }
        }
    } while (dp + stride < end || phase == 0 || rowbase + 1 < rowend);
    return end;
    }
    size = sp[0] + (sp[1] << 8);
    memcpy(dp, sp + 2, size);
    return dp + size;
}
