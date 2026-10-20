/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80DA7000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80DA7000_0;

typedef struct S_80DA7000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DA7000_1;

typedef struct S_80DA7000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DA7000_2;

typedef struct S_80DA7000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DA7000_4;

void *allocate_list_node();
s32 register_node(); /* extern */
s16 set_or_clear_actor_status_slot(); /* extern */
s32 generate_random_value();
void initialize_actor_sprite_and_animation(); /* extern */
s32 try_move_actor_to_valid_position(); /* extern */
extern M2C_UNK D_80158A3C;
extern M2C_UNK D_80158E68;
extern M2C_UNK D_8015B86C;

void *damp_effect_motion_and_fade_sprite(s16 init_flags, s16 value_24, s16 value_25, s16 value_0a) ;
/* Allocates an object and initializes its state and attached data from the supplied flags and values. */
void *damp_effect_motion_and_fade_sprite(s16 init_flags, s16 value_24, s16 value_25, s16 value_0a) {
    s32 global_byte;
    s32 unused_stack;
    s32 init_mode;
    SpriteFrameState *data_0c;
    S_80DA7000_2 *data_08;
    void *object;
    S_80DA7000_4 *extended_state;
    S_80DA7000_1 *state = NULL;
    s8 saved_value_24;
    s8 saved_value_25;
    s16 saved_value_0a;
    void *object_arg;
    void *data_arg;

    saved_value_24 = value_24;
    saved_value_0a = value_0a;
    saved_value_25 = value_25;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = allocate_list_node(0x112, ((s32 *)&D_80083498.next));
    if (object != NULL) {
        state = object + 0x20;
        ((S_80DA7000_0 *)object)->unk_10 = &D_80158A3C;
        state->unk_13 = 0x1A;
        register_node(object, project_sprite_chain);
        data_08 = ((S_80DA7000_0 *)object)->unk_08;
        data_08->unk_0A = saved_value_0a;
        data_0c = ((S_80DA7000_0 *)object)->unk_0C;
        init_mode = init_flags & 3;
        data_0c->unk_25 = saved_value_25;
        extended_state = state;
        data_0c->frameTable = &D_8015B86C;
        data_0c->unk_24 = saved_value_24;
        if (init_mode == 1) {
            state->unk_14 = (s32) (state->unk_14 | 0x6000);
            state->unk_1C = (s32) (state->unk_1C | 0x6000);
        } else if (init_mode >= 2) {
            state->unk_14 = (s32) (state->unk_14 | 0x2000);
            state->unk_1C = (s32) (state->unk_1C | 0x2000);
        } else {
            object_arg = object;
            if (((init_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & 0x200)) {
                    data_arg = data_08;
                    if (generate_random_value() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | 0x200);
                        set_or_clear_actor_status_slot(state, 1, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, data_08, data_0c, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_80158E68;
        try_move_actor_to_valid_position(extended_state, data_08, data_0c, state);
    }
    return state;
}
