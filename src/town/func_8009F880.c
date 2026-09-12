#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80033B2C();
s32 func_8008CC90();
extern s16 D_8006ADD4;
extern u16 D_80082D08[];

typedef struct S_8009CFE0_0 {
    u8 pad_00[0x84];
    u16 unk_84;
    u16 unk_86;
    u8 pad_88[0x10];
    void * unk_98;
} S_8009CFE0_0;   /* arg0 in func_8009CFE0 */

typedef struct S_8009CFE0_1 {
    u8 pad_00[0x1];
    u8 unk_01;
    s16 unk_02;
} S_8009CFE0_1;   /* temp_s0 in func_8009CFE0 */

typedef struct S_8009CFE0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8009CFE0_2;   /* arg1 in func_8009CFE0 */

/* Classify an object using its state and two positions relative to the geometry bounds. */
s32 func_8009CFE0(S_8009CFE0_0 *object, void *position_data)
{
    S_8009CFE0_2 *position = position_data;
    s32 result;
    s32 one;
    s32 geometry_result;
    s32 state_result;
    S_8009CFE0_1 *state;

    state = object->unk_98;
    if (state != NULL) {
        if (!(state->unk_01 & 1)) {
            if (func_80033B2C(state->unk_02) == 0) {
                return 1;
            }
            goto check_flags;
        }
        state_result = func_80033B2C(state->unk_02);
        one = 1;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (state_result == one) {
            result = 1;
            return result;
        }
check_flags:
        if (state->unk_01 & 0x10) {
            result = 0;
            return result;
        }
    } else {
        goto geometry;
    }
check_mode:
    if (D_8006ADD4 == 0xC) {
        result = 0;
        return result;
    }
geometry:
    if (func_8008CC90(
            (s16)(D_80082D08[0] - position->unk_02),
            (s16)(D_80082D08[1] - position->unk_06),
            (s16)(D_80082D08[4] - position->unk_02),
            (s16)(D_80082D08[5] - position->unk_06),
            (s32)(s16)(D_80082D08[8] - position->unk_02),
            (s32)(s16)(D_80082D08[9] - position->unk_06),
            (s32)(s16)(D_80082D08[0xC] - position->unk_02),
            (s32)(s16)(D_80082D08[0xD] - position->unk_06)) != 0) {
        goto return_zero;
    }
    geometry_result = func_8008CC90(
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
return_zero:
    result = 0;
    return result;
}
