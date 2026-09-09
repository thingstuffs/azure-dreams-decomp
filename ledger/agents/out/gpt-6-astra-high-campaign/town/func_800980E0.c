#include "common.h"

typedef struct S_80095840_0 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x1A];
    union { void * s; s32 u; } unk_2C;   /* accessed as both */
} S_80095840_0;   /* out in func_80095840 */

typedef struct S_80095840_1 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x1A];
    u8 unk_3A;
} S_80095840_1;   /* in in func_80095840 */

typedef struct S_80095840_2 {
    u8 pad_00[0x14];
    u8 unk_14;
    u8 pad_15[0x7];
    s32 unk_1C;
    u8 pad_20[0x1A];
    u8 unk_3A;
} S_80095840_2;   /* (void *)work in func_80095840 */

typedef struct S_80095840_3 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80095840_3;   /* entry in func_80095840 */



extern s32 D_800D0484[8];

/* Selects an eligible source entry and stores its pointer in the destination. */
s32 func_80095840(void *destination, void *source)
{
    S_80095840_0 *result;
    void *candidates;
    register s32 selection ASM_REG("$2");
    s32 offset;
    u8 entry_kind;

    result = destination;
    candidates = source;
    offset = result->unk_10;
    selection = offset + 0x100;
    if (selection >= 0) {
        selection >>= 7;
    } else {
        selection = (offset + 0x2FF) >> 7;
    }

    offset = (s32)D_800D0484;
    selection &= 0x1C;
    selection += offset;
    offset = *(s32 *)selection;
    if (offset == -1) {
        goto none;
    }

    selection = ((S_80095840_1 *)candidates)->unk_3A;
    if (selection != 0) {
        register void *entry ASM_REG("$6");

        selection = ((S_80095840_1 *)candidates)->unk_1C;
        ((S_80095840_1 *)candidates)->unk_18 = 0;
        ((S_80095840_1 *)candidates)->unk_10 = selection;
        ASM_SCHED_BARRIER();
        entry = (void *)selection;
        ASM_KEEP(entry);
        entry_kind = ((S_80095840_2 *)((void *)selection))->unk_14;
        if ((entry_kind == 1) || (entry_kind == 3)) {
            goto none;
        }
        selection = 2;
        result->unk_2C.s = entry;
        goto done;
    }

    selection = (s32)candidates + offset;
    if (((S_80095840_2 *)((void *)selection))->unk_3A != 0) {
        register void *entry ASM_REG("$6");

        selection = offset * 4;
        selection += (s32)candidates;
        selection = ((S_80095840_2 *)((void *)selection))->unk_1C;
        ((S_80095840_1 *)candidates)->unk_18 = offset;
        ((S_80095840_1 *)candidates)->unk_10 = selection;
        ASM_SCHED_BARRIER();
        entry = (void *)selection;
        entry_kind = ((S_80095840_3 *)entry)->unk_14;
        if ((entry_kind != 1) && (entry_kind != 3)) {
            selection = 1;
            result->unk_2C.s = entry;
            goto done;
        }
    }

none:
    result->unk_2C.u = 0;
    selection = 0;
done:
    ASM_SCHED_BARRIER();
    return selection;
}
