#include "shared/entity.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

#include "dungeon/player/object/action_state.h"
extern s16 actor_action_reset_value;

/* Initializes entity state and conditionally increments the dungeon count. */
void initialize_counted_entity_action(ActorRecord *entity_data, ObjectPosition *unused_position, SpriteFrameState *unused_sprite, ActorRecord *other_data)
{
    ActorRecord *entity = entity_data;
    ActorRecord *other = other_data;
    s32 kind = 0x17;

    other->movement_queue_state &= 0x7F;
    entity->unk_8C.address = initialize_counted_entity_action;
    entity->action_id = kind;
    entity->action_phase = 0;
    other->pending_turn_updates = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other) << 16) == 0)) {
        entity->unk_8C.address = 0;
        entity->action_id = kind;
        entity->action_phase = 0;
        actor_action_reset_value = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}
