#include "common.h"

#include "common.h"

extern s32 D_800869C0[];

void func_80059DAC(void)
{
    s32 sp[2];
    register s32 count ASM_REG("$8");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    s32 i;
    s32 j;
    void *scan;
    void *cur;
    void *base;
    register void *other ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *cur2;

    count = 0;
    scan = D_800869C0;
loop_1:
    if (*(s32 *)scan != 0) {
        count++;
        if (count < 16) {
            scan = (s8 *)scan + 8;
            goto loop_1;
        }
    }

    i = 0;
    if (count > 0) {
        cur = D_800869C0;
        base = cur;
        do {
            j = count - 1;
            if (i < j) {
                register s32 offset ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

                offset = j * 8;
                cur2 = cur;
                other = (void *)(offset + (s32)base);
                do {
                    if (*(s32 *)cur2 > *(s32 *)other) {
                        sp[1] = *(s32 *)((s8 *)cur2 + 4);
                        sp[0] = *(s32 *)cur2;
                        *(s32 *)((s8 *)cur2 + 4) = *(s32 *)((s8 *)other + 4);
                        *(s32 *)cur2 = *(s32 *)other;
                        *(s32 *)((s8 *)other + 4) = sp[1];
                        *(s32 *)other = sp[0];
                    }
                    j--;
                    other = (s8 *)other - 8;
                } while (i < j);
            }
            i++;
            cur = (s8 *)cur + 8;
        } while (i < count);
    }
}
