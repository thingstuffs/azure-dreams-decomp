#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/graphics.h"
#include "dungeon/effect.h"
#include "dungeon/monster/kewne.h"
#include "dungeon/player/object.h"


typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
extern u8 kewne_frame_set_3;

/* Clears the actor flag and conditionally updates its state and directional animation. */
void start_kewne_attack_action(ActorRecord *controller, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(actor), action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            controller->action_id = 0x17;
            controller->unk_8C.word = 0;
            controller->action_phase = 0;
            (sprite->frameTable) = &kewne_frame_set_3;
            select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)
                + &kewne_frame_set_3), 0);
            actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
            controller->action_state_flags = (u16) (controller->action_state_flags | 8);
            prepare_directional_attack(actor, sprite, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 0;
        }
    }
}
