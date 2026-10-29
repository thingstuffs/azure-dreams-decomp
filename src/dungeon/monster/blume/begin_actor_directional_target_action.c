#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

typedef struct S_80047784 S_80047784;

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x8C];
    s32 field_8C;
} ActionStateFieldView_80DBD29C;



typedef struct S_80174A9C_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80174A9C_1;   /* arg0 in begin_actor_directional_target_action */

struct SpriteFrameState;
void select_sprite_entry(void *, s16, s16);
void *find_eligible_actor_at_tile_and_height();
s16 try_claim_dungeon_action_slot(ActorRecord *actor);
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value);
extern u8 D_80175414;

/* Starts an actor action and selects its directional sprite and adjacent target. */
void begin_actor_directional_target_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 direction;

    actor->movement_queue_state = (u8)(actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->action_id.s = 0x17;
            (((ActionStateFieldView_80DBD29C *)action_state)->field_8C) = 0;
            action_state->action_phase.s = 0;
            (sprite->frameTable) = &D_80175414;
            select_sprite_entry(sprite,
                          *(&D_80175414 + (((s32)(g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)),
                          0);
            advance_status_timers(actor);
            actor->pending_turn_updates = (u8)(((u8)actor->pending_turn_updates) - 1);
            direction = ((u16)actor->facing >> 9) & 7;
            actor->target =
                find_eligible_actor_at_tile_and_height(actor,
                              (sprite->tile_x + ((u16 *)dir_step_x)[direction]) & 0xFFFF,
                              (sprite->tile_y + ((u16 *)dir_step_y)[direction]) & 0xFFFF,
                              actor->ground_height);
        }
    }
}
