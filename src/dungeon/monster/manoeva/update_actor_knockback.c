#include "shared/actor_status_flags.h"
#include "dungeon/player/object.h"

struct SpriteFrameState;

struct ObjectPosition;
#include "common.h"
#include "dungeon/system/random.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/monster/manoeva.h"
#include "dungeon/data.h"



extern u8 manoeva_action_resume_address[];

/* Three-stage knockback script driven by the 0x9B step byte: stage 0 seeds the velocity from the facing table and picks the timer, stage 1 decays that velocity a quarter per frame, stage 2 steers back to the tile centre and ends by clearing the motion record. */
void update_actor_knockback(ActorRecord *script, ObjectPosition *motion, SpriteFrameState *tile, ActorRecord *actor) {
    s16 timer;
    s32 value;
    s32 value2;
    s32 adjusted;
    s32 state;
    s32 random;
    s32 one;

    state = script->action_phase;
    one = 1;
    switch (state) {
    case 0:
        spawn_manoeva_particle_burst(motion, tile);
        apply_clamped_actor_value_delta(actor);
        motion->velocity_x =
            -dir_step_x[(actor->movement_facing >> 9) & 7] << 15;
        motion->velocity_y =
            -dir_step_y[(actor->movement_facing >> 9) & 7] << 15;
        script->action_phase++;

        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(script, motion, tile, manoeva_frame_set);
            return;
        }
        random = generate_random_value() & 3;
        if (tile->flags & 0x8000) {
            if (random == 0) {
                create_knockback_travel_object(script, motion, tile, actor);
            }
            script->unk_A8.s = -1;
            script->action_timer = 0;
            script->action_phase = 2;
            return;
        }
        timer = -1;
        if (actor->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        }
        script->action_timer = timer;
        if (random != 0) {
            script->unk_A8.s = -1;
        } else {
            script->unk_A8.s = one;
        }
                        /* fall through */
    case 1:
        value = motion->velocity_x;
        adjusted = value;
        if (value < 0) {
            adjusted = value + 3;
        }
        value2 = motion->velocity_y;
        motion->velocity_x = value - (adjusted >> 2);

        adjusted = value2;
        motion->velocity_y = value2 - (adjusted / 4);

        timer = script->unk_A8.u - 1;
        script->unk_A8.s = timer;
        if ((timer << 16) == 0) {
            create_knockback_travel_object(script, motion, tile, actor);
        }

        if ((s16)(script->action_timer) > 0) {
            script->action_timer = script->action_timer - 1;
        } else if (tile->flags & 0x6000) {
            script->action_timer = 0;
        }

        if ((s16)(script->action_timer) != 0) {
            return;
        }
        if (actor->hp == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(script, motion, tile, manoeva_frame_set);
        } else {
            script->action_timer = 8;
            script->action_phase++;
        }
        return;
    case 2:
        timer = (script->action_timer);
        if (timer != 0) {
            s32 sub, m;
            m = tile->tile_x;
            m <<= 6;
            sub = motion->x.w.i - 0x20;
            motion->velocity_x = ((m - sub) << 15) / timer;
            sub = motion->y.w.i - 0x20;
            motion->velocity_y =
                (((tile->tile_y << 6) - sub) << 15) /
                (s16)(script->action_timer);
        }

        timer = script->unk_A8.u - 1;
        script->unk_A8.s = timer;
        if ((timer << 16) == 0) {
            create_knockback_travel_object(script, motion, tile, actor);
        }

        timer = script->action_timer - 1;
        script->action_timer = timer;
        if ((timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x,
            tile->tile_y);
        {

            value = ((s32)g_dungeon_status.pending_display_owner);
            if (value == (s32)((u8 *)actor - 0x20)) {
                g_dungeon_status.pending_display_owner = value & 0x7FFFFFFF;
            }
        }
        script->unk_8C.address = manoeva_action_resume_address;
    }
}
