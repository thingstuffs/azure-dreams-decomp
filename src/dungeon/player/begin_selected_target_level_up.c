
struct ObjectPosition;
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"
#include "engine/graphics.h"
#include "dungeon/player/object.h"
#include "dungeon/effect.h"

extern u8  return_magic_frames[];
extern s8  D_80080AA0;
extern s8  scene_music_hold;

extern s32 play_sound_if_enabled(s32 query_value);

/* Starts the selected target's action when ready and reports whether a target is active. */
s32 begin_selected_target_level_up(void *actor_state, void *action_arg, void *sprite, void *target) {
    if (!(dungeon_floor_flags & 0x100000) || g_dungeon_status.active_actor == 0) {
        return 0;
    }
    if (g_dungeon_status.active_actor == target && g_dungeon_status.activity_counts.parts.pending_action_count == 0 && !(g_dungeon_status.flags & 8)) {
        *(s8 *)((char *)actor_state + 0x9A) = 9;
        *(s8 *)((char *)actor_state + 0x9B) = 0;
        *(s32 *)((char *)actor_state + 0x8C) = 0;
        select_nearby_target_and_initialize_slot((char *)actor_state - 0x20, action_arg, 8, 0x300);
        if (!(*(s32 *)((char *)target + 0x1C) & 0x100000)) {
            *(u8 **)((char *)sprite + 0x2C) = return_magic_frames;
            set_sprite_animation_frame(sprite, return_magic_frames[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((char *)target + 0x2A) + 0x100)
                >> 9) & 7], 1, 1);
        }
        play_sound_if_enabled(0x201);
        if (!(system_update_flags & 2)) {
            D_80080AA0 = 1;
            scene_music_hold = 0;
        }
        *(s16 *)((char *)actor_state + 0x96) = 0x78;
        raise_entity_level(target, 1);
    }
    return 1;
}
