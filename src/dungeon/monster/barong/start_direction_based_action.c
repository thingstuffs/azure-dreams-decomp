#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern void select_sprite_entry(void *, s32, s32);
extern void apply_scaled_entity_velocity(void *);
extern void advance_status_timers(void *);

extern u8 D_801755B4[];
extern u8 D_80175660[];

/* Starts a direction-based action when the object's state and global flags allow it. */
/* Copies Barong's turn counts into shared state and starts a directional action when the scaled count and
 * dungeon flags allow. */
void start_direction_based_action(void *action_state, void *unused, void *animation, void *object)
{
    u8 *state_data;
    register s32 data_page;
    u8 *direction_table;
    s32 direction_index;

    state_data = D_80175660;
    *(u16 *)(state_data + 0x6C) = *(u16 *)((u8 *)object + 0x6C);
    *(u16 *)(state_data + 0x6E) = *(u16 *)((u8 *)object + 0x6E);
    apply_scaled_entity_velocity(state_data);

    if (*(s8 *)(state_data + 0x6D) != 0) {
        u8 *state_data;
        *(u8 *)((u8 *)object + 0x71) &= 0x7F;
        state_data = ((u8 *)(&g_dungeon_status));
        if (!(*(u16 *)(state_data + 2) & 0x2000)) {
            direction_table = D_801755B4;
            *(s8 *)((u8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *(s8 *)((u8 *)action_state + 0x9B) = 0;
            *(s16 *)((u8 *)action_state + 0x96) = 0;

            *(u8 **)((u8 *)animation + 0x2C) = direction_table;
            data_page = (g_game_work.view.camera_rotation.parts.viewAngle + *(s16 *)((u8 *)object + 0x2A) + 0x100) >> 9;
            select_sprite_entry(animation, direction_table[data_page & 7], 0);
            advance_status_timers(object);
            *(u8 *)((u8 *)object + 0x6D) -= 1;
            *(u16 *)(state_data + 0xA) += 1;
        }
    }
}
