/* Actor directional action and its file-private helper. */
#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "engine/graphics.h"
/* extern */
static void apply_actor_delta_and_cap_value(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void apply_clamped_actor_value_delta(void *arg);

/* Starts action 7 with directional frames when ready; otherwise applies the pending actor delta. */
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames) {
    if (body->hp_delta > 0) {
        apply_actor_delta_and_cap_value(body, position, sprite, body);
        return 0;
    }
    g_dungeon_status.pending_display_owner = (ObjectNodeHeader *)body - 1;
    body->action_id.u = 7;
    body->action_phase.u = 0;
    body->unk_8C.handler = NULL;
    if (direction_frames != 0) {
        if (!(body->flags1C & 0x20)) {
            sprite->frameTable = direction_frames;
            select_sprite_entry(sprite, *(direction_frames + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
                + body->facing + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}

/*
 * Applies the actor value delta, then caps byte 0x28 at the limit in byte 0x29; the first three
 * arguments are unused.
 */
static void apply_actor_delta_and_cap_value(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 limit;

    (void)body;
    (void)position;
    (void)sprite;
    apply_clamped_actor_value_delta(actor);
    limit = actor->max_hp;
    if (limit < actor->hp) {
        actor->hp = limit;
    }
}
