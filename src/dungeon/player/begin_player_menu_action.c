#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/entity.h"
#include "dungeon/player.h"
#include "dungeon/system.h"

typedef struct ActionActor { u8 pad[0x8C]; s32 action; } ActionActor;

extern void *dungeon_menu_action_state[];

/* Initialize the actor action state or signal that the action is blocked. */
void begin_player_menu_action(void *actor_data, ObjectPosition *unused_1, SpriteFrameState *unused_2, void *action_value) {
    ActorRecord *actor = actor_data;

    if (!(system_update_flags & 1)) {
        if (dungeon_floor_flags & 0x200000) {
            if ((g_game_work.pressed_buttons) & 0x80) {
                play_sound_if_enabled(0x506);
                return;
            }
        } else {
            actor->action_id = 0x19;
            play_sound_if_enabled(0x514);
            dungeon_menu_action_state[0] = action_value;
            actor->action_phase = 0;
            actor->unk_8C.word = 0;
            reference_tile_object.unk_038 = 0;
            dungeon_floor_flags |= 0x2000;
        }
    }
}
