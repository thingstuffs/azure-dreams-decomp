#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80ABF07C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80ABF07C_1;   /* work in create_actor_for_selected_kind */

typedef struct S_80ABF07C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80ABF07C_2;   /* part_a in create_actor_for_selected_kind */

typedef struct S_80ABF07C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_80ABF07C_4;   /* actor in create_actor_for_selected_kind */

extern void *allocate_list_node();
extern void register_node();
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot();
extern void initialize_actor_sprite_and_animation();
extern void try_move_actor_to_valid_position();
extern u8 D_8014CA50[];
extern M2C_UNK D_8014CE7C;
extern u8 D_80150C3C[];
extern u8 D_80150C8C[];

/* Creates an actor and initializes its parts and flags for the selected kind. */
/* Creates Griffon with default frames at D_80150C3C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_actor_for_selected_kind(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_value)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_80ABF07C_2 *part_a;
    SpriteFrameState *part_b;
    S_80ABF07C_1 *work;
    S_80ABF07C_4 *actor;
    s32 flags_or_roll;
    s32 state_flags;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    void *init_part;

    work = 0;
    saved_x = tile_x;
    saved_value = part_value;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_8014CA50;
        work->unk_13 = MONSTER_GRIFFON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_value;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->frameTable = D_80150C3C;
        part_b->unk_24 = saved_x;
        do {

            if (kind == 1) {
                flags_or_roll = work->unk_14 | 0x6000;
                state_flags = work->unk_1C | 0x6000;
                work->unk_14 = flags_or_roll;
                work->unk_1C = state_flags;
            } else if (kind >= 2) {
                flags_or_roll = work->unk_14 | 0x2000;
                state_flags = work->unk_1C | 0x2000;
                work->unk_14 = flags_or_roll;
                work->unk_1C = state_flags;
            } else {
                init_part = obj;
                if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                    init_part = part_a;
                    flags_or_roll = generate_random_value();
                    init_part = obj;
                    if (!(flags_or_roll & 1)) {
                        break;
                    }
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value(obj) & 0x3F) | 0x20);
                    part_b->frameTable = D_80150C8C;
                }
            }
            init_part = obj;

        } while (0);
        initialize_actor_sprite_and_animation(init_part, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE7C;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
