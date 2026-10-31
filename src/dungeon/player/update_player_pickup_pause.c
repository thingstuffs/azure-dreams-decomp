#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "dungeon/player.h"


/* Waits for a countdown or global state change before resetting the object's handler. */
void update_player_pickup_pause(ActorRecord *object) {
    GameWork *shared_data = &g_game_work;
    u8 state = object->action_phase.u;
    u16 timer;

    switch (state) {
    case 0:
        object->action_timer.u = 0x10;
        object->action_phase.u++;
        break;
    case 1:
        timer = object->action_timer.u - 1;
        object->action_timer.u = timer;
        if ((s16)timer >= 0) {
            if ((shared_data->pressed_buttons) == 0) {
                return;
            }
            if (*(s32 *)0x80012090 == state) {
                return;
            }
        }
        *(s32 *)((u8 *)object + 0x124) = 0;
        object->unk_8C.address = handle_player_input;
        break;
    }
}
