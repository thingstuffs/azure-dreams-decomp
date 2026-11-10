#include "shared/actor_status_ids.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"
#include "dungeon/level.h"

extern s32 get_entity_effect_value(void *, s32);

/* Waits for status slot 1 to clear, processes linked actors, and updates pending-action and dungeon flags. */
void update_timed_actor_action(ActorRecord *object, s32 unused1, s32 unused2, ActorRecord *resource) {
    s32 state;
        /* MATCH: Keep the guard result in v0 across argument setup. */
    s32 guard;
    GameWork *work;
        /* MATCH: Keep the shared flag table in its retail saved register. */
    DungeonGlobalStatus *status;
        /* MATCH: Keep the incoming resource in a3 for the pass-through call. */
        /* MATCH: Set a0 in both guard delay slots without a redundant call-slot move. */
    ActorRecord *callResource;

    state = object->action_phase;
    work = &g_game_work;
    switch (state) {
    case 0:
        object->unk_8C.handler = apply_pending_actor_updates;
        object->action_phase += 1;
        break;
    case 1:
                /* MATCH: Prevent propagation of the a3 copy into the a0 argument setup. */
        if ((g_dungeon_status.flags & 4) == 0 && (object->unk_A0.parts.high & 0x10) != 0) {
            guard = work->buttons & 0x20;
            callResource = resource;
            if (guard != 0) {
                guard = check_action_available_without_nearby_actor();
                callResource = resource;
                if (guard != 0) {
                    status = &g_dungeon_status;
                    status->flags |= 0x80;
                }
            }
            if ((get_entity_effect_value(callResource, STATUS_SLEEP) << 16) == 0) {
                object->unk_8C.handler = 0;
                g_dungeon_status.activity_counts.parts.pending_action_count += 1;
                object->action_phase += 1;
            } else {
                process_unflagged_linked_entries_alt(resource->next_actor_header);
                process_unflagged_linked_entries(resource->next_actor_header);
                g_dungeon_status.flags |= 0x812;
            }
        }
        break;
    case 2:
        resource->flags1C &= ~0x200;
        process_unflagged_linked_entries_alt(resource->next_actor_header);
        process_unflagged_linked_entries(resource->next_actor_header);
        g_dungeon_status.flags |= 0x812;
        object->unk_8C.handler = handle_actor_commands_and_facing;
        g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
        break;
    }
    object->action_timer += 1;
}
