#ifndef DUNGEON_MONSTER_WEADOG_STEER_EFFECT_TOWARD_TARGET_G00278_H
#define DUNGEON_MONSTER_WEADOG_STEER_EFFECT_TOWARD_TARGET_G00278_H
/* Steer effect toward target. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00278 - CL:dungeon/func_80EDF8B8@dungeon/bank_eff000, CL:dungeon/func_80EDF8B8@dungeon/bank_f05000, CL:dungeon/func_80EDF8B8@dungeon/bank_f0b000, CL:dungeon/func_80EDF8B8@dungeon/bank_f11000, CL:dungeon/func_80EDF8B8@dungeon/bank_f17000, CL:dungeon/func_80EDF8B8@dungeon/bank_f1d000. */

#include "common.h"
#include "shared/object_flags.h"
#include "shared/vector.h"
#include "shared/dungeon_moving_views.h"
#include "shared/dungeon_projectile_views.h"
#include "shared/dungeon_delay_views.h"
#include "shared/position_views.h"

#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#ifndef NULL
#define NULL 0
#endif

typedef struct S_801712C4_0 {
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_00;   /* overlapping accesses */
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
    } unk_04;   /* overlapping accesses */
    s32 unk_08;
    u8 pad_0C[0xB];
    u8 unk_17;
    u8 pad_18[0x1A];
    union { u16 u; s16 s; } unk_32;   /* accessed as both */
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
} S_801712C4_0;

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
void *allocate_list_node();
s32 resolve_record_orientation_or_fallback();
s32 register_node();
s32 rand();
extern u8 D_80170ED8[];
extern u8 D_801712C4[];

/* Functions defined in this translation unit. */
void steer_effect_toward_target(void *motion, void *position, void *unused);
void initialize_shared_state_active_entries(void *effect, void *position, s32 update_param);
void create_random_color_offset_effect( void *parent, s16 initial_14, s32 unused, s16 initial_32, s16 offset_x, s16 offset_y, s16 offset_z);

#endif
