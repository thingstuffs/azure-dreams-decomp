#include "shared/actor_status_ids.h"
#include "dungeon/monster/nyuel/spawn_factory_slot_f.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_bbd094.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
u8 *spawn_mode_configured_monster_slot_f(s16 flags, s16 tile_x, u16 tile_y, s16 spawn_height)
{
    u8 saved_tile_x = tile_x;
    s16 saved_height = spawn_height;
    u8 saved_tile_y = tile_y;
    u8 *result;
    ObjectNodeHeader *allocation;
    ObjectPosition *part_a;
    u8 *part_b;
    u8 *secondary;
    s16 saved_flags;

    saved_flags = flags;
    result = 0;
    allocation = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    if (allocation != 0) {
        result = ((u8 *)allocation) + 0x20;
        result[0x13] = 14;
        register_node(allocation, project_sprite_chain);

        part_a = allocation->position;
        part_a->z.w.i = saved_height;
        part_b = *(u8 * *)&allocation->sprite;
        part_b[36] = saved_tile_x;
        part_b[37] = saved_tile_y;
        secondary = result;

        if ((flags & 3) == 1) {
            *(void (**)(void))(result + 140) = func_8016AE9C;
            *(u32 *)(result + 20) |= 0x6000;
            *(u32 *)(result + 28) |= 0x6000;
            ((SpriteFrameState *)part_b)->frameTable = func_8016EED8;
        } else {
            if ((flags & 3) >= 2) {
                *(void (**)(void))(result + 140) = func_8016AE9C;
                *(u32 *)(result + 20) |= 0x2000;
                *(u32 *)(result + 28) |= 0x2000;
                ((SpriteFrameState *)part_b)->frameTable = func_8016EED8;
            } else {
                if ((s16)(flags & -4) == 0) {
                    if ((*(u32 *)(result + 20) & 0x200) == 0) {
                        if ((generate_random_value() & 1) != 0) {
                            set_or_clear_actor_status_slot(result, STATUS_SLEEP,
                                          (generate_random_value() & 0x3F) | 0x20);
                            ((SpriteFrameState *)part_b)->frameTable = func_8016EF00;
                        }
                    }
                    *(void (**)(void))(secondary + 140) = func_8016AE9C;
                    ((SpriteFrameState *)part_b)->frameTable = func_8016EED8;
                } else {
                    *(void (**)(void))(result + 140) = func_8016AE9C;
                    ((SpriteFrameState *)part_b)->frameTable = func_8016EED8;
                }
            }
        }
        allocation->update_callback = func_8016AA98;
        initialize_actor_sprite_and_animation(allocation, part_a, part_b, saved_flags);

        secondary[154] = 0xFF;
        ((signed char *)secondary)[156] = -1;
        try_move_actor_to_valid_position(secondary, part_a, part_b, result);
    }
    return result;
}
