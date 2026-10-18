#include "common.h"
#include "shared/entity.h"
#include "records/Rec_D_800CFCB4.h"

s32 scale_random_to_unsigned_halfword_limit();                         /* extern */
s32 func_800644B8();                             /* extern */
void initialize_entity_flags_transform_type_dependent_variant(); /* extern */


typedef struct S_8009F374_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009F374_2;   /* arg3 in handle_jitter_position_pulse_scale_until_countdown_expires */

/* Jitter the position and pulse the scale until the countdown expires. */
void handle_jitter_position_pulse_scale_until_countdown_expires(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, S_8009F374_2 *scale) {
    s16 ticks_left;
    s32 scale_x_wave;
    s32 scale_y_wave;

    position->z.v = (s32) (state->unk_A0 + (((scale_random_to_unsigned_halfword_limit(0x10) & 0xFFFF) - 8) << 0x10));
    scale_x_wave = func_800644B8(state->unk_6C.as_s16 * 0x199);
    scale->unk_1C = (s16) ((scale_x_wave / 4) + 0x1000);
    scale_y_wave = func_800644B8(state->unk_6C.as_s16 * 0x199);
    scale->unk_1E = (s16) (0x1000 - (scale_y_wave / 4));
    ticks_left = (u16) state->unk_6C.as_s16 - 1;
    state->unk_6C.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        scale->unk_1E = 0x1000;
        scale->unk_1C = 0x1000;
        initialize_entity_flags_transform_type_dependent_variant(state, context, position, scale);
    }
}
