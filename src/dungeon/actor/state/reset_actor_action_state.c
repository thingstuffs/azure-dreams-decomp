#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/state.h"
#include "shared/entity.h"

typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern void select_sprite_entry(void *, s32, s32);

/* Resets actor action state and selects a sprite frame for its facing direction. */
s32 reset_actor_action_state(void *actor_data, void *unused, SpriteFrameState *sprite, u8 *direction_frames)
{
    ActorRecord *actor = actor_data;


    actor->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 0x2008) {
        actor->action_id.s = 0xE;
        return 1;
    }
    if (actor->flags1C & 0x20) {
        actor->action_id.s = 0xE;
        actor->flags1C &= ~0x200;
        return 0;
    }

    actor->action_id.s = 0xD;
    actor->action_phase.s = 0;
    actor->unk_8C.word = 0;
    if (direction_frames != 0) {
        sprite->frameTable = direction_frames;
        select_sprite_entry(sprite,
            direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }
    g_dungeon_status.activity_counts.parts.pending_action_count++;
    actor->flags1C &= ~0x40000;
    return 1;
}
