#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/dungeon_status.h"

extern void *player_action_tag[];
extern s32 can_entity_gain_level(void *entity);

/* Selects the target's table from flags and clears global state when the update returns zero. */
void finish_player_action_animation(void *target, void *unused, void *flag_data, void *source) {
    void *table;
    if (!(*(s32 *)((u8 *)source + 0x1C) & 0x100000)) {
        if (*(u16 *)((u8 *)flag_data + 0x14) & 0xE000) {
            table =handle_player_input;
        } else {
            return;
        }
    } else {
        table = player_action_tag;
    }

    *(void **)((u8 *)target + 0x8C) = table;
    if ((can_entity_gain_level(source) << 16) == 0) {
        g_dungeon_status.active_actor = 0;
    }
}
