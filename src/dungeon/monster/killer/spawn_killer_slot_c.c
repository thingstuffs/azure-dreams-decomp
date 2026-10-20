/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

#include "shared/entity.h"

typedef struct R03_80170A28_S_80170A28_2 R03_80170A28_S_80170A28_2;
typedef struct ActionState ActionState;
typedef struct ActorSprite ActorSprite;

typedef struct S_80FF3000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80FF3000_0;

typedef struct S_80FF3000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80FF3000_1;

typedef struct S_80FF3000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FF3000_2;

typedef struct S_80FF3000_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80FF3000_4;

void *allocate_list_node();
s32 register_node();
s16 set_or_clear_actor_status_slot();
s32 generate_random_value();
void initialize_actor_sprite_and_animation();
s32 try_move_actor_to_valid_position();
void func_80158A7C(void *entity, R03_80170A28_S_80170A28_2 *motion, void *part);
void func_80158EA8(ActionState *actor, void *context, ActorSprite *sprite, EntityRec *entity);
extern M2C_UNK D_8015C038;
extern M2C_UNK D_8015C088;

void *spawn_killer_slot_c(s16, s32, s32, s16)
#ifdef __mips__
#endif
;

/* Allocates and initializes a dungeon object with flags and placement parameters. */
void *spawn_killer_slot_c(s16 init_flags, s32 pos_x, s32 pos_y, s16 init_value) {
    S_80FF3000_1 *object_state;
    void *object;
    u16 saved_value;
    S_80FF3000_2 *base_data;
    s8 saved_y;
    s8 saved_x;
    s32 mode_or_flags;
    s32 config_value;
    SpriteFrameState *placement;
    S_80FF3000_4 *extended_state;

    saved_x = pos_x;
    saved_value = init_value;
    saved_y = pos_y;
    pos_y = 0;
    object_state = (void *)pos_y;
    pos_x = 0x112;
    object = allocate_list_node(pos_x, ((void *)&D_80083498.next));
    if (object != NULL) {
        object_state = object + 0x20;
        ((S_80FF3000_0 *)object)->unk_10 = &func_80158A7C;
        object_state->unk_13 = 0x28;
        register_node(object, project_sprite_chain);
        config_value = (s32) &D_8015C038;
        base_data = ((S_80FF3000_0 *)object)->unk_08;
        base_data->unk_0A = saved_value;
        placement = ((S_80FF3000_0 *)object)->unk_0C;
        mode_or_flags = init_flags & 3;
        placement->unk_25 = saved_y;
        extended_state = object_state;
        placement->frameTable = (void *) config_value;
        placement->unk_24 = saved_x;
        if (mode_or_flags == 1) {
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x6000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x6000);
        } else if (mode_or_flags >= 2) {
            object_state->unk_14 = (s32) (object_state->unk_14 | 0x2000);
            object_state->unk_1C = (s32) (object_state->unk_1C | 0x2000);
        } else {
            config_value = init_flags & ~3;
            if ((config_value << 0x10) == 0) {
                if (!(object_state->unk_14 & 0x200)) {
                    if (generate_random_value() & 1) {
                        object_state->unk_1C = (s32) (object_state->unk_1C | 0x200);
                        set_or_clear_actor_status_slot(object_state, 1, (generate_random_value() & 0x3F) | 0x20);
                        placement->frameTable = &D_8015C088;
                    }
                }
            }
        }
        initialize_actor_sprite_and_animation(object, base_data, placement, (s16)(s32) init_flags);
        extended_state->unk_9A = 0xFF;
        extended_state->unk_9C = -1;
        extended_state->unk_8C = &func_80158EA8;
        try_move_actor_to_valid_position(extended_state, base_data, placement, object_state);
    }
    return object_state;
}
