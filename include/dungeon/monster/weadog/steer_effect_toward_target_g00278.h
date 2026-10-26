#ifndef DUNGEON_MONSTER_WEADOG_STEER_EFFECT_TOWARD_TARGET_G00278_H
#define DUNGEON_MONSTER_WEADOG_STEER_EFFECT_TOWARD_TARGET_G00278_H
/* Steer effect toward target. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00278 - CL:dungeon/func_80EDF8B8@dungeon/bank_eff000, CL:dungeon/func_80EDF8B8@dungeon/bank_f05000, CL:dungeon/func_80EDF8B8@dungeon/bank_f0b000, CL:dungeon/func_80EDF8B8@dungeon/bank_f11000, CL:dungeon/func_80EDF8B8@dungeon/bank_f17000, CL:dungeon/func_80EDF8B8@dungeon/bank_f1d000. */

#include "common.h"
#include "shared/entity.h"
#include "shared/object_flags.h"
#include "shared/vector.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/dungeon_delay_views.h"
#include "shared/position_views.h"
#include "shared/object_node.h"
#include "sdk/libc.h"
struct RegistrationNode;

#ifndef NULL
#define NULL 0
#endif

typedef struct SteeringEffectWork {
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } color;   /* overlapping accesses */
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } fade_color;   /* overlapping accesses */
    s32 draw_color;
    u8 pad_0C[8];
    s16 param_14;
    u8 pad_16;
    u8 state;
    u8 pad_18[0x1A];
    union { u16 u; s16 s; } timer;   /* accessed as both */
    s16 fade_length;
    s16 origin_x, origin_y, origin_z;
    u8 pad_3C[4];
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    /* Acceleration is selected toward the target integer halves, then added
     * to velocity before each coordinate update. The spawner seeds target
     * coordinates from its parent's position and advances this same work. */
    s32 accel_x, accel_y, accel_z;
    Fixed1616 target_x, target_y, target_z;
} SteeringEffectWork;

/* effect in create_random_color_offset_effect */
typedef struct S_80171498_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80171498_1;

/* arg0 in create_random_color_offset_effect */
/* source in create_random_color_offset_effect */
typedef struct S_80171498_3 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x1E];
    s16 unk_5A;
    u8 pad_5C[0x2];
    s16 unk_5E;
    u8 pad_60[0x2];
    s16 unk_62;
} S_80171498_3;

/* base in create_random_color_offset_effect */
/* ((S_80171498_0 *)effect)->unk_08 in create_random_color_offset_effect */
/* ((S_80171498_1 *)arg0)->unk_08 in create_random_color_offset_effect */
void *allocate_list_node(s32 flags, ObjectNodeHeader **list_head);
s32 resolve_record_orientation_or_fallback();
s32 register_node(struct RegistrationNode *entry, void *registration_id);
extern u8 D_80170ED8[];
extern u8 D_801712C4[];

/* Functions defined in this translation unit. */
void steer_effect_toward_target(SteeringEffectWork *motion, ObjectPosition *position, void *unused);
void initialize_shared_state_active_entries(SteeringEffectWork *effect, ObjectPosition *position, s32 update_param);
void create_random_color_offset_effect( void *parent, s16 initial_14, s32 unused, s16 initial_32, s16 offset_x, s16 offset_y, s16 offset_z);

#endif
