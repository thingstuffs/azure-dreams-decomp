#include "modules/dungeon_ovl_7f1ed800.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_80158894(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *obj;
    S_80158894_2 *part_a;
    S_80158894_3 *part_b;
    S_80158894_1 *work;
    S_80158894_4 *actor;
    s32 left;
    s32 right;
    s8 held_a;
    s16 held_c;
    s8 held_b;

    work = 0;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_80158894_0 *)obj)->unk_10 = func_80158A68;
        work->unk_13 = 0x24;
        func_8004491C(obj, func_80045340);

        part_a = ((S_80158894_0 *)obj)->unk_08;
        part_a->unk_0A = held_c;
        part_b = ((S_80158894_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = work;
        part_b->unk_2C = D_8015CA7C;
        part_b->unk_24 = held_a;

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
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                left = generate_random_value();
                if (left & 1) {
                    work->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8015CAD4;
                }
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_80158E94;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
