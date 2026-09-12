#include "common.h"
#include "records/Rec_D_800E3D7C.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_8009CD58_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009CD58_1;   /* temp_a0_3 in func_8009CD58 */

/* Returns masked record flags augmented by the selected kind. */
s32 func_8009CD58(Rec_D_800E3D7C *record, s32 mask, s32 mode) {
    s32 shifted_mode;
    s32 base_flags;
    register s32 flags ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 third_kind;
    u8 *kind_ptr;
    s32 kind;
    S_8009CD58_1 *detail;

    shifted_mode = mode << 16;
    base_flags = record->unk_14.as_u16 & mask;
    flags = base_flags;
    if (shifted_mode != 0) {
        detail = record->unk_4C.as_pv;
        if (detail != NULL) {
            if (detail->unk_01 == 15) {
                kind = detail->unk_00;
                if (kind == 5) {
                    third_kind = mask & 1;
                    goto merge_flags;
                }
                if (kind == 6) {
                    third_kind = mask & 2;
                    goto merge_flags;
                }
                third_kind = 7;
                goto check_third_kind;
            }
            kind = detail->unk_00;
            if (kind == 6) {
                third_kind = mask & 1;
                goto merge_flags;
            }
            if (kind == 7) {
                third_kind = mask & 2;
                goto merge_flags;
            }
            third_kind = 8;
            goto check_third_kind;
        }
        return flags;
    }
    kind_ptr = record->unk_50.at00_pu8.v;
    if (kind_ptr != NULL) {
        kind = *kind_ptr;
        if (kind == 8) {
            third_kind = mask & 1;
            goto merge_flags;
        }
        if (kind == 9) {
            third_kind = mask & 2;
            goto merge_flags;
        }
        third_kind = 10;
check_third_kind:
        if (kind != third_kind) {
            return flags;
        }
        third_kind = mask & 4;
merge_flags:
        flags = base_flags | third_kind;
    }
    return flags;
}
