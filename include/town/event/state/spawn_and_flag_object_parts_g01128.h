#ifndef TOWN_EVENT_STATE_SPAWN_AND_FLAG_OBJECT_PARTS_G01128_H
#define TOWN_EVENT_STATE_SPAWN_AND_FLAG_OBJECT_PARTS_G01128_H
/* Spawn and flag object parts. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01128 - CL:town/func_8009ED0C, CL:town/func_8009EEE8. */

#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/vector.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"
#include "shared/entity.h"
#include "shared/object_links.h"
#include "shared/dungeon_effect_views.h"
#include "town/person/position.h"

#ifndef NULL
#define NULL 0
#endif

struct S_800814A0 {
    s32 v;
    s32 pad[2];
};


typedef struct S_8009C390_1 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x48];
    s32 unk_9C;
} S_8009C390_1;

typedef struct S_8009C46C_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(struct S_8009C46C_0 *, void *, void *);
} S_8009C46C_0;

typedef struct {
    s32 unk00;
    s8 unk04;
    s8 unk05;
} Struct8009ED34Arg2;

typedef struct {
    s8 pad00[0x50];
    void *unk50;
    s8 pad54[0x6C - 0x54];
    s16 unk6C;
} Struct8009ED34Arg0;

/* the 0x2 bytes before arg0 in update_timed_object_to_height_limit, addressed as arg0[-1] */
typedef struct S_8009C4E8_0 {
    u8 pad_00[0x50];
    void * unk_50;
    u8 pad_54[0x18];
    u16 unk_6C;
} S_8009C4E8_0;

/* arg0 in update_timed_object_to_height_limit */
typedef struct S_8009C4E8_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_8009C4E8_2;


typedef struct S_8009C390_3 S_8009C390_3;

typedef struct S_8009C648_0 {
    s32 unk_00;
    s32 unk_04;
} S_8009C648_0;


typedef struct S_8009C648_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_8009C648_2;

/* held_arg0 in spawn_randomized_effect_parts */
typedef struct S_8009C648_3 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_8009C648_3;

typedef struct S_8009C648_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8009C648_4;

typedef struct S_8009C648_5 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8009C648_5;

extern void SD_Call(s32 flags);
extern void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value);
extern void *allocate_list_node();
extern s32 register_node(void *entry, void *registration_id);
extern u8 D_8009C4E8[];
extern u8 D_8009C5D8[];
extern s32 rand(void);
extern u8 D_80088D78[8];
extern M2C_UNK D_800D06C8[3];

/* Shared import declarations; data casts preserve each measured view. */
extern void unlink_scene_list_node(void *node);
extern void unlink_node_if_registered(void *block_data);
extern u8 D_800814A0[];

/* Functions defined in this translation unit. */
void spawn_and_flag_object_parts(unsigned short *object, s32 unused, s32 action_id);
void run_object_secondary_callback(S_8009C46C_0 *object, void *motion, void *context);
void initialize_timed_fade_object(Struct8009ED34Arg0 *context, void *unused, Struct8009ED34Arg2 *state);
void update_timed_object_to_height_limit(void *object, ObjectPosition *motion, S_8009C4E8_2 *appearance);
void fade_object_primitive(void *object, void *unusedContext, u8 *primitive);
void spawn_randomized_effect_parts(u8 *source_data, s32 spawn_arg);

#endif
