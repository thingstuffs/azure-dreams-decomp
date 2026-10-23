#include "dungeon/monster/golem.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"



extern void set_record_integer_tile_center();
extern s32 play_sound_if_enabled();
void func_80170E94(void *actor, void *context, void *sprite, void *stats);



typedef struct S_8017346C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017346C_1;   /* arg2 in initialize_actor_motion_transition */


typedef struct S_8017346C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8017346C_3;   /* arg3 in initialize_actor_motion_transition */

/* Initialize actor motion and transition its handler when action flags are set. */
void initialize_actor_motion_transition(GolemActionWork *actor, ObjectPosition *motion, S_8017346C_1 *action, S_8017346C_3 *status) {
    u8 phase;

    phase = actor->phase;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
    } else {
        if (action->unk_14 & 0x8000) {
            actor->phase = 1U;
            action->unk_14 |= 0x6000;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        actor->phase = (u8) (actor->phase + 1);
    }
    if (((action->unk_04 == 5) && (action->unk_14 & 0x1000)) || (action->unk_14 & 0x8000)) {
        play_sound_if_enabled(0x803);
    }
    if (action->unk_14 & 0xE000) {
        actor->mode = 1;
        status->unk_14 = (s32) (status->unk_14 | 0x40000000);
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, action->unk_24, action->unk_25);
        actor->callback.address = &func_80170E94;
        g_dungeon_status.active_actor = 0;
    }
}
