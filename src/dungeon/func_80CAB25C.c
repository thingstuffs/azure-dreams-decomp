#include "modules/dungeon_ovl_ccb000.h"
#include "shared/sprite_frame_state.h"

void *func_80158A5C(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    CL_CCB000_80170A5C_S_80170A5C_2 *part0;
    SpriteFrameState *part1;
    CL_CCB000_80170A5C_S_80170A5C_4 *result_copy;

    result = 0;
    object = allocate_list_node(0x112, ((s32 *)&D_80083498.next));
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        ((CL_CCB000_80170A5C_S_80170A5C_0 *)object)->unk_10 = func_80158C24;
        ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_13 = 20;
        register_node(object, project_sprite_chain);

        {
            void *handler;

            part0 = ((CL_CCB000_80170A5C_S_80170A5C_0 *)object)->unk_08;
            handler = D_8015D2B4;
            part0->unk_0A = attr_c;
            part1 = ((CL_CCB000_80170A5C_S_80170A5C_0 *)object)->unk_0C;
            kind = spawn_flags & 3;
            part1->unk_25 = attr_b;
            result_copy = result;
            part1->frameTable = handler;
        }
        part1->unk_24 = attr_a;

        if (kind == 1) {
            flags0 = ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (((spawn_flags & -4) << 16) == 0 &&
                   (((CL_CCB000_80170A5C_S_80170A5C_1 *)result)->unk_14 & 0x200) == 0 &&
                   (generate_random_value() & 1) != 0) {
            set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
            part1->frameTable = D_8015D2FC;
        }

        initialize_actor_sprite_and_animation(object, part0, part1, spawn_flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = func_8015902C;
        try_move_actor_to_valid_position(result_copy, part0, part1, result);
    }
    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
