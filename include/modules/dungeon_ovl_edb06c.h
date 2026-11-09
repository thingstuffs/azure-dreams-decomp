#ifndef DUNGEON_OVL_EDB06C_H
#define DUNGEON_OVL_EDB06C_H
#include "common.h"
#include "engine/node.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/animation.h"
#include "dungeon/actor/status.h"
#include "engine/node/allocation.h"
struct ObjectNodeHeader;

typedef struct S_8016A86C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
} S_8016A86C_1;   /* work in func_8016A86C */

   /* part_a in func_8016A86C */

typedef struct S_8016A86C_5 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A86C_5;   /* current in func_8016A86C */

typedef struct S_8016A86C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u8 pad_08[0x90];
    u32 unk_98;
} S_8016A86C_6;   /* child in func_8016A86C */

   /* elem in func_8016A86C */

typedef struct S_8016A86C_8 {
    u8 pad_00[0xA4];
    void * unk_A4;
} S_8016A86C_8;   /* base in func_8016A86C */

extern void *func_8003FD64(s32 flags, ObjectNodeHeader **list_head);
extern s32 func_8004491C(struct ObjectNodeHeader *entry, void *registration_id);
extern s32 generate_random_value(); /* Unprototyped: zero or one ignored argument; retail overwrites a0. */
extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void texture_set_the_active_entries_matching_id_in_type_n_2_table_slots();

extern void func_8016AB64(void *actor, void *motion, void *sprite_arg);
extern void func_8016B1A4(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *status);
extern u8 D_8016E18C[];
extern u8 D_8016E1CC[];

void * spawn_kraken(s16 spawn_flags, s16 kind_id, s16 variant, s16 spawn_value);
void * func_8016A86C(s16 spawn_flags, s16 kind_id, s16 variant, s16 spawn_value);
#endif
