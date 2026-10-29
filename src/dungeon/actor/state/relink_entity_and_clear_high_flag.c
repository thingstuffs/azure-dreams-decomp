#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/dungeon_status.h"

typedef struct DungeonGateState {
    u16 unk0;
    u16 flags;
    u8 pad4[4];
    s16 active;
} DungeonGateState;

typedef struct DungeonOwner {
    u8 pad0[0x58];
    void *field58;
} DungeonOwner;


extern s32 check_entity_relation(void *, void *);
extern s16 select_creature_action_and_target(void *, u8 *, ActorRecord *, s16, s16, s8 *);

/* Process an entity and clear its high flag when relinking it into the active list. */
s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity,
                  s16 near_range, s16 far_range, s8 *state_out_addr) {
    register u16 entity_flags;
    s16 result = select_creature_action_and_target(context, position, entity, near_range, far_range, state_out_addr);

    if (result && (result != 2) && (result != 3) &&
        ((g_dungeon_status.activity_counts.parts.pending_movement_count != 0) ||
         ((g_dungeon_status.flags & 0x2808) != 0)) &&
        ((s16)check_entity_relation(entity,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0)) {
        register s16 failure = -1;

        entity_flags = *(u16 *)((u8 *)entity + 0x46);
        entity_flags &= 0x7FFF;
        *(u16 *)((u8 *)entity + 0x46) = entity_flags;
        return failure;
    }
    return result;
}

