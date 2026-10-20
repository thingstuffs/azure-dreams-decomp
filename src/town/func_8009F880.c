#include "town/menu/window.h"

/* Classify an object using its state and two positions relative to the geometry bounds. */
s32 classify_object_against_bounds(func_8009F880_S_8009CFE0_0 *object, void *position_data)
{
    func_8009F880_S_8009CFE0_2 *position = position_data;
    s32 result;
    s32 one;
    s32 geometry_result;
    s32 state_result;
    func_8009F880_S_8009CFE0_1 *state;

    state = object->unk_98;
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
        if (D_8006ADD4 == 0xC) {
            result = 0;
            return result;
        }
    }
    if (check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - position->unk_02),
            (s16)(D_80082D08[1] - position->unk_06),
            (s16)(D_80082D08[4] - position->unk_02),
            (s16)(D_80082D08[5] - position->unk_06),
            (s32)(s16)(D_80082D08[8] - position->unk_02),
            (s32)(s16)(D_80082D08[9] - position->unk_06),
            (s32)(s16)(D_80082D08[0xC] - position->unk_02),
            (s32)(s16)(D_80082D08[0xD] - position->unk_06)) == 0) {
        geometry_result = check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - object->unk_84),
            (s16)(D_80082D08[1] - object->unk_86),
            (s16)(D_80082D08[4] - object->unk_84),
            (s16)(D_80082D08[5] - object->unk_86),
            (s32)(s16)(D_80082D08[8] - object->unk_84),
            (s32)(s16)(D_80082D08[9] - object->unk_86),
            (s32)(s16)(D_80082D08[0xC] - object->unk_84),
            (s32)(s16)(D_80082D08[0xD] - object->unk_86));
        result = 2;
        if (geometry_result == 0) {
            return result;
        }
    }
    result = 0;
    return result;
}
