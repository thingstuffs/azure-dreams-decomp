#include "dungeon/monster/noise/move_fade_and_accelerate_effect.h"

/* Spawn the overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select (or the random 0x20-mask variant), and run the two setup calls. */
void *func_80171190(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    T_80171190_Work *work;
    ProjectileObject *obj;
    SignedHeightView *part_a;
    T_80171190_S_80171190_2 *part_b;
    void *resource;
    T_80171190_Work *actor;
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
        work = (T_80171190_Work *)((u8 *)obj + 0x20);
        obj->unk_10 = D_80171358;
        work->byte13 = 0x17;
        register_node(obj, project_sprite_chain);

        resource = D_80174E88;
        part_a = obj->unk_08;
        part_a->unk_0A = saved_spawn;
        part_b = obj->unk_0C;
        kind = flags & 3;
        part_b->unk_25 = saved_variant;
        actor = work;
        part_b->unk_2C = resource;
        part_b->unk_24 = saved_kind_id;

        if (kind == 1) {
            left = work->flags14 | 0x6000;
            right = work->flags1c | 0x6000;
            work->flags14 = left;
            work->flags1c = right;
        } else if (kind >= 2) {
            left = work->flags14 | 0x2000;
            right = work->flags1c | 0x2000;
            work->flags14 = left;
            work->flags1c = right;
        } else {
            call_a1 = obj;
            if (((flags & ~3) << 16) == 0) {
                if (!(work->flags14 & 0x200)) {
                    call_a1 = part_a;
                    left = generate_random_value();
                    call_a1 = obj;
                    if (left & 1) {
                        set_or_clear_actor_status_slot(work, 1,
                                      (generate_random_value() & 0x3F) | 0x20);
                        part_b->unk_2C = D_80174EF0;
                    }
                }
            }
        }
        call_a1 = obj;
        initialize_actor_sprite_and_animation(call_a1, part_a, part_b, flags);
        actor->byte9a = 0xFF;
        actor->byte9c = -1;
        actor->ptr8c = &update_actor_behavior_and_direction;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
