#include "common.h"
#include "shared/position_views.h"
#include "town/map/object.h"
#include "town/map.h"
#include "town/map/state_ids_data.h"

typedef struct S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    s16 unk_64;
    s16 unk_66;
    void * unk_68;
    s32 unk_6C;
} S_8008BA44_0;   /* obj in decrease_town_map_object_field_0a_and_transition */

   /* inner in decrease_town_map_object_field_0a_and_transition */

typedef struct S_8008BA44_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8008BA44_2;   /* test_inner in decrease_town_map_object_field_0a_and_transition */




extern s32 town_map_state_values[];

/* Decrement the inner value, clamping it to zero and resetting object state if it becomes negative. */
void decrease_town_map_object_field_0a_and_transition(S_8008BA44_0 *obj)
{
    UnsignedCountdownView *state;
    S_8008BA44_2 *signed_state;
    s32 reset_data;

    state = obj->unk_00;
    state->unk_0A = (u16)(state->unk_0A - 0x100);
    signed_state = obj->unk_00;
    if (signed_state->unk_0A < 0) {
        signed_state->unk_0A = 0;
        obj->unk_68 = handle_town_map_input;
        obj->unk_64 = (s8)town_map_state_ids[obj->unk_66];
        reset_data = town_map_state_values[obj->unk_66];
        obj->unk_64 = 0x16;
        obj->unk_6C = reset_data;
    }
}
