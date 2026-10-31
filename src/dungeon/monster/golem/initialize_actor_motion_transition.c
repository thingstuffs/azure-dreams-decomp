#include "dungeon/monster/golem.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "dungeon/system.h"



void func_80170E94(struct GolemActionWork *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *stats);




/* Initialize actor motion and transition its handler when action flags are set. */
void initialize_actor_motion_transition(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 phase;

    phase = body->action_phase.u;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
    } else {
        if (sprite->flags & 0x8000) {
            body->action_phase.u = 1U;
            sprite->flags |= 0x6000;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        body->action_phase.u = (u8) (body->action_phase.u + 1);
    }
    if (((sprite->unk_04 == 5) && (sprite->flags & 0x1000)) || (sprite->flags & 0x8000)) {
        play_sound_if_enabled(0x803);
    }
    if (sprite->flags & 0xE000) {
        body->unk_AC.bytes[2] = 1;
        actor->flags14 = (s32) (actor->flags14 | 0x40000000);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x, sprite->tile_y);
        body->unk_8C.address = &func_80170E94;
        g_dungeon_status.active_actor = 0;
    }
}
