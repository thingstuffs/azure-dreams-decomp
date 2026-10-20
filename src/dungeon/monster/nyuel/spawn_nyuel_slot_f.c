#include "modules/dungeon_ovl_bbd094.h"


u8 *func_8016A894(s16 flags, s16 kind_id, u16 variant, s16 spawn_value)
{
    u8 byte_kind_id = kind_id;
    s16 half_spawn = spawn_value;
    u8 byte_variant = variant;
    u8 *result;
    u8 *allocation;
    u8 *part_a;
    u8 *part_b;
    u8 *secondary;
    s16 saved_flags;

    saved_flags = flags;
    result = 0;
    allocation = allocate_list_node(0x112, ((u8 *)(&D_80083498)));
    if (allocation != 0) {
        result = allocation + 0x20;
        result[0x13] = 14;
        register_node(allocation, project_sprite_chain);

        part_a = *(u8 **)(allocation + 8);
        *(s16 *)(part_a + 10) = half_spawn;
        part_b = *(u8 **)(allocation + 12);
        part_b[36] = byte_kind_id;
        part_b[37] = byte_variant;
        secondary = result;

        if ((flags & 3) == 1) {
            *(void (**)(void))(result + 140) = func_8016AE9C;
            *(u32 *)(result + 20) |= 0x6000;
            *(u32 *)(result + 28) |= 0x6000;
            *(void (**)(void))(part_b + 44) = func_8016EED8;
        } else {
            if ((flags & 3) >= 2) {
                *(void (**)(void))(result + 140) = func_8016AE9C;
                *(u32 *)(result + 20) |= 0x2000;
                *(u32 *)(result + 28) |= 0x2000;
                *(void (**)(void))(part_b + 44) = func_8016EED8;
            } else {
                if ((s16)(flags & -4) == 0) {
                    if ((*(u32 *)(result + 20) & 0x200) == 0) {
                        if ((generate_random_value() & 1) != 0) {
                            set_or_clear_actor_status_slot(result, 1,
                                          (generate_random_value() & 0x3F) | 0x20);
                            *(void (**)(void))(part_b + 44) = func_8016EF00;
                        }
                    }
                    *(void (**)(void))(secondary + 140) = func_8016AE9C;
                    *(void (**)(void))(part_b + 44) = func_8016EED8;
                } else {
                    *(void (**)(void))(result + 140) = func_8016AE9C;
                    *(void (**)(void))(part_b + 44) = func_8016EED8;
                }
            }
        }
        *(void (**)(void))(allocation + 16) = func_8016AA98;
        initialize_actor_sprite_and_animation(allocation, part_a, part_b, saved_flags);

        secondary[154] = 0xFF;
        ((signed char *)secondary)[156] = -1;
        try_move_actor_to_valid_position(secondary, part_a, part_b, result);
    }
    return result;
}
