#include "modules/dungeon_resource16_slot0.h"

void *func_80170878(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c)
{
    void *result = 0;
    void *created;
    void *position;
    R16_80170878_S_80170878_3 *part_b;
    R16_80170878_S_80170878_4 *actor;
    s16 held_a;
    s32 held_c;
    s16 held_b;
    s16 flags_copy;
    void *call_a0;
    void *call_a1;
    s32 kind;

    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    created = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    flags_copy = spawn_flags;
    if (created != 0) {

        result = (u8 *)created + 0x20;
        ((R16_80170878_S_80170878_0 *)created)->unk_10 = update_entity_facing_and_ground;
        ((R16_80170878_S_80170878_1 *)result)->unk_13 = 0x10;
        func_8004491C(created, func_80045340);

        position = ((R16_80170878_S_80170878_0 *)created)->unk_08;
        ((R16_80170878_S_80170878_2 *)position)->unk_0A = held_c;
        part_b = ((R16_80170878_S_80170878_0 *)created)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = held_b;
        actor = result;
        part_b->unk_2C = ((u8 *)D_8017420C);
        part_b->unk_24 = held_a;

        if (kind == 1) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= 0x6000;
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            ((R16_80170878_S_80170878_1 *)result)->unk_14 |= 0x2000;
            ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x2000;
        } else {
            call_a0 = created;
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((R16_80170878_S_80170878_1 *)result)->unk_14 & 0x200)) {
                    call_a1 = position;
                    if (generate_random_value() & 1) {
                        set_or_clear_actor_status_slot(result, 1,
                            (generate_random_value() & 0x3F) | 0x20);
                        part_b->unk_2C = ((u8 *)D_8017425C);
                    }
                }
            }
        }

        initialize_actor_sprite_and_animation(created, position, part_b, (s16)flags_copy);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((u8 *)update_actor_state_and_dispatch_transition);
        ((R16_80170878_S_80170878_1 *)result)->unk_1C |= 0x40000;
        actor->unk_92 = -0x20;
        try_move_actor_to_valid_position(actor, position, part_b, result);
    }
    return result;
}
