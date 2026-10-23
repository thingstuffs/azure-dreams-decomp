#include "common.h"
#include "dungeon/actor/state.h"
#include "shared/dungeon_status.h"

typedef struct {
    u16 field_00;
    u16 field_02;
    u8 pad_04[8];
    s32 field_0C;
    s32 field_10;
    u16 field_14;
    u16 field_16;
} DungeonState;

extern s32 try_claim_dungeon_action_slot(void *);
extern s32 trigger_actor_floor_trap(void *, void *);

/* Attempts a pending action and updates dungeon state on success. */
s32 resolve_actor_floor_trap_once(void *action, s32 unused, void *source, void *target) {
    s32 result;

    if (*((u8 *)action + 0x9B) == 0) {
        *((u8 *)target + 0x71) &= 0x7F;
        if (g_dungeon_status.flags & 0x2000) {
            return 0;
        }
        if ((try_claim_dungeon_action_slot(target) << 16) != 0) {
            return 0;
        }

        result = trigger_actor_floor_trap(source, target);
        if ((result << 16) != 0) {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.trap_counts.parts.pending_trap_count -= 1;
            *((u8 *)action + 0x9B) = 1;
        }
    } else {
        result = 1;
    }
    return (s16)result;
}
