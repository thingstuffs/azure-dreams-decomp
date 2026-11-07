#include "shared/actor_status_flags.h"
#include "slus.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/actor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor/animation.h"
#include "dungeon/level.h"
#include "engine/entity.h"
#include "dungeon/player.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/object.h"
#include "engine/util.h"






/* cfail-repair: tf7-phase1-cache-v3 */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */
 /* extern */
extern s32 sprite_resource_pointer_slots[];
extern u8 actor_default_frames[];

/* Applies an action to the object's flags and tile state, then updates the object. */
void apply_entity_action_flags(ActorRecord *object, s32 action) {
    s32 clear_mask;
    s32 enable_clear_mask;
    s32 set_mask;
    s32 disable_clear_mask;
    s32 action_index;
    s32 *reset_slot;
    s32 updated_flags;
    s32 reset_index;
    TileObject *update_state;
    u8 tile_x;
    u8 tile_y;
    SpriteFrameState *target_sprite;

    action_index = (s16) (action - 1);
    switch (action_index) {
    case STATUS_SLEEP - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_ASLEEP);
        break;
    case STATUS_CONFUSION - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_CONFUSED);
        break;
    case STATUS_BLIND - 1:
        object->flags1C = (s32) ((object->flags1C & ACTOR_PLAYER_AWARE_CLEAR_MASK) | 0x10);
        break;
    case STATUS_PARALYSIS - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_PARALYZED);
        break;
    case STATUS_POISON - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_POISONED);
        break;
    case STATUS_MAGIC_BIND - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_MAGIC_BOUND);
        break;
    case STATUS_CURSE - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_CURSED);
        break;
    case STATUS_ANGER - 1:
        object->flags1C = (s32) (object->flags1C | ACTOR_ANGRY);
        break;
    case STATUS_NO_TILE_OCCUPANCY - 1:
        target_sprite = NODE_HEADER(object)->sprite;
        tile_x = target_sprite->tile_x;
        tile_y = target_sprite->tile_y;
        clear_mask = 0x3000;
        if (object->flags1C & ACTOR_PLAYER_SIDE) {
            clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, clear_mask);
        break;
    case STATUS_PLAYER_SIDE - 1:
        target_sprite = NODE_HEADER(object)->sprite;
        tile_x = target_sprite->tile_x;
        tile_y = target_sprite->tile_y;
        enable_clear_mask = 0x3000;
        if (object->flags1C & ACTOR_PLAYER_SIDE) {
            enable_clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, enable_clear_mask);
        updated_flags = object->flags1C | ACTOR_PLAYER_SIDE;
        object->flags1C = updated_flags;
        tile_x = target_sprite->tile_x;
        tile_y = target_sprite->tile_y;
        set_mask = 0x3000;
        if (updated_flags & ACTOR_PLAYER_SIDE) {
            set_mask = 0x300;
        }
        cycle_map_cell_flags(tile_x, tile_y, set_mask);
        break;
    case STATUS_BRAINWASH - 1:
        target_sprite = NODE_HEADER(object)->sprite;
        tile_x = target_sprite->tile_x;
        tile_y = target_sprite->tile_y;
        disable_clear_mask = 0x3000;
        if (object->flags1C & ACTOR_PLAYER_SIDE) {
            disable_clear_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, disable_clear_mask);
        object->flags1C = (s32) (object->flags1C & ~ACTOR_PLAYER_SIDE);
        tile_x = target_sprite->tile_x;
        tile_y = target_sprite->tile_y;
        set_mask = 0x3000;
        cycle_map_cell_flags(tile_x, tile_y, set_mask);
        break;
    case STATUS_FROG - 1:
        func_8003E188(0x2E, 0);
        if (object->flags14 & 0x20000000) {
            begin_actor_flagged_action((Rec_func_800A9E70_arg0 *)object, NODE_HEADER(object)->position, NODE_HEADER(object)->sprite,
                (EntityRec *)object);
            return;
        }
        reset_actor_animation_state(object);
        if (object->species != 0) {
            break;
        }
        restore_player_control_callback(object, object);
        update_state = &reference_tile_object;
        update_state->frame_table = actor_default_frames;
        select_record_entry_and_value(update_state, *(void **)(actor_default_frames + ((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (object->facing) + 0x100) >> 7) & 0x1C))), 0);
        reset_index = 3;
        reset_slot = sprite_resource_pointer_slots;
        reset_slot += 3;
        do {
            *reset_slot = 0;
            reset_index -= 1;
            reset_slot -= 1;
        } while (reset_index >= 0);
    }
    apply_entity_effects(object);
    return;
}
