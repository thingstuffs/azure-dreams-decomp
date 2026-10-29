#ifndef DUNGEON_OVL_7F469800_P06_H
#define DUNGEON_OVL_7F469800_P06_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"

typedef struct T_80174C44_S_80174C44_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   /* accessed as both */
    u8 pad_98[0x3];
    u8 phase;
} T_80174C44_S_80174C44_0;   /* arg0 in func_80174C44 */

extern u8 troll_frame_set_5[];
extern u8 troll_frame_set_6[];
extern u8 troll_frame_set_7[];
void advance_actor_timed_tile_motion(T_80174C44_S_80174C44_0 *controller, ObjectPosition *transform, SpriteFrameState *entity, void *actor);
void update_actor_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state);
#endif
