#include "dungeon/monster/dragon/create_tracked_effect_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/dragon/create_tracked_effect_object.h"

void *create_tracked_effect_object(s16 flags, s16 x, s16 y, s16 part_id)
{
    s32 kind;
    void *obj;
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
        ((S_8015E854_0 *)obj)->unk_10 = D_8015EA28;
        work->unk_13 = 0x3;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8015E854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((S_8015E854_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->frameTable = D_80161C7C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flag_bits = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = flag_bits;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            flag_bits = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = flag_bits;
            work->unk_1C = secondary_flags;
        } else {
            init_obj = obj;
            if (((flags & ~3) << 16) == 0) {
                if (!(work->unk_14 & 0x200)) {
                    query_part = part_a;
                    init_obj = (void *)generate_random_value();
                    flag_bits = (s32)init_obj;
                    init_obj = obj;
                    if (flag_bits & 1) {
                        work->unk_1C |= 0x200;
                        set_or_clear_actor_status_slot(work, 1,
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
        actor->unk_8C = &D_8015EE54;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
