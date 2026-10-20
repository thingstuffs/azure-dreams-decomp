#include "modules/dungeon_ovl_e1b054.h"


void *func_80158854(s16 value, s16 part_b_value_a, s16 part_b_value_b, s16 part_a_value)
{
    s32 kind;
    s32 left;
    s32 right;
    void *work;
    s16 saved_arg3;
    ProjectileObject *obj;
    register s8 saved_arg2;
    s8 saved_arg1;
    void *part_a;
    s16 final_arg0;
    S_80158854_3 *part_b;
    void *actor;

    work = 0;
    saved_arg1 = part_b_value_a;
    saved_arg3 = part_a_value;
    saved_arg2 = part_b_value_b;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    final_arg0 = value;
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80158854_0 *)work)->unk_13 = 0x1C;
        register_node(obj, project_sprite_chain);

        part_a = obj->unk_08;
        ((SignedHeightView *)part_a)->unk_0A = saved_arg3;
        part_b = obj->unk_0C;
        part_b->unk_24 = saved_arg1;
        part_b->unk_25 = saved_arg2;
        actor = work;
        kind = value & 3;

        if (kind == 1) {
            ((S_80158854_0 *)work)->unk_8C = func_80158E5C;
            left = ((S_80158854_0 *)work)->unk_14 | 0x6000;
            right = ((S_80158854_0 *)work)->unk_1C | 0x6000;
            ((S_80158854_0 *)work)->unk_14 = left;
            ((S_80158854_0 *)work)->unk_1C = right;
            part_b->unk_2C = D_8015C510;
        } else {
            if (kind >= 2) {
                ((S_80158854_0 *)work)->unk_8C = func_80158E5C;
                left = ((S_80158854_0 *)work)->unk_14 | 0x2000;
                right = ((S_80158854_0 *)work)->unk_1C | 0x2000;
                ((S_80158854_0 *)work)->unk_14 = left;
                ((S_80158854_0 *)work)->unk_1C = right;
                part_b->unk_2C = D_8015C510;
            } else {
                if (((value & ~3) << 16) == 0) {
                    if (!(((S_80158854_0 *)work)->unk_14 & 0x200)) {
                        if (generate_random_value() & 1) {
                            set_or_clear_actor_status_slot(work, 1,
                                          (generate_random_value() & 0x3F) | 0x20);
                            part_b->unk_2C = D_8015C538;
                        }
                    }
                    ;
                    ((S_80158854_4 *)actor)->unk_8C = func_80158E5C;
                part_b->unk_2C = D_8015C510;
                } else {
                    ((S_80158854_0 *)work)->unk_8C = func_80158E5C;
                part_b->unk_2C = D_8015C510;
                }
            }
        }
        obj->unk_10 = func_80158A58;
        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)final_arg0);
        ((S_80158854_4 *)actor)->unk_9A = 0xFF;
        ((S_80158854_4 *)actor)->unk_9C = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
