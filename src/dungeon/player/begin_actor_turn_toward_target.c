#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "dungeon/player.h"
#include "dungeon/item.h"
#include "engine/graphics.h"

extern u8 actor_attack_frames[];

   /* the 0x14 bytes before ((S_80091B5C_3 *)base)->unk_0C in begin_actor_turn_toward_target, addressed as ((S_80091B5C_3 *)base)->unk_0C[-1] */

/* Initializes the actor's action and turns it toward the current target. */
void begin_actor_turn_toward_target(ActorRecord *body, void *unused, void *actor_arg, ActorRecord *motion) {
    Rec_D_80082E80 *actor = actor_arg;
    s32 distance;
    MovingTile *target;

    if (actor->unk_14.at00_u16.v & 0x8000) {
        motion->flags14 &= 0xFFFDFFFF;
        return;
    }
    body->action_id.s = 0x2A;
    body->action_phase.s = 0;
    body->unk_8C.word = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    body->action_timer.s = 0x10;
    actor->unk_2C.as_pu8 = actor_attack_frames;
    set_sprite_animation_frame(actor_arg, actor_attack_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + motion->facing + 0x100)
        >> 9) & 7], 0, 1);
    target = ((SpriteLinkPrefixView *)(g_dungeon_status.active_actor))[-1].sprite;
    ((Rec_func_8008ACDC_arg0 *)body)->unk_11A = (u16) motion->facing;
    motion->facing = get_rounded_facing_and_rounding_flag(actor->unk_24,
        actor->unk_25, target->tile_x, target->tile_y,
        &distance);
}
