#include "common.h"

typedef struct S_800A3D18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_0;   /* owner in func_800A3D18 */

typedef struct S_800A3D18_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A3D18_1_pre;   /* the 0x14 bytes before cur in func_800A3D18, addressed as cur[-1] */

typedef struct S_800A3D18_1 {
    u8 pad_00[0x43];
    u8 unk_43;
    u8 pad_44[0x18];
    void * unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_800A3D18_1;   /* cur in func_800A3D18 */

typedef struct S_800A3D18_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_2;   /* other in func_800A3D18 */

typedef struct S_800A3D18_3 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800A3D18_3;   /* global_page in func_800A3D18 */

typedef struct S_800A3D18_4 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A3D18_4;   /* base in func_800A3D18 */

typedef struct S_800A3D18_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800A3D18_5;   /* best in func_800A3D18 */

typedef struct S_800A3D18_6 {
    u8 pad_00[0x128];
    s32 unk_128;
} S_800A3D18_6;   /* D_800E3D7C in func_800A3D18 */



extern u8 *D_800E3D7C;

extern s32 func_8009FD40(void *, void *);
extern s32 func_8009FE94(u8, u8, s16, u8, u8, s16);
extern s32 func_800A2CB8(void *, void *);
extern s32 func_800A41F0(void *);

void *func_800A3D18(void *arg0, void *arg1, s32 arg2)
{
    register void *owner ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *cur;
    S_800A3D18_4 *base;
    register void *best ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *special ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 special_value;
    s16 best_value;
    u8 *global_page;
    S_800A3D18_2 *other;
    void *next;
    s32 value;
    s32 special_cmp;
    s32 best_cmp;

    owner = arg0;
    ASM_KEEP_NV(owner);   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    if (((S_800A3D18_0 *)owner)->unk_26 < 0) {
        best_value = arg2;
    }

initial:
    next = ((S_800A3D18_1 *)cur)->unk_5C;
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

    other = ((S_800A3D18_1_pre *)cur)[-1].unk_00;
    if (((S_800A3D18_0 *)owner)->unk_26 == other->unk_26) {
        value = func_8009FD40(other, owner);
        if ((s16)value >= best_value) {
            goto advance;
        }
        if (cur == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
            special = cur;
            special_value = value;
        } else {
            best = cur;
            best_value = value;
        }
        goto advance;
    }

    if ((s16)func_8009FE94(((S_800A3D18_0 *)owner)->unk_24,
                           ((S_800A3D18_0 *)owner)->unk_25,
                           base->unk_88,
                           other->unk_24,
                           other->unk_25,
                           ((S_800A3D18_1 *)cur)->unk_88) == 0) {
        goto advance;
    }
    if (cur == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
        goto set_special;
    }
    best = cur;
    best_value = 1;
    goto done;

advance:
    next = ((S_800A3D18_1 *)cur)->unk_5C;
    ASM_KEEP(cur);   /* MATCH pin: retail register colouring depends on it */
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
    if (special_cmp == best_cmp) {
        if (((S_800A3D18_5 *)best)->unk_1C & 8) {
            best = special;
            goto out;
        }
        if ((((S_800A3D18_6 *)D_800E3D7C)->unk_128 + ((S_800A3D18_1 *)cur)->unk_43) & 3) {
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
