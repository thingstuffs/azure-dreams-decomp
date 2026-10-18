#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void func_80047784();
extern s32 try_claim_dungeon_action_slot();
extern void advance_status_timers();
extern void apply_camera_offset_and_select_target();
extern u8 D_8014A000[200000];
#define D_801764A0_OFF 0x2C4A0

/* Update action state and select a direction-specific sprite when the actor is ready. */
void update_action_state_direction_specific(void *action_state, s32 action_param, void *sprite, void *actor) {
    u8 *frame_table;
    s32 direction;

    *((u8 *)actor + 0x71) = (u8)(*((u8 *)actor + 0x71) & 0x7F);
    if (!(*(u16 *)((u8 *)((u16 *)(&g_dungeon_status)) + 2) & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        {
            void *actor_base = (u8 *)actor - 0x20;
            apply_camera_offset_and_select_target(actor_base, action_param, 8, 0x300);
        }
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            *((s8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *((s8 *)action_state + 0x9B) = 0;
            frame_table = &D_8014A000[D_801764A0_OFF];
            *(void **)((u8 *)sprite + 0x2C) = frame_table;
            direction = ((g_game_work.view.viewAngle + *(s16 *)((u8 *)actor + 0x2A) + 0x100) >> 9) & 7;
            func_80047784(sprite, frame_table[direction], 0);
            advance_status_timers(actor);
            *((u8 *)actor + 0x6D) = (u8)(*((u8 *)actor + 0x6D) - 1);
            *(u16 *)((u8 *)action_state + 0x98) = (u16)(*(u16 *)((u8 *)action_state + 0x98) | 8);
        }
    }
}
