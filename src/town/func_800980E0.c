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
    s32 selection;
    s32 offset;
    s32 initial_angle;
    void *entry;

    result = destination;
    candidates = source;
    initial_angle = result->unk_10;
    selection = initial_angle + 0x100;
    if (selection >= 0) {
        selection >>= 7;
        offset = 0x800D0000;
    } else {
        selection = (initial_angle + 0x2FF) >> 7;
        offset = 0x800D0000;
    }

    offset += 0x484;
    selection &= 0x1C;
    selection += offset;
    offset = *(s32 *)selection;
    if (offset != -1) {
        selection = ((S_80095840_1 *)candidates)->unk_3A;
        if (selection != 0) {

            selection = ((S_80095840_1 *)candidates)->unk_1C;
            ((S_80095840_1 *)candidates)->unk_10 = selection;
            ((S_80095840_1 *)candidates)->unk_18 = 0;
            entry = (void *)((S_80095840_1 *)candidates)->unk_10;
            offset = ((S_80095840_2 *)((void *)selection))->unk_14;
            if ((offset == 1) || (offset == 3)) {
                result->unk_2C.u = 0;
                selection = 0;
                return selection;
            }
            selection = 2;
            result->unk_2C.s = entry;
            return selection;
        }

        selection = (s32)candidates + offset;
        if (((S_80095840_2 *)((void *)selection))->unk_3A != 0) {

            selection = offset * 4;
            selection += (s32)candidates;
            selection = ((S_80095840_2 *)((void *)selection))->unk_1C;
            ((S_80095840_1 *)candidates)->unk_10 = selection;
            ((S_80095840_1 *)candidates)->unk_18 = offset;
            entry = (void *)((S_80095840_1 *)candidates)->unk_10;
            offset = ((S_80095840_3 *)entry)->unk_14;
            if ((offset != 1) && (offset != 3)) {
                selection = 1;
                result->unk_2C.s = entry;
                return selection;
            }
        }
    }
    result->unk_2C.u = 0;
    selection = 0;
    return selection;
}
