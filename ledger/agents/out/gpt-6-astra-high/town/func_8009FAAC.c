#include "common.h"
#include "records/Rec_D_80082D58.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80033B2C();
s32 func_8008CC90();
extern u16 D_80082D08[];


typedef struct S_8009D20C_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    s16 unk_02;
} S_8009D20C_1;   /* temp_s0 in func_8009D20C */

typedef struct S_8009D20C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8009D20C_2;   /* arg1 in func_8009D20C */

/* Classifies a record using its attached state and two position tests. */
s32 func_8009D20C(Rec_D_80082D58 *record, void *position_data)
{
    S_8009D20C_2 *position = position_data;
    register s32 result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 one;
    s32 geom_result;
    s32 state_result;
    S_8009D20C_1 *state;

    state = record->unk_98.as_pv;
    if (state != NULL) {
        if (!(state->unk_01 & 1)) {
            if (func_80033B2C(state->unk_02) == 0) {
                return 1;
            }
            goto check_flags;
        }
        state_result = func_80033B2C(state->unk_02);
        one = 1;
        if (state_result == one) {
            result = 1;
        } else {
check_flags:
            if (!(state->unk_01 & 0x10)) {
                goto check_positions;
            }
            result = 0;
        }
        return result;
    }
check_positions:
    if (func_8008CC90(
        (s16)(D_80082D08[0] - position->unk_02), (s16)(D_80082D08[1] - position->unk_06),
        (s16)(D_80082D08[4] - position->unk_02), (s16)(D_80082D08[5] - position->unk_06),
        (s32)(s16)(D_80082D08[8] - position->unk_02), (s32)(s16)(D_80082D08[9] - position->unk_06),
        (s32)(s16)(D_80082D08[0xC] - position->unk_02), (s32)(s16)(D_80082D08[0xD] - position->unk_06)) != 0) {
        goto geom_zero;
    }
    geom_result = func_8008CC90(
        (s16)(D_80082D08[0] - record->unk_84), (s16)(D_80082D08[1] - record->unk_86),
        (s16)(D_80082D08[4] - record->unk_84), (s16)(D_80082D08[5] - record->unk_86),
        (s32)(s16)(D_80082D08[8] - record->unk_84), (s32)(s16)(D_80082D08[9] - record->unk_86),
        (s32)(s16)(D_80082D08[0xC] - record->unk_84), (s32)(s16)(D_80082D08[0xD] - record->unk_86));
    result = 2;
    if (geom_result == 0) {
        goto geom_done;
    }
geom_zero:
    result = 0;
geom_done:
    return result;
}
