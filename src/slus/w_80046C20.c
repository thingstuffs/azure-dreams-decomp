#include "common.h"

#include "common.h"

s32 func_80046C20(s16 *arg0, s32 *arg1, u16 *arg2) {
    s16 *base; /* t4 */
    register s32 min_y ASM_REG("$11"); /* t3 */
    register s32 i ASM_REG("$9");      /* t1 */
    s32 mask;  /* t5 */
    register s32 *wp ASM_REG("$8");    /* t0 */
    register s16 *pair ASM_REG("$10"); /* t2 */
    register s32 lo ASM_REG("$3");     /* v1 */
    register s32 hi ASM_REG("$4");     /* a0 */
    s32 my;     /* a3 */
    register s32 tmp ASM_REG("$2");    /* v0 */
    s32 *out;
    s32 dy;
    s32 adx;

    base = arg0;
    __asm__ __volatile__("" :: "r"(base));
    min_y = 0x7FFF;
    i = 0;
    mask = -0x40;
    out = arg1;
    wp = (s32 *)((char *)arg1 + 0x1C);
    pair = base;

    do {
        lo = pair[1];
        lo = lo - pair[5];

        if (lo == 0) {
            *wp = -1;
            *arg2 -= 1;
        } else {
            if (lo < 0) {
                lo = i;
                hi = i + 1;
            } else {
                lo = i + 1;
                hi = i;
            }

            lo = (lo << 3) + (s32)base;
            *out = ((s16 *)lo)[0];
            tmp = *(u16 *)(lo + 2) & mask;
            my = (tmp << 16) >> 16;
            wp[-1] = my;
            if (my < min_y) {
                min_y = my;
            }

            hi = (hi << 3) + (s32)base;
            dy = ((s16 *)hi)[1] - my;
            wp[-4] = dy;
            __asm__ __volatile__("" ::: "memory");
            tmp = dy;
            __asm__ __volatile__("" :: "r"(tmp));
            tmp <<= 7;
            wp[-3] = dy;
            wp[-6] = tmp;

            /* reuse tmp ($v0) for dx so lh lands in v0 like retail */
            tmp = ((s16 *)hi)[0];
            tmp = tmp - *out;
            wp[-2] = tmp;
            adx = *(volatile s32 *)&wp[-2];
            if (tmp < 0) {
                tmp = -tmp;
            }
            wp[1] = tmp;
            wp[-5] = tmp << 7;
            if (adx > 0) {
                wp[-2] = 0x40;
            } else if (adx < 0) {
                wp[-2] = mask;
            }
            *wp = 0;
            tmp = wp[1] + 0x20;
            wp[1] = tmp;
            wp[2] = tmp;
        }
        pair += 4;
        i += 1;
        wp = (s32 *)((char *)wp + 0x28);
        out = (s32 *)((char *)out + 0x28);
    } while (i < 4);

    return min_y & -0x40;
}
