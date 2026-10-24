#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/object_node.h"
#include "dungeon/monster/dragon/create_tracked_effect_object.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/dragon/create_tracked_effect_object.h"

/* Creates a Dragon actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *create_tracked_effect_object(s16 flags, s16 x, s16 y, s16 part_id)
{
    s32 kind;
    ObjectNodeHeader *obj;
    S_8015E854_2 *part_a;
    SpriteFrameState *part_b;
    S_8015E854_1 *work;
    S_8015E854_4 *actor;
    u32 flag_bits;
    s32 secondary_flags;
    s8 saved_x;
    s16 saved_part_id;
    s8 saved_y;
    void *init_obj;
    void *query_part;

    work = 0;
    saved_x = x;
    saved_part_id = part_id;
    saved_y = y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->update_callback = D_8015EA28;
        work->unk_13 = MONSTER_DRAGON;
        register_node(obj, project_sprite_chain);

        part_a = obj->position;
        part_a->unk_0A = saved_part_id;
        part_b = obj->sprite;
        kind = flags & 3;
        part_b->tile_y = saved_y;
        actor = work;
        part_b->frameTable = D_80161C7C;
        part_b->tile_x = saved_x;

        if (kind == 1) {
            flag_bits = work->unk_14 | (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            secondary_flags = work->unk_1C | (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            work->unk_14 = flag_bits;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            flag_bits = work->unk_14 | ACTOR_CLASS_ENABLED;
            secondary_flags = work->unk_1C | ACTOR_PLAYER_SIDE;
            work->unk_14 = flag_bits;
            work->unk_1C = secondary_flags;
        } else {
            init_obj = obj;
            if (((flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & ACTOR_RESIST_SLEEP)) {
                    query_part = part_a;
                    init_obj = (void *)generate_random_value();
                    flag_bits = (s32)init_obj;
                    init_obj = obj;
                    if (flag_bits & 1) {
                        work->unk_1C |= ACTOR_ASLEEP;
                        set_or_clear_actor_status_slot(work, STATUS_SLEEP,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->frameTable = D_80161CDC;
                    }
                }
            }
        }
        init_obj = obj;
        initialize_actor_sprite_and_animation(init_obj, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &dragon_slot_d_action_callback;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
