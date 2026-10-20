#include "dungeon/monster/volcano/spawn_effect_object.h"
#include "dungeon/monster/volcano/spawn_effect_object.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *spawn_effect_object(s32 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    u8 *work = 0;
    long part_b;
    long work_copy;
    u8 *object;
    u8 *part_a;
    s16 flags_s16;
    s32 alloc_kind;
    ObjectNodeHeader *alloc_data;
    u32 flags0;
    u32 flags1;
    s32 random;

    alloc_kind = 0x112;
    alloc_data = &D_80083498;
    object = allocate_list_node(alloc_kind, alloc_data);
    flags_s16 = spawn_flags;
    if (object != 0) {
        work = object + 0x20;
        *(u8 *)(work + 0x13) = 0x1C;
        register_node(object, project_sprite_chain);

        part_a = *(u8 **)(object + 8);
        *(s16 *)(part_a + 0xA) = attr_c;
        part_b = (long)*(u8 **)(object + 0xC);
        *(u8 *)((u8 *)part_b + 0x24) = attr_a;
        *(u8 *)((u8 *)part_b + 0x25) = attr_b;
        work_copy = (long)work;

        if ((spawn_flags & 3) == 1) {
            *(Callback *)(work + 0x8C) = func_8014CE5C;
            *(u32 *)(work + 0x14) |= 0x6000;
            *(u32 *)(work + 0x1C) |= 0x6000;
            *(u8 **)((u8 *)part_b + 0x2C) = D_80150510;
        } else if ((spawn_flags & 3) >= 2) {
            *(Callback *)(work + 0x8C) = func_8014CE5C;
            flags0 = *(u32 *)(work + 0x14) | 0x2000;
            flags1 = *(u32 *)(work + 0x1C) | 0x2000;
            *(u32 *)(work + 0x14) = flags0;
            *(u32 *)(work + 0x1C) = flags1;
            *(u8 **)((u8 *)part_b + 0x2C) = D_80150510;
        } else {
            spawn_flags = (s16)(spawn_flags & -4);
            if (spawn_flags == 0) {
                if ((*(u32 *)(work + 0x14) & 0x200) == 0) {
                    if ((generate_random_value() & 1) != 0) {
                        random = generate_random_value();
                        set_or_clear_actor_status_slot(work, 1, (random & 0x3F) | 0x20);
                        *(u8 **)((u8 *)part_b + 0x2C) = D_80150538;
                    }
                }
                *(Callback *)((u8 *)work_copy + 0x8C) = func_8014CE5C;
                *(u8 **)((u8 *)part_b + 0x2C) = D_80150510;
            } else {
                *(Callback *)(work + 0x8C) = func_8014CE5C;
                *(u8 **)((u8 *)part_b + 0x2C) = D_80150510;
            }
        }

        *(Callback *)(object + 0x10) = func_8014CA58;
        initialize_actor_sprite_and_animation(object, part_a, (u8 *)part_b, (s16)flags_s16);

        *(u8 *)((u8 *)work_copy + 0x9A) = 0xFF;
        *(s8 *)((u8 *)work_copy + 0x9C) = -1;
        try_move_actor_to_valid_position((u8 *)work_copy, part_a, (u8 *)part_b, work);
    }
    return work;
}
