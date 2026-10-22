#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player/state.h"

extern void set_sprite_animation_frame(void *, u8, s32, s32);
extern u8 D_800DD000[];

/* Enters state 0x17, selects its directional animation, and resets state progress. */
void enter_directional_state_17(void *state, void *unused, void *animation, void *orientation) {
    u8 next_state = 0x17;

    if (*(u8 *)((s8 *)state + 0x9A) != next_state) {
        *(u8 **)((s8 *)animation + 0x2C) = D_800DD000;
        set_sprite_animation_frame(animation, D_800DD000[((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((s8 *)orientation + 0x2A) + 0x100)
            >> 9) & 7], 0, 1);
        g_dungeon_status.flags |= 0x100;
        *(u8 *)((s8 *)state + 0x9A) = next_state;
        *(s8 *)((s8 *)state + 0x9B) = 0;
        *(s32 *)((s8 *)state + 0x8C) = 0;
    }
}
