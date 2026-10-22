#include "dungeon/monster/naplass/allocate_actor_effect_object.h"

/* Allocates an object, initializes its parts and actor state, and returns its work area. */
/* Creates Naplass with default frames at D_80174194, applies spawn flags, and attempts valid tile
 * placement. */
void *allocate_actor_effect_object(s16 kind_flags, s16 x, s16 y, s16 part_value)
{
    s32 kind;
    ProjectileObject *obj;
    SignedHeightView *part_a;
    T_80170870_S_80170870_3 *part_b;
    T_80170870_S_80170870_1 *work;
    T_80170870_S_80170870_4 *actor;
    register s32 primary_flags;
    register s32 secondary_flags;
    s8 saved_x;
    s16 saved_value;
    s8 saved_y;

    work = 0;
    saved_x = x;
    saved_value = part_value;
    saved_y = y;
    obj = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        obj->unk_10 = D_80170A3C;
        work->unk_13 = 0x25;
        register_node(obj, project_sprite_chain);

        part_a = obj->unk_08;
        part_a->unk_0A = saved_value;
        part_b = obj->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_80174194;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            primary_flags = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = primary_flags;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            primary_flags = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = primary_flags;
            work->unk_1C = secondary_flags;
        } else {
            if (((kind_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                work->unk_1C |= 0x200;
                set_or_clear_actor_status_slot(work, 1,
                              (generate_random_value() & 0x3F) | 0x20);
                part_b->unk_2C = D_801741DC;
            }
        }
        initialize_actor_sprite_and_animation(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_80170E68;
        part_b->unk_14 |= 0xC;
        try_move_actor_to_valid_position(actor, part_a, part_b, work);
    }
    return work;
}
