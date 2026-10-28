#ifndef MODULE_DUNGEON_OVL_12C50AC_H
#define MODULE_DUNGEON_OVL_12C50AC_H
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "sdk/libgte.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "engine/texture.h"
#include "dungeon/actor/status.h"
#include "dungeon/level.h"
#include "engine/node/allocation.h"
#include "engine/node.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"

/* cfail-repair: tf7-phase1-cache-v3 */

void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);                 /* extern */
s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);                /* extern */
extern void *active_action_object[];
void update_actor_scripts_and_motion(ActorRecord *actor_in, ObjectPosition *motion_in, SpriteFrameState *sprite_in);

/* Creates and initializes an entity at the center of the specified tile. */

#include "shared/dir_step.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
extern int abs(int);

typedef struct S_812A524C_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_0;   /* &D_800FBE22 in func_80170A4C */

typedef struct S_812A524C_1 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
} S_812A524C_1;   /* &D_800FBE20 in func_80170A4C */



typedef struct S_812A524C_5 {
    void * unk_00;
} S_812A524C_5;   /* &D_800FBE54 in func_80170A4C */

typedef struct S_812A524C_6 {
    u16 unk_00;
} S_812A524C_6;   /* &D_80013714 in func_80170A4C */














typedef struct S_812A524C_34 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_812A524C_34;   /* temp_v1_3 in func_80170A4C */

typedef struct S_812A524C_36 {
    union { s32 n; s32 v; } unk_00;   /* accessed as both */
} S_812A524C_36;   /* &D_800E296C in func_80170A4C */




typedef struct S_812A524C_40 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_812A524C_40;   /* ((S_812A524C_5 *)(&D_800FBE54))->unk_00 in func_80170A4C */

s32 enqueue_runtime_pool_script(void *input_data); /* extern */
void clear_slots_of_type();
void func_80042B68(ActorRecord *owner, s8 match_type);                /* extern */
void advance_sprite_animation_and_textures(void *entity);                      /* extern */
void apply_monster_koyaw_data();                 /* extern */
#include "dungeon/player/object/action_state.h"
struct ObjectNodeHeader;
void update_actor_status_and_mp(ActorRecord *entity);                      /* extern */
s32 refresh_actor_facing_and_lifecycle();  /* extern */

extern u8 D_8006EE9C[16];
extern u8 kewne_spawn_pool_script[16];
extern u8 D_8006F50D[16];
extern u8 D_8006F6B9[16];
extern u8 D_8006F9D0[16];
extern u8 D_8006FD01[16];
extern u8 D_8006FFB7[16];
extern u8 D_800703D9[16];
extern u8 D_80070684[16];
extern u8 D_80070AF8[16];
extern u8 D_80070C11[16];
extern u8 D_80070E63[16];
extern u8 dungeon_floor_flags[16];

extern u8 D_800FB3C8[16];
extern u8 D_800FB8DF[16];
extern u8 D_800FBAD7[16];
extern u8 D_800FBD96[16];
extern u8 script_motion_phase[16];
extern u8 D_800FBE22[16];
extern u8 scripted_status_target[16];
typedef struct {
    u8 bytes[16];
} __attribute__((packed)) Packed16;
extern Packed16 D_80170804;
extern u8 kewne_uncached_action_resume_address[16];
extern u8 kewne_uncached_frame_set_1[16];
extern void (*kewne_uncached_callbacks[])(void *, void *, void *, void *);

#define event_base ((u8 *)((u8 *)(&reference_tile_object)))
#define position_base ((u8 *)((u8 *)(&view_reference_entity)))

/* Updates actor events, behavior, movement, and sprite height and facing. */

#endif
