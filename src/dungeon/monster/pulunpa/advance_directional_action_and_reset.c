#include "common.h"
#include "dungeon/monster/pulunpa.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "engine/graphics.h"
#include "dungeon/system.h"

typedef struct S_801725B8_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801725B8_0;   /* arg0 in advance_directional_action_and_reset */



void *resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance);



extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_attack_frames[];

/* Advances the actor's directional animation and resets its action state on completion. */
void advance_directional_action_and_reset(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *anim, ActorRecord *actor) {
    switch (action->action_phase.u) {
    case 0:
        if (anim->flags & 0x8000) {
            action->action_phase.u = 2;
            anim->flags |= 0x6000;
            resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
            return;
        }
        {
            u8 *direction_table;

            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            direction_table = pulunpa_attack_frames;
            anim->frameTable = direction_table;
            select_sprite_entry(anim,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            action->action_phase.u++;
        }
        return;

    case 1:
        if (anim->unk_04 == 3 && (anim->flags & 0x1000)) {
            play_sound_if_enabled(0x808);
        }
        if (!((anim->unk_04 == 6 && (anim->flags & 0x1000)) ||
              (anim->flags & 0xE000))) {
            return;
        }
        resolve_attack_damage_and_effects(actor, anim, actor->facing, 1);
        action->action_phase.u++;
                        /* fallthrough */
    case 2:
        if (!(anim->flags & 0xE000)) {
            return;
        }
        spend_actor_mp(actor, 0x100);
        action->unk_8C.address = &pulunpa_action_resume_address;
        g_dungeon_status.active_actor = 0;
        (actor->action_flags) &= 0x7FFF;
        advance_status_timers(actor);
        return;
    }
}
