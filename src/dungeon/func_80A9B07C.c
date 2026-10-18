#include "modules/dungeon_resource08_slot0.h"

void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    R08_8017087C_S_8017087C_2 *part_a;
    R08_8017087C_S_8017087C_3 *part_b;
    R08_8017087C_S_8017087C_1 *work;
    R08_8017087C_S_8017087C_4 *actor;
    s32 flags_or_roll;
    s32 secondary_flags;
    s8 saved_tile_x;
    s16 saved_part_id;
    s8 saved_tile_y;

    work = 0;
    saved_tile_x = tile_x;
    saved_part_id = part_id;
    saved_tile_y = tile_y;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((R08_8017087C_S_8017087C_0 *)obj)->unk_10 = ((u8 *)func_80170A50);
        work->unk_13 = 0x8;
        func_8004491C(obj, func_80045340);

        part_a = ((R08_8017087C_S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((R08_8017087C_S_8017087C_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_tile_y;
        actor = work;
        part_b->unk_2C = ((u8 *)D_80174C3C);
        part_b->unk_24 = saved_tile_x;

        if (kind == 1) {
            flags_or_roll = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = flags_or_roll;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            flags_or_roll = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = flags_or_roll;
            work->unk_1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = ((u8 *)D_80174C8C);
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((void *)update_actor_behavior_and_effect);
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
