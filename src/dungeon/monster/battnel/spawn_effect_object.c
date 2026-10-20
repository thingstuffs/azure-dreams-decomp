#include "dungeon/monster/battnel/spawn_effect_object.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/battnel/spawn_effect_object.h"

void *spawn_effect_object(s16 flags, s16 value_24, s16 value_25, s16 value_0A)
{
    s32 kind;
    S_8014C854_1 *work;
    void *obj;
    S_8014C854_2 *part_a;
    SpriteFrameState *part_b;
    S_8014C854_4 *actor;
    s32 left;
    s32 right;
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;

    work = 0;
    saved_arg1 = value_24;
    saved_arg2 = value_25;
    saved_arg3 = value_0A;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = obj;
        work = (u8 *)work + 0x20;
        actor = work;
        ((S_8014C854_0 *)obj)->unk_10 = D_8014CA30;
        work->unk_13 = 0xD;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8014C854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_arg3;
        part_b = ((S_8014C854_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_arg2;
        part_b->frameTable = D_8014FD0C;
        part_b->unk_24 = saved_arg1;

        if (kind == 1) {
            left = work->unk_14 | 0x6000;
            right = work->unk_1C | 0x6000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else if (kind >= 2) {
            left = work->unk_14 | 0x2000;
            right = work->unk_1C | 0x2000;
            work->unk_14 = left;
            work->unk_1C = right;
        } else {
            if (((flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->frameTable = D_8014FD4C;
                }
            }
        }

        initialize_actor_sprite_and_animation(obj, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE5C;
        actor->unk_A4 = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
