#include "dungeon/monster/volcano/create_tracked_effect_object.h"


/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *create_tracked_effect_object(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 left;
    s32 right;
    void *work;
    s16 saved_spawn;
    void *obj;
    register s8 saved_variant;
    s8 saved_kind_id;
    void *part_a;
    S_8015E854_3 *part_b;
    void *actor;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E854_0 *)work)->unk_13 = 0x1C;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8015E854_1 *)obj)->unk_08;
        ((S_8015E854_2 *)part_a)->unk_0A = saved_spawn;
        part_b = ((S_8015E854_1 *)obj)->unk_0C;
        part_b->unk_24 = saved_kind_id;
        part_b->unk_25 = saved_variant;
        actor = work;
        kind = flags & 3;

        if (kind == 1) {
            ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
            left = ((S_8015E854_0 *)work)->unk_14 | 0x6000;
            right = ((S_8015E854_0 *)work)->unk_1C | 0x6000;
            ((S_8015E854_0 *)work)->unk_14 = left;
            ((S_8015E854_0 *)work)->unk_1C = right;
            part_b->unk_2C = D_80162510;
        } else {
            if (kind >= 2) {
                ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
                left = ((S_8015E854_0 *)work)->unk_14 | 0x2000;
                right = ((S_8015E854_0 *)work)->unk_1C | 0x2000;
                ((S_8015E854_0 *)work)->unk_14 = left;
                ((S_8015E854_0 *)work)->unk_1C = right;
                part_b->unk_2C = D_80162510;
            } else {
                if (((flags & ~3) << 16) == 0) {
                    if (!(((S_8015E854_0 *)work)->unk_14 & 0x200)) {
                        if (generate_random_value() & 1) {
                            set_or_clear_actor_status_slot(work, 1,
                                          (generate_random_value() & 0x3F) | 0x20);
                            part_b->unk_2C = D_80162538;
                        }
                    }
                    ((S_8015E854_4 *)actor)->unk_8C = func_8015EE5C;
                    part_b->unk_2C = D_80162510;
                } else {
                    ((S_8015E854_0 *)work)->unk_8C = func_8015EE5C;
                    part_b->unk_2C = D_80162510;
                }
            }
        }
        ((S_8015E854_1 *)obj)->unk_10 = func_8015EA58;
        initialize_actor_sprite_and_animation(obj, part_a, part_b, (s16)flags);
        ((S_8015E854_4 *)actor)->unk_9A = 0xFF;
        ((S_8015E854_4 *)actor)->unk_9C = -1;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
