#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80B73054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B73054_1;   /* work in create_dungeon_actor_from_spawn_flags */

typedef struct S_80B73054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B73054_2;   /* part_a in create_dungeon_actor_from_spawn_flags */

typedef struct S_80B73054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B73054_4;   /* actor in create_dungeon_actor_from_spawn_flags */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8016AA30[];
extern M2C_UNK D_8016AE5C;
extern u8 D_8016DD0C[];
extern u8 D_8016DD4C[];

/* Creates a dungeon actor and initializes its parts and state from the spawn flags. */
/* Creates Battnel with default frames at D_8016DD0C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_dungeon_actor_from_spawn_flags(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_80B73054_2 *part_a;
    SpriteFrameState *part_b;
    S_80B73054_1 *work;
    S_80B73054_4 *actor;
    s32 state_bits;
    s32 next_state_bits;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    void *saved_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8016AA30;
        work->unk_13 = MONSTER_BATTNEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = D_8016DD0C;
        part_b->tile_x = saved_x;
        do {

            if (kind == 1) {
                state_bits = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
                next_state_bits = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
                work->unk_14 = state_bits;
                work->unk_1C = next_state_bits;
            } else if (kind >= 2) {
                state_bits = work->unk_14 | ACTOR_CLASS_ENABLED;
                next_state_bits = work->unk_1C | ACTOR_PLAYER_SIDE;
                work->unk_14 = state_bits;
                work->unk_1C = next_state_bits;
            } else {
                saved_part = obj;
                if (((spawn_flags & ~3) << 16) == 0) {
                    if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                        saved_part = part_a;
                        state_bits = generate_random_value();
                        saved_part = obj;
                        if (!(state_bits & 1)) {
                            break;
                        }
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value(obj) & 0x3F) | 0x20);
                        part_b->frameTable = D_8016DD4C;
                    }
                }
            }
            saved_part = obj;

        } while (0);
        initialize_actor_sprite_and_animation(saved_part, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8016AE5C;
        actor->unk_A4 = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
