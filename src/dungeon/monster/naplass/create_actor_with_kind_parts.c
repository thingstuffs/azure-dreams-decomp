#include "dungeon/monster/naplass/create_actor_with_kind_parts.h"
#include "dungeon/monster/naplass/create_actor_with_kind_parts.h"

/* Creates an actor and initializes its parts and flags for the requested kind. */
void *create_actor_with_kind_parts(s16 kind_flags, s16 grid_x, s16 grid_y, s16 part_value)
{
    s32 kind;
    S_8014C870_1 *work;
    void *obj;
    S_8014C870_2 *part_a;
    S_8014C870_3 *part_b;
    S_8014C870_4 *actor;
    void *init_obj;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;
    s32 flags_14;
    s32 flags_1c;

    work = 0;
    saved_x = grid_x;
    saved_value = part_value;
    saved_y = grid_y;
    obj = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (void *)((Work *)((u8 *)obj + 0x20));
        ((S_8014C870_0 *)obj)->unk_10 = func_8014CA3C;
        work->unk_13 = 0x25;
        register_node(obj, project_sprite_chain);

        part_a = ((S_8014C870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value;
        part_b = ((S_8014C870_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_80150194;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flags_14 = ((Work *)work)->flags14 | 0x6000;
            flags_1c = ((Work *)work)->flags1c | 0x6000;
            ((Work *)work)->flags14 = flags_14;
            ((Work *)work)->flags1c = flags_1c;
        } else if (kind >= 2) {
            flags_14 = ((Work *)work)->flags14 | 0x2000;
            flags_1c = ((Work *)work)->flags1c | 0x2000;
            ((Work *)work)->flags14 = flags_14;
            ((Work *)work)->flags1c = flags_1c;
        } else {
            init_obj = obj;
            if (((kind_flags & ~3) << 16) == 0) {
                if (!(((Work *)work)->flags14 & 0x200)) {
                    ((Work *)work)->flags1c |= 0x200;
                    set_or_clear_actor_status_slot(work, 1,
                                  (generate_random_value() & 0x3F) | 0x20);
                    part_b->unk_2C = D_801501DC;
                }
            }
        }
        init_obj = obj;
        initialize_actor_sprite_and_animation(init_obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &dispatch_dungeon_actor_behavior_and_facing;
        part_b->unk_14 |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
