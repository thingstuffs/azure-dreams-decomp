#include "shared/object_node.h"
#include "dungeon/monster/dragon/spawn_effect_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/dragon/spawn_effect_object.h"

/* Creates a Dragon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_effect_object(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_8014C854_2 *part_a;
    SpriteFrameState *part_b;
    S_8014C854_1 *work;
    S_8014C854_4 *actor;
    s32 flags;
    s32 extra_flags;
    s8 saved_x;
    s16 saved_id;
    s8 saved_y;

    work = 0;
    saved_x = tile_x;
    saved_id = part_id;
    saved_y = tile_y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_8014CA28;
        work->unk_13 = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_id;
        part_b = obj->sprite;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->frameTable = D_8014FC7C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flags = work->unk_14 | 0x6000;
            extra_flags = work->unk_1C | 0x6000;
            work->unk_14 = flags;
            work->unk_1C = extra_flags;
        } else if (kind >= 2) {
            flags = work->unk_14 | 0x2000;
            extra_flags = work->unk_1C | 0x2000;
            work->unk_14 = flags;
            work->unk_1C = extra_flags;
        } else if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8014FCDC;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE54;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
