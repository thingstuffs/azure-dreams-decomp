#include "town/menu/window.h"

/* Classifies a record using its attached state and two position tests. */
s32 classify_record_by_state_and_position(Rec_D_80082D58 *record, void *position_data)
{
    func_8009FAAC_S_8009D20C_2 *position = position_data;
    s32 result;
    s32 one;
    s32 geom_result;
    s32 state_result;
    func_8009FAAC_S_8009D20C_1 *state;

    state = record->unk_98.as_pv;
    if (state != NULL) {
        if (!(state->unk_01 & 1)) {
            if (test_resident_bitmap_bit(state->unk_02) == 0) {
                return 1;
            }
        } else {
            state_result = test_resident_bitmap_bit(state->unk_02);
            one = 1;
            if (state_result == one) {
                result = 1;
                return result;
            }
        }
        if (state->unk_01 & 0x10) {
            result = 0;
            return result;
        }
    }
    if (check_four_vector_half_turn_gaps(
        (s16)(D_80082D08[0] - position->unk_02), (s16)(D_80082D08[1] - position->unk_06),
        (s16)(D_80082D08[4] - position->unk_02), (s16)(D_80082D08[5] - position->unk_06),
        (s32)(s16)(D_80082D08[8] - position->unk_02), (s32)(s16)(D_80082D08[9] - position->unk_06),
        (s32)(s16)(D_80082D08[0xC] - position->unk_02), (s32)(s16)(D_80082D08[0xD] - position->unk_06)) == 0) {
        geom_result = check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - record->unk_84), (s16)(D_80082D08[1] - record->unk_86),
            (s16)(D_80082D08[4] - record->unk_84), (s16)(D_80082D08[5] - record->unk_86),
            (s32)(s16)(D_80082D08[8] - record->unk_84), (s32)(s16)(D_80082D08[9] - record->unk_86),
            (s32)(s16)(D_80082D08[0xC] - record->unk_84), (s32)(s16)(D_80082D08[0xD] - record->unk_86));
        result = 2;
        if (geom_result == 0) {
            return result;
        }
    }
    result = 0;
    return result;
}
