#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/dungeon_effect_views.h"


extern s32 runtime_script_state[];
extern u8 D_800A4F4C[];
extern u8 town_position_reference_state[];


typedef struct S_800A4F84_0 {
    union { void * p; s32 i; } unk_00;   /* accessed as both */
    u8 pad_04[0x20];
    void * unk_24;
    u8 pad_28[0x8];
    union { void * p; s32 i; } unk_30;   /* accessed as both */
    s32 unk_34;
} S_800A4F84_0;   /* arg0 in select_object_value_with_idle_fallback */

typedef struct S_800A4F84_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800A4F84_1;   /* table + (state[1] * 8) in select_object_value_with_idle_fallback */

   /* value in select_object_value_with_idle_fallback */


extern s32 service_script_controller(void);
/* Select the object value from an override or state entry, falling back after nine idle calls. */
void select_object_value_with_idle_fallback(S_800A4F84_0 *object, s32 check_arg_1, s32 check_arg_2, s32 check_arg_3) {
    u8 *state;
    u8 *state_table;
    EffectStateWordView *value;
    s32 idle_count;
    u8 state_index;

    if (service_script_controller() != 0) {
        state = (u8 *)runtime_script_state;
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
            state_table = ((u8 *)object_index_slots);
            value = ((S_800A4F84_1 *)(state_table + (state[1] * 8)))->unk_04;
            if (value != 0) {
                object->unk_00.i = value->unk_08;
                return;
            }
        } else if (state_index == 0) {
            idle_count = object->unk_34 + 1;
            object->unk_34 = idle_count;
            if (idle_count < 9) {
                return;
            }
            object->unk_34 = 9;
        }

        object->unk_00.p = town_position_reference_state;
        return;
    } else {
        object->unk_00.p = town_position_reference_state;
        object->unk_24 = D_800A4F4C;
        object->unk_30.i = 0;
    }
}
