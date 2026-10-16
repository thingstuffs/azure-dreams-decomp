/* Relink of matched dungeon/func_80E657E4; every changed retail word is a paired relocation. */
#define D_801755B4 D_801635B4
#define D_80175660 D_80163660
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern void func_80047784(void *, s32, s32);
extern void dungeonApplyScaledEntityVelocity(void *);
extern void dungeonAdvanceStatusTimers(void *);

extern u8 D_801635B4[];
extern u8 D_80163660[];

/* Starts a direction-based action when the object's state and global flags allow it. */
void func_80162FE4(void *action_state, void *unused, void *animation, void *object)
{
    u8 *state_data;
    register s32 data_page;
    u8 *direction_table;
    s32 direction_index;

    state_data = D_80163660;
    *(u16 *)(state_data + 0x6C) = *(u16 *)((u8 *)object + 0x6C);
    *(u16 *)(state_data + 0x6E) = *(u16 *)((u8 *)object + 0x6E);
    dungeonApplyScaledEntityVelocity(state_data);

    if (*(s8 *)(state_data + 0x6D) != 0) {
        u8 *state_data;
        *(u8 *)((u8 *)object + 0x71) &= 0x7F;
        state_data = ((u8 *)(&dungeonStatus));
        if (!(*(u16 *)(state_data + 2) & 0x2000)) {
            direction_table = D_801635B4;
            *(s8 *)((u8 *)action_state + 0x9A) = 0x17;
            *(s32 *)((u8 *)action_state + 0x8C) = 0;
            *(s8 *)((u8 *)action_state + 0x9B) = 0;
            *(s16 *)((u8 *)action_state + 0x96) = 0;

            *(u8 **)((u8 *)animation + 0x2C) = direction_table;
            data_page = (gameWork.view.viewAngle + *(s16 *)((u8 *)object + 0x2A) + 0x100) >> 9;
            func_80047784(animation, direction_table[data_page & 7], 0);
            dungeonAdvanceStatusTimers(object);
            *(u8 *)((u8 *)object + 0x6D) -= 1;
            *(u16 *)(state_data + 0xA) += 1;
        }
    }
}
