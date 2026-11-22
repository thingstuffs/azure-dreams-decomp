/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/effect.h"
#include "dungeon/monster/kid.h"
#include "dungeon/player/object.h"

typedef struct Ent Ent;
struct Ent *prepare_directional_attack();

/* Initialize action state and directional animation when the entity status permits. */
void begin_kid_attack_action(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite, ActorRecord *entity) {
    entity->movement_queue_state &= 0x7F;
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(entity) << 0x10) == 0)) {
        apply_camera_offset_and_select_target(NODE_HEADER(entity), motion_param, 8, 0x300);
        if ((try_claim_dungeon_action_slot(entity) << 0x10) == 0) {
            action_state->action_id = 0x11;
            action_state->unk_8C.handler = 0;
            action_state->action_phase = 0;
            select_sprite_entry(sprite,
                          *((u8 *)sprite->frameTable + (((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7)),
                          0);
            entity->pending_turn_updates--;
            prepare_directional_attack(entity, sprite, entity->facing, 1, 0);
            action_state->action_state_flags |= 8;
            entity->accuracy = 0x7C;
            entity->attack_bonus = 0;
        }
    }
}
