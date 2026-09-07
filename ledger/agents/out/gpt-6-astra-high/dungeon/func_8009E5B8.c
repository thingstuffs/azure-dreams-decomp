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

/* Selects the best eligible list candidate, resolving ties with the global candidate. */
void *func_800A3D18(void *owner_arg, void *start, s32 score_limit)
{
    register void *owner ASM_REG("$21");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *candidate;
    S_800A3D18_4 *base;
    register void *best ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register void *special ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 special_score;
    s16 best_score;
    u8 *global_page;
    S_800A3D18_2 *candidate_owner;
    void *next_link;
    s32 score;
    s32 special_cmp;
    s32 best_cmp;

    owner = owner_arg;
    ASM_KEEP_NV(owner);   /* MATCH pin: retail schedule: same instructions, different order without it */
    candidate = start;
    best = 0;
    special = best;
    special_score = 0x100;
    base = candidate;

    if ((s16)score_limit >= 0) {
        goto nonnegative;
    }
    best_score = -score_limit;
    goto initial;

set_special:
    special = candidate;
    special_score = 1;
    goto done;

nonnegative:
    best_score = 0x100;
    if (((S_800A3D18_0 *)owner)->unk_26 < 0) {
        best_score = score_limit;
    }

initial:
    next_link = ((S_800A3D18_1 *)candidate)->unk_5C;
    candidate = (u8 *)next_link + 0x20;
    if (candidate == base) {
        goto done;
    }
    global_page = (u8 *)0x800e0000;

loop:
    if ((s16)func_800A2CB8(base, candidate) == 0) {
        goto advance;
    }
    if ((s16)func_800A41F0(candidate) == 0) {
        goto advance;
    }

    candidate_owner = ((S_800A3D18_1_pre *)candidate)[-1].unk_00;
    if (((S_800A3D18_0 *)owner)->unk_26 == candidate_owner->unk_26) {
        score = func_8009FD40(candidate_owner, owner);
        if ((s16)score >= best_score) {
            goto advance;
        }
        if (candidate == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
            special = candidate;
            special_score = score;
        } else {
            best = candidate;
            best_score = score;
        }
        goto advance;
    }

    if ((s16)func_8009FE94(((S_800A3D18_0 *)owner)->unk_24,
                           ((S_800A3D18_0 *)owner)->unk_25,
                           base->unk_88,
                           candidate_owner->unk_24,
                           candidate_owner->unk_25,
                           ((S_800A3D18_1 *)candidate)->unk_88) == 0) {
        goto advance;
    }
    if (candidate == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
        goto set_special;
    }
    best = candidate;
    best_score = 1;
    goto done;

advance:
    next_link = ((S_800A3D18_1 *)candidate)->unk_5C;
    ASM_KEEP(candidate);   /* MATCH pin: retail register colouring depends on it */
    candidate = (u8 *)next_link + 0x20;
    if (candidate != base) {
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
    special_cmp = (s16)special_score;
    best_cmp = (s16)best_score;
    if (special_cmp == best_cmp) {
        if (((S_800A3D18_5 *)best)->unk_1C & 8) {
            best = special;
            goto out;
        }
        if ((((S_800A3D18_6 *)D_800E3D7C)->unk_128 + ((S_800A3D18_1 *)candidate)->unk_43) & 3) {
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
