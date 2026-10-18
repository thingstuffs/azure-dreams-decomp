#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern void begin_actor_flagged_action(void *, s32, void *, void *);

/* Update actor state and dungeon count, or dispatch special handling. */
s32 advance_actor_pending_action(void *actor_state, s32 action, void *status, void *actor) {

    *(u8 *)((u8 *)actor + 0x71) &= 0x7F;
    if (g_dungeon_status.flags & 0x2008) {
        *(s8 *)((u8 *)actor_state + 0x9A) = 0xE;
        return 0;
    }
    if (*(s32 *)((u8 *)actor + 0x14) & 0x20000000) {
        begin_actor_flagged_action(actor_state, action, status, actor);
        return 1;
    }
    if (!(*(s32 *)((u8 *)actor + 0x1C) & 8)) {
        g_dungeon_status.unk_0A--;
    }
    *(s8 *)((u8 *)actor_state + 0x9A) = 5;
    *(s8 *)((u8 *)actor_state + 0x9B) = 0;
    *(s32 *)((u8 *)actor_state + 0x8C) = 0;
    *(u16 *)((u8 *)actor_state + 0x98) &= 0xFFF7;
    *(s16 *)((u8 *)actor + 0x24) = 0;
    g_dungeon_status.unk_0A++;
    *(s32 *)((u8 *)actor + 0x1C) =
        (*(s32 *)((u8 *)actor + 0x1C) | 8) & 0xFFFBFFFF;
    *(u16 *)((u8 *)status + 0x14) |= 0x6000;
    return 1;
}
