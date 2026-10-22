/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80DB3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80DB3000_1;

typedef struct S_80DB3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80DB3000_2;

typedef struct S_80DB3000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80DB3000_4;

void *allocate_list_node();
s32 register_node(); /* extern */
s16 set_or_clear_actor_status_slot(); /* extern */
s32 generate_random_value();
void initialize_actor_sprite_and_animation(); /* extern */
s32 try_move_actor_to_valid_position(); /* extern */
extern M2C_UNK D_8014CA3C;
extern u8 D_8014CE68;
extern M2C_UNK D_8014F86C;

void *move_expand_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 property_value) ;
/* Allocates and initializes a dungeon object with the supplied flags and placement. */
/* Creates Dreamin with default frames at D_8014F86C, applies spawn flags, and attempts valid tile
 * placement. */
void *move_expand_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 property_value) {
    s32 global_byte;
    s32 unused_slot;
    s32 spawn_mode;
    s32 flags_14;
    s32 flags_1c;
    SpriteFrameState *placement;
    S_80DB3000_2 *properties;
    ObjectNodeHeader *object;
    S_80DB3000_4 *extended_state;
    S_80DB3000_1 *state = NULL;
    s8 saved_x;
    s8 saved_y;
    s16 saved_property;
    void *call_object;
    void *call_properties;

    saved_x = grid_x;
    saved_property = property_value;
    saved_y = grid_y;
    global_byte = (s32) *(s8 *)-0x56D4;
    object = allocate_list_node(0x112, ((s32 *)&scene_object_list_anchor.next));
    if (object != NULL) {
        state = ((void *)object) + 0x20;
        object->unk_10 = &D_8014CA3C;
        state->unk_13 = MONSTER_DREAMIN;
        register_node(object, project_sprite_chain);
        properties = object->position;
        properties->unk_0A = saved_property;
        placement = object->sprite;
        spawn_mode = spawn_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = state;
        placement->frameTable = &D_8014F86C;
        placement->unk_24 = saved_x;
        if (spawn_mode == 1) {
            flags_14 = state->unk_14 | 0x6000;
            flags_1c = state->unk_1C | 0x6000;
            state->unk_14 = flags_14;
            state->unk_1C = flags_1c;
        } else if (spawn_mode >= 2) {
            flags_14 = state->unk_14 | 0x2000;
            flags_1c = state->unk_1C | 0x2000;
            state->unk_14 = (s32) flags_14;
            state->unk_1C = (s32) flags_1c;
        } else {
            if (((spawn_flags & ~3) << 0x10) == 0) {
                if (!(state->unk_14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        state->unk_1C = (s32) (state->unk_1C | 0x200);
                        set_or_clear_actor_status_slot(state, 1, (generate_random_value() & 0x3F) | 0x20);
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, properties, placement, spawn_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &D_8014CE68;
        try_move_actor_to_valid_position(extended_state, properties, placement, state);
    }
    return state;
}
