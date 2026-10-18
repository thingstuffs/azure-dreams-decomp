#include "modules/dungeon_ovl_bcf094.h"

void *func_80158894(s16 flags, s16 kind_id, s32 variant, s32 spawn_value)
{
    void *result;
    void *created;
    void *position;
    s32 part_ptr;
    s32 actor_ptr;
    s16 saved_flags;
    s32 held_value;
    s32 held_variant;
    s16 original_flags;

    saved_flags = flags;
    held_value = spawn_value;
    held_variant = variant;
    result = 0;
    created = func_8003FD64(0x112, &D_80083498);
    original_flags = saved_flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        ((S_80158894_0 *)result)->unk_13 = 0xE;
        func_8004491C(created, func_80045340);

        position = ((S_80158894_1 *)created)->unk_08;
        variant = saved_flags & 3;
        ((S_80158894_2 *)position)->unk_0A = held_value;
        part_ptr = (s32)((S_80158894_1 *)created)->unk_0C;
        ((S_80158894_3 *)((void *)part_ptr))->unk_24 = kind_id;
        ((S_80158894_3 *)((void *)part_ptr))->unk_25 = held_variant;
        actor_ptr = (s32)result;

        if (variant == 1) {
            ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            ((S_80158894_0 *)result)->unk_14 |= 0x6000;
            ((S_80158894_0 *)result)->unk_1C |= 0x6000;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        } else if (variant >= 2) {
            ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            ((S_80158894_0 *)result)->unk_14 |= 0x2000;
            ((S_80158894_0 *)result)->unk_1C |= 0x2000;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
        } else {
            if (((saved_flags & ~3) << 16) == 0) {
                if (!(((S_80158894_0 *)result)->unk_14 & 0x200) && (generate_random_value() & 1)) {
                    set_or_clear_actor_status_slot(result, 1, (generate_random_value() & 0x3F) | 0x20);
                    ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CF00;
                }
                ((S_80158894_4 *)((void *)actor_ptr))->unk_8C = D_80158E9C;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
            } else {
                ((S_80158894_0 *)result)->unk_8C = D_80158E9C;
            ((S_80158894_3 *)((void *)part_ptr))->unk_2C = D_8015CED8;
            }
        }
        ((S_80158894_1 *)created)->unk_10 = func_80158A98;
        initialize_actor_sprite_and_animation(created, position, (void *)part_ptr, (s16)original_flags);
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9A = 0xFF;
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9C = -1;
        try_move_actor_to_valid_position((void *)actor_ptr, position, (void *)part_ptr, result);
    }
    return result;
}
