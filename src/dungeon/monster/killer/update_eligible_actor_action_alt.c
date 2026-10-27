#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s16 try_claim_dungeon_action_slot(ActorRecord *actor);                          /* extern */
s32 apply_camera_offset_and_select_target(void *object_addr, void *source_pos, s32 helper_arg, s32 slot_value); /* extern */
#include "dungeon/monster/killer.h"
#include "engine/graphics.h"

/* Updates the actor's action state and directional animation when it can act. */
void update_eligible_actor_action_alt(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)
        && (apply_camera_offset_and_select_target(((u8 *)actor - 0x20), context, 8, 0x300), ((try_claim_dungeon_action_slot(actor) << 0x10) == 0))) {
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
        if (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000) {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
            if (((EntityRec *)actor)->flags1C & ACTOR_ANGRY) {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                    (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 | 0x4000);
            } else {
                ((Rec_func_800A9E70_arg0 *)action_state)->unk_98 =
                    (u16) (((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0xBFFF);
            }
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_AC = (u8) (*(u8 *)((u8 *)&((EntityRec *)actor)->x + 3));
            (*(u8 *)((u8 *)&((EntityRec *)actor)->x + 3)) = 0xFFU;
            ((EntityRec *)actor)->unk_84 = 0x7E;
            ((EntityRec *)actor)->unk_85 = 8;
        } else {
            ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x11;
            ((EntityRec *)actor)->unk_84 = 0x7C;
            ((EntityRec *)actor)->unk_85 = 8;
        }
        (sprite->frameTable) = killer_direction_frames;
        select_sprite_entry(sprite, killer_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        prepare_directional_attack(actor, sprite, ((EntityRec *)actor)->facing, 1, 0);
        if (!(((Rec_func_800A9E70_arg0 *)action_state)->unk_98 & 0x8000)) {
            ((EntityRec *)actor)->flags1C = (s32) (((EntityRec *)actor)->flags1C & 0xFEFFFFFF);
        }
    }
}

