#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "dungeon/monster/nyuel/spawn_factory_slot_c.h"
#include "shared/object_node.h"
#include "modules/dungeon_ovl_bcf094.h"
#include "shared/monster_ids.h"
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_ovl_bcf094.h"

/* Creates a Nyuel actor at the supplied tile and height, then initializes mode flags, status, and
 * callbacks. */
void *spawn_mode_configured_monster_slot_c(s16 flags, s16 tile_x, s32 variant, s32 spawn_height)
{
    void *result;
    ObjectNodeHeader *created;
    ObjectPosition *position;
    s32 part_ptr;
    s32 actor_ptr;
    s16 saved_flags;
    s32 saved_height;
    s32 saved_tile_y;
    s16 original_flags;

    saved_flags = flags;
    saved_height = spawn_height;
    saved_tile_y = variant;
    result = 0;
    created = allocate_list_node(0x112, &scene_object_list_anchor);
    original_flags = saved_flags;
    if (created != 0) {
        result = (u8 *)created + 0x20;
        ((S_80158894_0 *)result)->unk_13 = MONSTER_NYUEL;
        register_node(created, project_sprite_chain);

        position = created->position;
        variant = saved_flags & 3;
        position->z.w.i = saved_height;
        part_ptr = (s32)created->sprite;
        ((SpriteFrameState *)part_ptr)->tile_x = tile_x;
        ((SpriteFrameState *)part_ptr)->tile_y = saved_tile_y;
        actor_ptr = (s32)result;

        if (variant == 1) {
            ((S_80158894_0 *)result)->unk_8C = nyuel_slot_c_action_callback;
            ((S_80158894_0 *)result)->unk_14 |= (ACTOR_CLASS_ENABLED | ACTOR_PARTY_MEMBER);
            ((S_80158894_0 *)result)->unk_1C |= (ACTOR_PLAYER_SIDE | ACTOR_PARTY_MEMBER);
            ((SpriteFrameState *)part_ptr)->frameTable = nyuel_frame_set_6;
        } else if (variant >= 2) {
            ((S_80158894_0 *)result)->unk_8C = nyuel_slot_c_action_callback;
            ((S_80158894_0 *)result)->unk_14 |= ACTOR_CLASS_ENABLED;
            ((S_80158894_0 *)result)->unk_1C |= ACTOR_PLAYER_SIDE;
            ((SpriteFrameState *)part_ptr)->frameTable = nyuel_frame_set_6;
        } else {
            if (((saved_flags & ~3) << 16) == 0) {
                if (!(((S_80158894_0 *)result)->unk_14 & ACTOR_RESIST_SLEEP) && (generate_random_value() & 1)) {
                    set_or_clear_actor_status_slot(result, STATUS_SLEEP, (generate_random_value() & 0x3F) | 0x20);
                    ((SpriteFrameState *)part_ptr)->frameTable = D_8015CF00;
                }
                ((S_80158894_4 *)((void *)actor_ptr))->unk_8C = nyuel_slot_c_action_callback;
            ((SpriteFrameState *)part_ptr)->frameTable = nyuel_frame_set_6;
            } else {
                ((S_80158894_0 *)result)->unk_8C = nyuel_slot_c_action_callback;
            ((SpriteFrameState *)part_ptr)->frameTable = nyuel_frame_set_6;
            }
        }
        created->update_callback = func_80158A98;
        initialize_actor_sprite_and_animation(created, position, (void *)part_ptr, (s16)original_flags);
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9A = 0xFF;
        ((S_80158894_4 *)((void *)actor_ptr))->unk_9C = -1;
        try_move_actor_to_valid_position((void *)actor_ptr, position, (void *)part_ptr, result);
    }
    return result;
}
