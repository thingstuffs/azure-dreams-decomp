#include "shared/actor_status_ids.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/system.h"

typedef struct {
    u8 pad0[0x1c];
    s32 flags;
    u8 pad20[0x3c];
    s32 value;
} Resource;

typedef struct {
    u8 pad0[0x8c];
    void (*callback)(void *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
    u8 pad90[6];
    u16 counter;
    u8 pad98[3];
    u8 state;
    u8 pad9c[6];
    u16 flags;
} Object;

extern s32 get_entity_effect_value(void *, s32);
extern void process_unflagged_linked_entries(s32);
extern void process_unflagged_linked_entries_alt(s32);

/* Waits for status slot 1 to clear, processes linked actors, and updates pending-action and dungeon flags. */
void update_timed_actor_action(Object *object, s32 unused1, s32 unused2, Resource *resource) {
    s32 state;
        /* MATCH: Keep the guard result in v0 across argument setup. */
    s32 guard;
    GameWork *work;
        /* MATCH: Keep the shared flag table in its retail saved register. */
    DungeonGlobalStatus *status;
        /* MATCH: Keep the incoming resource in a3 for the pass-through call. */
        /* MATCH: Set a0 in both guard delay slots without a redundant call-slot move. */
    Resource *callResource;

    state = object->state;
    work = &g_game_work;
    switch (state) {
    case 0:
        object->callback = apply_pending_actor_updates;
        object->state += 1;
        break;
    case 1:
                /* MATCH: Prevent propagation of the a3 copy into the a0 argument setup. */
        if ((g_dungeon_status.flags & 4) == 0 && (object->flags & 0x10) != 0) {
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
                object->callback = 0;
                g_dungeon_status.activity_counts.parts.pending_action_count += 1;
                object->state += 1;
            } else {
                process_unflagged_linked_entries_alt(resource->value);
                process_unflagged_linked_entries(resource->value);
                g_dungeon_status.flags |= 0x812;
            }
        }
        break;
    case 2:
        resource->flags &= ~0x200;
        process_unflagged_linked_entries_alt(resource->value);
        process_unflagged_linked_entries(resource->value);
        g_dungeon_status.flags |= 0x812;
        object->callback = handle_actor_commands_and_facing;
        g_dungeon_status.activity_counts.parts.pending_action_count -= 1;
        break;
    }
    object->counter += 1;
}
