#include "common.h"
#include "shared/types3a_types.h"

typedef struct S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    union { s16 s; s16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
    void * unk_68;
    s32 unk_6C;
} S_8008BA44_0;   /* obj in decrease_town_map_object_field_0a_and_transition */

   /* inner in decrease_town_map_object_field_0a_and_transition */

typedef struct S_8008BA44_2 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
} S_8008BA44_2;   /* test_inner in decrease_town_map_object_field_0a_and_transition */


extern u8 D_8008BC58[];
extern u8 D_800CFC70[];
extern s32 D_800CFC7C[];

/* Decrement the inner value, clamping it to zero and resetting object state if it becomes negative. */
void decrease_town_map_object_field_0a_and_transition(S_8008BA44_0 *obj)
{
    UnsignedCountdownView *state;
    S_8008BA44_2 *signed_state;
    s32 reset_data;

    state = obj->unk_00;
    state->unk_0A = (u16)(state->unk_0A - 0x100);
    signed_state = obj->unk_00;
    if (signed_state->unk_0A.s < 0) {
        signed_state->unk_0A.u = 0;
        obj->unk_68 = D_8008BC58;
        obj->unk_64.s = (s8)D_800CFC70[obj->unk_66];
        reset_data = D_800CFC7C[obj->unk_66];
        obj->unk_64.u = 0x16;
        obj->unk_6C = reset_data;
    }
}
