#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct {
    u8 pad[3];
    u8 flags;
} DungeonEntry;

extern s16 get_tile_chebyshev_distance(void *, void *);
extern void update_actor_status_and_mp(void *);
extern void begin_actor_floor_trap_action(void *, void *);
extern s16 find_entry_at_tile_coordinates(u8, u8, s16);

extern DungeonEntry floor_objects[];

typedef struct S_800AD9B4_0_pre {
    u16 unk_00;
} S_800AD9B4_0_pre;   /* the 0x2 bytes before arg1 in check_actor_floor_trap, addressed as arg1[-1] */

/* Process an eligible dungeon entry and apply its state updates. */
s32 check_actor_floor_trap(SpriteFrameState *actor, ActorRecord *target)
{
    TileObject *player;
    DungeonGlobalStatus *dungeon_state;
    DungeonEntry *entries;
    s32 entry_index;
    s32 result;
    s32 cost;
    s8 adjustment;

    if (((S_800AD9B4_0_pre *)target)[-1].unk_00 & 0x8000) {
        return 1;
    }
    player = &reference_tile_object;
    if (player->room_index != *(s8 *)&actor->room_index && get_tile_chebyshev_distance(player, actor) >= 7) {
        return 1;
    }
    if (target->mp_value.parts.whole == 0) {
        return 1;
    }

    entry_index = find_entry_at_tile_coordinates(actor->tile_x,
                                  actor->tile_y,
                                  target->ground_height);
    result = 1;
    if (entry_index >= 0) {
        entries = floor_objects;
        if (!(entries[entry_index].flags & 0x80)) {
            return 1;
        }

        dungeon_state = &g_dungeon_status;
        if (dungeon_state->flags & 0x1000) {
            adjustment = ((s8)target->movement_queue_state);
            if (adjustment > 0) {
                cost = adjustment - (u16)target->unk_8A;
                entry_index = (u16)dungeon_state->activity_counts.parts.pending_movement_count;
                entry_index -= cost;
                dungeon_state->activity_counts.parts.pending_movement_count = entry_index;
                target->movement_queue_state = 0;
            }
        }

        update_actor_status_and_mp(target);
        begin_actor_floor_trap_action(actor, target);
        result = 0;
    }
    return result;
}
