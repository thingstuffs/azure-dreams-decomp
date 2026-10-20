#include "modules/dungeon_ovl_7f211800.h"


/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_8016A894(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    void *obj;
    S_8016A894_2 *part_a;
    S_8016A894_3 *part_b;
    S_8016A894_1 *work;
    S_8016A894_4 *actor;
    s32 left;
    s32 right;
    s8 saved_kind_id;
    s16 saved_spawn;
    s8 saved_variant;
    void *call_a1;

    work = 0;
    saved_kind_id = kind_id;
    saved_spawn = spawn_value;
    saved_variant = variant;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8016A894_0 *)obj)->unk_10 = func_8016AA68;
        work->unk_13 = 0x24;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8016A894_0 *)obj)->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = ((S_8016A894_0 *)obj)->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = D_8016EA7C;
        part_b->unk_24 = saved_kind_id;

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
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                call_a1 = part_a;
                left = generate_random_value();
                call_a1 = obj;
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016EAD4;
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8016AE94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
