#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern u8  D_800DD0F8[];
extern s8  D_80080AA0;
extern s8  D_80080A88;

extern void select_nearby_target_and_initialize_slot();
extern void set_sprite_animation_frame();
extern void play_sound_if_enabled();
extern void raise_entity_level();

/* Starts the selected target's action when ready and reports whether a target is active. */
s32 begin_selected_target_level_up(void *actor_state, s32 action_arg, void *sprite, void *target) {
    if (!(D_800E296C & 0x100000) || g_dungeon_status.unk_0C == 0) {
        return 0;
    }
    if (g_dungeon_status.unk_0C == target && g_dungeon_status.unk_0A == 0 && !(g_dungeon_status.flags & 8)) {
        *(s8 *)((char *)actor_state + 0x9A) = 9;
        *(s8 *)((char *)actor_state + 0x9B) = 0;
        *(s32 *)((char *)actor_state + 0x8C) = 0;
        select_nearby_target_and_initialize_slot((char *)actor_state - 0x20, action_arg, 8, 0x300);
        if (!(*(s32 *)((char *)target + 0x1C) & 0x100000)) {
            *(u8 **)((char *)sprite + 0x2C) = D_800DD0F8;
            set_sprite_animation_frame(sprite, D_800DD0F8[((g_game_work.view.viewAngle + *(s16 *)((char *)target + 0x2A) + 0x100)
                >> 9) & 7], 1, 1);
        }
        play_sound_if_enabled(0x201);
        if (!(D_80013714 & 2)) {
            D_80080AA0 = 1;
            D_80080A88 = 0;
        }
        *(s16 *)((char *)actor_state + 0x96) = 0x78;
        raise_entity_level(target, 1);
    }
    return 1;
}
