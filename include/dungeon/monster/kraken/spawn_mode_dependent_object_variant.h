#ifndef DUNGEON_OVL_EED06C_H
#define DUNGEON_OVL_EED06C_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "engine/node/allocation.h"
struct ObjectNodeHeader;

typedef struct S_8015886C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8015886C_1;   /* work in func_8015886C */

   /* part_a in func_8015886C */

typedef struct S_8015886C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015886C_5;   /* current in func_8015886C */

typedef struct S_8015886C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8015886C_6;   /* child in func_8015886C */

   /* elem in func_8015886C */

typedef struct S_8015886C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8015886C_8;   /* base in func_8015886C */

extern s32 generate_random_value(void);
extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();

extern void func_80158B64(void *actor, void *motion, void *sprite_arg);
extern void func_801591A4(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status);
extern u8 D_8015C18C[];
extern u8 D_8015C1CC[];

void * spawn_mode_dependent_112_object_variant(s16 spawn_flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif
