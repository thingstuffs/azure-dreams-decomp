#include "modules/dungeon_resource10_slot0.h"

void *func_80170F3C(s16 flags, s16 kind_id, s16 variant, s32 spawn_value)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    R10_80170F3C_S_80170F3C_2 *part0;
    R10_80170F3C_S_80170F3C_3 *part1;
    R10_80170F3C_S_80170F3C_4 *result_copy;

    result = 0;
    object = func_8003FD64(0x112, ((s32 *)&D_80083498.next));
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        ((R10_80170F3C_S_80170F3C_0 *)object)->unk_10 = ((u8 *)update_actor_callbacks_animation_and_ground);
        ((R10_80170F3C_S_80170F3C_1 *)result)->unk_13 = 10;
        func_8004491C(object, func_80045340);

        {
            void *handler;

            part0 = ((R10_80170F3C_S_80170F3C_0 *)object)->unk_08;
            handler = ((u8 *)D_80175988);
            part0->unk_0A = spawn_value;
            part1 = ((R10_80170F3C_S_80170F3C_0 *)object)->unk_0C;
            kind = flags & 3;
            part1->unk_25 = variant;
            result_copy = result;
            part1->unk_2C = handler;
        }
        part1->unk_24 = kind_id;

        if (kind == 1) {
            flags0 = ((R10_80170F3C_S_80170F3C_1 *)result)->unk_14;
            flags1 = ((R10_80170F3C_S_80170F3C_1 *)result)->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((R10_80170F3C_S_80170F3C_1 *)result)->unk_14 = flags0;
            ((R10_80170F3C_S_80170F3C_1 *)result)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((R10_80170F3C_S_80170F3C_1 *)result)->unk_14;
            flags1 = ((R10_80170F3C_S_80170F3C_1 *)result)->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((R10_80170F3C_S_80170F3C_1 *)result)->unk_14 = flags0;
            ((R10_80170F3C_S_80170F3C_1 *)result)->unk_1C = flags1;
        } else if (((flags & -4) << 16) == 0 &&
                   (((R10_80170F3C_S_80170F3C_1 *)result)->unk_14 & 0x200) == 0 &&
                   (generate_random_value() & 1) != 0) {
            set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
            part1->unk_2C = ((u8 *)D_801759E8);
        }

        initialize_actor_sprite_and_animation(object, part0, part1,(s16)(flags));
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = ((void *)func_801717F4);
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }

    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   kind_id and variant arrive as s16: their narrowing copies survive cse, combine folds the a1/a2 temps
   into them, so sched1 schedules the parameter copies and the entry order is retail's. */
