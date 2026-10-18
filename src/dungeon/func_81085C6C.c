#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;


extern void set_record_integer_tile_center();
extern s32 play_sound_if_enabled();
extern M2C_UNK D_80170E94;


typedef struct S_8017346C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x12];
    s8 unk_AE;
} S_8017346C_0;   /* arg0 in initialize_actor_motion_transition */

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
void initialize_actor_motion_transition(S_8017346C_0 *actor, EntityRec *motion, S_8017346C_1 *action, S_8017346C_3 *status) {
    u8 phase;

    phase = actor->unk_9B;
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
    } else {
        if (action->unk_14 & 0x8000) {
            actor->unk_9B = 1U;
            action->unk_14 |= 0x6000;
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        actor->unk_9B = (u8) (actor->unk_9B + 1);
    }
    if (((action->unk_04 == 5) && (action->unk_14 & 0x1000)) || (action->unk_14 & 0x8000)) {
        play_sound_if_enabled(0x803);
    }
    if (action->unk_14 & 0xE000) {
        actor->unk_AE = 1;
        status->unk_14 = (s32) (status->unk_14 | 0x40000000);
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion, action->unk_24, action->unk_25);
        actor->unk_8C = &D_80170E94;
        g_dungeon_status.unk_0C = 0;
    }
}
