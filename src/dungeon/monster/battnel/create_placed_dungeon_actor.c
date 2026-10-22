#include "common.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

typedef struct S_80B7F054_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80B7F054_0;   /* obj in create_placed_dungeon_actor */

typedef struct S_80B7F054_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_80B7F054_1;   /* work in create_placed_dungeon_actor */

typedef struct S_80B7F054_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80B7F054_2;   /* part_a in create_placed_dungeon_actor */

typedef struct S_80B7F054_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x7];
    s16 unk_A4;
} S_80B7F054_4;   /* actor in create_placed_dungeon_actor */

extern void *allocate_list_node(s32, const void *);
extern void register_node(void *, const void *);
extern s32 generate_random_value();
extern void set_or_clear_actor_status_slot(void *, s32, s32);
extern void initialize_actor_sprite_and_animation(void *, void *, void *, s32);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern u8 D_8015EA30[];
extern u8 D_80161D0C[];
extern u8 D_80161D4C[];
extern M2C_UNK D_8015EE5C;

/* Creates a dungeon actor with the supplied placement and spawn flags. */
/* Creates Battnel with default frames at D_80161D0C, applies spawn flags, and attempts valid tile
 * placement. */
void *create_placed_dungeon_actor(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 rotation)
{
    s32 kind;
    void *work;
    S_80B7F054_0 *obj;
    S_80B7F054_2 *part_a;
    SpriteFrameState *part_b;
    S_80B7F054_4 *actor;
    s32 flags_or_roll;
    s32 pending_flags;
    s8 saved_x;
    s16 saved_rotation;
    s8 saved_y;
    void *saved_part_a;

    work = 0;
    saved_x = tile_x;
    saved_rotation = rotation;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj;
        work += 0x20;
        obj->unk_10 = D_8015EA30;
        ((S_80B7F054_1 *)work)->unk_13 = MONSTER_BATTNEL;
        register_node(obj, project_sprite_chain);

        part_a = obj->unk_08;
        part_a->unk_0A = saved_rotation;
        part_b = obj->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->frameTable = D_80161D0C;
        part_b->unk_24 = saved_x;
        do {

            if (kind == 1) {
                flags_or_roll = ((S_80B7F054_1 *)work)->unk_14 | 0x6000;
                pending_flags = ((S_80B7F054_1 *)work)->unk_1C | 0x6000;
                ((S_80B7F054_1 *)work)->unk_14 = flags_or_roll;
                ((S_80B7F054_1 *)work)->unk_1C = pending_flags;
            } else if (kind >= 2) {
                flags_or_roll = ((S_80B7F054_1 *)work)->unk_14 | 0x2000;
                pending_flags = ((S_80B7F054_1 *)work)->unk_1C | 0x2000;
                ((S_80B7F054_1 *)work)->unk_14 = flags_or_roll;
                ((S_80B7F054_1 *)work)->unk_1C = pending_flags;
            } else {
                saved_part_a = obj;
                if (((spawn_flags & ~3) << 16) == 0 && !(((S_80B7F054_1 *)work)->unk_14 & 0x200)) {
                    saved_part_a = part_a;
                    flags_or_roll = generate_random_value();
                    saved_part_a = obj;
                    if (!(flags_or_roll & 1)) {
                        break;
                    }
                    ((S_80B7F054_1 *)work)->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value(obj) & 0x3F) | 0x20);
                    part_b->frameTable = D_80161D4C;
                }
            }
            saved_part_a = obj;

        } while (0);
        initialize_actor_sprite_and_animation(saved_part_a, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8015EE5C;
        actor->unk_A4 = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
