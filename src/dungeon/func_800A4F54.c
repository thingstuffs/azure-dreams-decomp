#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor/motion.h"
#include "engine/graphics.h"

void apply_actor_delta_and_cap_value();         /* extern */


/* Set the entity to state 7 and select its directional sprite frame when ready. */
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames) {
    if (body->hp_delta > 0) {
        apply_actor_delta_and_cap_value(body, position, sprite, body);
        return 0;
    }
    g_dungeon_status.pending_display_owner = (ObjectNodeHeader *)body - 1;
    body->action_id.u = 7;
    body->action_phase.u = 0;
    body->unk_8C.handler = 0;
    if (direction_frames != 0) {
        if (!(body->flags1C & 0x20)) {
            sprite->frameTable = direction_frames;
            select_sprite_entry(sprite, *(direction_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + body->facing + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}
