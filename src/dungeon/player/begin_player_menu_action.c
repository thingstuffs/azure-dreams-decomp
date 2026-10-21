#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"

typedef struct ActionActor { u8 pad[0x8C]; s32 action; } ActionActor;

extern s32 dungeon_menu_action_state[];

extern void play_sound_if_enabled(u32);

/* Initialize the actor action state or signal that the action is blocked. */
void begin_player_menu_action(void *actor, s32 unused_1, s32 unused_2, s32 action_value) {
    if (!(system_update_flags & 1)) {
        if (dungeon_floor_flags & 0x200000) {
            if (((s32)g_game_work.pressed_buttons) & 0x80) {
                play_sound_if_enabled(0x506);
                return;
            }
        } else {
            *(u8 *)((u8 *)actor + 0x9A) = 0x19;
            play_sound_if_enabled(0x514);
            dungeon_menu_action_state[0] = action_value;
            *(u8 *)((u8 *)actor + 0x9B) = 0;
            ((ActionActor *)actor)->action = 0;
            reference_tile_object.unk_038 = 0;
            dungeon_floor_flags |= 0x2000;
        }
    }
}
