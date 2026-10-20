#include "modules/dungeon_ovl_7f217800.h"
#include "modules/dungeon_ovl_7f217800.h"

/* Spawn this overlay's 0x112 object: fill its two sub-parts from kind_id/variant/spawn_value, apply the 0x6000 or 0x2000 flag pair the low two bits of flags select, then finish through the mode branch that either zeroes or arms the actor's 0xA6 state. */
void *func_80158854(s16 flags, s16 kind_id, s16 variant, s16 spawn_value)
{
    s32 kind;
    s32 mode;
    void *object_base;
    S_80158854_3 *part1;
    S_80158854_2 *part0;
    void *actor;
    void *object;
    S_80158854_1 *result;

    result = 0;
    mode = 1;
    object = allocate_list_node(274, ((u8 *)(&D_80083498)));
    if (object != 0) {
        result = (u8 *)object + 0x20;
        ((S_80158854_0 *)object)->unk_10 = func_80158A8C;
        result->unk_13 = 0x23;
        register_node(object, project_sprite_chain);
        part0 = ((S_80158854_0 *)object)->unk_08;
        part0->unk_0A = spawn_value;
        part1 = ((S_80158854_0 *)object)->unk_0C;
        part1->unk_25 = variant;
        actor = result;
        part1->unk_2C = D_8015BD30;
        kind = flags & 3;
        part1->unk_24 = kind_id;
        if (kind == 1) {
            result->unk_14 |= 0x6000;
            result->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            result->unk_14 |= 0x2000;
            result->unk_1C |= 0x2000;
        } else if (((flags & ~3) << 16) == 0) {
            if (!(result->unk_14 & 0x200)) {
                if (generate_random_value() & 1) {
                    result->unk_1C |= 0x200;
                    set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                    part1->unk_2C = D_8015BD78;
                }
            }
            mode = generate_random_value() & 3;
        }
        initialize_actor_sprite_and_animation(object, part0, part1, flags);
        ((S_80158854_4 *)actor)->unk_9A = 0xFF;
        ((S_80158854_4 *)actor)->unk_9C = -1;
        ((S_80158854_4 *)actor)->unk_8C = func_80158F74;
        ((S_80158854_4 *)actor)->unk_A4 = -1;
        if (mode != 0) {
            ((S_80158854_4 *)actor)->unk_A6 = 0;
        } else {
            object_base = (u8 *)actor - 0x20;
            ((S_80158854_4 *)actor)->unk_A6 = 1;
            part1->unk_10 = 0x60;
            part1->unk_14 |= 0xC;
            part1->unk_12 -= 0x80;
            unlink_node(object_base);
            retire_tracked_effect_by_id(object_base);
        }
        try_move_actor_to_valid_position(actor, part0, part1, result);
    }

    return result;
}
