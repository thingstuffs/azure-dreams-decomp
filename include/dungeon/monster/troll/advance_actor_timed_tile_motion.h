#ifndef DUNGEON_OVL_7F469800_P06_H
#define DUNGEON_OVL_7F469800_P06_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct T_80174C44_S_80174C44_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } timer;   /* accessed as both */
    u8 pad_98[0x3];
    u8 phase;
} T_80174C44_S_80174C44_0;   /* arg0 in func_80174C44 */


typedef struct T_80174C44_S_80174C44_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} T_80174C44_S_80174C44_4;   /* global in func_80174C44 */




extern void set_record_integer_tile_center(void *, u8, u8);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);
extern u8 troll_frame_set_5[];
extern u8 troll_frame_set_6[];
extern u8 troll_frame_set_7[];
void advance_actor_timed_tile_motion(T_80174C44_S_80174C44_0 *controller, ObjectPosition *transform, SpriteFrameState *entity, void *actor);
extern void update_actor_behavior();
#endif
