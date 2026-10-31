#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad00[0x8C];
    s32 unk8C;
    u8 pad90[0x0A];
    s8 unk9A;
    s8 unk9B;
} Entity;

typedef struct {
    u8 pad00[0x2C];
    u8 *unk2C;
} Object;

typedef struct {
    u8 pad00[0x2A];
    s16 unk2A;
    u8 pad2C[0x41];
    u8 unk6D;
    u8 pad6E[3];
    u8 unk71;
} State;

#include "dungeon/player/object/action_state.h"
struct SpriteFrameState;
extern void select_sprite_entry(void *, s16, s16);
extern u8 picket_frame_set_4[];

/* Clears the state flag and, when allowed, resets the entity and selects a directional object value. */
void clear_the_state_flag_allowed_resets_entity_selects_directional(ActorRecord *entity, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    DungeonGlobalStatus *flags = &g_dungeon_status;

    actor->movement_queue_state &= 0x7F;
    if (!(flags->flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 16) == 0)) {
        entity->action_id.s = 0x18;
        entity->unk_8C.run = 0;
        entity->action_phase.s = 0;
        sprite->frameTable = picket_frame_set_4;
        select_sprite_entry(sprite,
                      picket_frame_set_4[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->pending_turn_updates--;
        flags->activity_counts.parts.pending_action_count++;
    }
}
