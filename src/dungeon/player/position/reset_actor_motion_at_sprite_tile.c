#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"
#include "dungeon/player/position.h"
#include "dungeon/player/object.h"
#include "engine/graphics.h"

extern u8 D_800DD120[];

/* Set the facing animation, reset actor state, and update the map entry. */
void reset_actor_motion_at_sprite_tile(void *actor_state, void *map_entry, SpriteFrameState *sprite, void *entity) {
    sprite->frameTable = D_800DD120;
    set_sprite_animation_frame(sprite, D_800DD120[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((s8 *)entity + 0x2A) + 0x100) >> 9) & 7], 0,
        1);
    *(u8 *)((s8 *)actor_state + 0x9A) = 8;
    *((s8 *)actor_state + 0x9B) = 0;
    *(s32 *)((s8 *)actor_state + 0x8C) = 0;
    clear_player_linked_action_flags();
    *(s32 *)((s8 *)entity + 0x1C) &= ~0x1638;
    *(s32 *)((s8 *)map_entry + 0x10) = 0;
    *(s32 *)((s8 *)map_entry + 0xC) = 0;
    set_record_integer_tile_center(map_entry, sprite->tile_x, sprite->tile_y);
    g_dungeon_status.activity_counts.parts.pending_action_count += 1;
}
