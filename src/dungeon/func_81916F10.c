#include "common.h"
#include "m2c_compat.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */

typedef struct S_80024710_0 {
    void * unk_00;
    u8 pad_04[0xA];
    s16 unk_0E;
    s16 unk_10;
} S_80024710_0;   /* arg0 in func_80024710 */

typedef struct S_80024710_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024710_1;   /* temp_v1 in func_80024710 */

typedef struct S_80024710_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024710_2;   /* arg1 in func_80024710 */

/* Advance the object counter and offset the position using its two angles. */
void func_80024710(S_80024710_0 *object, S_80024710_2 *position) {
    s32 angle_scale_x;
    s32 angle_scale_y;
    S_80024710_1 *state;

    state = object->unk_00;
    state->unk_14 = (u16) (state->unk_14 + 1);
    angle_scale_x = func_800644B8(object->unk_0E);
    position->unk_00 = (s32) (position->unk_00 + ((angle_scale_x >> 4) * (func_800644B8(object->unk_10) >> 4) * 0x1C));
    angle_scale_y = func_800644B8(object->unk_0E);
    position->unk_04 = (s32) (position->unk_04 + ((angle_scale_y >> 4) * (func_80064584(object->unk_10) >> 4) * 0x1C));
    position->unk_08 = (s32) (position->unk_08 + ((func_80064584(object->unk_0E) >> 4) * 0x1C00));
}
