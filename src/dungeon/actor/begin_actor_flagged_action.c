#include "common.h"
#include "dungeon/actor.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern struct {
    s8 pad[0xA];
    u16 field_0xA;
} g_dungeon_status;

/* Sets entity state 0x14, resets progress, sets status flags, and increments the global counter. */
void begin_actor_flagged_action(Rec_func_800A9E70_arg0 *entity, void *unused, SpriteFrameState *status, EntityRec *event_state) {
    entity->unk_9A.as_s8 = 0x14;
    entity->unk_9B.as_s8 = 0;
    entity->unk_8C = 0;
    status->flags = (u16)(status->flags | 0x800);
    entity->unk_96.as_s16 = 0;
    g_dungeon_status.field_0xA = g_dungeon_status.field_0xA + 1;
    event_state->flags1C = (s32)(event_state->flags1C | 0x10000000);
}
