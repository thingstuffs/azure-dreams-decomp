#include "common.h"

typedef struct {
    s32 unk00;
    s32 unk04;
} S_800869C0;

extern S_800869C0 D_800869C0[16];
extern u8 D_8007382B[9];
extern s32 D_80073830[9];
extern void func_80059DAC(void);

s32 func_80059E94(s32 arg0)
{
    s32 saved;
    s32 result;
    S_800869C0 *entry0;
    s32 candidate;
    s32 *new_var2;
    s32 boundary;
    s32 v1;
    S_800869C0 *p;
    s32 new_var;
    s32 i;
    u8 idx;

    saved = arg0;
    result = 0x1010;
    entry0 = &D_800869C0[0];
    if (entry0->unk00 != 0) {
        goto loop_start;
    }
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    candidate = saved + 0x1010;
    {
        u8 fast_idx = D_8007382B[0];
        s32 *fast_table = D_80073830;

        boundary = 0x80000 - fast_table[fast_idx];
    }
    if ((u32)candidate >= (u32)boundary) {
        return -1;
    }
    entry0->unk00 = result;
    entry0->unk04 = saved;
    goto tail;

found:
    p->unk00 = v1;
    p->unk04 = saved;
    goto tail;

loop_start:
    {
        s32 loop_boundary;

        i = 0;
        loop_boundary = 0x80000;
        p = entry0;
        idx = D_8007382B[0];
        for (; 16 > i; i++, p++) {
            if (p->unk04 != 0) {
                continue;
            }
            new_var = (new_var2 = D_80073830)[idx];
            result = p->unk00;
            v1 = result + saved;
            if ((u32)v1 >= (u32)(loop_boundary - new_var)) {
                return -1;
            }
            goto found;
        }
    }

tail:
    func_80059DAC();
    return result;
}
