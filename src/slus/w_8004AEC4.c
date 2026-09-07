#include "common.h"

#include "common.h"

extern void *memcpy(void *dest, void *src, s32 n);

/* Selection sort: for each position i in [0, count-1), find the "best"
 * element in [i, count) via compar, then swap base[i] with best via a
 * 0x100-byte stack temp (frame 0x138, temp at sp+0x10 kept in s7).
 *
 * Retail s-reg roles: s6=count, s5=size, fp=cmp, s3=base/cur, s4=i, s7=tmp.
 * Default -O2 rotates size/i with base; pin i→s4 and size→s5, and compile
 * with -fno-schedule-insns so the prologue param→s-reg order matches
 * (a1, a2, a3, a0) rather than declaration order. */
void func_8004AEC4(u8 *base, s32 count, s32 size, s32 (*compar)(u8 *, u8 *)) {
    u8 temp[0x100];
    u8 *tmp;
    u8 *best;
    u8 *p;
    u8 *cur;
    s32 j;
    s32 n;
    s32 (*cmp)(u8 *, u8 *);
    register s32 i ASM_REG("$20"); /* s4 */
    register s32 sz ASM_REG("$21"); /* s5 */

    n = count;
    sz = size;
    cmp = compar;
    cur = base;

    if (n != 0) {
        i = 0;
        if ((n - 1) > 0) {
            tmp = temp;
            do {
                best = cur;
                j = i + 1;
                p = cur + sz;
                if (j < n) {
                    do {
                        if (cmp(best, p) > 0) {
                            best = p;
                        }
                        j += 1;
                        p += sz;
                    } while (j < n);
                }
                memcpy(tmp, cur, sz);
                memcpy(cur, best, sz);
                memcpy(best, tmp, sz);
                i += 1;
                cur += sz;
            } while (i < (n - 1));
        }
    }
}
