/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80D95000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80D95000_0;

typedef struct S_80D95000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80D95000_1;

typedef struct S_80D95000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80D95000_2;

typedef struct S_80D95000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80D95000_4;

void *allocate_list_node();
s32 register_node();
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
extern u8 D_8016AA3C[];
extern s32 D_8016AE68;
extern s32 D_8016D86C;

void *damp_and_fade_effect_sprite(s16 init_flags, s16 x, s16 y, s16 initial_value) ;
/* Allocates an object and initializes its state, placement, and mode. */
/* Creates Dreamin with default frames at D_8016D86C, applies spawn flags, and attempts valid tile
 * placement. */
void *damp_and_fade_effect_sprite(s16 init_flags, s16 x, s16 y, s16 initial_value) {
    s32 global_byte;
    s32 unused_slot;
    s32 mode;
    SpriteFrameState *placement;
    S_80D95000_2 *object_data;
    void *object;
    S_80D95000_4 *extended_state;
    S_80D95000_1 *state = 0;
    s8 saved_x;
    s8 saved_y;
    s16 saved_value;
    s32 state_flags;
    s32 pending_flags;

    saved_x = x;
    saved_value = initial_value;
    saved_y = y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != 0) {
        state = object + 0x20;
        ((S_80D95000_0 *)object)->unk_10 = &D_8016AA3C;
        state->unk_13 = MONSTER_DREAMIN;
        register_node(object, project_sprite_chain);
        object_data = ((S_80D95000_0 *)object)->unk_08;
        object_data->unk_0A = saved_value;
        placement = ((S_80D95000_0 *)object)->unk_0C;
        mode = init_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->frameTable = &D_8016D86C;
        placement->unk_24 = saved_x;
        if (mode == 1) {
            state_flags = state->unk_14 | 0x6000;
            pending_flags = state->unk_1C | 0x6000;
            state->unk_14 = state_flags;
            state->unk_1C = pending_flags;
        } else if (mode >= 2) {
            state_flags = state->unk_14 | 0x2000;
            pending_flags = state->unk_1C | 0x2000;
            state->unk_14 = state_flags;
            state->unk_1C = pending_flags;
        } else {
            if (((init_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | 0x200);
                        set_or_clear_actor_status_slot(state, 1, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, object_data, placement, init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8016AE68;
        try_move_actor_to_valid_position(extended_state, object_data, placement, state);
    }
    return state;
}
