#include "shared/actor_status_ids.h"
#include "dungeon/actor/motion.h"
#include "dungeon/player/input.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "dungeon/player.h"
#include "engine/entity.h"

/* Selects the target dispatch pointer from the source type and flags. */
void restore_player_control_callback(void *target, void *source) {

    {
        s32 type_match;
        type_match = get_entity_effect_value(source, STATUS_FROG) << 16;
        if (type_match != 0) {
            *(void **)((u8 *)target + 0x8C) = handle_actor_commands_and_facing;
        } else {

            {
                s32 source_flags;
                source_flags = *(s32 *)((u8 *)source + 0x1C);
                source_flags &= 0x100000;
                if (source_flags != 0) {
                    *(void **)((u8 *)target + 0x8C) = handle_carrying_player_input;
                } else {

                    {
                        u8 *default_dispatch;
                        default_dispatch = (u8 *)handle_player_input;
                        *(void **)((u8 *)target + 0x8C) = default_dispatch;
                    }
                }
            }
        }
    }
}
