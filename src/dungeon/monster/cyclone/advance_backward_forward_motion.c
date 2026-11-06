#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"

struct SpriteFrameState;
#include "common.h"
#include "dungeon/monster/cyclone.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgte.h"
#include "dungeon/monster/cyclone_frames.h"

extern s32 create_directional_effect(ActorRecord *, void *,struct SpriteFrameState *);
extern s32 create_offset_directional_effect(ActorRecord *, void *,struct SpriteFrameState *);

/* Updates a timed backward-then-forward movement sequence and handles animation completion. */
void advance_backward_forward_motion(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *animation, ActorRecord *actor) {
    u16 timer;
    s32 state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        action->unk_AC.halves.high.s = 6;
        motion->velocity_x =
            -(((rcos(actor->facing) >> 4) << 13) /
              action->unk_AC.halves.high.s);
        motion->velocity_y =
            -(((rsin(actor->facing) >> 4) << 13) /
              action->unk_AC.halves.high.s);
        action->action_phase.u++;

    case 1:
        if (animation->flags & 0x8000) {
            action->action_phase.u = 3;
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
            animation->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            return;
        }

        timer = action->unk_AC.halves.high.u - 1;
        action->unk_AC.halves.high.u = timer;
        if ((s16)timer < 0) {
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
        }

        if (animation->flags & 0x6000) {
            u8 *direction_anims = cyclone_attack_frames;

            animation->frameTable = direction_anims;
            select_sprite_entry(
                animation,
                direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->unk_AC.halves.high.s = 6;
            motion->velocity_x =
                ((rcos(actor->facing) >> 4) << 14) /
                action->unk_AC.halves.high.s;
            motion->velocity_y =
                ((rsin(actor->facing) >> 4) << 14) /
                action->unk_AC.halves.high.s;
            action->unk_AC.halves.high.u--;
            create_directional_effect(action, motion, animation);
            create_offset_directional_effect(action, motion, animation);
            play_sound_if_enabled(0x80E);
            action->action_phase.u++;
            action->action_timer.u = 0;
        }
        return;

    case 2:
        timer = action->unk_AC.halves.high.u - 1;
        action->unk_AC.halves.high.u = timer;
        if ((s16)timer < 0) {
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
        }

        timer = action->action_timer.u + 1;
        action->action_timer.u = timer;
        if (((s16)timer == 5) || (animation->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, animation, actor->facing, 1);
            play_sound_if_enabled(0x808);
        }

    case 3:
        if (animation->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            set_record_integer_tile_center(motion, animation->tile_x, animation->tile_y);
            motion->velocity_x =
                motion->velocity_y =
                    motion->velocity_z = 0;
            action->unk_8C.address = update_actor_animation;
            g_dungeon_status.active_actor = 0;
            (actor->action_flags) &= 0x7FFF;
            advance_status_timers(actor);
        }
    }
}
