#include "modules/dungeon_ovl_a01054.h"

void *func_80158854(s16 mode_flags, s16 attribute_24, s16 attribute_25, s16 attribute_0a)
{
    s32 kind;
    void *obj;
    S_80158854_2 *part_a;
    S_80158854_3 *part_b;
    S_80158854_1 *work;
    S_80158854_4 *actor;
    s32 flags_or_result;
    s32 secondary_flags;
    s8 saved_attribute_24;
    s16 saved_attribute_0a;
    s8 saved_attribute_25;

    work = 0;
    saved_attribute_24 = attribute_24;
    saved_attribute_0a = attribute_0a;
    saved_attribute_25 = attribute_25;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80158854_0 *)obj)->unk_10 = D_80158A28;
        work->unk_13 = 0x3;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80158854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_attribute_0a;
        part_b = ((S_80158854_0 *)obj)->unk_0C;
        kind = mode_flags & 3;
        part_b->unk_25 = saved_attribute_25;
        actor = work;
        part_b->unk_2C = D_8015BC7C;
        part_b->unk_24 = saved_attribute_24;

        if (kind == 1) {
            flags_or_result = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = flags_or_result;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            flags_or_result = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = flags_or_result;
            work->unk_1C = secondary_flags;
        } else if (((mode_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1, (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8015BCDC;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, mode_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80158E54;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
