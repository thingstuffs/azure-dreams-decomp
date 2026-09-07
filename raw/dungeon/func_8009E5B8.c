#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern u8 *D_800E3D7C;

extern s32 func_8009FD40(void *, void *);
extern s32 func_8009FE94(u8, u8, s16, u8, u8, s16);
extern s32 func_800A2CB8(void *, void *);
extern s32 func_800A41F0(void *);

void *func_800A3D18(void *arg0, void *arg1, s32 arg2)
{
    register void *owner ASM_REG("$21");
    register void *cur ASM_REG("$16");
    register void *base ASM_REG("$18");
    register void *best ASM_REG("$19");
    register void *special ASM_REG("$20");
    register s16 special_value ASM_REG("$22");
    register s16 best_value ASM_REG("$17");
    register u8 *global_page ASM_REG("$23");
    void *other;
    void *next;
    s32 value;
    s32 special_cmp;
    s32 best_cmp;

    owner = arg0;
    ASM_KEEP_NV(owner);
    cur = arg1;
    best = 0;
    special = best;
    special_value = 0x100;
    base = cur;

    if ((s16)arg2 >= 0) {
        goto nonnegative;
    }
    best_value = -arg2;
    goto initial;

set_special:
    special = cur;
    special_value = 1;
    goto done;

nonnegative:
    best_value = 0x100;
    if (FIELD(owner, s8, 0x26) < 0) {
        best_value = arg2;
    }

initial:
    next = FIELD(cur, void *, 0x5c);
    ASM_KEEP(cur);
    cur = (u8 *)next + 0x20;
    if (cur == base) {
        goto done;
    }
    global_page = (u8 *)0x800e0000;

loop:
    if ((s16)func_800A2CB8(base, cur) == 0) {
        goto advance;
    }
    if ((s16)func_800A41F0(cur) == 0) {
        goto advance;
    }

    other = FIELD(cur, void *, -0x14);
    if (FIELD(owner, s8, 0x26) == FIELD(other, s8, 0x26)) {
        value = func_8009FD40(other, owner);
        if ((s16)value >= best_value) {
            goto advance;
        }
        if (cur == FIELD(global_page, u8 *, 0x3d7c)) {
            special = cur;
            special_value = value;
        } else {
            best = cur;
            best_value = value;
        }
        goto advance;
    }

    if ((s16)func_8009FE94(FIELD(owner, u8, 0x24),
                           FIELD(owner, u8, 0x25),
                           FIELD(base, s16, 0x88),
                           FIELD(other, u8, 0x24),
                           FIELD(other, u8, 0x25),
                           FIELD(cur, s16, 0x88)) == 0) {
        goto advance;
    }
    if (cur == FIELD(global_page, u8 *, 0x3d7c)) {
        goto set_special;
    }
    best = cur;
    best_value = 1;
    goto done;

advance:
    next = FIELD(cur, void *, 0x5c);
    ASM_KEEP(cur);
    cur = (u8 *)next + 0x20;
    if (cur != base) {
        goto loop;
    }

done:
    if (special == 0) {
        goto out;
    }
    if (best == 0) {
        best = special;
        goto out;
    }
    special_cmp = (s16)special_value;
    best_cmp = (s16)best_value;
    ASM_KEEP(special_value);
    ASM_KEEP(best_value);
    if (special_cmp == best_cmp) {
        if (FIELD(best, s32, 0x1c) & 8) {
            best = special;
            goto out;
        }
        if ((FIELD(D_800E3D7C, s32, 0x128) + FIELD(cur, u8, 0x43)) & 3) {
            goto out;
        }
        best = special;
        goto out;
    } else if (special_cmp < best_cmp) {
        best = special;
    }

out:
    return best;
}
