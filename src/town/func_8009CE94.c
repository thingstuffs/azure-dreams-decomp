#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 func_800C2B6C(s16 angle);
extern u8 D_80082660;
extern s32 D_80082A38[];
/* player_now_ang_get: Store the current player angle when the player slot is available. */
void player_now_ang_get(void)
{
    u8 *player_slot;
    void *player;
    s32 *script_values;
    s32 player_angle;
    int slot_index;
    slot_index = 8;
    script_values = D_80082A38;
    player_slot = (&D_80082660) + slot_index;
    if ((*((s8 *) (player_slot + 1))) == 0) {
        player = *((void **) (player_slot + 4));
        if (player != 0) {
            slot_index = 0x12;
            player_angle = func_800C2B6C(*((s16 *) (((u8 *) player) + 0x30)));
            script_values[slot_index] = player_angle;
        }
    }
}
