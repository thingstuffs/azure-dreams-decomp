#include "common.h"
#include "dungeon/monster/manoeva.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"
#include "dungeon/actor.h"
#include "dungeon/effect/screen.h"

typedef struct S_801726A4_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801726A4_0;   /* arg0 in advance_actor_sprite_action */

extern void create_action_sprite_effect(void *);

extern u8 manoeva_action_resume_address[];
extern u8 D_80176600[];
extern u8 manoeva_frame_set_2[];

/* Advances an actor's animation sequence and handles its completion. */
void advance_actor_sprite_action(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 sprite_flags;
    u16 frame_count;
    s32 state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
        action->action_state_flags |= 1;
        action->action_phase.u++;
                        /* fall through */
    case 1:
        sprite_flags = sprite->flags;
        if (sprite_flags & 0x8000) {
            action->action_phase.u = 3;
            sprite->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
            return;
        }

        if (sprite_flags & 0x6000) {
            motion->velocity_x =
                motion->velocity_y =
                motion->velocity_z = 0;
            sprite->frameTable = D_80176600;
            select_sprite_entry(sprite,
                D_80176600[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            create_action_sprite_effect((u8 *)action - 0x20);
            action->action_timer.u = 0;
            action->action_phase.u++;
            play_sound_if_enabled(0x804);
            return;
        }
        break;
    case 2:
        frame_count = action->action_timer.u + 1;
        action->action_timer.u = frame_count;

        if ((s16)frame_count == state ||
            (sprite->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite, actor->facing, 1);
        }

        if (sprite->flags & 0xE000) {
            sprite->frameTable = manoeva_frame_set_2;
            select_sprite_entry(sprite,
                manoeva_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u++;
            action->action_state_flags &= 0xFFFE;
            return;
        }
        break;
    case 3:
        if (sprite->flags & 0xE000) {
            spend_actor_mp(actor, 0x100);
            action->unk_8C.address = manoeva_action_resume_address;
            g_dungeon_status.active_actor = 0;
            (actor->action_flags) &= 0x7FFF;
            advance_status_timers(actor);
        }
    }
}
