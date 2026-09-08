#include "common.h"

#include "common.h"

extern s32 D_80085FA4[4];
extern s32 D_800869B0[4];

typedef struct {
    s32 unk00;
    u8 pad04[0x28];
    s32 unk2C;
} S_800589B8;

s32 func_800589B8(S_800589B8 *arg)
{
    S_800589B8 *p = arg;
    register u32 limit_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 *base;
    s32 idx;
    s32 val;
    s32 limit;

    base = (u8 *)D_80085FA4[0];
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    idx = p->unk00;
    limit_page = 0x80080000;
    val = base[idx];
    limit = *(s32 *)(limit_page + 0x69B0);
    idx = idx + 1;
    p->unk00 = idx;
    if ((u32)limit < (u32)idx) {
        p->unk2C = 1;
        return -1;
    }
    ASM_USE(limit_page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    return val;
}
