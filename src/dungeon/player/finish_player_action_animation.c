#include "shared/dungeon_actor_callbacks.h"
#include "dungeon/player/input.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 can_entity_gain_level(void *entity);

/* Selects the target's table from flags and clears global state when the update returns zero. */
void finish_player_action_animation(ActorRecord *target, void *unused, void *flag_data, ActorRecord *source) {
    void *table;
    if (!(source->flags1C & 0x100000)) {
        if (*(u16 *)((u8 *)flag_data + 0x14) & 0xE000) {
            table =handle_player_input;
        } else {
            return;
        }
    } else {
        table = handle_carrying_player_input;
    }

    target->unk_8C.address = table;
    if ((can_entity_gain_level(source) << 16) == 0) {
        g_dungeon_status.active_actor = 0;
    }
}
