#include "common.h"


extern u8 D_80082660;
extern s32 D_80082A38[];
extern u8 D_800A4F4C[];
extern u8 D_80100D98[];


typedef struct S_800A4F84_0 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    u8 pad_04[0x20];
    void * unk_24;
    u8 pad_28[0x8];
    union { void * p; s32 i; } unk_30;   /* accessed as both */
    s32 unk_34;
} S_800A4F84_0;   /* arg0 in func_800A4F84 */

typedef struct S_800A4F84_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800A4F84_1;   /* table + (state[1] * 8) in func_800A4F84 */

typedef struct S_800A4F84_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A4F84_2;   /* value in func_800A4F84 */


extern s32 func_800352FC(S_800A4F84_0 *, s32, s32, s32);
/* Select the object value from an override or state entry, falling back after nine idle calls. */
void func_800A4F84(S_800A4F84_0 *object, s32 check_arg_1, s32 check_arg_2, s32 check_arg_3) {
    u8 *state;
    u8 *state_table;
    S_800A4F84_2 *value;
    s32 idle_count;
    u8 state_index;

    if (func_800352FC(object, check_arg_1, check_arg_2, check_arg_3) != 0) {
        state = (u8 *)D_80082A38;
        if (state[1] != 0) {
            object->unk_34 = 0;
        }

        value = object->unk_30.p;
        if (value != 0) {
            object->unk_00.p = value;
            return;
        }

        state_index = state[1];
        if ((u32)(state_index - 2) < 0x53U) {
            state_table = &D_80082660;
            value = ((S_800A4F84_1 *)(state_table + (state[1] * 8)))->unk_04;
            if (value != 0) {
                object->unk_00.i = value->unk_08;
                return;
            }
            goto use_default;
        }

        if (state_index == 0) {
            idle_count = object->unk_34 + 1;
            object->unk_34 = idle_count;
            if (idle_count < 9) {
                return;
            }
            object->unk_34 = 9;
        }

use_default:
        object->unk_00.p = D_80100D98;
        return;
    } else {
        object->unk_00.p = D_80100D98;
        object->unk_24 = D_800A4F4C;
        object->unk_30.i = 0;
    }
}
