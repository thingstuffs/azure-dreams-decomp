#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/player.h"
#include "engine/graphics.h"
#ifndef NULL
#define NULL 0
#endif

extern u8 D_800DCFF0[8];

/* Starts action 0x24, clears linked action flags, doubles movement time, and selects its animation. */
void begin_wake_nearby_monsters(ActorRecord *state_ptr, void *value, u8 *target_ptr, u8 *angle_ptr) {
    u16 flags;
    s32 index;
    u8 *table;

    flags = state_ptr->unk_A0.parts.high;
    state_ptr->action_id.s = 0x24;
    state_ptr->action_phase.s = 0;
    state_ptr->unk_8C.address = NULL;
    state_ptr->unk_A0.parts.high = flags & 0xFEFF;
    clear_player_linked_action_flags();

    g_dungeon_status.movement_frames_left = g_dungeon_status.movement_frames_left * 2;
    table = &D_800DCFF0[0];
    *(u8 **)(target_ptr + 0x2C) = table;

    index = ((g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)(angle_ptr + 0x2A) + 0x100) >> 9) & 7;
    set_sprite_animation_frame(target_ptr, table[index], 0, 1);
}
