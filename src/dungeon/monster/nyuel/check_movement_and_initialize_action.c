#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/nyuel.h"

typedef struct S_80171E00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80171E00_3;   /* arg0 in check_movement_and_initialize_action */

void select_sprite_entry();         /* extern */
typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s32 get_actor_height_difference();                     /* extern */
s32 probe_directional_neighbor();             /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 check_entity_interaction_compatibility();                     /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */
extern u8 D_80174F28;

/* Check movement conditions and initialize the actor action and directional animation. */
/* Starts Nyuel's attack against a compatible neighbor within 63 height units; returns 1, 0 if unsuitable,
 * or -1 if busy. */
s32 check_movement_and_initialize_action(void *action_state, void *action_ctx, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 unused[2]; /* never accessed: retail's frame reserves 8 bytes for this unused local */
    u8 *direction_table;
    s32 move_heading;
    u16 flags;

    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (g_dungeon_status.flags & 0x2000) {
        return -1;
    }
    move_heading = probe_directional_neighbor(actor, sprite->unk_24, sprite->unk_25,
        actor->facing);
    if ((check_entity_interaction_compatibility(actor, move_heading) << 0x10) == 0) {
        return 0;
    }
    flags = g_dungeon_status.flags;
    if (flags & 0x2000) {
        return -1;
    }
    if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
        if (flags & 8) {
            return -1;
        }
    }
    if ((u32) (((0 - get_actor_height_difference(move_heading, actor)) + 0x3F) & 0xFFFF) >= 0x7FU) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 0x10) != 0) {
        return -1;
    }
    apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
        ((S_80171E00_3 *)action_state)->unk_9A = 0x11;
        ((S_80171E00_3 *)action_state)->unk_9B = 0;
        ((S_80171E00_3 *)action_state)->unk_8C = 0;
        actor->unk_84 = 0x7C;
        actor->unk_85 = 0;
        direction_table = &D_80174F28;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(sprite, direction_table[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
        return 1;
    }
    return -1;
}
