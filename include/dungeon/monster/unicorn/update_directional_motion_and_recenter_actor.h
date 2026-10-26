#ifndef DUNGEON_OVL_7F511800_P03_H
#define DUNGEON_OVL_7F511800_P03_H
#include "dungeon/actor.h"
#include "dungeon/player/object.h"

struct SpriteFrameState;
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


   /* arg0 in func_8017314C */





#include "shared/object_flags.h"
#include "shared/actor_action.h"

typedef struct T_80173450_S_80173450_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} T_80173450_S_80173450_0;   /* arg0 in func_80173450 */


typedef struct T_80173450_S_80173450_2 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} T_80173450_S_80173450_2;   /* arg2 in func_80173450 */




extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
extern void unlink_entity_node(void *);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void distribute_experience_and_report_gains(void *);
extern void * detach_record_and_update_slot_state(void *);
extern void play_sound_if_enabled(s32);
extern u8 unicorn_action_continuation_address;
extern u8 D_80174D5C;
void update_directional_motion_and_recenter_actor(ActorActionTimerView *action, ObjectPosition *motion, SpriteFrameState *actor, void *source);
void fade_and_remove_entity_sprite(void *action, void *unused, void *sprite,struct SpriteFrameState *entity);
#endif
